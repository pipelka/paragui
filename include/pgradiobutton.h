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
    Update Date:      $Date: 2002/04/15 13:31:30 $
    Source File:      $Source: /sources/paragui/paragui/include/pgradiobutton.h,v $
    CVS/RCS Revision: $Revision: 1.2 $
    Status:           $State: Exp $
*/

#ifndef PG_RADIOBUTTON_H
#define PG_RADIOBUTTON_H

#ifdef SWIG
%include "swigcommon.h"
%module pgradiobutton
%{
#include "pgradiobutton.h"
%}
#endif

#include "pgthemewidget.h"
#include "pgbutton.h"
#include "pglabel.h"

/**
	@author Alexander Pipelka
 
	@short A single radio button.
 
	A single radio button, which has an attribute to signify what group
	it belongs to.
*/
/* Perhaps radio buttons should have a special PG_RadioButtonGroup parent class
 * to make things more clear and eliminate all the group stuff within the radio
 * button itself?
 *
 * NO :)
 * I think this kind of implementation is simple and easy to understand. 
 */
class DECLSPEC PG_RadioButton : public PG_ThemeWidget {
public:

	/** */
	PG_RadioButton(PG_Widget* parent, int id, const PG_Rect& r, const char* text, PG_RadioButton* firstOfGroup = NULL, const char* style="RadioButton");

	/** */
	~PG_RadioButton();

	void LoadThemeStyle(const char* widgettype);

	/** */
	bool GetPressed();

	/** */
	void SetPressed();

//#ifndef SWIG
	/** Sets formated text (like printf)*/
//	void SetTextFormat(const char* text, ...);
//#endif

	/** */
	void SetText(const char* text);

	/** */
	const char* GetText();

protected:

	/** */
	void AddToGroup(PG_RadioButton* w);

	/** */
	void ReleaseButton();

	/** */
	void eventMouseEnter();

	/** */
	void eventMouseLeave();

	/** */
	bool eventMouseButtonUp(const SDL_MouseButtonEvent* button);

	/** */
	bool eventButtonClick(int id, PG_Widget* widget);

	PG_RadioButton* my_groupFirst;
	PG_RadioButton* my_groupNext;

	PG_Button* my_widgetButton;
	PG_Label* my_widgetLabel;
	bool my_isPressed;

private:
#ifndef SWIG

	PG_RadioButton(const PG_RadioButton&);
	PG_RadioButton& operator=(const PG_RadioButton&);
#endif

	bool my_storeMarker;
	Uint8 my_hoverTransparency;
};

#endif // PG_RADIOBUTTON_H
