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
    Update Date:      $Date: 2003/11/24 09:17:22 $
    Source File:      $Source: /sources/paragui/paragui/src/widgets/pglabel.cpp,v $
    CVS/RCS Revision: $Revision: 1.3.6.1.2.1 $
    Status:           $State: Exp $
*/

#include "paragui.h"
#include "pglabel.h"

PG_Label::PG_Label(PG_Widget* parent, const PG_Rect& r, const char* text, const char* style) :
PG_Widget(parent, r) {

	my_alignment = PG_TA_CENTER;
	my_srfIcon = NULL;
	my_indent = 0;
	my_freeicon = false;

	SetText(text);
	LoadThemeStyle(style);
}

PG_Label::~PG_Label() {
	if(my_freeicon) {
		PG_Application::UnloadSurface(my_srfIcon); // false
	}
}

void PG_Label::LoadThemeStyle(const char* style) {
	PG_Label::LoadThemeStyle("Label", "Label");
	PG_Label::LoadThemeStyle(style, "Label");
}

void PG_Label::LoadThemeStyle(const char* widgettype, const char* object) {
	PG_Theme* t = PG_Application::GetTheme();

	const char* s = t->FindString(widgettype, object, "label");

	if(s != NULL) {
		SetText(s);
	}

	t->GetProperty(widgettype, object, "alignment", my_alignment);

	PG_Widget::LoadThemeStyle(widgettype, object);
}

void PG_Label::eventBlit(SDL_Surface* srf, const PG_Rect& src, const PG_Rect& dst) {
	int xshift = my_indent;

	// should we blit an icon ?
	if(my_srfIcon != NULL) {
		xshift = my_srfIcon->w + my_indent;

		PG_Rect icon_rect(
		    my_xpos + my_indent,
		    my_ypos + (my_height - my_srfIcon->h)/2,
		    my_srfIcon->w,
		    my_srfIcon->h);

		PG_Rect icon_src;
		PG_Rect icon_dst;

		GetClipRects(icon_src, icon_dst, icon_rect);

		PG_Widget::eventBlit(my_srfIcon, icon_src, icon_dst);
	}

	Uint16 wl;
	Uint16 hl;

	GetTextSize(wl, hl);

	switch (my_alignment) {
		case PG_TA_LEFT:
			my_rectLabel.my_xpos = xshift;
			my_rectLabel.my_ypos = (my_height - hl) >> 1;
			break;

		case PG_TA_RIGHT:
			my_rectLabel.my_xpos = (my_width - wl);
			my_rectLabel.my_ypos = (my_height - hl) >> 1;
			break;

		case PG_TA_CENTER:
			my_rectLabel.my_xpos = (my_width - wl) >> 1;
			my_rectLabel.my_ypos = (my_height - hl) >> 1;
			break;
	}

	DrawText(my_rectLabel, my_text.c_str());
}

/**  */
void PG_Label::eventDraw(SDL_Surface* surface, const PG_Rect& rect) {}

void PG_Label::SetAlignment(int a) {
	my_alignment = a;
	Update();
}

SDL_Surface* PG_Label::SetIcon(SDL_Surface* icon) {

	if((icon != my_srfIcon)  && my_freeicon){
		PG_Application::UnloadSurface(my_srfIcon);
	}

	my_srfIcon = icon;
	my_freeicon = false;
	Update();

	return my_srfIcon;
}

SDL_Surface* PG_Label::SetIcon(const char* filename) {
	if(my_freeicon){
		PG_Application::UnloadSurface(my_srfIcon);
	}

	my_srfIcon = PG_Application::LoadSurface(filename);
	my_freeicon = true;
	Update();

	return my_srfIcon;
}

SDL_Surface* PG_Label::GetIcon() {
	return my_srfIcon;
}

void PG_Label::SetIndent(int indent) {
	my_indent = indent;
}
