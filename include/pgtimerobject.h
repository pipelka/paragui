#ifndef PG_TIMEROBJECT_H
#define PG_TIMEROBJECT_H

#include "paragui.h"
#include <map>

class PG_TimerObject {
	
public:
	
	PG_TimerObject();

	virtual ~PG_TimerObject();
	
	SDL_TimerID AddTimer(Uint32 interval);
	
	bool RemoveTimer();
	
	virtual Uint32 eventTimer(Uint32 interval);
	
private:
	
	static Uint32 callbackTimer(Uint32 interval, void* data);
	
	SDL_TimerID my_timerid;	
	static Uint32 my_objectcount;
};

#endif // PG_TIMEROBJECT_H
