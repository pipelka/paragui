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
    Update Date:      $Date: 2002/11/01 15:00:59 $
    Source File:      $Source: /sources/paragui/paragui/include/paragui_types.h,v $
    CVS/RCS Revision: $Revision: 1.3.6.2 $
    Status:           $State: Exp $
*/

/** \file paragui_types.h
	various macros and typedefs.
	This header file declares many often used data types and macros.
*/

#ifndef PARAGUI_TYPES_H
#define PARAGUI_TYPES_H

#ifdef SWIG
%include "swigcommon.h"
%module paragui_types
%{
#include "paragui_types.h"
%}
#endif

// Forward declarations

class PG_MessageObject;
class PG_Widget;
class PG_EventObject;
#ifndef SWIG
class PG_Rect;
#endif

#ifdef __cplusplus
extern "C" {
#endif

//! Structure for a screen point
typedef struct {
	Sint16 x;	//!< screen X-Coordinate
	Sint16 y;	//!< screen Y-Coordinate
} PG_Point;

//! Structure for widget gradients
typedef struct {
	SDL_Color colors[4];	//!< array of gradient colors
} PG_Gradient;

#ifndef DOXYGEN_SKIP
typedef unsigned long MSG_ID;
typedef unsigned long MSG_DATA;
#endif

//! ParaGUI message types
typedef enum {
	MSG_BUTTONCLICK,	//!< a button was pressed
	MSG_SCROLLPOS,	//!< scrollbar changed it's position
	MSG_SLIDEEND = MSG_SCROLLPOS,	//!< slider changed it's position
	MSG_SCROLLTRACK,	//!< scrollbar position changing currently
	MSG_SLIDE = MSG_SCROLLTRACK,	//!< slider position changing currently
	MSG_THREAD_SIGNAL,	//!< general appeal signal (can by used for signal events)
	MSG_SIGNAL,	//!< general appeal signal (can by used for signal events)
	MSG_QUIT,	//!< the appliction's messageloop will quit
	MSG_EDITBEGIN,	//!< a lineedit object entered "edit-mode"
	MSG_EDITEND,	//!< a lineedit object has left "edit-mode"
	MSG_APPIDLE,	//!< fired repeatedly (if enabled) when the event queue is empty
	MSG_SELECTITEM,	//!< a listbox item has been selected
	MSG_VIDEORESIZE,	//!< the videowindow has been resized by the user
	MSG_SPINNER_CHANGE,	//!< a spinnerobject changed it's value
	MSG_WINDOWCLOSE,	//!< a window was closed
	MSG_WINDOWMINIMIZE,	//!< a window was minimized
	MSG_WINDOWRESTORE,	//!< a window was restored
	MSG_RETURN,	//!< RETURN/ENTER was pressed in a lineedit widget
	MSG_MODALQUIT,	//!< signal to leave a modal eventloop
	MSG_SELECTMENUITEM,	//!< a menuitem has been selected
	MSG_NOTEBOOK_TAB_CLICK,	//!< a notebook tab was clicked
	MSG_XMLTAG, //!< callback for unknown XML "head" tags
	MSG_USER_1 = 10001,	//!< userevent 1
	MSG_USER_2 = 10002,	//!< userevent 2
	MSG_USER_3 = 10003,	//!< userevent 3
	MSG_USER_4 = 10004,	//!< userevent 4
	MSG_USER_5 = 10005,	//!< userevent 5
	MSG_USER_6 = 10006,	//!< userevent 6
	MSG_USER_7 = 10007,	//!< userevent 7
	MSG_USER_8 = 10008,	//!< userevent 8
	MSG_USER_9 = 10009,	//!< userevent 9
	MSG_USER_10 = 10010	//!< userevent 10
} PG_MSG_TYPE;

//! Keyevent actions
typedef enum {
	PG_ACT_ACTIVATE,	//!< Widget got the input focus
	PG_ACT_DEACTIVATE,	//!< Widget has lost the input focus
	PG_ACT_OK,	//!< Widget action event (e.g. button press on a PG_Button object)
	PG_ACT_CANCEL,	//!< Widget cancel-action
	PG_ACT_LEFT,	//!< Cursor left was pressed
	PG_ACT_RIGHT,	//!< Cursor right was pressed
	PG_ACT_UP,	//!< Cursor up was pressed
	PG_ACT_DOWN	//!< Cursor down was pressed
} PG_ACTION;

//! Cursor mode
typedef enum {
	PG_CURSOR_QUERY, //!< Used to query the current mode
	PG_CURSOR_NONE,  //!< Show no cursor at all
	PG_CURSOR_HARDWARE, //!< Use hardware (standard SDL) cursor
	PG_CURSOR_SOFTWARE //!< Use ParaGUI software cursor (when possible)
} PG_CURSOR_MODE;

/**
	General callback handler definition
	@param id id of the calling widget
	@param widget pointer to the caller
	@param message specific data
	@param clientdata pointer to userdefined callback data
	@return true on success
*/
#define PARAGUI_CALLBACK(funcname) \
bool funcname (int id, PG_Widget* widget, unsigned long data, void *clientdata)

/**
	callbackhandler for MSG_BUTTONCLICK messages
	@param id id of the activated button
	@param button pointer to the calling button
	@param clientdata pointer to userdefined callback data
	@return true on success
*/
#define PARAGUI_CALLBACK_BUTTONCLICK(funcname) \
bool funcname##_internal (int id, PG_Button* button, unsigned long data, void *clientdata); \
bool funcname (int id, PG_Widget* widget, unsigned long data, void *clientdata) { \
	return funcname##_internal (id, (PG_Button*)widget, data, clientdata); \
} \
inline bool funcname##_internal (int id, PG_Button* button, unsigned long data, void *clientdata)

/**
	callbackhandler for MSG_SELECTMENUITEM messages
	@param id id of the activated menuitem
	@param item pointer to the calling MenuItem
	@param clientdata pointer to userdefined callback data
	@return true on success
*/
#define PARAGUI_CALLBACK_SELECTMENUITEM(funcname) \
bool funcname##_internal (int id, PG_PopupMenu::MenuItem* item, void *clientdata); \
bool funcname (int id, PG_Widget* widget, unsigned long data, void *clientdata) { \
	return funcname##_internal (id, (PG_PopupMenu::MenuItem*)data, clientdata); \
} \
inline bool funcname##_internal (int id, PG_PopupMenu::MenuItem* item, void *clientdata)

/**
	Callback function for ParaGUI events.
	@param id ID of the Widget/MessageObject that fired this event.
	@param widget pointer to the caller widget.
	@param data message specific data
	@param clientdata user defined callback data
	@return true - if the message was processed.

	This is the typedef of C-style callback functions.
*/
typedef bool (*MSG_CALLBACK)(int id, PG_Widget* widget, unsigned long data, void *clientdata);

#ifndef SWIG
/**
	Member callback function for ParaGUI events.
	@param id ID of the Widget/MessageObject that fired this event.
	@param widget pointer to the caller widget.
	@param data message specific data
	@param clientdata user defined callback data
	@return true - if the message was processed.

	This is the typedef of C++-style member callback functions.
	Any class implementing C++-style callbacks must be derived from PG_EventObject.
*/
typedef bool (PG_EventObject::*MSG_CALLBACK_OBJ)(int id, PG_Widget* widget, unsigned long data, void* clientdata);
#endif

// MSG_MESSAGE
#ifndef DOXYGEN_SKIP
typedef struct {
	PG_MSG_TYPE	type;
	PG_MessageObject* _from;
	PG_MessageObject* _to;
	unsigned long widget_id;
	unsigned long data;
	PG_Point pt;
} MSG_MESSAGE;
#endif

#ifdef __cplusplus
}
#endif

#endif // PARAGUI_TYPES_H

/*
 * Local Variables:
 * c-basic-offset: 8
 * End:
 */
