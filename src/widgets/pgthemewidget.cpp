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
    Update Date:      $Date: 2004/01/22 16:52:43 $
    Source File:      $Source: /sources/paragui/paragui/src/widgets/pgthemewidget.cpp,v $
    CVS/RCS Revision: $Revision: 1.3.6.7.2.4 $
    Status:           $State: Exp $
*/

#include "pgthemewidget.h"
#include "pgdraw.h"
#include "pgapplication.h"
#include "pglog.h"
#include "pgtheme.h"

static PG_SurfaceCache my_SurfaceCache;

class PG_WidgetDataInternal {
public:
	PG_WidgetDataInternal() : 
	cachesurface(NULL),
	backgroundcolor(128,128,128),
	freeimage(false),
	simplebackground(false),
	nocache(false) {};

	SDL_Surface* cachesurface;
	PG_Color backgroundcolor;

	bool freeimage;
	bool simplebackground;
	bool nocache;

};

PG_ThemeWidget::PG_ThemeWidget(PG_Widget* parent, const PG_Rect& r, const char* style) : PG_Widget(parent, r) {
	Init(style);
}

PG_ThemeWidget::PG_ThemeWidget(PG_Widget* parent, const PG_Rect& r, bool bCreateSurface, const char* style) : PG_Widget(parent, r, bCreateSurface) {
	Init(style);
}

void PG_ThemeWidget::Init(const char* style) {
	SetDirtyUpdate(true);
	
	_mid = new PG_WidgetDataInternal;
	
	my_backgroundFree = false;
	my_background = NULL;
	my_blendLevel = 0;
	my_backgroundMode = BKMODE_TILE;
	my_bordersize = 0;
	my_has_gradient = false;

	my_image = NULL;
	/*_mid->freeimage = false;
	_mid->simplebackground = false;
	_mid->nocache = false;

	_mid->cachesurface = NULL;*/

	LoadThemeStyle(style);
}

PG_ThemeWidget::~PG_ThemeWidget() {
	
	// free surfaces
	FreeSurface();
	FreeImage();
	
	// remove the cachesurface
	DeleteThemedSurface(_mid->cachesurface);
	
	// delete internal data
	delete _mid;
}

void PG_ThemeWidget::LoadThemeStyle(const char* widgettype) {
	if(strcmp(widgettype, "ThemeWidget") != 0) {
		PG_ThemeWidget::LoadThemeStyle("ThemeWidget", "ThemeWidget");
	}
	PG_ThemeWidget::LoadThemeStyle(widgettype, "ThemeWidget");
}

void PG_ThemeWidget::LoadThemeStyle(const char* widgettype, const char* objectname) {
	PG_Theme* t = PG_Application::GetTheme();

	if(my_srfObject == NULL) {
		if(strcmp(objectname, "ThemeWidget") != 0) {
			PG_ThemeWidget::LoadThemeStyle(widgettype, "ThemeWidget");
		}

		t->GetProperty(widgettype, objectname, "simplebackground", _mid->simplebackground);
		t->GetProperty(widgettype, objectname, "nocache", _mid->nocache);
		t->GetColor(widgettype, objectname, "backgroundcolor", _mid->backgroundcolor);
	}

	const char *font = t->FindFontName(widgettype, objectname);
	int fontsize = t->FindFontSize(widgettype, objectname);
	PG_Font::Style fontstyle = t->FindFontStyle(widgettype, objectname);

	if(font != NULL)
		SetFontName(font);
	if(fontsize > 0)
		SetFontSize(fontsize);
	if(fontstyle >= 0)
		SetFontStyle(fontstyle);

	SetBackground(t->FindSurface(widgettype, objectname, "background"));

	t->GetProperty(widgettype, objectname, "blend", my_blendLevel);
	t->GetProperty(widgettype, objectname, "bordersize", my_bordersize);
	t->GetProperty(widgettype, objectname, "backmode", my_backgroundMode);

	PG_Gradient* g = t->FindGradient(widgettype, objectname, "gradient");

	if(g) {
		SetGradient(*g);
		my_has_gradient = true;
	}

	Uint8 trans = GetTransparency();
	t->GetProperty(widgettype, objectname, "transparency", trans);
	SetTransparency(trans);

	PG_Widget::LoadThemeStyle(widgettype, objectname);

	int w = Width();
	t->GetProperty(widgettype, objectname, "width", w);
	int h = Height();
	t->GetProperty(widgettype, objectname, "height", h);

	if((w != Width()) || (h != Height())) {
		SizeWidget(w, h);
	}
}

void PG_ThemeWidget::eventDraw(SDL_Surface* surface, const PG_Rect& rect) {
	if(my_srfObject == NULL) {
		return;
	}

	PG_Draw::DrawThemedSurface(
	    surface,
	    rect,
	    my_has_gradient ? &my_gradient : 0,
	    my_background,
	    my_backgroundMode,
	    my_blendLevel);

	if(my_bordersize > 0) {
		DrawBorder(rect, my_bordersize);
	}
}

bool PG_ThemeWidget::SetBackground(const char* filename, int mode, const PG_Color &colorkey) {
	// try to load the file
	SDL_Surface* temp = PG_Application::LoadSurface(filename, true);

	// success ?
	if(!temp) {
		return false;
	}

	// free previous surface
	FreeSurface();

	// mark my_background to be freed on destruction
	my_backgroundFree = true;
	my_backgroundMode = mode;
	my_background = temp;

	if(my_background == NULL) {
		return false;
	}

	Uint32 c = colorkey.MapRGB(my_background->format);
	SDL_SetColorKey(my_background, SDL_SRCCOLORKEY, c);
	 
	if(my_srfObject == NULL) {
		CreateSurface();
	}

	return (my_background != NULL);
}

bool PG_ThemeWidget::SetBackground(const char* filename, int mode) {

	// try to load the file
	SDL_Surface* temp = PG_Application::LoadSurface(filename, true);

	// success ?
	if(!temp) {
		return false;
	}

	// free previous surface
	FreeSurface();

	// mark my_background to be freed on destruction
	my_backgroundFree = true;
	my_backgroundMode = mode;
	my_background = temp;

	if(my_background == NULL) {
		return false;
	}

	if(my_srfObject == NULL) {
		CreateSurface();
	}

	return (my_background != NULL);
}


bool PG_ThemeWidget::SetBackground(SDL_Surface* surface, int mode) {

	if(!surface) {
		return false;
	}

	FreeSurface();

	my_background = surface;
	my_backgroundFree = false;
	my_backgroundMode = mode;

	return true;
}

void PG_ThemeWidget::SetBackgroundBlend(Uint8 backblend) {
	my_blendLevel = backblend;
}

void PG_ThemeWidget::FreeSurface() {

	// check if we have to free a previous surface

	if (my_backgroundFree && my_background != NULL) {
		PG_Application::UnloadSurface(my_background);
		my_background = NULL;
		my_backgroundFree = false;
	}
}

void PG_ThemeWidget::SetGradient(PG_Gradient& grad) {
	my_gradient = grad;
	my_has_gradient = true;
	DeleteThemedSurface(_mid->cachesurface);
	_mid->cachesurface = NULL;
	Redraw();
}

PG_Gradient PG_ThemeWidget::GetGradient() {
	return my_gradient;
}

void PG_ThemeWidget::SetBorderSize(int b) {
	my_bordersize = b;
}

void PG_ThemeWidget::FreeImage() {

	if(_mid->freeimage) {
		PG_Application::UnloadSurface(my_image); // false
	}

	_mid->freeimage = false;
	my_image = NULL;
	return;
}

bool PG_ThemeWidget::SetImage(SDL_Surface* image, bool bFreeImage) {
	if(image == NULL) {
		return false;
	}

	if(image == my_image) {
		return true;
	}

	FreeImage();
	_mid->freeimage = bFreeImage;
	my_image = image;

	Update();
	return true;
}

bool PG_ThemeWidget::LoadImage(const char* filename, Uint32 key) {
	if(LoadImage(filename)) {
		SDL_SetColorKey(my_image, SDL_SRCCOLORKEY, key);
		return true;
	}
	
	return false;
}

bool PG_ThemeWidget::LoadImage(const char* filename) {
	SDL_Surface* image = PG_Application::LoadSurface(filename);
	return SetImage(image, true);
}

void PG_ThemeWidget::eventSizeWidget(Uint16 w, Uint16 h) {

	if((w == Width()) && (h == Height())) {
		return;
	}

	CreateSurface(w, h);
}

void PG_ThemeWidget::CreateSurface(Uint16 w, Uint16 h) {
	if(_mid->simplebackground) {
		return;
	}

	DeleteThemedSurface(_mid->cachesurface);

	if(w == 0 || h == 0) {
		_mid->cachesurface = NULL;
		return;
	}

	PG_Rect r(my_xpos, my_ypos, w, h);

	_mid->cachesurface = CreateThemedSurface(
	                      r,
	                      my_has_gradient ? &my_gradient : 0,
	                      my_background,
	                      my_backgroundMode,
	                      my_blendLevel);
}

void PG_ThemeWidget::eventBlit(SDL_Surface* srf, const PG_Rect& src, const PG_Rect& dst) {

	if(my_srfObject != NULL) {
		PG_Widget::eventBlit(srf, src, dst);
		return;
	}

	if(!_mid->simplebackground && !_mid->nocache) {
		if(_mid->cachesurface == NULL) {
			CreateSurface(Width(), Height());
		}
		PG_Widget::eventBlit(_mid->cachesurface, src, dst);
	} else if (_mid->simplebackground) {
		if(GetTransparency() < 255) {
			Uint32 c = _mid->backgroundcolor.MapRGBA(
			               my_srfScreen->format,
						   255-GetTransparency());
			SDL_FillRect(my_srfScreen, (SDL_Rect*)&dst, c);
		}
	} else if (_mid->nocache) {
		_mid->cachesurface = CreateThemedSurface(
		                      *this,
		                      my_has_gradient ? &my_gradient : 0,
		                      my_background,
		                      my_backgroundMode,
		                      my_blendLevel);
		PG_Widget::eventBlit(_mid->cachesurface, src, dst);
		DeleteThemedSurface(_mid->cachesurface);
		_mid->cachesurface = NULL;
	}

	if(my_bordersize > 0) {
		DrawBorder(PG_Rect(0, 0, Width(), Height()), my_bordersize, true);
	}

	if(my_image != NULL) {
		PG_Rect my_src;
		PG_Rect my_dst;

		GetClipRects(my_src, my_dst, *this);
		PG_Widget::eventBlit(my_image, my_src, my_dst);
	}
}

void PG_ThemeWidget::SetTransparency(Uint8 t) {
	if(_mid->simplebackground || _mid->nocache) {
		PG_Widget::SetTransparency(t);
		return;
	}

	if(t == 255) {
		DeleteThemedSurface(_mid->cachesurface);
		_mid->cachesurface = NULL;
	} else if(GetTransparency() == 255) {
		CreateSurface();
	}
	PG_Widget::SetTransparency(t);
}

SDL_Surface* PG_ThemeWidget::CreateThemedSurface(const PG_Rect& r, PG_Gradient* gradient, SDL_Surface* background, int bkmode, Uint8 blend) {
	SDL_Surface* cache_surface = NULL;
	SDL_Surface* screen = PG_Application::GetScreen();
	string key;

	if(r.w == 0 || r.h == 0) {
		return NULL;
	}

	// create a key for the surface
	my_SurfaceCache.CreateKey(key, r.my_width, r.my_height,  gradient, background, bkmode, blend);

	// lookup the surface in cache
	cache_surface = my_SurfaceCache.FindSurface(key);

	// draw the cached surface :)
	if(cache_surface != NULL) {
		// increase the reference count
		my_SurfaceCache.IncRef(key);
		return cache_surface;
	}

	Uint8 bpp = screen->format->BitsPerPixel;
	Uint32 Rmask = screen->format->Rmask;
	Uint32 Gmask = screen->format->Gmask;
	Uint32 Bmask = screen->format->Bmask;
	Uint32 Amask = 0;

	if(background != NULL) {
		if((background->format->Amask != 0) || ((bpp < background->format->BitsPerPixel) && (bpp <= 8))) {
			bpp = background->format->BitsPerPixel;
			Rmask = background->format->Rmask;
			Gmask = background->format->Gmask;
			Bmask = background->format->Bmask;
			Amask = background->format->Amask;
		}
	}

	SDL_Surface *surface = SDL_CreateRGBSurface(
	                           SDL_HWSURFACE,
	                           r.my_width,
	                           r.my_height,
	                           bpp,
	                           Rmask,
	                           Gmask,
	                           Bmask,
	                           Amask
	                       );

	if(SDL_MUSTLOCK(surface)) {
		SDL_LockSurface(surface);
	}

	if ( bpp == 8 )
		SDL_SetPalette ( surface, SDL_LOGPAL, screen->format->palette->colors, 0, 256 );

	if(surface) {
		if(background || gradient) {
			PG_Draw::DrawThemedSurface(surface, PG_Rect(0, 0, r.my_width, r.my_height), gradient, background, bkmode, blend);
		} else {
			SDL_SetColorKey(surface, SDL_SRCCOLORKEY, 0);
		}
	}
	
	if(SDL_MUSTLOCK(surface)) {
		SDL_UnlockSurface(surface);
	}

	my_SurfaceCache.AddSurface(key, surface);
	return surface;
}

void PG_ThemeWidget::DeleteThemedSurface(SDL_Surface* surface) {
	if(surface == NULL) {
		return;
	}
	my_SurfaceCache.DeleteSurface(surface);
}

void PG_ThemeWidget::SetSimpleBackground(bool simple) {
	_mid->simplebackground = simple;
	DeleteThemedSurface(_mid->cachesurface);
	_mid->cachesurface = NULL;
	Redraw();
}

void PG_ThemeWidget::SetBackgroundColor(const PG_Color& c) {
	_mid->backgroundcolor = c;
}
