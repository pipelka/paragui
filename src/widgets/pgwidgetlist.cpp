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
    Update Date:      $Date: 2004/03/03 13:12:17 $
    Source File:      $Source: /sources/paragui/paragui/src/widgets/pgwidgetlist.cpp,v $
    CVS/RCS Revision: $Revision: 1.3.6.9.2.12 $
    Status:           $State: Exp $
*/

#include "pgwidgetlist.h"
#include "pgapplication.h"
#include "pglog.h"

struct PG_WidgetListDataInternal{
};

PG_WidgetList::PG_WidgetList(PG_Widget* parent, const PG_Rect& r, const char* style) : PG_ThemeWidget(parent, r, style),
my_objVerticalScrollbar(NULL),
my_objHorizontalScrollbar(NULL) ,
my_scrollarea(NULL)
{
	my_enableVerticalScrollbar = true;
	my_enableHorizontalScrollbar = false;
	my_widthScrollbar = my_heightHorizontalScrollbar = 5;

	my_internaldata = new PG_WidgetListDataInternal;

	// It is important to make sure that the substractions below won't
	// render values < 0 and, eventually,
	// surface widths such as 32768 or 65535 when cast to an unsigned type.
	// This can lead to segfaults later on in, for example, DrawGradient...
	if (my_widthScrollbar > r.my_width)
		my_widthScrollbar = r.my_width;
	    
	if (my_heightHorizontalScrollbar > r.my_height)
		my_heightHorizontalScrollbar = r.my_height;

	my_objVerticalScrollbar = new PG_ScrollBar(this, PG_Rect(0,0,my_widthScrollbar,r.h), PG_ScrollBar::VERTICAL, IDWIDGETLIST_SCROLL, style);
	my_objVerticalScrollbar->SetRange(0,0);
	my_widthScrollbar = my_objVerticalScrollbar->Width();
	my_objVerticalScrollbar->Hide();
	my_objVerticalScrollbar->sigScrollPos.connect(slot(*this, &PG_WidgetList::handleScrollPos));
	my_objVerticalScrollbar->sigScrollTrack.connect(slot(*this, &PG_WidgetList::handleScrollTrack));
	
	my_objHorizontalScrollbar = new PG_ScrollBar(this, PG_Rect(0,0,r.w, my_heightHorizontalScrollbar), PG_ScrollBar::HORIZONTAL, IDWIDGETLIST_SCROLL, style);
	my_objHorizontalScrollbar->SetRange(0,0);
	my_heightHorizontalScrollbar = my_objHorizontalScrollbar->Height();
	my_objHorizontalScrollbar->Hide();
	my_objHorizontalScrollbar->sigScrollPos.connect(slot(*this, &PG_WidgetList::handleScrollPos));
	my_objHorizontalScrollbar->sigScrollTrack.connect(slot(*this, &PG_WidgetList::handleScrollTrack));

	my_scrollarea = new PG_ScrollArea(this);
	my_scrollarea->sigAreaChangedHeight.connect(slot(*this, &PG_WidgetList::handleAreaChangedHeight));
	my_scrollarea->sigAreaChangedWidth.connect(slot(*this, &PG_WidgetList::handleAreaChangedWidth));
	my_scrollarea->SetShiftOnRemove(false, true);

	if(strcmp(style, "WidgetList") != 0) {
		LoadThemeStyle("WidgetList");
	}
	LoadThemeStyle(style);
}

PG_WidgetList::~PG_WidgetList() {
	my_scrollarea->DeleteAll();
	delete my_internaldata;
}

void PG_WidgetList::RecalcPositions(bool bV, bool bH) {

	// only vertical
	if(bV && !bH) {
		my_rectVerticalScrollbar.SetRect(
			my_width - (my_widthScrollbar + my_bordersize),
			my_bordersize,
			my_widthScrollbar,
			my_height - my_bordersize*2);
		my_rectHorizontalScrollbar.SetRect(0,0,0,0);
	}

	// only horizontal
	if(!bV && bH) {
		my_rectHorizontalScrollbar.SetRect(
			my_bordersize,
			my_height - (my_heightHorizontalScrollbar + my_bordersize),
			my_width - my_bordersize*2,
			my_heightHorizontalScrollbar);
		my_rectVerticalScrollbar.SetRect(0,0,0,0);
	}

	// both
	if(bV && bH) {
		my_rectVerticalScrollbar.SetRect(
			my_width - (my_widthScrollbar + my_bordersize),
			my_bordersize,
			my_widthScrollbar,
			my_height - (my_heightHorizontalScrollbar + my_bordersize*2));

		my_rectHorizontalScrollbar.SetRect(
			my_bordersize,
			my_height - (my_heightHorizontalScrollbar + my_bordersize),
			my_width - (my_widthScrollbar+my_bordersize*2),
			my_heightHorizontalScrollbar);
	}

	// scrollarea
	my_rectList.SetRect(
			my_bordersize, my_bordersize,
			my_width - (my_rectVerticalScrollbar.w + my_bordersize*2),
			my_height - (my_rectHorizontalScrollbar.h + my_bordersize*2));

	if(*my_objVerticalScrollbar != my_rectVerticalScrollbar) {
		my_objVerticalScrollbar->MoveWidget(my_rectVerticalScrollbar);
	}

	if(*my_objHorizontalScrollbar != my_rectHorizontalScrollbar) {
		my_objHorizontalScrollbar->MoveWidget(my_rectHorizontalScrollbar);
	}

	if(*my_scrollarea != my_rectList) {
		my_scrollarea->MoveWidget(my_rectList);
	}
}

void PG_WidgetList::LoadThemeStyle(const char* widgettype) {
	PG_ThemeWidget::LoadThemeStyle(widgettype);
	my_objVerticalScrollbar->LoadThemeStyle(widgettype);
	my_objHorizontalScrollbar->LoadThemeStyle(widgettype);

	my_widthScrollbar = my_objVerticalScrollbar->Width();
	my_heightHorizontalScrollbar = my_objHorizontalScrollbar->Height();
	RecalcPositions(my_objVerticalScrollbar->IsVisible(), my_objHorizontalScrollbar->IsVisible());
}

void PG_WidgetList::eventSizeWidget(Uint16 w, Uint16 h) {

	PG_ThemeWidget::eventSizeWidget(w,h);

	if(h != my_height) {
		my_height = h;
		handleAreaChangedHeight(my_scrollarea, GetListHeight());
	}

	if(w != my_width) {
		my_width = w;
		handleAreaChangedWidth(my_scrollarea, GetListWidth());
	}
}

bool PG_WidgetList::handleScrollPos(PG_ScrollBar* widget, long data) {
	if(widget == my_objVerticalScrollbar) {
		my_scrollarea->ScrollTo(my_scrollarea->GetScrollPosX(), data);
		return true;
	}

	if(widget == my_objHorizontalScrollbar) {
		my_scrollarea->ScrollTo(data, my_scrollarea->GetScrollPosY());
		return true;
	}

	return true;
}

bool PG_WidgetList::handleScrollTrack(PG_ScrollBar* widget, long data) {
	if(widget == my_objVerticalScrollbar) {
		my_scrollarea->ScrollTo(my_scrollarea->GetScrollPosX(), data);
		return true;
	}

	if(widget == my_objHorizontalScrollbar) {
		my_scrollarea->ScrollTo(data, my_scrollarea->GetScrollPosY());
		return true;
	}

	return true;
}

void PG_WidgetList::AddChild(PG_Widget* w) {
	if(w == NULL) {
		return;
	}
		
	if (my_objVerticalScrollbar == NULL || my_objHorizontalScrollbar == NULL || my_scrollarea == NULL) {
		PG_Widget::AddChild(w);
		return;
	}

	w->MoveRect(0, w->my_ypos + my_scrollarea->GetAreaHeight());
	my_scrollarea->AddChild(w);
}

PG_Widget* PG_WidgetList::GetWidgetFromPos(Sint32 y) {
	Uint32 dy = 0;
	Uint32 min_dy = 100000000;

	PG_Widget* result = NULL;

	PG_Widget* list = GetChildList()->first();
	for( ; list != NULL; list = list->next()) {
		dy = abs(0- (list->my_ypos - my_ypos));

		if(dy < min_dy) {
			min_dy = dy;
			result = list;
		}
	}

	return result;
}

bool PG_WidgetList::RemoveWidgetAt(int index) {
	return RemoveChild(FindWidget(index));
}

bool PG_WidgetList::DeleteWidgetAt(int index) {
	delete FindWidget(index);
	return true;
}

PG_Widget* PG_WidgetList::FindWidget(int index) {

	if((index < 0) || (index >= GetWidgetCount())) {
		return NULL;
	}

	int i = 0;
	PG_Widget* list = my_scrollarea->GetChildList()->first();
	for( ; list != NULL; list = list->next()) {
		if(i == index) {
			return list;
		}
		i++;
	}

	return NULL;
}

int PG_WidgetList::FindIndex(PG_Widget* w) {
	int index = 0;

	PG_Widget* list = GetChildList()->first();
	for( ; list != NULL; list = list->next()) {
		if(list == w) {
			return index;
		}
		index++;
	}

	return -1;
}

void PG_WidgetList::CheckScrollBars() {
	int ls = 0, i;
	PG_ScrollBar *scrollBars[] = { my_objVerticalScrollbar, my_objHorizontalScrollbar };
	Uint32 listsizes[] = { GetListHeight(), GetListWidth() };
	Uint16 sizes[] = { my_scrollarea->Height(), my_scrollarea->Width() };
	for (i = 0; i < 2; i++) {
		if(GetWidgetCount() != 0) {
			ls = listsizes[i] / GetWidgetCount();

			if(ls == 0) {
				ls = 1;
			}
			scrollBars[i]->SetLineSize(ls);
		}
		else {
			scrollBars[i]->SetLineSize(10);
		}
		scrollBars[i]->SetRange(0, listsizes[i] - sizes[i]);
		scrollBars[i]->SetPageSize(sizes[i]);
		scrollBars[i]->SetPosition(scrollBars[i]->GetPosition());
	}

}

void PG_WidgetList::EnableScrollBar(bool enable, PG_ScrollBar::ScrollDirection direction) {
	if (direction == PG_ScrollBar::VERTICAL) {
		my_enableVerticalScrollbar = enable;
	} else if (direction == PG_ScrollBar::HORIZONTAL) {
		my_enableHorizontalScrollbar = enable;
	}
	RecalcPositions(my_objVerticalScrollbar->IsVisible(), my_objHorizontalScrollbar->IsVisible());
	CheckScrollBars();
}

void PG_WidgetList::ScrollToWidget(PG_Widget* widget, bool bVertical) {
	my_scrollarea->ScrollToWidget(widget, bVertical);
}

void PG_WidgetList::ScrollToWidget(int index, bool bVertical) {
	PG_Widget* w = FindWidget(index);

	if(w == NULL) {
		return;
	}

	ScrollToWidget(w, bVertical);
}

void PG_WidgetList::PageUp() {
	my_scrollarea->ScrollTo(my_scrollarea->GetScrollPosX(), my_scrollarea->GetScrollPosY() - my_height );
}

void PG_WidgetList::PageDown() {
	my_scrollarea->ScrollTo(my_scrollarea->GetScrollPosX(), my_scrollarea->GetScrollPosY() + my_height );
}

Uint16 PG_WidgetList::GetListHeight() {
	return my_scrollarea->GetAreaHeight();
}

Uint16 PG_WidgetList::GetListWidth() {
	return my_scrollarea->GetAreaWidth();
}

Uint16 PG_WidgetList::GetWidgetCount() {
	return my_scrollarea->GetWidgetCount();
}

bool PG_WidgetList::handleAreaChangedHeight(PG_ScrollArea* area, Uint16 h) {
	if(h > my_scrollarea->h && my_enableVerticalScrollbar) {
		RecalcPositions(true, my_objHorizontalScrollbar->IsVisible());
		my_objVerticalScrollbar->Show();
	}
	else {
		my_objVerticalScrollbar->Hide();
		RecalcPositions(false, my_objHorizontalScrollbar->IsVisible());
	}

	Sint32 max_y = my_scrollarea->GetAreaHeight() - my_scrollarea->GetScrollPosY();
	if(max_y < my_scrollarea->my_height) {
		max_y = my_scrollarea->GetAreaHeight() - my_scrollarea->my_height;
		if(max_y < 0) {
			max_y = 0;
		}
		my_scrollarea->ScrollTo(my_scrollarea->GetScrollPosX(), max_y);
	}

	CheckScrollBars();
	return true;
}

bool PG_WidgetList::handleAreaChangedWidth(PG_ScrollArea* area, Uint16 w) {
	if(w > my_scrollarea->w && my_enableHorizontalScrollbar) {
		RecalcPositions(my_objVerticalScrollbar->IsVisible(), true);
		my_objHorizontalScrollbar->Show();
	}
	else {
		my_objHorizontalScrollbar->Hide();
		RecalcPositions(my_objVerticalScrollbar->IsVisible(), false);
	}

	Sint32 max_x = my_scrollarea->GetAreaWidth() - my_scrollarea->GetScrollPosX();
	if(max_x < my_scrollarea->my_width) {
		max_x = my_scrollarea->GetAreaWidth() - my_scrollarea->my_width;
		if(max_x < 0) {
			max_x = 0;
		}
		my_scrollarea->ScrollTo(max_x, my_scrollarea->GetScrollPosY());
	}

	CheckScrollBars();
	return true;
}

PG_Widget* PG_WidgetList::GetFirstInList() {
	return my_scrollarea->GetFirstInList();
}
