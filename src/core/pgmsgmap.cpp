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
    Update Date:      $Date: 2002/04/15 14:53:56 $
    Source File:      $Source: /sources/paragui/paragui/src/core/Attic/pgmsgmap.cpp,v $
    CVS/RCS Revision: $Revision: 1.1 $
    Status:           $State: Exp $
*/

#include "pgmsgmap.h"
#include "pglog.h"
#include <map>
#include <string>
#include <iostream>

void PG_DisplayEventMap(std::string message = "");

// the PG_MessageObject -> callback function pair definition

struct objcb_cmp {
	bool operator()(PG_MessageObject* o1, PG_MessageObject* o2) const {
		return o1 < o2;
	}
};

typedef std::map<PG_MessageObject*, PG_EVENTHANDLERDATA*, objcb_cmp> OBJCBMAP;
typedef std::map<PG_MessageObject*, PG_EVENTHANDLERDATA*, objcb_cmp>::iterator OBJCBMAP_ITERATOR;

// the messagetype <-> messageobject pair definition

struct msgobj_cmp {
	bool operator()(PG_MSG_TYPE t1, PG_MSG_TYPE t2) const {
		return (int)t1 < (int)t2;
	}
};

typedef std::map<PG_MSG_TYPE, OBJCBMAP*, msgobj_cmp> MSGOBJMAP;
typedef std::map<PG_MSG_TYPE, OBJCBMAP*, msgobj_cmp>::iterator MSGOBJMAP_ITERATOR;

// the global eventmap
static MSGOBJMAP PG_EventMap;

PG_EVENTHANDLERDATA* PG_FindEventHandler(PG_MSG_TYPE type, PG_MessageObject* obj) {
	MSGOBJMAP_ITERATOR i = PG_EventMap.find(type);

	if(i == PG_EventMap.end()) {
		return NULL;
	}

	OBJCBMAP_ITERATOR li = (*i).second->find(obj);

	if(li == (*i).second->end()) {
		return NULL;
	}

	return (*li).second;
}

void PG_DisplayOBJCBMAP(OBJCBMAP* list) {
	OBJCBMAP_ITERATOR li;

    if (!list)
        return;
    
	for ( li = list->begin() ; li != list->end() ; li++ ) {
		PG_LogDBG(" - Message Object: %d Event Handler Data: %d", (int)(*li).first, (int)(*li).second);
	}
}

void PG_DisplayEventMap(std::string message) {
	MSGOBJMAP_ITERATOR i;

	PG_LogDBG("Current Event Map: %s",message.c_str());

	for(i = PG_EventMap.begin(); i != PG_EventMap.end(); i++) {

		PG_LogDBG(" - Type: %d",(int)(*i).first);

		OBJCBMAP* list = (*i).second;

		PG_DisplayOBJCBMAP(list);

		PG_LogDBG(" ---- ");
	}

	return;
}




bool PG_RegisterEventHandler(PG_MSG_TYPE type, PG_MessageObject* obj, MSG_CALLBACK cbfunc, void* data) {

	if(cbfunc == NULL) {
		return false;
	}

	PG_EVENTHANDLERDATA* cbdata = PG_FindEventHandler(type, obj);

	if(cbdata == NULL) {
		cbdata = new PG_EVENTHANDLERDATA;
	}

	cbdata->cbfunc = cbfunc;
	cbdata->calledobj = NULL;
	cbdata->obj_cbfunc = NULL;
	cbdata->data = data;

	OBJCBMAP* list = NULL;

	// check if we already have a list for "type"
	if(PG_EventMap.find(type) == PG_EventMap.end()) {

		// create a new objectlist for "type"
		list = new OBJCBMAP;
		PG_EventMap[type] = list;
	} else {
		list = PG_EventMap[type];
	}

	// check if we already have "obj" in the list
	OBJCBMAP_ITERATOR i = list->find(obj);

	if(i != list->end()) {
		(*i).second = cbdata;
	} else {
		(*list)[obj] = cbdata;
	}

	return true;
}

bool PG_RegisterEventHandlerObj(PG_MSG_TYPE type, PG_MessageObject* obj, PG_EventObject* called_obj, MSG_CALLBACK_OBJ obj_cbfunc, void* data) {

	if(obj_cbfunc == 0) {
		return false;
	}

	PG_EVENTHANDLERDATA* cbdata = PG_FindEventHandler(type, obj);

	if(cbdata == NULL) {
		cbdata = new PG_EVENTHANDLERDATA;
	}

	cbdata->cbfunc = NULL;
	cbdata->calledobj = called_obj;
	cbdata->obj_cbfunc = obj_cbfunc;
	cbdata->data = data;

	OBJCBMAP* list = NULL;

	// check if we already have a list for "type"
	if(PG_EventMap.find(type) == PG_EventMap.end()) {

		// create a new objectlist for "type"
		list = new OBJCBMAP;
		PG_EventMap[type] = list;
	} else {
		list = PG_EventMap[type];
	}

	// check if we already have "obj" in the list
	OBJCBMAP_ITERATOR i = list->find(obj);

	if(i != list->end()) {
		(*i).second = cbdata;
	} else {
		(*list)[obj] = cbdata;
	}

	return true;
}

bool PG_UnregisterEventHandler(PG_MSG_TYPE type, PG_MessageObject* obj) {

	MSGOBJMAP_ITERATOR i = PG_EventMap.find(type);

	if(i == PG_EventMap.end()) {
		return false;
	}

	OBJCBMAP_ITERATOR li = (*i).second->find(obj);

	if(li == (*i).second->end()) {
		return false;
	}

	PG_EVENTHANDLERDATA* cbdata = (*li).second;

	(*i).second->erase(li);

	if ((*i).second->empty()) {
		PG_EventMap.erase(i);
	}

	if(cbdata == NULL) {
		return false;
	}

	delete cbdata;

	return true;
}

bool PG_UnregisterEventObject(PG_MessageObject* obj) {
	MSGOBJMAP_ITERATOR i;

	for(i = PG_EventMap.begin(); i != PG_EventMap.end();) {
		OBJCBMAP_ITERATOR li;

		while ( (li = (*i).second->find(obj) ) != (*i).second->end() ) {

			PG_EVENTHANDLERDATA* data = (*li).second;

			(*i).second->erase(li);

			if(data != NULL) {
				delete data;
			}

		}

		if ((*i).second->empty()) {
			OBJCBMAP* temp = (*i).second;
			PG_EventMap.erase(i);
			delete temp;
			i = PG_EventMap.begin();
		} else {
			i++;
		}
	}

	return true;
}

bool PG_UnregisterEventTarget(PG_EventObject* obj) {

	MSGOBJMAP_ITERATOR i;
	PG_EVENTHANDLERDATA* data = NULL;
	bool found = false;

	for(i = PG_EventMap.begin(); i != PG_EventMap.end();) {

		OBJCBMAP_ITERATOR j = (*i).second->begin();

		for(; j != (*i).second->end();) {
			data = (*j).second;

			if(data->calledobj == obj) {
				found = true;
				(*i).second->erase(j);
				delete data;
				j = (*i).second->begin();
			} else {
				j++;
			}
		}

		if ((*i).second->empty()) {
			OBJCBMAP* temp = (*i).second;
			PG_EventMap.erase(i);
			delete temp;
			i = PG_EventMap.begin();
		} else {
			i++;
		}

	}

	return found;
}
