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
    Update Date:      $Date: 2002/04/15 13:35:35 $
    Source File:      $Source: /sources/paragui/paragui/include/pgspinnerbox.h,v $
    CVS/RCS Revision: $Revision: 1.3 $
    Status:           $State: Exp $
*/

#ifndef PG_SPINNERBOX_H
#define PG_SPINNERBOX_H

#ifdef SWIG
%include "swigcommon.h"
%module pgspinnerbox
%{
#include "pgspinnerbox.h"
%}
#endif

#include "pgmaskedit.h"
#include "pgbutton.h"
#include "pgthemewidget.h"
#include "pgeventobject.h"

/**
 * @author Atani - Mike Dunston
 *
 * @short PG_SpinnerBox creates a textbox with attached increase/decrease buttons to control the numeric value.
 *
 * PG_SpinnerBox creates a textbox with attached increase/decrease buttons to
 * control the numeric value.   Many convenience methods are available...
 * SetValue, SetMinValue, SetMaxValue, SetMask
 * GetValue, GetMinValue, GetMaxValue, GetMask
 *
 * Registerable Events:
 *
 * MSG_SPINNER_CHANGE -
 *
 * Fired when the user clicks either up or down on the spinner buttons.
 * Currently typed modifications are not populated to the value.  This will be
 * added soon.  Note: using SetValue above will fire this event.
 */

class DECLSPEC PG_SpinnerBox : public PG_ThemeWidget, public PG_EventObject {
public:

	/**
	*/
	PG_SpinnerBox(PG_Widget *parent, const PG_Rect& r, const char* style = "SpinnerBox");

	/**
	*/
	~PG_SpinnerBox();

	void SetValue(int value) {
		m_iValue = value;
		SetTextValue();
	}
	void SetMinValue( int value ) {
		m_iMinValue = value;
	}
	void SetMaxValue( int value ) {
		m_iMaxValue = value;
	}
	void SetMask( const char *value ) {
		strcpy( m_sMask, value );
		m_pEditBox->SetMask( m_sMask );
		AdjustSize();
	}

	int GetValue() {
		return( m_iValue );
	}
	int GetMinValue() {
		return( m_iMinValue );
	}
	int GetMaxValue() {
		return( m_iMaxValue );
	}
	char *GetMask() {
		return( m_sMask );
	}

protected:

	bool eventButtonClick(int id, PG_Widget *widget);
	PARAGUI_CALLBACK(handle_editend);

private:

	PG_Widget *m_pParent;
	PG_MaskEdit *m_pEditBox;
	PG_Button *m_pButtonUp, *m_pButtonDown;
	int m_iMinValue;
	int m_iMaxValue;
	int m_iValue;
	char m_sMask[10];
	void SetTextValue();
	void AdjustSize();
};

#endif	// PG_SPINNERBOX_H
