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
    Update Date:      $Date: 2002/04/15 13:22:31 $
    Source File:      $Source: /sources/paragui/paragui/include/pgmessagebox.h,v $
    CVS/RCS Revision: $Revision: 1.1 $
    Status:           $State: Exp $
*/

#ifndef PG_MESSAGEBOX_H
#define PG_MESSAGEBOX_H

#ifdef SWIG
%include "swigcommon.h"
%module pgmessagebox
%{
#include "pgmessagebox.h"
    %}
#endif

#include "paragui.h"
#include "pgbutton.h"
#include "pgwindow.h"
#include "pgwidget.h"
#include "pgrichedit.h"

/**
	@author Thomas Bamesberger
*/

class DECLSPEC PG_MessageBox : public PG_Window {
public:
	/**
	Creates a PopUp with 2 Buttons
		
	@param parent							Parent widget
	@param r									rectangle of PopUp
	@param windowtitle					Title of window
	@param windowtext					Text to appear in window
	@param btn1								Struct PG_Rect to create Button 1
	@param btn1text						Text to appear in Button 1
	@param btn2								Struct PG_Rect to create Button 2
	@param btn2text						Text to appear in Button 2
	@param textalign						Alignment for windowtext
	*/
	PG_MessageBox(PG_Widget* parent, const PG_Rect& r, const char* windowtitle, const char* windowtext, const PG_Rect& btn1, const char* btn1text, const PG_Rect& btn2, const char* btn2text, int textalign=PG_TA_CENTER, const char* style="MessageBox");

#ifdef SWIG

	%name(PG_MessageBox1) PG_MessageBox(PG_Widget* parent, const PG_Rect& r, const char* windowtitle, const char* windowtext, const PG_Rect& btn1, const char* btn1text, int textalign=PG_TA_CENTER, const char* style="MessageBox");
#else
	/**
	Creates a PopUp with 1 Button

	@param parent							Parent widget
	@param r									rectangle of PopUp
	@param windowtitle					Title of window
	@param windowtext					Text to appear in window
	@param btn1								Struct PG_Rect to create Button 1
	@param btn1text						Text to appear in Button 1
	@param textalign						Alignment for windowtext
	*/
	PG_MessageBox(PG_Widget* parent, const PG_Rect& r, const char* windowtitle, const char* windowtext, const PG_Rect& btn1, const char* btn1text, int textalign=PG_TA_CENTER, const char* style="MessageBox");
#endif

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
	Checks Event, if button is clicked, sets buttonflag to ID of Button		

	@param id											ButtonID
	@param widget									widget for Evenet
	*/
	bool eventButtonClick(int id, PG_Widget* widget);

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
