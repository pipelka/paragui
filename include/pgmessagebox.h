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
    Update Date:      $Date: 2004/02/21 10:11:15 $
    Source File:      $Source: /sources/paragui/paragui/include/pgmessagebox.h,v $
    CVS/RCS Revision: $Revision: 1.3.2.3 $
    Status:           $State: Exp $
*/

#ifndef PG_MESSAGEBOX_H
#define PG_MESSAGEBOX_H

#include "paragui.h"
#include "pglabel.h"
#include "pgwindow.h"

class PG_Button;
class PG_RichEdit;

/**
	@author Thomas Bamesberger
*/

class DECLSPEC PG_MessageBox : public PG_Window {
public:
	/**
	Creates a PopUp with 2 Buttons
		
	@param parent Parent widget
	@param r rectangle of PopUp
	@param windowtitle Title of window
	@param windowtext Text to appear in window
	@param btn1 Struct PG_Rect to create Button 1
	@param btn1text Text to appear in Button 1
	@param btn2 Struct PG_Rect to create Button 2
	@param btn2text Text to appear in Button 2
	@param textalign Alignment for windowtext
	@param style widgetstyle to use (default "MessageBox")
	*/
	PG_MessageBox(PG_Widget* parent, const PG_Rect& r, const char* windowtitle, const char* windowtext, const PG_Rect& btn1, const char* btn1text, const PG_Rect& btn2, const char* btn2text, PG_Label::TextAlign textalign = PG_Label::CENTER, const char* style="MessageBox");

	/**
	Creates a PopUp with 1 Button

	@param parent Parent widget
	@param r rectangle of PopUp
	@param windowtitle Title of window
	@param windowtext Text to appear in window
	@param btn1 Struct PG_Rect to create Button 1
	@param btn1text Text to appear in Button 1
	@param textalign Alignment for windowtext
	@param style widgetstyle to use (default "MessageBox")
	*/
	PG_MessageBox(PG_Widget* parent, const PG_Rect& r, const char* windowtitle, const char* windowtext, const PG_Rect& btn1, const char* btn1text, PG_Label::TextAlign textalign = PG_Label::CENTER, const char* style="MessageBox");

	/**
	Destructor
	*/
	~PG_MessageBox();

	void LoadThemeStyle(const char* widgettype);

	/**
	Waits for a button click and returns Button ID
	*/
	int WaitForClick();

protected:

	/**
	Checks if button is pressed

	@param button pointer to PG_BUtton
	*/
	bool handleButton(PG_Button* button);

	/**
	Buttonflag is set to ButtonID, if a button is clicked
	*/
	int buttonflag;

	PG_Button* my_btnok;
	PG_Button* my_btncancel;

private:

	PG_RichEdit* my_textbox;
	int my_msgalign;

	void Init(const char* windowtext, int textalign, const char* style) ;
};

#endif //PG_MESSAGEBOX_H
