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
    Source File:      $Source: /sources/paragui/paragui/src/widgets/pgcheckbutton.cpp,v $
    CVS/RCS Revision: $Revision: 1.2 $
    Status:           $State: Exp $
*/

#include "pgcheckbutton.h"

PG_CheckButton::PG_CheckButton(PG_Widget* parent, int id, const PG_Rect& r, const char* text, const char* style)
        : PG_RadioButton(parent, id, r, text, NULL)
{
	LoadThemeStyle(style);
	my_widgetButton->LoadThemeStyle(style, "CheckKnob");

	SetUnpressed();
}

PG_CheckButton::~PG_CheckButton() {}

bool PG_CheckButton::eventMouseButtonUp(const SDL_MouseButtonEvent* my_widgetButton) {

	if(my_isPressed) {
		SetUnpressed();
	} else {
		SetPressed();
	}

	return true;
}

bool PG_CheckButton::eventButtonClick(int id, PG_Widget* widget) {
	return false;
}

void PG_CheckButton::SetUnpressed() {
	my_widgetButton->SetPressed(false);
	my_isPressed = false;

	Update();

	// Notify parent
	SendMessage(GetParent(), MSG_BUTTONCLICK, (MSG_ID)GetID(), (MSG_DATA)0);
}
