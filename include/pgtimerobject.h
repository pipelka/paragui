#ifndef PG_TIMEROBJECT_H
#define PG_TIMEROBJECT_H

#include "paragui.h"
#include <map>

typedef Uint32 PG_TimerID;

class PG_TimerObject {
	
public:
	
	PG_TimerObject();

	virtual ~PG_TimerObject();
	
	PG_TimerID AddTimer(Uint32 interval);
	
	bool RemoveTimer(PG_TimerID id);
	
	int SetTimer(Uint32 interval);
	
	void StopTimer();
	
	virtual Uint32 eventTimer(PG_TimerID id, Uint32 interval);
	virtual Uint32 eventTimer(Uint32 interval);
	
private:
	
	static Uint32 callbackTimer(Uint32 interval, void* data);
	static Uint32 callbackSingleTimer(Uint32 interval);
	
	static PG_TimerID globalTimerID;
	static std::map<PG_TimerID, PG_TimerObject*> timermap;
	static Uint32 objectcount;
	static PG_TimerObject* objSingleTimer;
	
	std::map<PG_TimerID, SDL_TimerID> my_timermap;	
};

#endif // PG_TIMEROBJECT_H
