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
    Source File:      $Source: /sources/paragui/paragui/include/pgwindow.h,v $
    CVS/RCS Revision: $Revision: 1.1 $
    Status:           $State: Exp $
*/

#ifndef PG_WINDOW_H
#define PG_WINDOW_H

#ifdef SWIG
%include "swigcommon.h"
%module pgwindow
%{
#include "pgwindow.h"
    %}
#endif

#include "pgthemewidget.h"
#include "pgbutton.h"
#include "pglabel.h"
#include <string>

typedef enum {
    WF_MODAL = 0x01,
    WF_SHOW_CLOSE = 0x02,
    WF_SHOW_MINIMIZE = 0x04,
    WF_DEFAULT = WF_SHOW_CLOSE
} PG_WINDOWFLAGS;

/**
	@author Alexander Pipelka
 
	@short A window inside the program (not a windowing environment window)
 
	Creates a window entirely inside ParaGUI. This window can be modal or non-modal.
	Non-modal windows can be brought in front of others by clicking the titlebar.
*/

class DECLSPEC PG_Window : public PG_ThemeWidget  {
public:

	/** */
	PG_Window(PG_Widget* parent, const PG_Rect& r, const char* windowtext, Uint32 flags = WF_DEFAULT, const char* style="Window", int heightTitlebar = 25);

	/** */
	~PG_Window();

	void LoadThemeStyle(const char* widgettype);

#ifdef SWIG
	%name(SetColorTitleBar32) void SetColorTitlebar(Uint32 color);
#else
	void SetColorTitlebar(Uint32 color);
#endif

	void SetColorTitlebar(const SDL_Color& c);

protected:

	/** */
	void eventShow();

	/** */
	void eventBlit(SDL_Surface* srf, const PG_Rect& src, const PG_Rect& dst);

	/** */
	void eventSizeWidget(Uint16 w, Uint16 h);

	/** */
	bool eventButtonClick(int id, PG_Widget* widget);

	/** */
	bool eventMouseButtonDown(const SDL_MouseButtonEvent* button);

	/** */
	bool eventMouseButtonUp(const SDL_MouseButtonEvent* button);

	/** */
	bool eventMouseMotion(const SDL_MouseMotionEvent* motion);

private:

	Uint8 my_heightTitlebar;

	PG_Button* my_buttonClose;
	PG_Button* my_buttonMinimize;
	PG_Button* my_buttonIcon;

	PG_ThemeWidget* my_titlebar;
	PG_Label* my_labelTitle;

	bool my_moveMode;
	Uint8 my_moveTransparency;
	PG_Point my_moveDelta;

	bool my_showCloseButton;
	bool my_showMinimizeButton;

private: // disable the copy operators
#ifndef SWIG
	PG_Window(const PG_Window&);
	PG_Window& operator=(const PG_Window&);
#endif

};

#endif // PG_WINDOW_H
