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
    Source File:      $Source: /sources/paragui/paragui/src/widgets/pgslider.cpp,v $
    CVS/RCS Revision: $Revision: 1.2 $
    Status:           $State: Exp $
*/

#include "pgslider.h"
#include "pgapplication.h"

PG_Slider::PG_Slider(PG_Widget* parent, int id, const PG_Rect& r, int direction, const char* style) : PG_ScrollBar(parent, id, r, direction) {

	my_showButtons = false;

	if(sb_direction == PG_SB_VERTICAL) {
		my_sliderSize = r.my_width;
		position[3].h = r.my_width;
	} else {
		my_sliderSize = r.my_height;
		position[3].w = r.my_height;
	}

	LoadThemeStyle(style);

	dragbutton->SizeWidget(position[3].w, position[3].h);
	dragbutton->SetTickMode(true);

	if(!my_showButtons) {

		position[0].w = 0;
		position[0].h = 0;
		position[1].w = 0;
		position[1].h = 0;

		position[2].x = 0;
		position[2].y = 0;
		position[2].w = r.my_width;
		position[2].h = r.my_height;

		delete scrollbutton[0];
		scrollbutton[0] = NULL;

		delete scrollbutton[1];
		scrollbutton[1] = NULL;

		SetPosition(scroll_min);
	}
}

PG_Slider::~PG_Slider() {}

void PG_Slider::LoadThemeStyle(const char* widgettype) {
	int b;
	PG_Theme* t = PG_Application::GetTheme();

	//PG_ScrollBar::LoadThemeStyle(widgettype);

	if(sb_direction == PG_SB_VERTICAL) {
		b = t->FindProperty(widgettype, "SliderDragV", "height");
		if(b != -1) {
			position[3].h = b;
			my_sliderSize = b;
		}

		scrollbutton[0]->LoadThemeStyle(widgettype, "SliderUp");
		scrollbutton[1]->LoadThemeStyle(widgettype, "SliderDown");
	} else {
		b = t->FindProperty(widgettype, "SliderDragH", "width");
		if(b != -1) {
			position[3].w = b;
			my_sliderSize = b;
		}

		scrollbutton[0]->LoadThemeStyle(widgettype, "SliderLeft");
		scrollbutton[1]->LoadThemeStyle(widgettype, "SliderRight");
	}

	dragbutton->LoadThemeStyle(widgettype, "SliderDrag");

	if(sb_direction == PG_SB_VERTICAL) {
		dragbutton->LoadThemeStyle(widgettype, "SliderDragV");
		PG_ThemeWidget::LoadThemeStyle(widgettype, "SliderV");
	} else {
		dragbutton->LoadThemeStyle(widgettype, "SliderDragH");
		PG_ThemeWidget::LoadThemeStyle(widgettype, "SliderH");
	}

}

bool PG_Slider::eventMouseButtonUp(const SDL_MouseButtonEvent* button) {

	switch(button->button) {
		case 4:
			if(scroll_current <= scroll_min + my_linesize) {
				SetPosition(scroll_min);
			} else {
				SetPosition(scroll_current - my_linesize);
			}
			break;

		case 5:
			SetPosition(scroll_current + my_linesize);
			break;
	}

	SendMessage(GetParent(), MSG_SCROLLTRACK, GetID(), scroll_current);

	return true;
}

void PG_Slider::eventSizeWidget(Uint16 w, Uint16 h) {
	PG_ScrollBar::eventSizeWidget(w, h);

	if(!my_showButtons) {

		position[0].w = 0;
		position[0].h = 0;
		position[1].w = 0;
		position[1].h = 0;

		position[2].x = 0;
		position[2].y = 0;
		position[2].w = w;
		position[2].h = h;
	}

	if(sb_direction == PG_SB_VERTICAL) {
		position[3].h = my_sliderSize;
	} else {
		position[3].w = my_sliderSize;
	}

	dragbutton->SizeWidget(position[3].w, position[3].h);
}
