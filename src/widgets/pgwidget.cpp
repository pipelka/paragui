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
   Update Date:      $Date: 2002/05/28 10:25:07 $
   Source File:      $Source: /sources/paragui/paragui/src/widgets/pgwidget.cpp,v $
   CVS/RCS Revision: $Revision: 1.4.4.2 $
   Status:           $State: Exp $
 */

//#include <iostream>
#include <cstring>
#include <stdarg.h>

#include "pgwidget.h"
#include "pgapplication.h"
#include "pglog.h"
#include "pgdraw.h"
#include "pglayout.h"

bool PG_Widget::bBulkUpdate = false;
PG_RectList PG_Widget::widgetList;
int PG_Widget::my_ObjectCounter = 0;

typedef STL_MAP<int, PG_Widget*> PG_IdToWidgetMap;
typedef std::map<std::string, PG_Widget*> PG_NameToWidgetMap;

struct PG_WidgetDataInternal{

	PG_Font* font;

	PG_IdToWidgetMap childrenIdMap;
	PG_NameToWidgetMap childrenNameMap;

	bool quitModalLoop;
	bool dirtyUpdate;
	
	PG_Widget* widgetParent;
	PG_RectList* childList;

	SDL_mutex* mutexProcess;

	char* userdata;
	int userdatasize;

	PG_Point ptDragStart;
	PG_Rect rectClip;

	int id;
	bool mouseInside;
	int fadeSteps;
	bool haveTooltip;
	bool visible;
	bool firstredraw;
	Uint8 transparency;
	bool havesurface;

	Uint16 widthText;
	Uint16 heightText;

	bool inDestruct;
	std::string name;
	
	bool hidden;
};

#define TXT_HEIGHT_UNDEF 0xFFFF

PG_Widget::PG_Widget(PG_Widget* parent, const PG_Rect& rect) :
	PG_Rect(rect),
	my_srfObject(NULL)
{
	InitWidget(parent, false);
}

PG_Widget::PG_Widget(PG_Widget* parent, const PG_Rect& rect, bool bObjectSurface) :
	PG_Rect(rect),
	my_srfObject(NULL)
{
	InitWidget(parent, bObjectSurface);
}

void PG_Widget::InitWidget(PG_Widget* parent, bool bObjectSurface) {

	my_internaldata = new PG_WidgetDataInternal;
	
	my_internaldata->inDestruct = false;

	//Set default font
	if(PG_Application::DefaultFont != NULL) {
		my_internaldata->font = new PG_Font(
					PG_Application::DefaultFont->GetName(),
					PG_Application::DefaultFont->GetSize());
	}
	else {
		my_internaldata->font = NULL;
		PG_LogWRN("Unable to get default font! Did you load a theme ?");
	}

	my_internaldata->dirtyUpdate = false;
	my_internaldata->widgetParent = parent;
	my_internaldata->havesurface = bObjectSurface;
	my_srfScreen = PG_Application::GetScreen();

	if(my_internaldata->havesurface) {
		my_srfObject = PG_Draw::CreateRGBSurface(w, h);
	}

	// ??? - How can i do this better - ???
	char buffer[15];
	sprintf(buffer, "Object%d", ++my_ObjectCounter);
	my_internaldata->name = buffer;

	// default border colors
	my_colorBorder[0][0].r = 255;
	my_colorBorder[0][0].g = 255;
	my_colorBorder[0][0].b = 255;

	my_colorBorder[0][1].r = 239;
	my_colorBorder[0][1].g = 239;
	my_colorBorder[0][1].b = 239;

	my_colorBorder[1][0].r = 89;
	my_colorBorder[1][0].g = 89;
	my_colorBorder[1][0].b = 89;

	my_colorBorder[1][1].r = 134;
	my_colorBorder[1][1].g = 134;
	my_colorBorder[1][1].b = 134;

	my_internaldata->mutexProcess = SDL_CreateMutex();
	my_internaldata->id = -1;
	my_internaldata->transparency = 0;
	my_internaldata->quitModalLoop = false;
	my_internaldata->visible = false;
	my_internaldata->hidden = false;
	my_internaldata->firstredraw = true;

	my_internaldata->childList = NULL;
	my_internaldata->haveTooltip = false;
	my_internaldata->fadeSteps = 10;

	my_text = "";

	if (my_internaldata->widgetParent != NULL) {
		my_xpos = my_internaldata->widgetParent->my_xpos + my_xpos;
		my_ypos = my_internaldata->widgetParent->my_ypos + my_ypos;
		my_internaldata->widgetParent->AddChild(this);
	}

	my_internaldata->mouseInside = false;
	my_internaldata->userdata = NULL;
	my_internaldata->userdatasize = 0;

	my_internaldata->widthText = TXT_HEIGHT_UNDEF;
	my_internaldata->heightText = TXT_HEIGHT_UNDEF;

	my_internaldata->rectClip = *this;

	AddToWidgetList();
}

void PG_Widget::RemoveAllChilds() {

	// remove all child widgets
	if(my_internaldata->childList != NULL) {

		PG_RectList::iterator i = my_internaldata->childList->begin();
		while(i != my_internaldata->childList->end()) {
			PG_Widget* w = *i;

			RemoveChild(w);
			delete (w);
			i = my_internaldata->childList->begin();
		}

		my_internaldata->childList->clear();
	}

}

PG_Widget::~PG_Widget() {

	my_internaldata->inDestruct = true;

	if(!my_internaldata->havesurface && my_srfObject) {
		PG_LogWRN("DrawObject declared without a surface has unexpectedly born one ?");
	}
	PG_Application::UnloadSurface(my_srfObject);
	my_srfObject = NULL;

	Hide();

	RemoveAllChilds();

	// remove myself from my parent's childlist (if any parent)

	if (GetParent() != NULL) {
		GetParent()->RemoveChild(this);
	}
    
	RemoveFromWidgetList();

	// unlock process mutex
	SDL_DestroyMutex(my_internaldata->mutexProcess);

	// remove childlist
	delete my_internaldata->childList;
	my_internaldata->childList = NULL;

	if (my_internaldata->userdata != NULL) {
		free(my_internaldata->userdata);
	}
	
	// remove the font
	delete my_internaldata->font;
	
	// remove my private data
	delete my_internaldata;
}

void PG_Widget::RemoveFromWidgetList() {
	widgetList.Remove(this);
}

void PG_Widget::AddToWidgetList() {
	if(!GetParent()) {
		widgetList.Add(this);
	}
}

/** Check if we can accept the event */

bool PG_Widget::AcceptEvent(const SDL_Event * event) {

	if (!IsVisible()) {
		return false;
	}

	switch (event->type) {
		case SDL_MOUSEMOTION:
			if ((event->motion.x < my_internaldata->rectClip.my_xpos) ||
				(event->motion.x > (my_internaldata->rectClip.my_xpos + my_internaldata->rectClip.my_width - 1))) {
				if (my_internaldata->mouseInside) {
					my_internaldata->mouseInside = false;
					eventMouseLeave();
				}
				return false;
			}
			if ((event->motion.y < my_internaldata->rectClip.my_ypos) ||
				(event->motion.y > (my_internaldata->rectClip.my_ypos + my_internaldata->rectClip.my_height - 1))) {
				if (my_internaldata->mouseInside) {
					my_internaldata->mouseInside = false;
					eventMouseLeave();
				}
				return false;
			}
			if (!my_internaldata->mouseInside) {
				my_internaldata->mouseInside = true;
				eventMouseEnter();
				return true;
			}
			break;

		case SDL_MOUSEBUTTONUP:
		case SDL_MOUSEBUTTONDOWN:
			if ((event->button.x < my_internaldata->rectClip.my_xpos) ||
				(event->button.x > (my_internaldata->rectClip.my_xpos + my_internaldata->rectClip.my_width - 1)))
				return false;

			if ((event->button.y < my_internaldata->rectClip.my_ypos) ||
				(event->button.y > (my_internaldata->rectClip.my_ypos + my_internaldata->rectClip.my_height - 1)))
				return false;

			break;
	}

	return true;		// accept the event as default
}


/**  */
void PG_Widget::eventMouseEnter() {}


/**  */
void PG_Widget::eventMouseLeave() {
	my_internaldata->mouseInside = false;

	if(GetParent()) {
		GetParent()->eventMouseLeave();
	}
}

/**  */
void PG_Widget::eventShow() {}

/**  */
void PG_Widget::eventHide() {}

/**  */
PG_Point PG_Widget::ClientToScreen(int sx, int sy) {
	PG_Point p;

	p.x = sx + my_xpos;
	p.y = sy + my_ypos;

	return p;
}

PG_Point PG_Widget::ScreenToClient(int x, int y) {
	PG_Point p;

	p.x = x - my_xpos;
	p.y = y - my_ypos;

	return p;
}

void PG_Widget::AddChild(PG_Widget * child) {

    if (!child)
        return;
    
	// remove our new child from previous lists
	if(child->GetParent()) {
		child->GetParent()->RemoveChild(child);
	} else {
		child->RemoveFromWidgetList();
	}

	child->my_internaldata->widgetParent = this;

	if (my_internaldata->childList == NULL) {
		my_internaldata->childList = new PG_RectList;
	}

	my_internaldata->childList->Add(child);

    AddChildToCache(child, child->GetName());
	AddChildToCache(child,  child->GetID());
}

void PG_Widget::AddChildToCache(PG_Widget *child, const char *name) {
	if (name == NULL) {
		return;
	}

	if (FindChild(name)) {
			PG_LogDBG("Child with name '%s' already exists in the name cache. Ignoring the new child.", name);
	}
	else {
			std::string n = name;
			my_internaldata->childrenNameMap[n] = child;
	}
}

void PG_Widget::AddChildToCache(PG_Widget *child, int id) {
	if (id <= 0) {
		return;
	}

	if (FindChild(id)) {
			PG_LogDBG("Child with ID '%d' already exists in the id cache. Ignoring the new child.", id);
	}
	else {
		my_internaldata->childrenIdMap[id] = child;
	}
}

/**  */
bool PG_Widget::MoveWindow(int x, int y) {
	return MoveWidget(x, y);
}

bool PG_Widget::MoveWidget(int x, int y) {

	if (GetParent() != NULL) {
		x += GetParent()->my_xpos;
		y += GetParent()->my_ypos;
	}
	if(x == my_xpos && y == my_ypos) {
		// Optimization: We haven't moved, so do nothing.
		return false;
	}

	if(!IsVisible()) {
		MoveRect(x, y);
		return true;
	}

	// delta x,y
	int dx = x - my_xpos;
	int dy = y - my_ypos;

	// calculate vertical update rect

	PG_Rect vertical(0, 0, abs(dx), my_height + abs(dy));

	if(dx >= 0) {
		vertical.my_xpos = my_xpos;
	} else {
		vertical.my_xpos = my_xpos + my_width + dx;
	}

	vertical.my_ypos = my_ypos;

	// calculate vertical update rect

	PG_Rect horizontal(0, 0, my_width + abs(dx), abs(dy));

	horizontal.my_xpos = my_xpos;

	if(dy >= 0) {
		horizontal.my_ypos = my_ypos;
	} else {
		horizontal.my_ypos = my_ypos + my_height + dy;
	}

	// move rectangle and store new background
	MoveRect(x, y);

	if(vertical.my_xpos + vertical.my_width > my_srfScreen->w) {
		vertical.my_width = my_srfScreen->w - vertical.my_xpos;
	}
	if(vertical.my_ypos + vertical.my_height > my_srfScreen->h) {
		vertical.my_height = my_srfScreen->h - vertical.my_ypos;
	}

	if(horizontal.my_xpos + horizontal.my_width > my_srfScreen->w) {
		horizontal.my_width = my_srfScreen->w- horizontal.my_xpos;
	}
	if(horizontal.my_ypos + horizontal.my_height > my_srfScreen->h) {
		horizontal.my_height = my_srfScreen->h - horizontal.my_ypos;
	}

	if(!PG_Application::GetBulkMode()) {
		UpdateRect(vertical);
		UpdateRect(horizontal);
		UpdateRect(my_internaldata->rectClip);
		PG_Application::LockScreen();
		SDL_UpdateRects(my_srfScreen, 1, &my_internaldata->rectClip);
		SDL_UpdateRects(my_srfScreen, 1, &vertical);
		SDL_UpdateRects(my_srfScreen, 1, &horizontal);
		PG_Application::UnlockScreen();
	}

	return true;
}

bool PG_Widget::MoveWindow(const PG_Rect& r) {
	return MoveWidget(r);
}

bool PG_Widget::MoveWidget(const PG_Rect& r) {
	MoveWidget(r.x, r.y);
	SizeWidget(r.w, r.h);
	return true;
}

bool PG_Widget::SizeWindow(Uint16 w, Uint16 h) {
	return SizeWidget(w, h);
}

bool PG_Widget::SizeWidget(Uint16 w, Uint16 h) {
	bool v = IsVisible();

	if (v) {
		SetVisible(false);
	}

	if (my_internaldata->firstredraw != true) {
		RestoreBackground();
	}

	// create new widget drawsurface
	if(my_srfObject) {
		PG_Application::UnloadSurface(my_srfObject);

		if(w > 0 && h > 0) {
			my_srfObject = PG_Draw::CreateRGBSurface(w, h);
		}
		else {
			my_srfObject = NULL;
		}
	}

	eventSizeWindow(w, h);
	eventSizeWidget(w, h);

	my_width = w;
	my_height = h;

	if (v) {
		SetVisible(true);
	}
	return true;
}
/**  */
bool PG_Widget::ProcessEvent(const SDL_Event * event, bool bModal) {

	SDL_mutexP(my_internaldata->mutexProcess);

	bool processed = false;
	// do i have a capturehook set ? (modal)
	if(bModal) {
		// i will send that event to my children

		if(my_internaldata->childList != NULL) {
			PG_RectList::reverse_iterator list = my_internaldata->childList->rbegin();

			while (!processed && (list != my_internaldata->childList->rend())) {
				processed = (*list)->ProcessEvent(event, true);
				list++;
			}
		}

		if(processed) {
			SDL_mutexV(my_internaldata->mutexProcess);
			return processed;
		}
    }

	// let me see if i can process it myself

	if(PG_MessageObject::ProcessEvent(event)) {
		SDL_mutexV(my_internaldata->mutexProcess);
		return true;
	}

	if(bModal) {
		SDL_mutexV(my_internaldata->mutexProcess);
		return processed;
	}

	// ask my parent to process the event

	if(GetParent()) {
		if(GetParent()->ProcessEvent(event)) {
			SDL_mutexV(my_internaldata->mutexProcess);
			return true;
		}
	}

	SDL_mutexV(my_internaldata->mutexProcess);

	return false;
}

bool PG_Widget::RemoveChild(PG_Widget * child) {
	if(my_internaldata->childList == NULL) {
		return false;
	}

    if (!child)
        return false;
    
    const char *name = child->GetName();
    int id = child->GetID();

    if (FindChild(name))
        my_internaldata->childrenNameMap[name] = 0;

    if (FindChild(id))
        my_internaldata->childrenIdMap[id] = 0;

	return my_internaldata->childList->Remove(child);
}

bool PG_Widget::IsMouseInside() {
	PG_Point p;
	int x, y;
	
	SDL_GetMouseState(&x, &y);
	p.x = static_cast<Sint16>(x);
	p.y = static_cast<Sint16>(y);
	my_internaldata->mouseInside = IsInside(p);

	return my_internaldata->mouseInside;
}

/**  */
bool PG_Widget::Redraw(bool update) {
	PG_Rect r(0, 0, my_width, my_height);

	if(my_srfObject != NULL) {
		eventDraw(my_srfObject, r);
	}

	if(my_internaldata->childList != NULL) {
		PG_RectList::iterator list = my_internaldata->childList->begin();

		while (list != my_internaldata->childList->end()) {
			(*list)->Redraw(false);
			list++;
		}
	}

	if (update) {
		Update();
	}
	return true;
}

void PG_Widget::SetVisible(bool visible) {

	if(IsHidden()) {
		return;
	}
	
	// Attempt to make object visible
	if(visible) {
		if(my_internaldata->visible) {			// Object already visible
			return;
		} else {					// Display object
			my_internaldata->visible = visible;
			if(my_internaldata->firstredraw) {
				Redraw(false);
				my_internaldata->firstredraw = false;
			}
		}

	}

	// Attempt to make object invisible
	if(!visible) {
		if(!my_internaldata->visible) {			// Object is already invisible
			return;
		} else {					// Hide object
			RestoreBackground();
			my_internaldata->visible = visible;
		}
	}

	if(my_internaldata->childList != NULL) {
		PG_RectList::iterator list = my_internaldata->childList->begin();

		while (list != my_internaldata->childList->end()) {
			(*list)->SetVisible(visible);
			if(!(*list)->IsHidden()) {
				if(visible) {
					(*list)->eventShow();
				} else {
					(*list)->eventHide();
				}
			}
			list++;
		}
	}
}

/**  */
void PG_Widget::Show(bool fade) {

	widgetList.BringToFront(this);

	SetHidden(false);
	SetVisible(true);
	
	eventShow();

	if (fade) {
		FadeIn();
	}

	if(IsMouseInside()) {
		eventMouseEnter();
	}

	SDL_SetClipRect(my_srfScreen, NULL);
	Update();

	return;
}

/**  */
void PG_Widget::Hide(bool fade) {

	if(!IsVisible()) {
		SetHidden(true);
		return;
	}

	RecalcClipRect();

	if(!my_internaldata->inDestruct) {
		eventMouseLeave();
	}

	if (fade) {
		FadeOut();
	}

	SetVisible(false);
	eventHide();

	ReleaseCapture();
	ReleaseInputFocus();

	RestoreBackground();

	if(!PG_Application::GetBulkMode()) {
		UpdateRect(my_internaldata->rectClip);
	}

	SDL_SetClipRect(my_srfScreen, NULL);

	if(!PG_Application::GetBulkMode()) {
		PG_Application::LockScreen();
		SDL_UpdateRects(my_srfScreen, 1, &my_internaldata->rectClip);
		PG_Application::UnlockScreen();
	}

	SetHidden(true);

	return;
}

/**  */
void PG_Widget::MoveRect(int x, int y) {
	int dx = x - my_xpos;
	int dy = y - my_ypos;

	// recalc cliprect
	RecalcClipRect();

	my_xpos = x;
	my_ypos = y;
	my_internaldata->rectClip.my_xpos += dx;
	my_internaldata->rectClip.my_ypos += dy;

	// recalc cliprect
	RecalcClipRect();

	if(my_internaldata->childList != NULL) {
		PG_RectList::iterator list = my_internaldata->childList->begin();

		while (list != my_internaldata->childList->end()) {
			(*list)->MoveRect((*list)->my_xpos + dx, (*list)->my_ypos + dy);
			list++;
		}
	}

	eventMoveWindow(x, y);
	eventMoveWidget(x, y);
}

void PG_Widget::Blit(bool recursive, bool restore) {
	static PG_Rect src;
	static PG_Rect dst;
	
	if(!my_internaldata->visible) {
		return;
	}

	// recalc clipping rectangle
	RecalcClipRect();

	// don't draw a null rect
	if(my_internaldata->rectClip.w == 0 || my_internaldata->rectClip.h == 0) {
		return;
	}

	PG_Application::LockScreen();

	// restore the background
	if(restore) {
		RestoreBackground(&my_internaldata->rectClip);
	}

	// get source & destination rectangles
	src.SetRect(my_internaldata->rectClip.x - my_xpos, my_internaldata->rectClip.y - my_ypos, my_internaldata->rectClip.w, my_internaldata->rectClip.h);
	dst = my_internaldata->rectClip;

	// call the blit handler
	eventBlit(my_srfObject, src, dst);

	// should we draw our children
	if(recursive) {
		// draw the children-list
		if(my_internaldata->childList != NULL) {
			my_internaldata->childList->Blit();
		}
	}

	PG_Application::UnlockScreen();
}

/**  */
void PG_Widget::Update(bool doBlit) {
	static PG_Rect src;
	static PG_Rect dst;
	
	if(PG_Application::GetBulkMode()) {
		return;
	}

	if(!my_internaldata->visible) {
		return;
	}

	// recalc cliprect
	RecalcClipRect();

	if(my_internaldata->rectClip.w == 0 || my_internaldata->rectClip.h == 0) {
		return;
	}

	PG_Application::LockScreen();

	// BLIT
	if(doBlit) {

		RestoreBackground(&my_internaldata->rectClip);

		src.SetRect(my_internaldata->rectClip.x - my_xpos, my_internaldata->rectClip.y - my_ypos, my_internaldata->rectClip.w, my_internaldata->rectClip.h);
		dst = my_internaldata->rectClip;

		eventBlit(my_srfObject, src, dst);

		if(my_internaldata->childList != NULL) {
			my_internaldata->childList->Blit();
		}

		int index = 0;

		// check if other children of my parent overlap myself
		if(GetParent() != NULL) {
			PG_RectList* children = GetParent()->GetChildList();
			if(children) {
				index = children->FindIndexOf(this);
				if(index != -1) {
					SDL_SetClipRect(my_srfScreen, &my_internaldata->rectClip);
					children->Intersect(&my_internaldata->rectClip, index+1, -1).Blit(my_internaldata->rectClip);
				}
			}
		}

		// find the toplevel widget
		PG_Widget* obj = GetToplevelWidget();

		// find my index
		index = widgetList.FindIndexOf(obj);

		if(index != -1) {
			SDL_SetClipRect(my_srfScreen, &my_internaldata->rectClip);
			widgetList.Intersect(&my_internaldata->rectClip, index+1, -1).Blit(my_internaldata->rectClip);
		}

		PG_Application::DrawCursor();
	}

	// Update screen surface
#ifdef DEBUG
	PG_LogDBG("UPD: x:%d y:%d w:%d h:%d",dst.x,dst.y,dst.w,dst.h);
#endif // DEBUG
	SDL_UpdateRects(my_srfScreen, 1, &my_internaldata->rectClip);

	SDL_SetClipRect(my_srfScreen, NULL);
	PG_Application::UnlockScreen();
}

/**  */
void PG_Widget::SetChildTransparency(Uint8 t) {
	if(my_internaldata->childList == NULL) {
		return;
	}

	PG_RectList::iterator list = my_internaldata->childList->begin();

	while (list != my_internaldata->childList->end()) {
		(*list)->SetTransparency(t);
		list++;
	}
	Update();
}

void PG_Widget::StartWidgetDrag() {
	int x, y;
	
	SDL_GetMouseState(&x, &y);
	my_internaldata->ptDragStart.x = static_cast<Sint16>(x);
	my_internaldata->ptDragStart.y = static_cast<Sint16>(y);
	
	my_internaldata->ptDragStart.x -= my_xpos;
	my_internaldata->ptDragStart.y -= my_ypos;
}

void PG_Widget::WidgetDrag(int x, int y) {

	x -= my_internaldata->ptDragStart.x;
	y -= my_internaldata->ptDragStart.y;

	if(x < 0)
		x=0;
	if(y < 0)
		y=0;
	if(x > (my_srfScreen->w - my_width -1))
		x = (my_srfScreen->w - my_width -1);
	if(y > (my_srfScreen->h - my_height -1))
		y = (my_srfScreen->h - my_height -1);

	MoveWidget(x,y);
}

void PG_Widget::EndWidgetDrag(int x, int y) {
	WidgetDrag(x,y);
	my_internaldata->ptDragStart.x = 0;
	my_internaldata->ptDragStart.y = 0;
}

void PG_Widget::HideAll() {
	for(Uint16 i=0; i<widgetList.size(); i++) {
		widgetList[i]->Hide();
	}
}

void PG_Widget::BulkUpdate() {
	bBulkUpdate = true;

	for(Uint16 i=0; i<widgetList.size(); i++) {
		if(widgetList[i]->IsVisible()) {
			widgetList[i]->Update();
		}
	}

	bBulkUpdate = false;
}

void PG_Widget::BulkBlit() {
	bBulkUpdate = true;
	widgetList.Blit();
	PG_Application::DrawCursor();
	bBulkUpdate = false;
}

void PG_Widget::LoadThemeStyle(const char* widgettype, const char* objectname) {
	PG_Theme* t = PG_Application::GetTheme();
	SDL_Color* c;

	const char *font = t->FindFontName(widgettype, objectname);
	int fontsize = t->FindFontSize(widgettype, objectname);
	int fontstyle = t->FindFontStyle(widgettype, objectname);

	if(font != NULL)
		SetFontName(font);

	if (fontsize > 0)
		SetFontSize(fontsize);

	if (fontstyle >= 0)
		SetFontStyle(fontstyle);

	c = t->FindColor(widgettype, objectname, "textcolor");
	if(c != NULL)
		SetFontColor(*c);

	c = t->FindColor(widgettype, objectname, "bordercolor0");
	if(c != NULL) {
		my_colorBorder[0][0] = *c;
	}

	c = t->FindColor(widgettype, objectname, "bordercolor1");
	if(c != NULL) {
		my_colorBorder[1][0] = *c;
	}
}

void PG_Widget::LoadThemeStyle(const char* widgettype) {}

void PG_Widget::FadeOut() {
	PG_Rect r(0, 0, my_width, my_height);

	// blit the widget to screen (invisible)
	Blit();

	// create a temp surface
	SDL_Surface* srfFade = PG_Draw::CreateRGBSurface(my_width, my_height);

	// blit the widget to temp surface
	PG_Draw::BlitSurface(my_srfScreen, *this, srfFade, r);

	int d = (255-my_internaldata->transparency)/ my_internaldata->fadeSteps;
	if(!d) {
		d = 1;
	} // minimum step == 1
	
	PG_Application::LockScreen();
	
	for(int i=my_internaldata->transparency; i<255; i += d) {
		RestoreBackground(NULL, true);
		SDL_SetAlpha(srfFade, SDL_SRCALPHA, 255-i);
		SDL_BlitSurface(srfFade, NULL, my_srfScreen, this);
		SDL_UpdateRects(my_srfScreen, 1, &my_internaldata->rectClip);
	}

	RestoreBackground(NULL, true);
	SDL_SetAlpha(srfFade, SDL_SRCALPHA, 0);
	SDL_BlitSurface(srfFade, NULL, my_srfScreen, this);
	SetVisible(false);
	PG_Application::UnlockScreen();

	Update(false);

	PG_Application::UnloadSurface(srfFade);
}

void PG_Widget::FadeIn() {

	// blit the widget to screen (invisible)
	SDL_SetClipRect(my_srfScreen, NULL);
	Blit();

	PG_Rect src(
	    0,
	    0,
	    (my_xpos < 0) ? my_width + my_xpos : my_width,
	    (my_ypos < 0) ? my_height + my_ypos : my_height);

	// create a temp surface
	SDL_Surface* srfFade = PG_Draw::CreateRGBSurface(w, h);

	PG_Application::LockScreen();
	
	// blit the widget to temp surface
	PG_Draw::BlitSurface(my_srfScreen, my_internaldata->rectClip, srfFade, src);

	int d = (255-my_internaldata->transparency)/ my_internaldata->fadeSteps;

	if(!d) {
		d = 1;
	} // minimum step == 1
	for(int i=255; i>my_internaldata->transparency; i -= d) {
		RestoreBackground(NULL, true);
		SDL_SetAlpha(srfFade, SDL_SRCALPHA, 255-i);
		PG_Draw::BlitSurface(srfFade, src, my_srfScreen, my_internaldata->rectClip);
		SDL_UpdateRects(my_srfScreen, 1, &my_internaldata->rectClip);
	}

	PG_Application::UnlockScreen();

	Update();

	PG_Application::UnloadSurface(srfFade);
}

void PG_Widget::SetFadeSteps(int steps) {
	my_internaldata->fadeSteps = steps;
}

bool PG_Widget::Action(PG_ACTION action) {
	int x = my_xpos + my_width / 2;
	int y = my_ypos + my_height / 2;

	switch(action) {
		case PG_ACT_ACTIVATE:
			SDL_WarpMouse(x,y);
			eventMouseEnter();
			break;

		case PG_ACT_DEACTIVATE:
			eventMouseLeave();
			break;

		case PG_ACT_OK:
			SDL_MouseButtonEvent button;
			button.button = 1;
			button.x = x;
			button.y = y;
			eventMouseButtonDown(&button);
			SDL_Delay(200);
			eventMouseButtonUp(&button);
			Action(PG_ACT_ACTIVATE);
			break;

		default:
			break;
	}

	return false;
}

bool PG_Widget::RestoreBackground(PG_Rect* clip, bool force) {

	if(my_internaldata->dirtyUpdate && (my_internaldata->transparency == 0) && !force) {
		return false;
	}
	
	if(PG_Application::GetBulkMode()) {
		return false;
	}

	if(clip == NULL) {
		clip = &my_internaldata->rectClip;
	}

	if(GetParent() == NULL) {
		PG_Application::RedrawBackground(*clip);

		int index = widgetList.FindIndexOf(this);

		if(index != -1) {
			SDL_SetClipRect(my_srfScreen, clip);
			widgetList.Intersect(clip, 0, index).Blit(*clip);
		}
		return true;
	}

	GetParent()->RestoreBackground(clip);
	SDL_SetClipRect(my_srfScreen, clip);
	GetParent()->Blit(false, false);

	return true;
}

PG_Widget* PG_Widget::FindWidgetFromPos(int x, int y) {
	PG_Point p;
	p.x = x;
	p.y = y;
	bool finished = false;

	PG_Widget* toplevel = widgetList.IsInside(p);
	PG_Widget* child = NULL;

	if(!toplevel) {
		return NULL;
	}

	while(!finished) {

		if(toplevel->GetChildList()) {
			child = toplevel->GetChildList()->IsInside(p);

			if(child) {
				toplevel = child;
				child = NULL;
			} else {
				finished = true;
			}

		} else {
			finished = true;
		}
	}

	return toplevel;
}

void PG_Widget::UpdateRect(const PG_Rect& r) {
	if(PG_Application::GetBulkMode()) {
		return;
	}

	SDL_Surface* screen = PG_Application::GetScreen();

	PG_Application::LockScreen();
	PG_Application::RedrawBackground(r);
	SDL_SetClipRect(screen, (PG_Rect*)&r);
	widgetList.Intersect((PG_Rect*)&r).Blit(r);
	SDL_SetClipRect(screen, NULL);
	PG_Application::UnlockScreen();
}

void PG_Widget::UpdateScreen() {
	UpdateRect(
	    PG_Rect(0, 0, PG_Application::GetScreenWidth(), PG_Application::GetScreenHeight())
	);
}

bool PG_Widget::IsInFrontOf(PG_Widget* widget) {
	PG_Widget* w1 = NULL;
	PG_Widget* w2 = NULL;
	PG_RectList* list = &widgetList;

	// do both widgets have the same parent ?
	if((GetParent() != NULL) && (GetParent() == widget->GetParent())) {
		w1 = this;
		w2 = widget;
		list = GetParent()->GetChildList();
	} else {
		w1 = this->GetToplevelWidget();
		w2 = widget->GetToplevelWidget();
	}

	return (list->FindIndexOf(w1) > list->FindIndexOf(w2));
}

PG_Widget* PG_Widget::GetToplevelWidget() {
	if(GetParent() == NULL) {
		return this;
	}

	return GetParent()->GetToplevelWidget();
}

void PG_Widget::SendToBack() {
	if(GetParent() == NULL) {
		widgetList.SendToBack(this);
	} else {
		GetParent()->GetChildList()->SendToBack(this);
	}
	Update();
}

void PG_Widget::BringToFront() {
	if(GetParent() == NULL) {
		widgetList.BringToFront(this);
	} else {
		GetParent()->GetChildList()->BringToFront(this);
	}
	Update();
}

void PG_Widget::RecalcClipRect() {
	static PG_Rect pr;

	if (my_internaldata->widgetParent != NULL) {
		pr = *(my_internaldata->widgetParent->GetClipRect());
	} else {
		pr.SetRect(
		    0,
		    0,
		    PG_Application::GetScreenWidth(),
		    PG_Application::GetScreenHeight());
	}

	PG_Rect ir = IntersectRect(pr);
	SetClipRect(ir);
}

bool PG_Widget::LoadLayout(const char *name) {
	bool rc = PG_Layout::Load(this, name, NULL, NULL);
	Update();
	return rc;
}

bool PG_Widget::LoadLayout(const char *name, void (* WorkCallback)(int now, int max)) {
	bool rc = PG_Layout::Load(this, name, WorkCallback, NULL);
	Update();
	return rc;

}

bool PG_Widget::LoadLayout(const char *name, void (* WorkCallback)(int now, int max),void *UserSpace) {
	bool rc = PG_Layout::Load(this, name, WorkCallback, UserSpace);
	Update();
	return rc;
}

void PG_Widget::SetUserData(void *userdata, int size) {
	my_internaldata->userdata = new char(size);
	memcpy(my_internaldata->userdata, userdata, size);
	my_internaldata->userdatasize = size;
}

int PG_Widget::GetUserDataSize() {
	return my_internaldata->userdatasize;
}

void PG_Widget::GetUserData(void *userdata) {
	if (my_internaldata->userdata == NULL)
		return;
		
	memcpy(userdata, my_internaldata->userdata, my_internaldata->userdatasize);
}

void PG_Widget::ReleaseUserData() {
	if (my_internaldata->userdata != NULL)
		delete[] my_internaldata->userdata;
	my_internaldata->userdatasize = 0;
}

void PG_Widget::AddText(const char* text, bool update) {
	my_text += text;
	my_internaldata->widthText = TXT_HEIGHT_UNDEF;
	my_internaldata->heightText = TXT_HEIGHT_UNDEF;

	//TO-DO : Optimalize this !!! - because of widget functions overloading SetText()
	if (update) {
		SetText(GetText());
	}
}

void PG_Widget::SetText(const char* text) {

	my_internaldata->widthText = TXT_HEIGHT_UNDEF;
	my_internaldata->heightText = TXT_HEIGHT_UNDEF;

	if(text == NULL) {
		my_text = "";
		return;
	}

	my_text = text;
	Update();
}

void PG_Widget::SetTextFormat(const char* text, ...) {
	va_list ap;
	va_start(ap, text);
	char temp[256];

	if(text == NULL) {
		my_text = "";
		return;
	}

	if(text[0] == 0) {
		my_text = "";
		return;
	}

	vsprintf(temp, text, ap);
	SetText(temp);
	va_end(ap);
}

void PG_Widget::SetFontColor(const SDL_Color& Color) {
	my_internaldata->font->SetColor(Color);
}

void PG_Widget::SetFontColor(int Red, int Green, int Blue) {
	SDL_Color c;
	c.r = Red;
	c.g = Green;
	c.b = Blue;
	SetFontColor(c);
}

void PG_Widget::SetFontColor(int Color) {
	SDL_Color c;
	c.r = (Color >> 16) & 0xff;
	c.g = (Color >> 8) & 0xff;
	c.b = Color & 0xff;
	SetFontColor(c);
}

void PG_Widget::SetFontAlpha(int Alpha, bool bRecursive) {
	my_internaldata->font->SetAlpha(Alpha);

	if(!bRecursive || (GetChildList() == NULL)) {
		return;
	}

	for(PG_RectList::iterator i = GetChildList()->begin(); i != GetChildList()->end(); i++) {
		(*i)->SetFontAlpha(Alpha, true);
	}
}

void PG_Widget::SetFontStyle(int Style, bool bRecursive) {
	my_internaldata->font->SetStyle(Style);

	if(!bRecursive || (GetChildList() == NULL)) {
		return;
	}

	for(PG_RectList::iterator i = GetChildList()->begin(); i != GetChildList()->end(); i++) {
		(*i)->SetFontStyle(Style, true);
	}
}

int PG_Widget::GetFontSize() {
	return my_internaldata->font->GetSize();
}

void PG_Widget::SetFontSize(int Size, bool bRecursive) {
	my_internaldata->font->SetSize(Size);

	if(!bRecursive || (GetChildList() == NULL)) {
		return;
	}

	for(PG_RectList::iterator i = GetChildList()->begin(); i != GetChildList()->end(); i++) {
		(*i)->SetFontSize(Size, true);
	}

}

void PG_Widget::SetFontIndex(int Index, bool bRecursive) {
//	my_internaldata->font->SetIndex(Index);
}

void PG_Widget::SetFontName(const char *Name, bool bRecursive) {
	my_internaldata->font->SetName(Name);

	if(!bRecursive || (GetChildList() == NULL)) {
		return;
	}

	for(PG_RectList::iterator i = GetChildList()->begin(); i != GetChildList()->end(); i++) {
		(*i)->SetFontName(Name, true);
	}

}

void PG_Widget::SetSizeByText(int Width, int Height, const char *Text) {
	Uint16 w,h;

	if (Text == NULL) {
		Text = my_text.c_str();
	}

	if (PG_FontEngine::GetTextSize(Text, my_internaldata->font, &w, &h) != 0) {
		return;
	}

	//SizeWidget(w + Width, h + Height);
	my_width = w + Width;
	my_height = h + Height;
}

void PG_Widget::SetFont(PG_Font* font) {
	if(my_internaldata->font != NULL) {
		delete my_internaldata->font;
	}
	
	my_internaldata->font = new PG_Font(font->GetName(), font->GetSize());
}

void PG_Widget::GetTextSize(Uint16& w, Uint16& h, const char* text) {
	if(text == NULL) {
		if(my_internaldata->widthText != TXT_HEIGHT_UNDEF) {
			w = my_internaldata->widthText;
			h = my_internaldata->heightText;
			return;
		}
		text = my_text.c_str();
	}

	GetTextSize(w, h, text, my_internaldata->font);

	if(text == NULL) {
		my_internaldata->widthText = w;
		my_internaldata->heightText = h;
	}
}

void PG_Widget::GetTextSize(Uint16& w, Uint16& h, const char* text, PG_Font* font) {
	PG_FontEngine::GetTextSize(text, font, &w);
	h = font->GetFontHeight();
}

int PG_Widget::GetTextWidth() {

	if(my_internaldata->widthText != TXT_HEIGHT_UNDEF) {
		return my_internaldata->widthText;
	}
		
	GetTextSize(my_internaldata->widthText, my_internaldata->heightText);

	return my_internaldata->widthText;
}

int PG_Widget::GetTextHeight() {
	return my_internaldata->font->GetFontAscender();
}

void PG_Widget::DrawText(const PG_Rect& rect, const char* text) {
	if(my_srfObject == NULL) {
		PG_FontEngine::RenderText(my_srfScreen, my_internaldata->rectClip, my_xpos+ rect.x, my_ypos + rect.y + GetFontAscender(), text, my_internaldata->font);
	}
	else {
		PG_FontEngine::RenderText(my_srfObject, PG_Rect(0,0,Width(),Height()), rect.x, rect.y + GetFontAscender(), text, my_internaldata->font);
	}
}

void PG_Widget::DrawText(int x, int y, const char* text) {
	DrawText(PG_Rect(x,y,0,0), text);
}

void PG_Widget::DrawText(int x, int y, const char* text, const PG_Rect& cliprect) {
	if(my_srfObject == NULL) {
		PG_Rect rect = cliprect;
		rect.x += my_xpos;
		rect.y += my_ypos;
		PG_FontEngine::RenderText(my_srfScreen, rect, my_xpos + x, my_ypos + y + GetFontAscender(), text, my_internaldata->font);
	}
	else {
		PG_FontEngine::RenderText(my_srfObject, cliprect, x, y + GetFontAscender(), text, my_internaldata->font);
	}
}

void PG_Widget::DrawText(const PG_Rect& rect, const char* text, const SDL_Color& c) {
	SetFontColor(c);
	DrawText(PG_Rect(x,y,0,0), text);
}

void PG_Widget::DrawText(int x, int y, const char* text, const SDL_Color& c) {
	DrawText(PG_Rect(x,y,0,0), text, c);
}

void PG_Widget::QuitModal() {
		SendMessage(this, MSG_MODALQUIT, 0, 0);
}

int PG_Widget::RunModal() {
	SDL_Event event;
	my_internaldata->quitModalLoop = false;

	// unlock the mutex
	//SDL_mutexV(my_mutexReceiveMessage);

	while(!my_internaldata->quitModalLoop) {
		SDL_WaitEvent(&event);
		ProcessEvent(&event, true);
		PG_Application::DrawCursor();
	}

	return 0;
}

bool PG_Widget::eventQuitModal(int id, PG_MessageObject* widget, unsigned long data) {
	my_internaldata->quitModalLoop = true;
	return true;
}

const char* PG_Widget::GetText() {
	return my_text.c_str();
}

void PG_Widget::eventBlit(SDL_Surface* srf, const PG_Rect& src, const PG_Rect& dst) {

	// Don't blit an object without a surface

	if(srf == NULL) {
		return;
	}

	// Set alpha
	if(my_internaldata->transparency != 255) {
		SDL_SetAlpha(srf, SDL_SRCALPHA, 255-my_internaldata->transparency);

		// Blit widget surface to screen
#ifdef DEBUG
		PG_LogDBG("SRC BLIT: x:%d y:%d w:%d h:%d",src.x,src.y,src.w,src.h);
		PG_LogDBG("DST BLIT: x:%d y:%d w:%d h:%d",dst.x,dst.y,dst.w,dst.h);
#endif // DEBUG

		PG_Draw::BlitSurface(srf, src, my_srfScreen, dst);
	}
}

void PG_Widget::DrawBorder(const PG_Rect& r, int size, bool up) {
	int i0, i1;

	if(!IsVisible()) {
		return;
	}

	i0 = (up) ? 0 : 1;
	i1 = (up) ? 1 : 0;

	// outer frame
	if (size >= 1) {
		DrawHLine(r.x + 0, r.y + 0, r.w, my_colorBorder[i0][0].r, my_colorBorder[i0][0].g, my_colorBorder[i0][0].b);
		DrawVLine(r.x + 0, r.y + 0, r.h - 1, my_colorBorder[i0][0].r, my_colorBorder[i0][0].g, my_colorBorder[i0][0].b);

		DrawHLine(r.x + 0, r.y + r.h - 1, r.w - 1, my_colorBorder[i1][0].r, my_colorBorder[i1][0].g, my_colorBorder[i1][0].b);
		DrawVLine(r.x + r.w - 1, r.y + 1, r.h - 1, my_colorBorder[i1][0].r, my_colorBorder[i1][0].g, my_colorBorder[i1][0].b);
	}
	// inner frame
	if (size >= 2) {
		DrawHLine(r.x + 1, r.y + 1, r.w - 1, my_colorBorder[i0][1].r, my_colorBorder[i0][1].g, my_colorBorder[i0][1].b);
		DrawVLine(r.x + 1, r.y + 1, r.h - 2, my_colorBorder[i0][1].r, my_colorBorder[i0][1].g, my_colorBorder[i0][1].b);

		DrawHLine(r.x + 1, r.y + r.h - 2, r.w - 2, my_colorBorder[i1][1].r, my_colorBorder[i1][1].g, my_colorBorder[i1][1].b);
		DrawVLine(r.x + r.w - 2, r.y + 2, r.h - 2, my_colorBorder[i1][1].r, my_colorBorder[i1][1].g, my_colorBorder[i1][1].b);
	}
}

void PG_Widget::SetTransparency(Uint8 t) {
	my_internaldata->transparency = t;
}

void PG_Widget::SetClipRect(PG_Rect& r) {
	my_internaldata->rectClip = r;
}

void PG_Widget::GetClipRects(PG_Rect& src, PG_Rect& dst, const PG_Rect& rect) {

	dst = IntersectRect(my_internaldata->rectClip, rect);

	int dx = dst.my_xpos - rect.my_xpos;
	int dy = dst.my_ypos - rect.my_ypos;

	if(dx < 0) {
		dx = 0;
	}

	if(dy < 0) {
		dy = 0;
	}

	src.my_xpos = dx;
	src.my_ypos = dy;
	src.my_width = dst.my_width;
	src.my_height = dst.my_height;
}

void PG_Widget::SetPixel(int x, int y, Uint8 r, Uint8 g, Uint8 b) {
	static PG_Point p;

	if(my_srfObject == NULL) {
		p.x = my_xpos + x;
		p.y = my_ypos + y;
		if(my_internaldata->rectClip.IsInside(p)) {
			PG_Draw::SetPixel(p.x, p.y, r, g, b, my_srfScreen);
		}
	} else {
		PG_Draw::SetPixel(x, y, r, g, b, my_srfObject);
	}
}

void PG_Widget::DrawHLine(int x, int y, int w, Uint8 r, Uint8 g, Uint8 b) {
	static PG_Rect rect;
	SDL_Surface* surface = my_srfObject;
	
	if(my_srfObject == NULL) {
		surface = my_srfScreen;
	}
	
	x += my_xpos;
	y += my_ypos;

	if((y < my_internaldata->rectClip.y) || (y >= (my_internaldata->rectClip.y+my_internaldata->rectClip.h))) {
		return;
	}
	
	/*SDL_GetClipRect(surface, &rect);

	if((y < rect.y) || (y >= (rect.y+rect.h))) {
		return;
	}*/

	// clip to widget cliprect
	int x0 = PG_MAX(x, my_internaldata->rectClip.x);
	int x1 = PG_MIN(x+w, my_internaldata->rectClip.x+my_internaldata->rectClip.w);
	Uint32 c = SDL_MapRGB(surface->format, r, g, b);

	// clip to surface cliprect
	/*x0 = PG_MAX(x0, rect.x);
	x1 = PG_MIN(x1, rect.x+rect.w);*/

	int wl = (x1-x0);
	
	if(wl <= 0) {
		return;
	}
	
	if(my_srfObject != NULL) {
		x0 -= my_xpos;
		y -= my_ypos;
	}

	rect.SetRect(x0, y, wl, 1);
	SDL_FillRect(surface, &rect, c);
}

void PG_Widget::DrawVLine(int x, int y, int h, Uint8 r, Uint8 g, Uint8 b) {
	static PG_Rect rect;
	SDL_Surface* surface = my_srfObject;
	
	if(my_srfObject == NULL) {
		surface = my_srfScreen;
	}
	
	x += my_xpos;
	y += my_ypos;

	if((x < my_internaldata->rectClip.x) || (x >= (my_internaldata->rectClip.x+my_internaldata->rectClip.w))) {
		return;
	}
	
	/*SDL_GetClipRect(surface, &rect);

	if((x < rect.x) || (x >= (rect.x+rect.w))) {
		return;
	}*/

	// clip to widget cliprect
	int y0 = PG_MAX(y, my_internaldata->rectClip.y);
	int y1 = PG_MIN(y+h, my_internaldata->rectClip.y+my_internaldata->rectClip.h);
	Uint32 c = SDL_MapRGB(surface->format, r, g, b);

	// clip to surface cliprect
	/*y0 = PG_MAX(y0, rect.y);
	y1 = PG_MIN(y1, rect.y+rect.h);*/

	int hl = (y1-y0);
	
	if(hl <= 0) {
		return;
	}
	
	if(my_srfObject != NULL) {
		y0 -= my_ypos;
		x -= my_xpos;
	}

	rect.SetRect(x, y0, 1, hl);
	SDL_FillRect(surface, &rect, c);
}

/**  */
void PG_Widget::DrawRectWH(int x, int y, int w, int h, Uint8 r, Uint8 g, Uint8 b) {

	DrawHLine(x, y, w, r, g, b);
	DrawHLine(x, y + h - 1, w, r, g, b);
	DrawVLine(x, y, h, r, g, b);
	DrawVLine(x + w - 1, y, h, r, g, b);

}

void PG_Widget::DrawLine(Uint32 x0, Uint32 y0, Uint32 x1, Uint32 y1, const SDL_Color& color, Uint8 width) {
	SDL_Surface* surface = my_srfObject;

	if(surface == NULL) {
		surface = PG_Application::GetScreen();
		x0 += my_xpos;
		y0 += my_ypos;
		x1 += my_xpos;
		y1 += my_ypos;
	}

	PG_Draw::DrawLine(surface, x0, y0, x1, y1, color, width);
}

void PG_Widget::eventDraw(SDL_Surface* surface, const PG_Rect& rect) {
}

void PG_Widget::eventMoveWidget(int x, int y) {
}

void PG_Widget::eventMoveWindow(int x, int y) {
}

void PG_Widget::eventSizeWindow(Uint16 w, Uint16 h) {
}

void PG_Widget::eventSizeWidget(Uint16 w, Uint16 h) {
}

SDL_Surface* PG_Widget::GetWidgetSurface() {
	return my_srfObject;
}

SDL_Surface* PG_Widget::GetScreenSurface() {
	return my_srfScreen;
}

bool PG_Widget::IsVisible() {
	return my_internaldata->visible;
}

PG_Widget* PG_Widget::GetParent() {
	if(my_internaldata == NULL) {
		return NULL;
	}
	return my_internaldata->widgetParent;
}

int PG_Widget::GetID() {
	if(my_internaldata == NULL) {
		return -1;
	}
	return my_internaldata->id;
}

PG_Widget* PG_Widget::FindChild(int id) {
	PG_IdToWidgetMap::iterator r = my_internaldata->childrenIdMap.find(id);

	if(r == my_internaldata->childrenIdMap.end()) {
		return NULL;
	}

	return (*r).second;
}

PG_Widget* PG_Widget::FindChild(const char *name) {
	std::string n = name;
	PG_NameToWidgetMap::iterator r = my_internaldata->childrenNameMap.find(n);

	if(r == my_internaldata->childrenNameMap.end()) {
		return NULL;
	}

	return (*r).second;
}

PG_RectList* PG_Widget::GetChildList() {
	return my_internaldata->childList;
}

int PG_Widget::GetChildCount() {
	return my_internaldata->childList ? my_internaldata->childList->size() : 0;
}

PG_RectList* PG_Widget::GetWidgetList() {
	return &widgetList;
}

void PG_Widget::SetName(const char *name) {
	my_internaldata->name = name;
	if (my_internaldata->widgetParent) {
		my_internaldata->widgetParent->AddChildToCache(this, name);
	}
}

const char* PG_Widget::GetName() {
	return my_internaldata->name.c_str();
}

int PG_Widget::GetFontAscender() {
	return my_internaldata->font->GetFontAscender();
}

int PG_Widget::GetFontHeight() {
	return my_internaldata->font->GetFontHeight();
}

SDL_Color PG_Widget::GetFontColor() {
	return my_internaldata->font->GetColor();
}

PG_Font* PG_Widget::GetFont() {
	return my_internaldata->font;
}

Uint8 PG_Widget::GetTransparency() {
	return my_internaldata->transparency;
}

PG_Rect* PG_Widget::GetClipRect() {
	return &my_internaldata->rectClip;
}

bool PG_Widget::IsClippingEnabled() {
	return ((my_internaldata->rectClip.my_width != my_width) || (my_internaldata->rectClip.my_height != my_height));
}

void PG_Widget::GetClipRects(PG_Rect& src, PG_Rect& dst) {
	GetClipRects(src, dst, *this);
}

bool PG_Widget::eventButtonClick(int id, PG_Widget* widget) {
	return false;
}


bool PG_Widget::eventScrollPos(int id, PG_Widget* widget, unsigned long data) {
	return false;
}


bool PG_Widget::eventScrollTrack(int id, PG_Widget* widget, unsigned long data) {
	return false;
}

bool PG_Widget::eventMessage(MSG_MESSAGE* msg) {
	bool rc = false;

    if (!msg)
        return false;

	if((msg->to != this) && (msg->to != NULL)) {
		return false;
	}

	if(PG_MessageObject::eventMessage(msg)) {
		return true;
	}

	switch(msg->type) {
		case MSG_BUTTONCLICK:
			rc = eventButtonClick(msg->widget_id, (PG_Widget*)(msg->from));
			break;

		case MSG_SCROLLPOS:
			rc = eventScrollPos(msg->widget_id, (PG_Widget*)(msg->from), msg->data);
			break;

		case MSG_SCROLLTRACK:
			rc = eventScrollTrack(msg->widget_id, (PG_Widget*)(msg->from), msg->data);
			break;

		default:
			rc = false;
			break;
	}

	return rc;
}

void PG_Widget::SetID(int id) {
	my_internaldata->id = id;
	if (my_internaldata->widgetParent) {
		my_internaldata->widgetParent->AddChildToCache(this, id);
	}
}

void PG_Widget::SetDirtyUpdate(bool bDirtyUpdate) {
	if(PG_Application::GetDirtyUpdatesDisabled()) {
		my_internaldata->dirtyUpdate = false;
		return;
	}
	
	my_internaldata->dirtyUpdate = bDirtyUpdate;
}

bool PG_Widget::GetDirtyUpdate() {
	return my_internaldata->dirtyUpdate;
}

void PG_Widget::SetHidden(bool hidden) {
	my_internaldata->hidden = hidden;
}

	
bool PG_Widget::IsHidden() {
	return my_internaldata->hidden;
}
