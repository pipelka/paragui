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
    Update Date:      $Date: 2004/02/13 12:20:49 $
    Source File:      $Source: /sources/paragui/paragui/src/widgets/pglistboxitem.cpp,v $
    CVS/RCS Revision: $Revision: 1.5.4.1.2.3 $
    Status:           $State: Exp $
*/

#include "pglistboxitem.h"
#include "pglistbox.h"
#include "pgapplication.h"
#include "pgtheme.h"

PG_ListBoxItem::PG_ListBoxItem(int height, const char* text, SDL_Surface* icon, void* userdata, const char* style) : PG_ListBoxBaseItem(height, userdata) {
	
	for(int i=0; i<3; i++) {
		my_background[i] = NULL;
		my_bkmode[i] = BKMODE_TILE;
		my_blend[i] = 0;
		my_gradient[i] = NULL;
	}

	SetText(text);
	LoadThemeStyle(style, "ListBoxItem");

	my_srfHover = NULL;
	my_srfSelected = NULL;
	
	my_srfIcon = icon;
}

PG_ListBoxItem::~PG_ListBoxItem() {
	PG_ThemeWidget::DeleteThemedSurface(my_srfHover);
	PG_ThemeWidget::DeleteThemedSurface(my_srfSelected);
}

void PG_ListBoxItem::eventSizeWidget(Uint16 w, Uint16 h) {
	PG_ThemeWidget::DeleteThemedSurface(my_srfHover);
	PG_ThemeWidget::DeleteThemedSurface(my_srfSelected);

	my_srfHover = PG_ThemeWidget::CreateThemedSurface(
	                  PG_Rect(0, 0, w, my_itemheight),
	                  my_gradient[2],
	                  my_background[2],
	                  my_bkmode[2],
	                  my_blend[2]);

	my_srfSelected = PG_ThemeWidget::CreateThemedSurface(
	                     PG_Rect(0, 0, w, my_itemheight),
	                     my_gradient[1],
	                     my_background[1],
	                     my_bkmode[1],
	                     my_blend[1]);
}

void PG_ListBoxItem::eventBlit(SDL_Surface* srf, const PG_Rect& src, const PG_Rect& dst) {
	SDL_Surface* temp = NULL;

	if((dst.my_width == 0) || (dst.my_height == 0)) {
		return;
	}

	PG_Rect my_src = src;
	PG_Rect my_dst = dst;

	temp = NULL;

	if(my_srfHover == NULL) {
		my_srfHover = PG_ThemeWidget::CreateThemedSurface(
						  PG_Rect(0, 0, my_width, my_itemheight),
						  my_gradient[2],
						  my_background[2],
						  my_bkmode[2],
						  my_blend[2]);
	}
	
	if(my_srfSelected == NULL) {
		my_srfSelected = PG_ThemeWidget::CreateThemedSurface(
							 PG_Rect(0, 0, my_width, my_itemheight),
							 my_gradient[1],
							 my_background[1],
							 my_bkmode[1],
							 my_blend[1]);
	}

	if(my_selected) {
		PG_Widget::eventBlit(my_srfSelected, src, dst);
	}
	else if(my_hover) {
		PG_Widget::eventBlit(my_srfHover, src, dst);
	}

	PG_Label::eventBlit(NULL, my_src, my_dst);
}

void PG_ListBoxItem::LoadThemeStyle(const char* widgettype, const char* objectname) {
	static char prop[80];
	PG_Theme* t = PG_Application::GetTheme();

	for(int i=0; i<3; i++) {
		sprintf(prop, "background%i", i);
		my_background[i] = t->FindSurface(widgettype, objectname, prop);

		sprintf(prop, "blend%i", i);
		t->GetProperty(widgettype, objectname, prop, my_blend[i]);

		sprintf(prop, "backmode%i", i);
		t->GetProperty(widgettype, objectname, prop, my_bkmode[i]);

		sprintf(prop, "gradient%i", i);
		PG_Gradient* g = t->FindGradient(widgettype, objectname, prop);

		if(g) {
			my_gradient[i] = g;
		}

	}
	
	PG_Color fontcolor(0xFFFFFF);
	t->GetColor(widgettype, objectname, "textcolor", fontcolor);
	SetFontColor(fontcolor);
}
