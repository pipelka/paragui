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
    Source File:      $Source: /sources/paragui/paragui/include/pgwidgetlistex.h,v $
    CVS/RCS Revision: $Revision: 1.2 $
    Status:           $State: Exp $
*/

#ifndef PG_WIDGETLISTEX_H
#define PG_WIDGETLISTEX_H

#include "pgwidgetlist.h"

/**
	@author Jaroslav Vozab
 
	@short A group of widgets arranged in a specific way graphically supporting Y spaceing
 
	Generally used to make a large 'pane' of widgets that can be scrolled
	through in a smaller 'portal' with scrollbars.
*/

class PG_WidgetListEx : public PG_WidgetList {
public:
	/**
	Constructor of the PG_WidgetListEx class
	*/
	PG_WidgetListEx(PG_Widget* parent, const PG_Rect& r, const char* style="WidgetList");

	/**
	Add a widget to the list

	@param	w			pointer to a widget
	*/
	void AddWidget(PG_Widget* w);

	/**
	Remove a widget from the list

	@param	w			pointer to a widget
	*/
	bool RemoveWidget(PG_Widget* w, bool shiftx = false, bool shifty = false);
};

#endif
