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
    Update Date:      $Date: 2002/04/27 11:57:22 $
    Source File:      $Source: /sources/paragui/paragui/include/paragui.h,v $
    CVS/RCS Revision: $Revision: 1.4 $
    Status:           $State: Exp $
*/

/** \file paragui.h
	The main include file.
	This include file sets up the basic configuration for
	a ParaGUI enabled application. It includes all dependend
	headers (SDL,...) and defines some macros used by many
	other files.
*/

#ifndef PARAGUI_H
#define PARAGUI_H

#ifdef SWIG
%include "swigcommon.h"
%module paragui
%{
#include "paragui.h"
%}
%include "paragui_types.h"
%include "pgrect.h"
%include "pgmessageobject.h"
%include "pgwidget.h"
%include "pgthemewidget.h"
%include "pgwidgetdnd.h"
%include "pgwidgetlist.h"
%include "pgfilearchive.h"
%include "pgfile.h"
%include "pgfont.h"
%include "pgapplication.h"
%include "pgbutton.h"
%include "pgradiobutton.h"
%include "pgcheckbutton.h"
%include "pglabel.h"
%include "pglineedit.h"
%include "pgscrollbar.h"
%include "pgprogressbar.h"
%include "pgwindow.h"
%include "pgslider.h"
%include "pglistboxbaseitem.h"
%include "pglistboxitem.h"
%include "pgcolumnitem.h"
%include "pglistbox.h"
%include "pgmaskedit.h"
%include "pgmessagebox.h"
%include "pgspinnerbox.h"
%include "pgimage.h"
%include "pgpopupmenu.h"
#endif

#ifndef SWIG
#include <cstdlib>
#include <iostream>
#include <string>
#endif

// SDL
#include "SDL.h"
#include "SDL_thread.h"

#include "paraconfig.h"

// mpatrol
#ifdef MPATROL_ENABLED
#include "mpatrol.h"
#endif

#include "paragui_types.h"

#include "pgrect.h"

/**
	calculate the minimum of 2 values
*/
#define PG_MAX(a, b)	((a<b) ? b : a)

/**
	calculate the maximum of 2 values
*/
#define PG_MIN(a, b)	((a<b) ? a : b)

/**
	default display depth.
	this is the default  display depth used for PG_Application::InitScreen.
*/
#define DISPLAY_DEPTH 16

/**
	suffix for theme (xml) files.
	The themeloader tries to open themefiles with the extension THEME_SUFFIX
*/
#define THEME_SUFFIX ".theme"

// Background modes

/**
	Backgroundmode TILE.
	Macro defining the background mode for tiling
*/
#define BKMODE_TILE			1
/**
	Backgroundmode STRETCH.
	Macro defining the background mode for stretching
*/
#define BKMODE_STRETCH		2
/**
	Backgroundmode 3TILEH.
	Macro defining the background mode for horizontal 3 part tiling
*/
#define BKMODE_3TILEH		3
/**
	Backgroundmode 3TILEV.
	Macro defining the background mode for vertical 3 part tiling
*/
#define BKMODE_3TILEV		4

// Button states

/**
	Buttonstate: Normal (up).
*/
#define BTN_STATE_NORMAL		0
/**
	Buttonstate: Pressed (down).
*/
#define BTN_STATE_PRESSED		1
/**
	Buttonstate: Highlited.
*/
#define BTN_STATE_HIGH			2


// Text alignment

/**
	Textalignment: left.
	justify text to the left
*/
#define PG_TA_LEFT		0
/**
	Textalignment: center.
	center text
*/
#define PG_TA_CENTER		1
/**
	Textalignment: right.
	justify text to the right
*/
#define PG_TA_RIGHT		2


// Scrollbars

/**
	Scrollbartype: Vertical.
	Flag for creating a vertical scrollbar
*/
#define PG_SB_VERTICAL		1
/**
	Scrollbartype: Horizontal.
	Flag for creating a horizontal scrollbar
*/
#define PG_SB_HORIZONTAL	2

// internal widget ids

/**
	Internal widget ID.
	All internal widget ID's start at this value.
*/
#define	PG_WIDGETID_INTERNAL	10000

// Scrollbar up,down,dragbutton

/**
	ID Scrollbar Button "up".
	This is the widget ID of the "up" button.
*/
#define PG_IDSCROLLBAR_UP		PG_WIDGETID_INTERNAL + 1
/**
	ID Scrollbar Button "down".
	This is the widget ID of the "down" button.
*/
#define PG_IDSCROLLBAR_DOWN	PG_WIDGETID_INTERNAL + 2
/**
	ID Scrollbar Button "left".
	This is the widget ID of the "left" button.
*/
#define PG_IDSCROLLBAR_LEFT		PG_WIDGETID_INTERNAL + 3
/**
	ID Scrollbar Button "right".
	This is the widget ID of the "right" button.
*/
#define PG_IDSCROLLBAR_RIGHT	PG_WIDGETID_INTERNAL + 4
/**
	ID Scrollbar Button "drag".
	This is the widget ID of the scrollbar slider in the middle.
*/
#define PG_IDSCROLLBAR_DRAG	PG_WIDGETID_INTERNAL + 5

// WidgetList scrollbar
/**
	ID WidgetList Scrollbar.
	This is the widget ID of the scrollbar inside a widgetlist.
*/
#define PG_IDWIDGETLIST_SCROLL	PG_WIDGETID_INTERNAL + 10

// Dropdown box
/**
	ID DropDown button.
	This is the widget ID of the button inside a dropdown widget.
*/
#define PG_IDDROPDOWN_BOX	PG_WIDGETID_INTERNAL + 11

// SpinnerBox
/**
	ID SpinnerBox up.
	This is the widget ID of the "up" button inside a spinnerbox widget.
*/
#define PG_IDSPINNERBOX_UP		PG_WIDGETID_INTERNAL + 12
/**
	ID SpinnerBox down.
	This is the widget ID of the "down" button inside a spinnerbox widget.
*/
#define PG_IDSPINNERBOX_DOWN	PG_WIDGETID_INTERNAL + 13

// Window
/**
	ID Window clode.
	This is the widget ID of the "close" button inside a window widget.
*/
#define PG_WINDOW_CLOSE		PG_WIDGETID_INTERNAL + 14
#define PG_WINDOW_MINIMIZE	PG_WIDGETID_INTERNAL + 15
#define PG_WINDOW_RESTORE		PG_WIDGETID_INTERNAL + 15

// Application object
/**
	ID Application.
	This is the MessageObject ID of the main application object.
*/
#define PG_IDAPPLICATION		PG_WIDGETID_INTERNAL + 100

// Font styles
#define PG_FSTYLE_NORMAL	0x00
#define PG_FSTYLE_BOLD		0x01
#define PG_FSTYLE_ITALIC	0x02
#define PG_FSTYLE_UNDERLINE	0x04

#endif // PARAGUI_H
