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
    Update Date:      $Date: 2002/04/15 13:22:30 $
    Source File:      $Source: /sources/paragui/paragui/include/Attic/pgbuttongroup.h,v $
    CVS/RCS Revision: $Revision: 1.1 $
    Status:           $State: Exp $
*/

#ifndef PG_BUTTONGROUP_H
#define PG_BUTTONGROUP_H

#ifdef SWIG
%include "swigcommon.h"
%module pgbuttongroup
%{
#include "pgbuttongroup.h"
%}
#endif

#include "pgthemewidget.h"
#include "pgbutton.h"

/**
	@author Alexander Pipelka
	
	@short A group of PG_Buttons
 
	An array of PG_Buttons with functions to tie them together in various ways.
FIXME: what is this used for?
*/

class DECLSPEC PG_ButtonGroup : public PG_ThemeWidget {
public:
	PG_ButtonGroup(PG_Widget* parent, int id, const PG_Rect& r, int x, int y, int d=1);
	~PG_ButtonGroup();

	void Activate(int x, int y, int d=0);
	void Deactivate(int x, int y, int d=0);
	void Show();
	void SwitchTo(int d);
	void BlendTo(int d);

	void SetText(int x, int y, int d, char* text);

	PG_Button* GetButton(int x, int y, int d);

	virtual bool OnButton(int x, int y, int d, PG_Widget* widget);

protected:
	int GetIndex(int x, int y, int d);

	/** Event Handler */
	bool eventButtonClick(int id, PG_Widget* widget);

private: // disable the copy operators
#ifndef SWIG

	PG_ButtonGroup(const PG_ButtonGroup&);
	PG_ButtonGroup& operator=(const PG_ButtonGroup&);
#endif

private:
	void GetPosFromId(int id, int& x, int& y, int& d);

	PG_Button** btnArray;
	Uint8*		actArray;
	int			count_x;
	int			count_y;
	int			count_d;
	int			current_depth;
};


#endif // PG_BUTTONGROUP_H
