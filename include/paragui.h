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
    Update Date:      $Date: 2004/01/21 16:01:02 $
    Source File:      $Source: /sources/paragui/paragui/include/paragui.h,v $
    CVS/RCS Revision: $Revision: 1.3.6.5.2.4 $
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

// SDL
#include "SDL.h"
#include "SDL_thread.h"

#include "paraconfig.h"

//our default namespace is std
using namespace std;

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
//#define DISPLAY_DEPTH 16

/**
	suffix for theme (xml) files.
	The themeloader tries to open themefiles with the extension THEME_SUFFIX
*/
#define THEME_SUFFIX ".theme"

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
//#define PG_IDSCROLLBAR_UP		PG_WIDGETID_INTERNAL + 1
/**
	ID Scrollbar Button "down".
	This is the widget ID of the "down" button.
*/
//#define PG_IDSCROLLBAR_DOWN	PG_WIDGETID_INTERNAL + 2
/**
	ID Scrollbar Button "left".
	This is the widget ID of the "left" button.
*/
//#define PG_IDSCROLLBAR_LEFT		PG_WIDGETID_INTERNAL + 3
/**
	ID Scrollbar Button "right".
	This is the widget ID of the "right" button.
*/
//#define PG_IDSCROLLBAR_RIGHT	PG_WIDGETID_INTERNAL + 4
/**
	ID Scrollbar Button "drag".
	This is the widget ID of the scrollbar slider in the middle.
*/
//#define PG_IDSCROLLBAR_DRAG	PG_WIDGETID_INTERNAL + 5

// WidgetList scrollbar
/**
	ID WidgetList Scrollbar.
	This is the widget ID of the scrollbar inside a widgetlist.
*/
//#define PG_IDWIDGETLIST_SCROLL	PG_WIDGETID_INTERNAL + 10

// Dropdown box
/**
	ID DropDown button.
	This is the widget ID of the button inside a dropdown widget.
*/
//#define PG_IDDROPDOWN_BOX	PG_WIDGETID_INTERNAL + 11

// SpinnerBox
/**
	ID SpinnerBox up.
	This is the widget ID of the "up" button inside a spinnerbox widget.
*/
//#define PG_IDSPINNERBOX_UP		PG_WIDGETID_INTERNAL + 12
/**
	ID SpinnerBox down.
	This is the widget ID of the "down" button inside a spinnerbox widget.
*/
//#define PG_IDSPINNERBOX_DOWN	PG_WIDGETID_INTERNAL + 13

// Window
/**
	ID Window clode.
	This is the widget ID of the "close" button inside a window widget.
*/
//#define PG_WINDOW_CLOSE		PG_WIDGETID_INTERNAL + 14
//#define PG_WINDOW_MINIMIZE	PG_WIDGETID_INTERNAL + 15
//#define PG_WINDOW_RESTORE		PG_WIDGETID_INTERNAL + 15

// Application object
/**
	ID Application.
	This is the MessageObject ID of the main application object.
*/
//#define PG_IDAPPLICATION		PG_WIDGETID_INTERNAL + 100

// Font styles
//#define PG_FSTYLE_NORMAL	0x00
//#define PG_FSTYLE_BOLD		0x01
//#define PG_FSTYLE_ITALIC	0x02
//#define PG_FSTYLE_UNDERLINE	0x04

#endif // PARAGUI_H
