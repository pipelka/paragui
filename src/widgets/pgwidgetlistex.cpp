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
    Update Date:      $Date: 2002/04/15 13:22:16 $
    Source File:      $Source: /sources/paragui/paragui/src/widgets/pgwidgetlistex.cpp,v $
    CVS/RCS Revision: $Revision: 1.1 $
    Status:           $State: Exp $
*/

#include "pgwidgetlistex.h"

PG_WidgetListEx::PG_WidgetListEx(PG_Widget* parent, const PG_Rect& r, const char* style) :
PG_WidgetList(parent, r, style) {}

/**  */
void PG_WidgetListEx::AddWidget(PG_Widget* w) {
	if(w == NULL) {
		return;
	}

	w->SetVisible(false);
	AddChild(w);

	if (((w->Width() + w->my_xpos) > 0) && (Uint32(w->Height() + w->my_ypos) > my_listheight)) {
		my_listheight = w->Height() + w->my_ypos;
	}
	if (((w->Width() + w->my_ypos) > 0) && (Uint32(w->Width() + w->my_xpos) > my_listwidth)) {
		my_listwidth = w->Width() + w->my_xpos;
	}

	w->MoveWidget(w->my_xpos + my_bordersize, w->my_ypos + my_bordersize);

	my_widgetList.insert(my_widgetList.end(), w);
	my_widgetCount++;

	UpdateScrollBarsPos();

	if(IsVisible()) {
		CheckScrollBars();
		w->SetVisible(true);
		Update();
	}

	GetChildList()->BringToFront(my_objVerticalScrollbar);
	GetChildList()->BringToFront(my_objHorizontalScrollbar);
}

bool PG_WidgetListEx::RemoveWidget(PG_Widget* w, bool shiftx, bool shifty) {
	std::vector<PG_Widget*>::iterator wi = my_widgetList.begin();
	PG_Widget* widget = NULL;

	while (wi != my_widgetList.end()) {
		widget = *wi;

		if(widget == w) {
			my_widgetList.erase(wi);
			w->SetVisible(false);
			my_widgetCount--;

			if(shiftx)
				my_listwidth = 0;
			if(shifty)
				my_listheight = 0;

			for (std::vector<PG_Widget*>::iterator header = my_widgetList.begin(); header < my_widgetList.end(); header++) {

				PG_Point pos = ScreenToClient((*header)->
				                              my_xpos, (*header)->my_ypos);

				if(shiftx) {
					if ((((*header)->Width() + pos.x) > 0) && (my_listwidth < Uint32((*header)->Width() + pos.x))) {

						my_listwidth = (*header)->Width() + pos.x;

					}
				}

				if(shifty) {
					if ((((*header)->Height() + pos.y) > 0) && (my_listheight < Uint32((*header)->Height() + pos.y))) {

						my_listheight = (*header)->Height() + pos.y;
					}
				}

			}

			if(my_listheight >= (Uint32)Height()) {
				ScrollToY(my_firstWidget)
				;
			} else {
				ScrollToY(0);
			}

			if(my_listwidth >= (Uint32)Width()) {
				ScrollToX(my_firstWidget)
				;
			} else {
				ScrollToX(0);
			}

			UpdateScrollBarsPos();
			if(IsVisible()) {
				CheckScrollBars()
				;
				Update();
			}

			return true;
		};

		wi++;
	}

	return false;
}
