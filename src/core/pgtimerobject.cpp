/*
    ParaGUI - crossplatform widgetset
    Copyright (C) 2000 - 2009 Alexander Pipelka

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
    Update Date:      $Date: 2009/06/04 10:25:12 $
    Source File:      $Source: /sources/paragui/paragui/src/core/pgtimerobject.cpp,v $
    CVS/RCS Revision: $Revision: 1.1.2.6.2.11 $
    Status:           $State: Exp $
*/

#include "pgtimerobject.h"

Uint32 PG_TimerObject::objectcount = 0;
PG_TimerObject::ID PG_TimerObject::globalTimerID = 0;
std::map<PG_TimerObject::ID, PG_TimerObject*> PG_TimerObject::timermap;
PG_TimerObject* PG_TimerObject::objSingleTimer = NULL;

PG_TimerObject::PG_TimerObject() {
	if(objectcount == 0) {
		SDL_InitSubSystem(SDL_INIT_TIMER);
	}

	objectcount++;
	my_lock = SDL_CreateMutex();
}

PG_TimerObject::~PG_TimerObject() {

	// stop single timers
	StopTimer();

	// remove all timers of this object
	std::map<PG_TimerObject::ID, SDL_TimerID>::iterator i;

	for(i = my_timermap.begin(); i != my_timermap.end(); ) {
		RemoveTimer((*i).first);
		i = my_timermap.begin();
	}

	objectcount--;

	if(objectcount == 0) {
		SDL_QuitSubSystem(SDL_INIT_TIMER);
	}

	SDL_DestroyMutex(my_lock);
}

PG_TimerObject::ID PG_TimerObject::AddTimer(Uint32 interval) {
	SDL_mutexP(my_lock);
	SDL_TimerID id = SDL_AddTimer(interval, &PG_TimerObject::callbackTimer, (void*)(globalTimerID+1));

	if(id == 0) {
		SDL_mutexV(my_lock);
		return 0;
	}

	PG_TimerObject::ID pgid = ++globalTimerID;
	my_timermap[pgid] = id;
	timermap[pgid] = this;
	SDL_mutexV(my_lock);

	return pgid;
}

bool PG_TimerObject::RemoveTimer(PG_TimerObject::ID id) {
	SDL_mutexP(my_lock);
	SDL_TimerID sid = my_timermap[id];
	my_timermap.erase(id);
	timermap.erase(id);

	bool rc = (SDL_RemoveTimer(sid) != 0);
	SDL_mutexV(my_lock);
	return rc;
}

Uint32 PG_TimerObject::eventTimer(PG_TimerObject::ID id, Uint32 interval) {
	return interval;
}

Uint32 PG_TimerObject::eventTimer(Uint32 interval) {
	return interval;
}

Uint32 PG_TimerObject::callbackTimer(Uint32 interval, void* data) {
	PG_TimerObject::ID id = reinterpret_cast<PG_TimerObject::ID>(data);
	PG_TimerObject* o = timermap[id];

	// check for unregistered timerobjects
	if(o == NULL) {
		return 0;
	}
	SDL_mutexP(o->my_lock);

	o->sigTimer(timermap[id], id);
	Uint32 r = o->eventTimer(id, interval);
	SDL_mutexV(o->my_lock);

	return r;
}

Uint32 PG_TimerObject::callbackSingleTimer(Uint32 interval) {
	Uint32 r = 0;
	if(objSingleTimer != NULL) {
		SDL_mutexP(objSingleTimer->my_lock);
		objSingleTimer->sigTimer(objSingleTimer, (PG_TimerObject::ID)0);
		r = objSingleTimer->eventTimer(interval);
		SDL_mutexV(objSingleTimer->my_lock);
	}

	return r;
}

int PG_TimerObject::SetTimer(Uint32 interval) {
	SDL_mutexP(my_lock);
	StopTimer();
	objSingleTimer = this;
	int r = SDL_SetTimer(interval, &PG_TimerObject::callbackSingleTimer);
	SDL_mutexV(my_lock);

	return r;
}

void PG_TimerObject::StopTimer() {
	SDL_mutexP(my_lock);
	if(objSingleTimer != NULL) {
		objSingleTimer = NULL;
		SDL_SetTimer(0, NULL);
	}
	SDL_mutexV(my_lock);
}
