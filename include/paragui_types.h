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
    Update Date:      $Date: 2002/04/27 15:36:54 $
    Source File:      $Source: /sources/paragui/paragui/include/paragui_types.h,v $
    CVS/RCS Revision: $Revision: 1.5 $
    Status:           $State: Exp $
*/

/** \file paragui_types.h
	various macros and typedefs.
	This header file declares many often used data types and macros.
*/

#ifndef PARAGUI_TYPES_H
#define PARAGUI_TYPES_H

#include "SDL.h"

//! Structure for widget gradients
typedef struct {
	SDL_Color colors[4];	//!< array of gradient colors
} PG_Gradient;

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

#endif // PARAGUI_TYPES_H

/*
 * Local Variables:
 * c-basic-offset: 8
 * End:
 */
