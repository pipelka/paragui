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
    Update Date:      $Date: 2003/12/02 15:27:58 $
    Source File:      $Source: /sources/paragui/paragui/include/pglistboxitem.h,v $
    CVS/RCS Revision: $Revision: 1.3.2.1 $
    Status:           $State: Exp $
*/

#ifndef PG_LISTBOXITEM_H
#define PG_LISTBOXITEM_H

#include "pglistboxbaseitem.h"

class PG_ListBox;

class DECLSPEC PG_ListBoxItem : public PG_ListBoxBaseItem {
public:

	/** */
	PG_ListBoxItem(int height, const char* text = NULL, SDL_Surface* icon = NULL, void* userdata = NULL, const char* style="ListBox");

	/** */
	~PG_ListBoxItem();

	/** */
	void LoadThemeStyle(const char* widgettype, const char* objectname);

protected:

	/** */
	void eventBlit(SDL_Surface* srf, const PG_Rect& src, const PG_Rect& dst);

	/** */
	void eventSizeWidget(Uint16 w, Uint16 h);

private:

	PG_Gradient* my_gradient[3];
	SDL_Surface* my_background[3];
	SDL_Surface* my_srfHover;
	SDL_Surface* my_srfSelected;

	int my_bkmode[3];
	Uint8 my_blend[3];
};

#endif	// PG_LISTBOXITEM_H
