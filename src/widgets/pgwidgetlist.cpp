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
    Update Date:      $Date: 2002/04/15 13:31:31 $
    Source File:      $Source: /sources/paragui/paragui/src/widgets/pgwidgetlist.cpp,v $
    CVS/RCS Revision: $Revision: 1.2 $
    Status:           $State: Exp $
*/

#include "pgwidgetlist.h"
#include "pgapplication.h"
#include "pglog.h"

struct PG_WidgetListDataInternal{
	int my_scrolldeltax;
	int my_scrolldeltay;
};

PG_WidgetList::PG_WidgetList(PG_Widget* parent, const PG_Rect& r, const char* style) : PG_ThemeWidget(parent, r, style) {
	my_widgetCount = 0;
	my_listheight = my_listwidth = 0;
	my_firstWidget = 0;
	my_enableVerticalScrollbar = true;
	my_enableHorizontalScrollbar = false;
	my_widthScrollbar = my_heightHorizontalScrollbar = 5;

	my_internaldata = new PG_WidgetListDataInternal;
	my_internaldata->my_scrolldeltax = 0;
	my_internaldata->my_scrolldeltay = 0;

	// It is important to make sure that the substractions below won't
	// render values < 0 and, eventually,
	// surface widths such as 32768 or 65535 when cast to an unsigned type.
	// This can lead to segfaults later on in, for example, DrawGradient...
	if (my_widthScrollbar > r.my_width)
		my_widthScrollbar = r.my_width;
	    
	if (my_heightHorizontalScrollbar > r.my_height)
		my_heightHorizontalScrollbar = r.my_height;

	my_rectVerticalScrollbar.SetRect(
	    r.my_width - my_widthScrollbar,
	    0,
	    my_widthScrollbar,
	    r.my_height);

	my_rectHorizontalScrollbar.SetRect(
	    0,
	    r.my_height - my_heightHorizontalScrollbar,
	    r.my_width - my_widthScrollbar,
	    my_heightHorizontalScrollbar);

	my_objVerticalScrollbar = new PG_ScrollBar(this, PG_IDWIDGETLIST_SCROLL, my_rectVerticalScrollbar, PG_SB_VERTICAL, style);
	my_objVerticalScrollbar->SetRange(0,0);
	my_widthScrollbar = my_objVerticalScrollbar->Width();
	my_objVerticalScrollbar->MoveWidget(r.my_width - my_widthScrollbar, 0);
	my_objVerticalScrollbar->SizeWidget(my_widthScrollbar, r.my_height);

	my_objHorizontalScrollbar = new PG_ScrollBar(this, PG_IDWIDGETLIST_SCROLL, my_rectHorizontalScrollbar, PG_SB_HORIZONTAL, style);
	my_objHorizontalScrollbar->SetRange(0,0);
	my_heightHorizontalScrollbar = my_objHorizontalScrollbar->Height();
	my_objHorizontalScrollbar->MoveWidget(0, r.my_height - my_heightHorizontalScrollbar);
	my_objHorizontalScrollbar->SizeWidget(r.my_width, my_heightHorizontalScrollbar);

	my_rectList.SetRect(
	    my_bordersize,
	    my_bordersize,
	    r.my_width - my_widthScrollbar - my_bordersize*2,
	    r.my_height - my_heightHorizontalScrollbar - my_bordersize*2);

	LoadThemeStyle(style);
}

PG_WidgetList::~PG_WidgetList() {
	DeleteAll();
	delete my_internaldata;
}

void PG_WidgetList::LoadThemeStyle(const char* widgettype) {
	PG_ThemeWidget::LoadThemeStyle(widgettype);
	my_objVerticalScrollbar->LoadThemeStyle(widgettype);
	my_objHorizontalScrollbar->LoadThemeStyle(widgettype);

	my_widthScrollbar = my_objVerticalScrollbar->Width();
	my_objVerticalScrollbar->MoveWidget(my_width - my_widthScrollbar, 0);

	my_heightHorizontalScrollbar = my_objHorizontalScrollbar->Height();
	my_objHorizontalScrollbar->MoveWidget(0, my_height - my_heightHorizontalScrollbar);
}

void PG_WidgetList::eventBlit(SDL_Surface* srf, const PG_Rect& src, const PG_Rect& dst) {
	PG_Rect r = my_rectList;
	r.my_xpos -= my_bordersize;
	r.my_ypos -= my_bordersize;
	r.my_width += my_bordersize*2;
	r.my_height += my_bordersize*2;

	r.my_xpos += my_xpos;
	r.my_ypos += my_ypos;

	PG_ThemeWidget::eventBlit(srf, src, dst);
	//  TO-DO : This doesn`t work in 3th or more level widgets ...
	//	DrawBorder(r, my_bordersize);
}

void PG_WidgetList::eventSizeWidget(Uint16 w, Uint16 h) {

	PG_ThemeWidget::eventSizeWidget(w,h);

	my_rectList.SetRect(
	    my_bordersize,
	    my_bordersize,
	    w - my_widthScrollbar - my_bordersize*2,
	    h - my_heightHorizontalScrollbar - my_bordersize*2);

	my_rectVerticalScrollbar.SetRect(
	    w - my_widthScrollbar,
	    0,
	    my_widthScrollbar,
	    h);

	my_rectHorizontalScrollbar.SetRect(
	    0,
	    h - my_heightHorizontalScrollbar,
	    w,
	    my_heightHorizontalScrollbar);

	my_objVerticalScrollbar->MoveWidget(my_rectVerticalScrollbar.my_xpos, my_rectVerticalScrollbar.my_ypos);
	my_objVerticalScrollbar->SizeWidget(my_rectVerticalScrollbar.my_width, my_rectVerticalScrollbar.my_height);

	my_objHorizontalScrollbar->MoveWidget(my_rectHorizontalScrollbar.my_xpos, my_rectHorizontalScrollbar.my_ypos);
	my_objHorizontalScrollbar->SizeWidget(my_rectHorizontalScrollbar.my_width, my_rectHorizontalScrollbar.my_height);

	CheckScrollBars();
}

bool PG_WidgetList::eventScrollPos(int id, PG_Widget* widget, unsigned long data) {
	if(widget == my_objVerticalScrollbar) {
		ScrollToY(data);
		return true;
	}

	if(widget == my_objHorizontalScrollbar) {
		ScrollToX(data);
		return true;
	}

	return true; //PG_ThemeWidget::eventScrollPos(id, widget, data);
}

bool PG_WidgetList::eventScrollTrack(int id, PG_Widget* widget, unsigned long data) {
	if(widget == my_objVerticalScrollbar) {
		ScrollToY(data);
		return true;
	}

	if(widget == my_objHorizontalScrollbar) {
		ScrollToX(data);
		return true;
	}

	return true; // PG_ThemeWidget::eventScrollTrack(id, widget, data);
}

void PG_WidgetList::eventShow() {
	CheckScrollBars();
}

void PG_WidgetList::AddWidget(PG_Widget* w) {
	if(w == NULL) {
		return;
	}

	w->SetVisible(false);
	AddChild(w);

	if(my_widgetList.empty()) {
		my_listheight = w->Height() + w->my_ypos;
	} else {
		my_listheight += (w->Height() +  + w->my_ypos);
	}

	if (((w->Width() + w->my_xpos) > 0) && (Uint32(w->Width() + w->my_xpos) > my_listwidth)) {
		my_listwidth = w->Width() + w->my_xpos;
	}

	if(my_widgetCount == 0) {
		w->MoveWidget(w->my_xpos + my_bordersize, my_listheight - w->my_height + my_bordersize);
	}
	else {
		PG_Widget* last = my_widgetList[my_widgetCount - 1];
		w->MoveWidget(w->my_xpos + my_bordersize, (last->y - my_ypos) + last->h + w->my_ypos);
	}

	my_widgetList.insert(my_widgetList.end(), w);
	my_widgetCount++;

	GetChildList()->BringToFront(my_objVerticalScrollbar);
	GetChildList()->BringToFront(my_objHorizontalScrollbar);
	UpdateScrollBarsPos();

	if(IsVisible()) {
		CheckScrollBars();
		w->SetVisible(true);
		Update();
	}
}

void PG_WidgetList::DeleteAll() {
	if(my_widgetList.size() == 0) {
		return;
	}
	
	std::vector<PG_Widget*>::iterator list = my_widgetList.begin();
	PG_Widget* w = NULL;

	while(list != my_widgetList.end()) {
		w = *list;
		delete w;
		my_widgetList.erase(list);
		list = my_widgetList.begin();
	}

	RemoveAll();
}

void PG_WidgetList::RemoveAll() {
	my_listheight = my_listwidth = 0;
	my_widgetCount = 0;
	my_widgetList.clear();
	ScrollToY(0);
	ScrollToX(0);
}



Sint32 PG_WidgetList::ScrollToY(Sint32 position) {

	PG_Rect r;
	int addheight = ((my_objHorizontalScrollbar->IsVisible()) ? my_heightHorizontalScrollbar : 0);

	if(position > Sint32(my_listheight - Height() + addheight)) {
		position  = my_listheight - Height() + addheight;
	}

	if(position < 0)
		position = 0;

	my_internaldata->my_scrolldeltay -= position;

	for(int i=0; i<my_widgetCount; i++) {
		r = *(my_widgetList[i]);

		r.my_ypos += my_internaldata->my_scrolldeltay;
		if(r.my_ypos < -32000) {
			r.my_ypos = -32000;
		} else if (r.my_ypos > 32000) {
			r.my_ypos = 32000;
		}

		my_widgetList[i]->MoveRect(r.my_xpos, r.my_ypos);
	}

	Update();
	my_internaldata->my_scrolldeltay = position;
	return position;
}

Sint32 PG_WidgetList::ScrollToX(Sint32 position) {

	PG_Rect r;
	int addwidth = ((my_objVerticalScrollbar->IsVisible()) ? my_widthScrollbar : 0);

	if(position > Sint32(my_listwidth - Width() + addwidth)) {
		position  = my_listwidth - Width() + addwidth;
	}

	if(position < 0)
		position = 0;

	my_internaldata->my_scrolldeltax -= position;

	for(int i=0; i<my_widgetCount; i++) {
		r = *(my_widgetList[i]);

		r.my_xpos += my_internaldata->my_scrolldeltax;
		if(r.my_xpos < -32000) {
			r.my_xpos = -32000;
		} else if (r.my_xpos > 32000) {
			r.my_xpos = 32000;
		}

		my_widgetList[i]->MoveRect(r.my_xpos, r.my_ypos);
	}

	Update();
	my_internaldata->my_scrolldeltax = position;
	return position;
}

PG_Widget* PG_WidgetList::GetWidgetFromPos(Sint32 y) {
	Uint32 dy = 0;
	Uint32 min_dy = 100000000;

	PG_Widget* result = NULL;

	for(int i=0; i<my_widgetCount; i++) {
		dy = abs(0- (my_widgetList[i]->my_ypos - my_ypos));

		if(dy < min_dy) {
			min_dy = dy;
			result = my_widgetList[i];
		}
	}

	return result;
}

bool PG_WidgetList::RemoveWidget(PG_Widget* w, bool shiftx, bool shifty) {
	std::vector<PG_Widget*>::iterator wi = my_widgetList.begin();
	std::vector<PG_Widget*>::iterator ri = my_widgetList.end();

	PG_Widget* widget = NULL;

	PG_Point ref1 = ScreenToClient(w->x + w->w, w->y + w->h);

	while (wi != my_widgetList.end()) {
		widget = *wi;
		PG_Point ref2 = ScreenToClient(widget->x, widget->y);

		// check if i should move the widget (x)
		if(shiftx && (ref2.x >= ref1.x)) {
			widget->MoveRect(widget->x - w->w, widget->y);
		}

		// check if i should move the widget (y)
		if(shifty && (ref2.y >= ref1.y)) {
			widget->MoveRect(widget->x, widget->y - w->h);
		}

		if(widget == w) {

			ri = wi;
			w->SetVisible(false);
			w->MoveRect(0,-2000);

			if(shifty) {
				my_listheight -= w->Height();
			}

			my_widgetCount--;

			my_listwidth = 0;
			std::vector<PG_Widget*>::iterator header;

			for (header = my_widgetList.begin(); header < my_widgetList.end(); header++) {
				PG_Point pos = ScreenToClient((*header)->my_xpos, (*header)->my_ypos);

				if ((((*header)->Width() + pos.x) > 0) && (my_listwidth < Uint32((*header)->Width() + pos.x))) {
					my_listwidth = (*header)->Width() + pos.x;
				}
			}

		};

		wi++;
	}

	if(ri != my_widgetList.end()) {
		my_widgetList.erase(ri);
	}

	if(my_listheight >= (Uint32)Height()) {
		ScrollToY(my_firstWidget);
	} else {
		ScrollToY(0);
	}

	if(my_listwidth >= (Uint32)Width()) {
		ScrollToX(my_firstWidget);
	} else {
		ScrollToX(0);
	}

	UpdateScrollBarsPos();

	if(IsVisible()) {
		CheckScrollBars();
		Update();
	}

	return true;
}

bool PG_WidgetList::RemoveWidgetAt(int index, bool shiftx, bool shifty) {
	return RemoveWidget(FindWidget(index), shiftx, shifty);
}

bool PG_WidgetList::DeleteWidget(PG_Widget* w, bool shiftx, bool shifty) {

	if(!RemoveWidget(w, shiftx, shifty)) {
		return false;
	}

	delete w;

	return true;
}

bool PG_WidgetList::DeleteWidgetAt(int index) {
	return DeleteWidget(FindWidget(index));
}

PG_Widget* PG_WidgetList::FindWidget(int index) {

	if((index < 0) || (index >= (int)my_widgetList.size())) {
		return NULL;
	}

	return my_widgetList[index];
}

int PG_WidgetList::GetWidgetCount() {
	return my_widgetCount;
}

void PG_WidgetList::UpdateScrollBarsPos() {
	int ls = 0, i;
	PG_ScrollBar *scrollBars[] = { my_objVerticalScrollbar, my_objHorizontalScrollbar };
	Uint32 listsizes[] = { my_listheight, my_listwidth };
	Uint16 sizes[] = { Height(), Width() };
	if(my_widgetCount != 0) {
		for (i = 0; i < 2; i++) {
			ls = listsizes[i] / my_widgetCount;

			if(ls == 0) {
				ls = 1;
			}
			scrollBars[i]->SetLineSize(ls);
			scrollBars[i]->SetRange(0, listsizes[i] - sizes[i]);
			scrollBars[i]->SetPageSize(sizes[i]);
			scrollBars[i]->SetPosition(scrollBars[i]->GetPosition());
		}
	}

}

void PG_WidgetList::CheckScrollBars() {
	my_rectVerticalScrollbar.my_height = Height();
	my_rectHorizontalScrollbar.my_width = Width();

	if(my_listheight > (Uint32)Height()) {
		my_objVerticalScrollbar->SetVisible(my_enableVerticalScrollbar);
	} else {
		my_objVerticalScrollbar->SetVisible(false);
	}

	if(my_listwidth > (Uint32)(Width() - ((my_objVerticalScrollbar->IsVisible()) ? my_widthScrollbar : 0))) {
		my_objHorizontalScrollbar->SetVisible(my_enableHorizontalScrollbar);

		if(my_listheight > (Uint32)(Height() - my_heightHorizontalScrollbar)) {
			my_objVerticalScrollbar->SetVisible(my_enableVerticalScrollbar);
		}

		if ((my_enableHorizontalScrollbar) && (my_objVerticalScrollbar->IsVisible())) {
			my_rectVerticalScrollbar.my_height -= my_heightHorizontalScrollbar;
			my_rectHorizontalScrollbar.my_width -= my_widthScrollbar;
		}
	} else {
		my_objHorizontalScrollbar->SetVisible(false);
	}

	if (my_objVerticalScrollbar->IsVisible()) {
		my_objVerticalScrollbar->SetRange(0, my_listheight - Height() + my_heightHorizontalScrollbar);
	}
	if (my_objHorizontalScrollbar->IsVisible()) {
		my_objHorizontalScrollbar->SetRange(0, my_listwidth - Width() + my_widthScrollbar);
	}

	my_objVerticalScrollbar->SizeWidget(my_widthScrollbar, my_rectVerticalScrollbar.my_height);
	my_objHorizontalScrollbar->SizeWidget(my_rectHorizontalScrollbar.my_width, my_heightHorizontalScrollbar);
}

void PG_WidgetList::EnableScrollBar(bool enable, int direction) {
	if (direction == PG_SB_VERTICAL) {
		my_enableVerticalScrollbar = enable;
	} else if (direction == PG_SB_HORIZONTAL) {
		my_enableHorizontalScrollbar = enable;
	}
	CheckScrollBars();

	if ((!my_enableVerticalScrollbar) && (direction == PG_SB_VERTICAL)) {
		my_widthScrollbar = 0;
		SizeWidget(Width(), Height());
	} else if ((!my_enableHorizontalScrollbar) && (direction == PG_SB_HORIZONTAL)) {
		my_heightHorizontalScrollbar = 0;
		SizeWidget(Width(), Height());
	}
}

void PG_WidgetList::ScrollTo(PG_Widget* widget, int direction) {
	if(my_widgetCount == 0) {
		return;
	}

	if (direction == PG_SB_VERTICAL) {
		int ypos = widget->y - FindWidget(0)->y;

		ypos = ScrollToY(ypos);
		my_objVerticalScrollbar->SetPosition(ypos);
	} else if (direction == PG_SB_HORIZONTAL) {
		int xpos = widget->x - FindWidget(0)->x;

		xpos = ScrollToX(xpos);
		my_objHorizontalScrollbar->SetPosition(xpos);
	}
}

void PG_WidgetList::ScrollTo(int index, int direction) {
	PG_Widget* w = FindWidget(index);

	if(w == NULL) {
		return;
	}

	ScrollTo(w, direction);
}
