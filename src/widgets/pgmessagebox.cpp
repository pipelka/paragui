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
    Update Date:      $Date: 2003/12/02 15:27:59 $
    Source File:      $Source: /sources/paragui/paragui/src/widgets/pgmessagebox.cpp,v $
    CVS/RCS Revision: $Revision: 1.3.2.2 $
    Status:           $State: Exp $
*/

#include "pgmessagebox.h"
#include "pglog.h"
#include "pgwindow.h"
#include "pgrichedit.h"

//create PopUp and 2 Buttons
PG_MessageBox::PG_MessageBox(PG_Widget* parent, const PG_Rect& r, const char* windowtitle, const char* windowtext, const PG_Rect& btn1, const char* btn1text, const PG_Rect& btn2, const char* btn2text, PG_Label::TextAlign textalign, const char* style) :
PG_Window(parent, r, windowtitle, MODAL) {

	my_btnok = new PG_Button(this, 1, btn1, btn1text);
	my_btnok->sigClick.connect(slot(*this, &PG_MessageBox::handleButton));
	
	my_btncancel = new PG_Button(this, 2, btn2, btn2text);
	my_btncancel->sigClick.connect(slot(*this, &PG_MessageBox::handleButton));

	Init(windowtext, textalign, style);
}

PG_MessageBox::PG_MessageBox(PG_Widget* parent, const PG_Rect& r, const char* windowtitle, const char* windowtext, const PG_Rect& btn1, const char* btn1text, PG_Label::TextAlign textalign, const char* style) :
PG_Window(parent, r, windowtitle, MODAL) {

	my_btnok = new PG_Button(this, 1, btn1, btn1text);
	my_btnok->sigClick.connect(slot(*this, &PG_MessageBox::handleButton));
	my_btncancel = NULL;

	Init(windowtext, textalign, style);
}

//Delete the Buttons
PG_MessageBox::~PG_MessageBox() {
	delete my_btnok;
	delete my_btncancel;
}

void PG_MessageBox::Init(const char* windowtext, int textalign, const char* style) {
	buttonflag=0;

	my_textbox = new PG_RichEdit(this, PG_Rect(10, 40, my_width-20, my_height-50));
	my_textbox->SetTransparency(255);
	my_textbox->SetText(windowtext);

	my_msgalign = textalign;

	LoadThemeStyle(style);
}

void PG_MessageBox::LoadThemeStyle(const char* widgettype) {
	PG_Window::LoadThemeStyle(widgettype);

	my_btnok->LoadThemeStyle(widgettype, "Button1");
	if(my_btncancel) {
		my_btncancel->LoadThemeStyle(widgettype, "Button2");
	}
}

//Event?
bool PG_MessageBox::handleButton(PG_Button* button) {
	PG_LogDBG("PG_MessageBox::handleButton()");

	//Set Buttonflag to ButtonID
	buttonflag = button->GetID();
	QuitModal();
	return true;
}

int PG_MessageBox::WaitForClick() {
	RunModal();
	return buttonflag;
}
