#include "pgtimerobject.h"

Uint32 PG_TimerObject::my_objectcount = 0;

PG_TimerObject::PG_TimerObject() {
	if(my_objectcount == 0) {
		SDL_Init(SDL_INIT_TIMER);
	}
	
	my_timerid = 0;
	my_objectcount++;
}

PG_TimerObject::~PG_TimerObject() {
	my_objectcount--;
}
	
SDL_TimerID PG_TimerObject::AddTimer(Uint32 interval) {
	my_timerid = SDL_AddTimer(interval, &PG_TimerObject::callbackTimer, this);
	return my_timerid;
}
	
bool PG_TimerObject::RemoveTimer() {
	SDL_TimerID id = my_timerid;
	my_timerid = 0;
	return SDL_RemoveTimer(id);
}
	
Uint32 PG_TimerObject::eventTimer(Uint32 interval) {
	return interval;
}

Uint32 PG_TimerObject::callbackTimer(Uint32 interval, void* data) {
	PG_TimerObject* caller = static_cast<PG_TimerObject*>(data);
	return caller->eventTimer(interval);
}
