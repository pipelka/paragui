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
    Update Date:      $Date: 2002/04/27 15:36:55 $
    Source File:      $Source: /sources/paragui/paragui/include/pgslider.h,v $
    CVS/RCS Revision: $Revision: 1.5 $
    Status:           $State: Exp $
*/

#ifndef PG_SLIDER_H
#define PG_SLIDER_H

#include "paragui.h"
#include "pgscrollbar.h"

class DECLSPEC PG_Slider : public PG_ScrollBar {

public:

	/** */
	PG_Slider(PG_Widget* parent, int id, const PG_Rect& r, int direction = PG_SB_VERTICAL, const char* style="Slider");

	/** */
	~PG_Slider();

	void LoadThemeStyle(const char* widgettype);

	PG_SignalSlide sigSlide;
	
protected:

	virtual bool handleTrack(PG_ScrollBar* from, long pos);
	
	/** */
	bool eventMouseButtonUp(const SDL_MouseButtonEvent* button);

	/** */
	void eventSizeWidget(Uint16 w, Uint16 h);

	/** */
	bool my_showButtons;

private:

	int my_sliderSize;
};

#endif	// PG_SLIDER_H
