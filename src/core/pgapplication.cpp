/*
    ParaGUI - crossplatform widgetset
    Copyright (C) 2000,2001,2002  Alexander Pipelka
 
    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.
 
    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.
 
    You should have received a copy of the GNU Library General Public
    License along with this library; if not, write to the Free
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    Alexander Pipelka
    pipelka@teleweb.at
 
    Last Update:      $Author: braindead $
    Update Date:      $Date: 2004/01/22 16:52:42 $
    Source File:      $Source: /sources/paragui/paragui/src/core/pgapplication.cpp,v $
    CVS/RCS Revision: $Revision: 1.2.4.22.2.4 $
    Status:           $State: Exp $
*/

#include "pgapplication.h"
#include "pgwidget.h"
#include "pglayout.h"
#include "pglog.h"
#include "pgdraw.h"
#include "pgtheme.h"

#include <iostream>
#include <cstring>
#include <cassert>
#include <cmath>

// usually PARAGUI_THEMEDIR is defined by the configure script
// or passed to the compiler. This is just a kind of last resort.

#ifndef PARAGUI_THEMEDIR
#ifdef __MACOS__
#define PARAGUI_THEMEDIR        ""
#else
#define PARAGUI_THEMEDIR        "./"
#endif  // macintosh
#endif  // PARAGUI_THEMEDIR

using namespace std;


SDL_mutex* PG_Application::mutexScreen = NULL;
PG_Application* PG_Application::pGlobalApp = NULL;
SDL_Surface* PG_Application::screen = NULL;
string PG_Application::app_path = "";
PG_Theme* PG_Application::my_Theme = NULL;
bool PG_Application::bulkMode = false;
bool PG_Application::glMode = false;
bool PG_Application::emergencyQuit = false;
bool PG_Application::enableBackground = true;
bool PG_Application::enableAppIdleCalls = false;
SDL_Surface *PG_Application::my_mouse_pointer = NULL;
PG_Rect PG_Application::my_mouse_position = PG_Rect(0,0,0,0);
PG_Application::CursorMode PG_Application::my_mouse_mode = PG_Application::HARDWARE;
PG_Font* PG_Application::DefaultFont = NULL;
SDL_Surface* PG_Application::my_background = NULL;
SDL_Surface* PG_Application::my_scaled_background = NULL;
PG_Color PG_Application::my_backcolor;
int PG_Application::my_backmode = BKMODE_TILE;
bool PG_Application::disableDirtyUpdates = false;

/**
	new shutdown procedure (called at application termination
*/
void PARAGUI_ShutDownCode() {

	// shutdown SDL
	SDL_Quit();
}


PG_Application::PG_Application() {

	if(pGlobalApp != NULL) {
		PG_LogWRN("PG_Application Object already exists !");
		exit(-1);
	}

	atexit(PARAGUI_ShutDownCode);

/* We need to kludge a bit for keyboards work under windows */
/* we'll call SDL_RegisterApp right before SDL_Init()       */
/* Pete Shinners, Feb 1, 2001                               */

#ifdef WIN32
#ifndef __GNUC__
	SDL_RegisterApp("ParaGUI", 0, GetModuleHandle(NULL));
#endif
#endif

	// -- see above

	/* Initialize the SDL library */
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_NOPARACHUTE) < 0) {
		cerr << "Could not initialize SDL: " << SDL_GetError() << endl;
		exit(-1);
	}

	pGlobalApp = this;
	screen = NULL;

	mutexScreen = SDL_CreateMutex();
	my_background = NULL;
	my_freeBackground = false;
	my_backmode = BKMODE_TILE;
	
	// add our base dir to the searchpath
	AddArchive(GetBaseDir());
}

PG_Application::~PG_Application() {
	Shutdown();
	
	pGlobalApp = NULL;

	// shutdown log
	PG_LogConsole::Done();
	
	// remove all archives from PG_FileArchive
	PG_FileArchive::RemoveAllArchives();
}

/**  */
bool PG_Application::InitScreen(int w, int h, int depth, Uint32 flags) {

	if(depth == 0) {
		const SDL_VideoInfo* info = SDL_GetVideoInfo();
		if ( info->vfmt->BitsPerPixel > 8 ) {
			depth = info->vfmt->BitsPerPixel;
		}
	}

	//if(SDL_VideoModeOK(w, h, depth, flags) == 0)
	//	return false;

	/* Initialize the display */
	PG_Application::screen = SDL_SetVideoMode(w, h, depth, flags);
	if (PG_Application::screen == NULL) {
		PG_LogERR("Could not set video mode: %s", SDL_GetError());
		return false;
	}

#ifdef DEBUG
	PrintVideoTest();
#endif // DEBUG

	SetScreen(screen);

	eventInit();

	PG_LogConsole::SetMethod( PG_LogConsole::GetMethod() |PG_LOGMTH_CONSOLE);
	PG_LogDBG("Screen initialized !");

	return true;
}

/**  */
SDL_Thread* PG_Application::Run(bool threaded) {
#ifndef WIN32
	if(threaded) {
		SDL_Thread* thrd = SDL_CreateThread(PG_Application::RunEventLoop, this);
		return thrd;
	}
#endif
	RunEventLoop(this);
	return NULL;
}

void PG_Application::EnableAppIdleCalls(bool enable) {
	enableAppIdleCalls = enable;
}

bool PG_Application::GetAppIdleCallsEnabled()
{
	return enableAppIdleCalls;
}

/** Event processing loop */

int PG_Application::RunEventLoop(void* data) {
	PG_Application* object = static_cast<PG_Application*>(data);
	SDL_Event event;
	my_quitEventLoop = false;

	assert(data);

	FlushEventQueue();
	
	while(!my_quitEventLoop) {
		
		// pull motion events (may flood the eventqueue)
		while(SDL_PeepEvents(&event, 1, SDL_GETEVENT, SDL_MOUSEMOTIONMASK) > 0)
			;
		
		if(enableAppIdleCalls) {
			if (SDL_PollEvent(&event) == 0) {
				object->eventIdle();
			} else {
				PG_MessageObject::PumpIntoEventQueue(&event);
			}
		} else {
			SDL_WaitEvent(&event);
			PG_MessageObject::PumpIntoEventQueue(&event);
		}

		DrawCursor();
	}
	return -1;
}


void PG_Application::ClearOldMousePosition() {
	if(!my_mouse_position.my_width) {
		return;
	}

	PG_RectList *widgetList = PG_Widget::GetWidgetList();
	PG_Application::RedrawBackground(my_mouse_position);

	SDL_SetClipRect(screen, &my_mouse_position);
	PG_RectList backlist = widgetList->Intersect(&my_mouse_position);
	backlist.Blit(my_mouse_position);
	SDL_SetClipRect(screen, 0);
	return;
}

void PG_Application::DrawCursor() {
	int x, y;
	PG_Rect saved;
	if(!my_mouse_pointer || my_mouse_mode != SOFTWARE) {
		return;
	}
	if(SDL_ShowCursor(SDL_QUERY) == SDL_ENABLE) {
		// Hide hardware cursor if visible
		SDL_ShowCursor(SDL_DISABLE);
	}
	//SDL_PumpEvents();
	SDL_GetMouseState(&x, &y);
	saved = my_mouse_position;
	if(!GetBulkMode()) {
		ClearOldMousePosition();
	}
	my_mouse_position.my_xpos = x;
	my_mouse_position.my_ypos = y;
	SDL_BlitSurface(my_mouse_pointer, 0, screen, &my_mouse_position);
	if(!GetBulkMode()) {
		SDL_UpdateRects(screen, 1, &saved);
		SDL_UpdateRects(screen, 1, &my_mouse_position);
	}
}
void PG_Application::Quit() {
	sigQuit(this);
	eventQuit(0, this, 0);
}

/**  */
bool PG_Application::eventKeyDown(const SDL_KeyboardEvent* key) {
	SDLKey ckey = PG_LogConsole::GetConsoleKey();
	
	if(ckey == 0) {
		return false;
	}
	
	if (key->keysym.sym == ckey) {
		PG_LogConsole::Update();
		PG_LogConsole::Toggle();
		return true;
	}

	return false;
}

bool PG_Application::eventKeyUp(const SDL_KeyboardEvent* key) {

	if((key->keysym.sym == SDLK_ESCAPE) && emergencyQuit) {
		Quit();
		return true;
	}

	return false;
}

bool PG_Application::eventResize(const SDL_ResizeEvent* event) {
        if (!event)
                return false;
        
	screen = SDL_SetVideoMode(
	             event->w, event->h,
	             screen->format->BitsPerPixel,
	             screen->flags);

	PG_Widget::UpdateRect(PG_Rect(0,0,event->w,event->h));
	SDL_UpdateRect(screen,0,0,event->w,event->h);
	sigVideoResize(this, event);

	return true;
}

void PG_Application::SetCursor(SDL_Surface *image) {
	if(image == 0) {
		if(!my_mouse_pointer) {
			return;
		}
		UnloadSurface(my_mouse_pointer);
		my_mouse_pointer = 0;
		ClearOldMousePosition();
		SDL_UpdateRects(screen, 1, &my_mouse_position);
		SDL_ShowCursor(SDL_ENABLE);
		return;
	}
	if(!my_mouse_pointer) {
		my_mouse_pointer = image;
	} else {
		UnloadSurface(my_mouse_pointer);
		my_mouse_pointer = image;
	}
	image->refcount++;
	DrawCursor();
}

PG_Application::CursorMode PG_Application::ShowCursor(CursorMode mode) {
	switch(mode) {
		case NONE:
			SDL_ShowCursor(SDL_DISABLE);
			break;
		case HARDWARE:
			SDL_ShowCursor(SDL_ENABLE);
			break;
		case SOFTWARE:
			DrawCursor();
			break;
		case QUERY:
			return my_mouse_mode;

	}
	CursorMode orig = my_mouse_mode;
	if(mode != SOFTWARE && my_mouse_mode == SOFTWARE) {
		ClearOldMousePosition();
		SDL_UpdateRects(screen, 1, &my_mouse_position);
	}
	my_mouse_mode = mode;
	return orig;
}


/**  */
SDL_Surface* PG_Application::SetScreen(SDL_Surface* surf) {
        if (!surf)
                return PG_Application::screen;
        
	PG_Application::screen = surf;

	glMode = (surf->flags & SDL_OPENGLBLIT);

	SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);
	SDL_EnableUNICODE(true);

	PG_Widget::UpdateRect(PG_Rect(0,0,screen->w,screen->h));
	SDL_UpdateRect(screen, 0,0,screen->w,screen->h);

	return PG_Application::screen;
}

/**  */
bool PG_Application::SetBackground(const char* filename, int mode) {
        if (!filename)
                return false;
        
	if(my_freeBackground && my_background) {
		UnloadSurface(my_background);
		my_freeBackground = false;
	}
		
	my_background = LoadSurface(filename);

	if(my_scaled_background) {
		// Destroyed scaled background if present
		SDL_FreeSurface(my_scaled_background);
		my_scaled_background = 0;
	}		
	if(my_background != NULL) {
		my_freeBackground = true;
		my_backmode = mode;
		RedrawBackground(PG_Rect(0,0,screen->w,screen->h));
		return true;
	} else {
		PG_LogWRN("Failed to load '%s'",(char*)filename);
	}

	return false;
}

/**  */
bool PG_Application::SetBackground(SDL_Surface* surface, int mode) {
	if(surface == NULL)
		return false;

	if(my_scaled_background) {
		// Destroyed scaled background if present
		SDL_FreeSurface(my_scaled_background);
		my_scaled_background = 0;
	}
	if(my_freeBackground && my_background) {
		UnloadSurface(my_background);
		my_freeBackground = false;
	}

	my_background = surface;
	my_backmode = mode;

	RedrawBackground(PG_Rect(0,0,screen->w,screen->h));
	return true;
}

/**  */
void PG_Application::RedrawBackground(const PG_Rect& rect) {
	static PG_Rect screenrect(0,0,screen->w,screen->h);

	if(GetBulkMode() || !enableBackground) {
		return;
	}

	PG_Rect fillrect = rect;

	if(!my_background) {
		SDL_FillRect(screen, (SDL_Rect*)&fillrect, my_backcolor.MapRGB(screen->format));
		return;
	}
	if(my_backmode == BKMODE_STRETCH &&
	   (my_background->w != screen->w ||
	    my_background->h != screen->h)) {
		if(my_scaled_background && 
		   (my_scaled_background->w != screen->w ||
		    my_scaled_background->h != screen->h)) {
			SDL_FreeSurface(my_scaled_background); // size mismatch
			my_scaled_background = 0;
		}
		if(!my_scaled_background) {
			my_scaled_background =
				PG_Draw::ScaleSurface(my_background,
						      static_cast<Uint16>(screen->w), static_cast<Uint16>(screen->h));
		}
		SDL_GetClipRect(screen, (SDL_Rect*)&fillrect);
		SDL_SetClipRect(screen, (SDL_Rect*)&rect);
		SDL_BlitSurface(my_scaled_background, (SDL_Rect*)&rect, screen, (SDL_Rect*)&rect);
		SDL_SetClipRect(screen, (SDL_Rect*)&fillrect);

	} else {
		PG_Draw::DrawTile(screen, screenrect, rect, my_background);
	}
}

/**  */
const char* PG_Application::GetApplicationPath() {
	return app_path.c_str();
}

void PG_Application::SetApplicationPath(const char* path) {
	AddArchive(path);
	app_path = path;
}

/**  */
const char* PG_Application::GetRelativePath(const char* file) {
	static string buffer = "";

	if(Exists(file)) {
		buffer = (string)GetRealDir(file) + (string)file;
	}

	return buffer.c_str();
}

void PG_Application::FlipPage() {
	SDL_Flip(screen);
}

#ifdef DEBUG
// All calls to this are ifdefd out also
void PG_Application::PrintVideoTest() {
	const SDL_VideoInfo *info;
	int i;
	SDL_Rect **modes;

	info = SDL_GetVideoInfo();
	PG_LogDBG("Current display: %d bits-per-pixel", info->vfmt->BitsPerPixel);

	if ( info->vfmt->palette == NULL ) {
		// FIXME: did I screw this up? :) -Dave
		PG_LogDBG(" - Red Mask = 0x%x", info->vfmt->Rmask);
		PG_LogDBG(" - Green Mask = 0x%x", info->vfmt->Gmask);
		PG_LogDBG(" - Blue Mask = 0x%x", info->vfmt->Bmask);
	}
	/* Print available fullscreen video modes */
	modes = SDL_ListModes(NULL, SDL_FULLSCREEN);
	if ( modes == (SDL_Rect **)0 ) {
		PG_LogDBG("No available fullscreen video modes");
	} else
		if ( modes == (SDL_Rect **)-1 ) {
			PG_LogDBG("No special fullscreen video modes");
		} else {
			PG_LogDBG("Fullscreen video modes:");
			for ( i=0; modes[i]; ++i ) {
				PG_LogDBG(" - %d x %d", modes[i]->w, modes[i]->h);
			}
		}
	if ( info->wm_available ) {
		PG_LogDBG("A window manager is available");
	}
	if ( info->hw_available ) {
		PG_LogDBG("Hardware surfaces are available (%d K video memory)", info->video_mem);
	}
	if ( info->blit_hw ) {
		PG_LogDBG("Copy blits between hardware surfaces are accelerated");
	}
	if ( info->blit_hw_CC ) {
		PG_LogDBG("Colorkey blits between hardware surfaces are accelerated");
	}
	if ( info->blit_hw_A ) {
		PG_LogDBG("Alpha blits between hardware surfaces are accelerated");
	}
	if ( info->blit_sw ) {
		PG_LogDBG("Copy blits from software surfaces to hardware surfaces are accelerated");
	}
	if ( info->blit_sw_CC ) {
		PG_LogDBG("Colorkey blits from software surfaces to hardware surfaces are accelerated");
	}
	if ( info->blit_sw_A ) {
		PG_LogDBG("Alpha blits from software surfaces to hardware surfaces are accelerated");
	}
	if ( info->blit_fill ) {
		PG_LogDBG("Color fills on hardware surfaces are accelerated");
	}
}
#endif // DEBUG

void PG_Application::eventInit() {}

PG_Theme* PG_Application::LoadTheme(const char* xmltheme, bool asDefault, const char* searchpath) {
	PG_Theme* theme = NULL;

	PG_LogDBG("Locating theme '%s' ...", xmltheme);

	if(searchpath != NULL) {
		if(AddArchive(searchpath)) {
			PG_LogDBG("'%s' added to searchpath", searchpath);
		}
	}

#ifdef __MACOS__

	if(AddArchive("")) {
		PG_LogDBG("'' added to searchpath");
	}

	if(AddArchive(":")) {
		PG_LogDBG("':' added to searchpath");
	}

	if(AddArchive(":data:")) {
		PG_LogDBG("':data:' added to searchpath");
	}

	if(AddArchive("::data:")) {
		PG_LogDBG("'::data:' added to searchpath");
	}

	if(PARAGUI_THEMEDIR != NULL) {
		PG_LogDBG("'"PARAGUI_THEMEDIR"' added to searchpath");
	}

#else	

	if(AddArchive("./")) {
		PG_LogDBG("'./' added to searchpath");
	}

	if(AddArchive("../")) {
		PG_LogDBG("'../' added to searchpath");
	}

	if(AddArchive("./data/")) {
		PG_LogDBG("'./data/' added to searchpath");
	}

	if(AddArchive("../data/")) {
		PG_LogDBG("'../data/' added to searchpath");
	}

	if(getenv("PARAGUIDIR") != NULL) {
		if(AddArchive(getenv("PARAGUIDIR"))) {
			PG_LogDBG("'%s' added to searchpath", getenv("PARAGUIDIR"));
		}
	}

#endif // __MACOS__

	if(AddArchive(PARAGUI_THEMEDIR)) {
		PG_LogDBG("'"PARAGUI_THEMEDIR "' added to searchpath");
	}

	theme = PG_Theme::Load(xmltheme);

	if(theme && asDefault) {

		const char* c = theme->FindDefaultFontName();
		if(c == NULL) {
			PG_LogWRN("Unable to load default font ...");
			delete theme;
			return NULL;
		}

		DefaultFont = new PG_Font(c, theme->FindDefaultFontSize());
		DefaultFont->SetStyle(theme->FindDefaultFontStyle());

		PG_LogMSG("defaultfont: %s", c);
		PG_LogMSG("size: %i", DefaultFont->GetSize());

		my_background = theme->FindSurface("Background", "Background", "background");
		theme->GetProperty("Background", "Background", "backmode", my_backmode);
		theme->GetColor("Background", "Background", "backcolor", my_backcolor);

		if(my_scaled_background) {
			// Destroyed scaled background if present
			SDL_FreeSurface(my_scaled_background);
			my_scaled_background = 0;
		}		
	} else {

		PG_LogWRN("Failed to load !");
	}

	if((my_Theme != NULL) && asDefault) {
		delete my_Theme;
		my_Theme = NULL;
	}

	if(asDefault && theme) {
		my_Theme = theme;
	}

	return theme;
}

bool PG_Application::eventQuit(int id, PG_MessageObject* widget, unsigned long data) {
	if(GetBulkMode()) {
		return false;
	}

	my_quitEventLoop = true;

	if(my_mouse_pointer) {
		UnloadSurface(my_mouse_pointer);
		my_mouse_pointer = 0;
		SDL_ShowCursor(SDL_ENABLE);
	}

	return true;
}

void PG_Application::SetBulkMode(bool bulk) {
	bulkMode = bulk;
}

void PG_Application::Shutdown() {
	if(my_scaled_background) {
		// Destroyed scaled background if present
		SDL_FreeSurface(my_scaled_background);
		my_scaled_background = 0;
	}
	// destroy still existing objects
	vector<PG_MessageObject*>::iterator list = objectList.begin();

	while(list != objectList.end()) {

		if(!(*list == this || *list == NULL)) {
			delete *list;
		}

		objectList.erase(list);
		list = objectList.begin();
	}

	// unload theme (and free the allocated mem)
	if(my_Theme) {
		delete my_Theme;
		my_Theme = NULL;
	}

	// destroy screen mutex
	SDL_DestroyMutex(mutexScreen);

	// delete the default font
	delete DefaultFont;
	DefaultFont = NULL;
}

void PG_Application::SetEmergencyQuit(bool esc) {
	emergencyQuit = esc;
}

void PG_Application::SetIcon(const char *filename) {
	SDL_Surface* icon;
	Uint8* pixels;
	Uint8* mask;
	int mlen, i;

	// Load the icon surface
	icon = LoadSurface(filename);
	if ( icon == NULL ) {
		PG_LogWRN("Failed to load icon!");
		return;
	}

	// Check width and height
	if ( (icon->w%8) != 0 ) {
		PG_LogWRN("Icon width must be a multiple of 8!");
		UnloadSurface(icon);
		return;
	}

	//Check the palette
	if ( icon->format->palette == NULL ) {
		PG_LogWRN("Icon must have a palette!");
		UnloadSurface(icon);
		return;
	}

	// Set the colorkey
	SDL_SetColorKey(icon, SDL_SRCCOLORKEY, *((Uint8 *)icon->pixels));

	// Create the mask
	pixels = (Uint8 *)icon->pixels;
	mlen = icon->w*icon->h;
	mask =  new Uint8[mlen/8];

	if ( mask == NULL ) {
		PG_LogWRN("Out of memory when allocating mask for icon !");
		UnloadSurface(icon);
		return;
	}

	memset(mask, 0, mlen/8);
	for ( i=0; i<mlen; ) {
		if ( pixels[i] != *pixels ) {
			mask[i/8] |= 0x01;
		}

		++i;
		if ( (i%8) != 0 ) {
			mask[i/8] <<= 1;
		}
	}

	//Set icon
	if ( icon != NULL ) {
		SDL_WM_SetIcon(icon, mask);
	}

	//Clean up
	delete[] mask;
	return;
}

void PG_Application::SetCaption(const char *title, const char *icon) {
	SDL_WM_SetCaption(title,icon);
	return;
}

void PG_Application::GetCaption(char **title, char **icon) {
	SDL_WM_GetCaption(title,icon);
	return;
}

int PG_Application::Iconify(void) {
	return SDL_WM_IconifyWindow();
}


bool PG_Application::LoadLayout(const char *name) {
	return PG_Layout::Load(NULL, name, NULL, NULL);
}

bool PG_Application::LoadLayout(const char *name, void (* WorkCallback)(int now, int max)) {
	return PG_Layout::Load(NULL, name, WorkCallback, NULL);
}

bool PG_Application::LoadLayout(const char *name, void (* WorkCallback)(int now, int max), void *UserSpace) {
	return PG_Layout::Load(NULL, name, WorkCallback, UserSpace);
}

static PG_Widget *FindInChildObjects(PG_RectList *RectList, const char *Name) {
	PG_Widget *retWidget = NULL;

	if (RectList == NULL) {
		return NULL;
	}

	if (!Name)
            return NULL;
    
	PG_RectList::iterator list = RectList->begin();

	while(list != RectList->end()) {
		if (strcmp((*list)->GetName(), Name) == 0) {
			return((*list));
		}

		PG_Widget* result = (*list)->FindChild(Name);
		if(result != NULL) {
			return result;
		}

		retWidget = FindInChildObjects((*list)->GetChildList(), Name);
		if (retWidget != NULL) {
			return retWidget;
		}

		list++;
	}

	return NULL;
}

static inline PG_Widget *FindInChildObjects(PG_RectList *RectList, int id) {
	PG_Widget *retWidget = NULL;

	if (RectList == NULL) {
		return NULL;
	}

	if (id < 0)
            return 0;
    
	PG_RectList::iterator list = RectList->begin();

	while(list != RectList->end()) {
		if ((*list)->GetID() == id) {
			return((*list));
		}


		PG_Widget* result = (*list)->FindChild(id);
		if(result != NULL) {
			return result;
		}
        
		retWidget = FindInChildObjects((*list)->GetChildList(), id);
		if (retWidget != NULL) {
			return retWidget;
		}

		list++;
	}

	return NULL;
}

PG_Widget *PG_Application::GetWidgetByName(const char *Name) {
        return (FindInChildObjects(PG_Widget::GetWidgetList(), Name));
}

PG_Widget *PG_Application::GetWidgetById(int id) {
        return (FindInChildObjects(PG_Widget::GetWidgetList(), id));
}

void PG_Application::SetFontColor(const PG_Color& Color) {
	DefaultFont->SetColor(Color);
}

void PG_Application::SetFontAlpha(int Alpha) {
	DefaultFont->SetAlpha(Alpha);
}

void PG_Application::SetFontStyle(PG_Font::Style Style) {
	DefaultFont->SetStyle(Style);
}

void PG_Application::SetFontSize(int Size) {
	DefaultFont->SetSize(Size);
}

void PG_Application::SetFontIndex(int Index) {
	//DefaultFont->SetIndex(Index);
}

void PG_Application::SetFontName(const char *Name) {
	DefaultFont->SetName(Name);
}

SDL_Surface* PG_Application::GetScreen() {
	return screen;
}

int PG_Application::GetScreenHeight() {
	return screen->h;
}

int PG_Application::GetScreenWidth() {
	return screen->w;
}

PG_Theme* PG_Application::GetTheme() {
	return my_Theme;
}

bool PG_Application::GetBulkMode() {
	return bulkMode;
}

bool PG_Application::GetGLMode() {
		return glMode;
}

void PG_Application::EnableBackground(bool enable) {
	enableBackground = enable;
}

void PG_Application::DeleteBackground() {
 	enableBackground = false;

 	if(my_scaled_background) {
 		// Destroyed scaled background if present
 		SDL_FreeSurface(my_scaled_background);
 		my_scaled_background = 0;
 	}
	if(my_freeBackground && my_background) {
		UnloadSurface(my_background);
		my_freeBackground = false;
	}
}

#ifdef WIN32
bool PG_Application::LockScreen() {
	return (SDL_mutexP(mutexScreen) == 0);
}
#endif

#ifdef WIN32
bool PG_Application::UnlockScreen() {
	return (SDL_mutexV(mutexScreen) == 0);
}
#endif

void PG_Application::DisableDirtyUpdates(bool disable) {
	disableDirtyUpdates = disable;
}

bool PG_Application::GetDirtyUpdatesDisabled() {
	return disableDirtyUpdates;
}

PG_Application* PG_Application::GetApp() {
	return pGlobalApp;
}

void PG_Application::FlushEventQueue() {
	SDL_Event event;

	while(SDL_PollEvent(&event)) {
		/*if(event.type == SDL_USEREVENT) {
			delete (MSG_MESSAGE*)(event.user.data1);
		}*/
	}
}

/*
 * Local Variables:
 * c-basic-offset: 8
 * End:
 */

