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
    Update Date:      $Date: 2003/11/24 09:17:21 $
    Source File:      $Source: /sources/paragui/paragui/src/core/Attic/pgmsgmap.h,v $
    CVS/RCS Revision: $Revision: 1.1.2.1 $
    Status:           $State: Exp $
*/

#error pgmsgmap.h is obsolete

#ifndef PARAGUI_MSGMAP_H
#define PARAGUI_MSGMAP_H

#include "paragui.h"
#include "pgmessageobject.h"
#include "pgeventobject.h"

/**
	ParaGUI eventhandler data structure
*/

typedef struct PG_EVENTHANDLERDATA {

	/** the function to call */
	MSG_CALLBACK cbfunc;

	/** object member function */
	MSG_CALLBACK_OBJ obj_cbfunc;

	/** the object to call **/
	PG_EventObject* calledobj;

	/** pointer to userdata */
	void* data;

}
PG_EVENTHANDLERDATA;

/**
	Searches for a specific eventhandler
 
	@param	type			the messagetype
	@param	obj			the emiting PG_MessageObject
*/

PG_EVENTHANDLERDATA* PG_FindEventHandler(PG_MSG_TYPE type, PG_MessageObject* obj);

/**
	Register a new eventhandler for an object
 
	@param	type			the messagetype
	@param	obj			the messageobject
	@param	cbfunc		the callback function to register
	@param	data			optional userdata
*/

bool PG_RegisterEventHandler(PG_MSG_TYPE type, PG_MessageObject* obj, MSG_CALLBACK cbfunc, void* data);

bool PG_RegisterEventHandlerObj(PG_MSG_TYPE type, PG_MessageObject* obj, PG_EventObject* called_obj, MSG_CALLBACK_OBJ obj_cbfunc, void* data);

/**
	Unregister an objects eventhandler
 
	@param	type			the messagetype to unregister
	@param	obj			the messageobject
*/

bool PG_UnregisterEventHandler(PG_MSG_TYPE type, PG_MessageObject* obj);

/**
	Unregister all eventhandlers of an object
 
	@param	obj			the messageobject to unregister
*/

bool PG_UnregisterEventObject(PG_MessageObject* obj);

/**
	Unregister all message target objects (PG_EventObject)
	@param	obj			the PG_EventObject to unregister
*/

bool PG_UnregisterEventTarget(PG_EventObject* obj);

#endif // PARAGUI_MSGMAP_H

