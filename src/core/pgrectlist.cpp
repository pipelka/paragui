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
    Update Date:      $Date: 2004/02/19 16:50:11 $
    Source File:      $Source: /sources/paragui/paragui/src/core/pgrectlist.cpp,v $
    CVS/RCS Revision: $Revision: 1.1.6.2.2.4 $
    Status:           $State: Exp $
*/

#include "pgrectlist.h"
#include "pgwidget.h"
#include "pgapplication.h"
#include "pglog.h"

#include <algorithm>

PG_RectList::PG_RectList() :
my_first(NULL),
my_last(NULL) {
}

PG_RectList::~PG_RectList() {}

/*PG_RectList PG_RectList::Intersect(PG_Rect* rect, PG_Rect* first, PG_Rect* last) {
	PG_RectList result;

	if(first == NULL) {
		return result;
	}

	//PG_Widget* testwidget;
	PG_Rect* testrect;

	// loop through all rects
	for(PG_Widget* i = static_cast<PG_Widget*>(first); i != last; i = static_cast<PG_Widget*>(i->next)) {

		// get the next rectangle to test
		//testwidget = (*i).second;

		if(!i->IsVisible() || i->IsHidden()) {
			continue;
		}

		testrect = i->GetClipRect();
		if(rect->OverlapRect(*testrect)) {
			// append the matching rectangle
			result.Add(new PG_Rect(*i));
		}
	}

	return result;
}*/

PG_Widget* PG_RectList::IsInside(const PG_Point& p) {
	PG_Widget* testrect;

	// loop down all rects till we find a match
	for(PG_Rect* i = last(); i != NULL; i = i->prev) {

		testrect = static_cast<PG_Widget*>(i);

		// check if the tested rect is visible
		if(!testrect->IsVisible() || testrect->IsHidden()) {
			continue;
		}

		// check for a match
		if(testrect->GetClipRect()->IsInside(p)) {
			return testrect;
		}
	}

	return NULL;
}

void PG_RectList::Add(PG_Widget* rect, bool front) {
	if(rect->next != NULL || rect->prev != NULL) {
		PG_LogWRN("PG_RectList::Add(...) Trying to add a linked PG_Rect object");
		return;
	}

	Uint32 index = 2^31;
	my_count++;

	// get highest index
	if(my_last != NULL) {
		index = my_last->index;
	}
	index++;
	
	if(front) {
		if(my_first != NULL) {
			my_first->prev = rect;
			rect->index = index;
		}
		else {
			rect->index = my_first->index-1;
		}
		rect->next = my_first;
		rect->prev = NULL;
		my_first = rect;
		return;
	}

	if(my_first == NULL) {
		my_first = rect;
		rect->prev = NULL;
		rect->next = NULL;
	}
	else {
		my_last->next = rect;
		rect->next = NULL;
		rect->prev = my_last;
	}
	my_last = rect;
	rect->index = index;
}

bool PG_RectList::Remove(PG_Rect* rect) {
	if(rect == NULL) {
		return false;
	}

	if((rect->next == NULL) && (rect->prev == NULL) && (my_first != rect)) {
		//PG_LogWRN("PG_RectList::Add(...) Trying to remove an unlinked PG_Rect object");
		return false;
	}
	
	my_count--;

	// first in list
	if(rect == my_first) {
		my_first = rect->next;
		if(my_first != NULL) {
			my_first->prev = NULL;
		}
	}
	// last
	else if(rect == my_last) {
		my_last = rect->prev;
		if(my_last != NULL) {
			my_last->next = NULL;
		}
	}
	// in between
	else {
		rect->prev->next = rect->next;
		rect->next->prev = rect->prev;
	}

	rect->next = NULL;
	rect->prev = NULL;

	return true;
}

void PG_RectList::Blit(const PG_Rect& rect) {
	Blit(rect, first());
}

void PG_RectList::Blit(const PG_Rect& rect, PG_Rect* start, PG_Rect* end) {
	if(start == NULL) {
		return;
	}

	PG_RectList* childs;
	SDL_Surface* screen = PG_Application::GetScreen();

	// store old clipping rectangle
	PG_Rect o;
	SDL_GetClipRect(screen, &o);

	// blit all objects in the list
	for(PG_Widget* i = static_cast<PG_Widget*>(start); i != end; i = static_cast<PG_Widget*>(i->next)) {

		if(!i->IsVisible() || i->IsHidden()) {
			continue;
		}

		// calculate the clipping rectangle
		// cliprect = blittingregion / widgetcliprect
		PG_Rect* cr = i->GetClipRect();
		if(!rect.OverlapRect(*cr)) {
			continue;
		}
		
		PG_Rect c = cr->IntersectRect(rect);
		SDL_SetClipRect(screen, &c);

		// blit it
		i->Blit(false, false);

		// blit all children of the widget
		childs = i->GetChildList();
		if(childs) {
			childs->Blit(rect);
		}
	}

	// reset clipping rectangle
	SDL_SetClipRect(PG_Application::GetScreen(), &o);
}

void PG_RectList::Blit() {
	// blit all objects in the list
	for(PG_Widget* i = static_cast<PG_Widget*>(first()); i != NULL; i = static_cast<PG_Widget*>(i->next)) {
		if(!i->IsVisible() || i->IsHidden()) {
			continue;
		}

		i->Blit(true, false);
	}
}

bool PG_RectList::BringToFront(PG_Widget* rect) {
	if(!Remove(rect)) {
		return false;
	}
	Add(rect);

	return true;
}

bool PG_RectList::SendToBack(PG_Widget* rect) {
	if(!Remove(rect)) {
		return false;
	}
	Add(rect, true);

	return true;
}

PG_Widget* PG_RectList::Find(int id) {
	for(PG_Widget* i = static_cast<PG_Widget*>(first()); i != NULL; i = static_cast<PG_Widget*>(i->next)) {
		if(i->GetID() == id) {
			return i;
		}
	}
	return NULL;
}

PG_Widget* PG_RectList::Find(const char* name) {
	for(PG_Widget* i = static_cast<PG_Widget*>(first()); i != NULL; i = static_cast<PG_Widget*>(i->next)) {
		if(strcmp(i->GetName(), name) == 0) {
			return i;
		}
	}
	return NULL;
}

void PG_RectList::clear() {
	my_first = NULL;
	my_last = NULL;
	my_count = 0;
}
