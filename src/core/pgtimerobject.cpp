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
}
	
PG_TimerObject::ID PG_TimerObject::AddTimer(Uint32 interval) {
	SDL_TimerID id = SDL_AddTimer(interval, &PG_TimerObject::callbackTimer, (void*)(globalTimerID+1));

	if(id == 0) {
		return 0;
	}
	
	PG_TimerObject::ID pgid = ++globalTimerID;
	my_timermap[pgid] = id;
	timermap[pgid] = this;
	
	return pgid;
}
	
bool PG_TimerObject::RemoveTimer(PG_TimerObject::ID id) {
	SDL_TimerID sid = my_timermap[id];
	my_timermap.erase(id);
	timermap.erase(id);
	
	return SDL_RemoveTimer(sid);
}
	
Uint32 PG_TimerObject::eventTimer(PG_TimerObject::ID id, Uint32 interval) {
	return interval;
}

Uint32 PG_TimerObject::eventTimer(Uint32 interval) {
	return interval;
}

Uint32 PG_TimerObject::callbackTimer(Uint32 interval, void* data) {
	PG_TimerObject::ID id = reinterpret_cast<PG_TimerObject::ID>(data);
	timermap[id]->sigTimer(timermap[id], id);
	return timermap[id]->eventTimer(id, interval);
}

Uint32 PG_TimerObject::callbackSingleTimer(Uint32 interval) {
	if(objSingleTimer != NULL) {
		objSingleTimer->sigTimer(objSingleTimer, (PG_TimerObject::ID)0);
		return objSingleTimer->eventTimer(interval);
	}
	
	return 0;
}

int PG_TimerObject::SetTimer(Uint32 interval) {
	StopTimer();
	objSingleTimer = this;
	return SDL_SetTimer(interval, &PG_TimerObject::callbackSingleTimer);
}
	
void PG_TimerObject::StopTimer() {
	objSingleTimer = NULL;
	SDL_SetTimer(0, NULL);
}
