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
    Source File:      $Source: /sources/paragui/paragui/include/pgtimerobject.h,v $
    CVS/RCS Revision: $Revision: 1.1.2.6.2.1 $
    Status:           $State: Exp $
*/

#ifndef PG_TIMEROBJECT_H
#define PG_TIMEROBJECT_H

#include "paragui.h"
#include "pgsignals.h"
#include <map>

typedef Uint32 PG_TimerID;

/**
	@author Alexander Pipelka
 
	@short A class to handle periodical timers
 
	This class encapsulates the SDL_AddTimer, SDL_RemoveTimer functions.
*/

class DECLSPEC PG_TimerObject {
	
public:
	
	/**
	Signal type declaration
	**/
	template<class datatype = PG_Pointer> class SignalTimer : public PG_Signal2<PG_TimerObject*, PG_TimerID, datatype> {};

	/**
	Constructor of the PG_TimerObject class.
	The constructor also calls SDL_InitSubSystem(SDL_Timer) to enable
	the SDL timer subsystem.
	*/
	PG_TimerObject();

	virtual ~PG_TimerObject();
	
	/**
	Add a timer to the object.
	
	@param interval timer intervall in ms
	@return id of the timer
	
	You can add any number of timers to an object.
	After the timer-interval the virtual function eventTimer(PG_TimerID id, Uint32 interval)
	will be called
	*/
	PG_TimerID AddTimer(Uint32 interval);
	
	/**
	Remove a timer
	
	@param id id of the timer to remove
	*/
	bool RemoveTimer(PG_TimerID id);
	
	int SetTimer(Uint32 interval);
	
	void StopTimer();
	
	/**
	timer event handler
	
	@param id id of the elapsed timer
	@param interval timer interval
	@return should return the interval of the next timer event
	*/
	virtual Uint32 eventTimer(PG_TimerID id, Uint32 interval);
	
	virtual Uint32 eventTimer(Uint32 interval);
	
	SignalTimer<> sigTimer;

private:
	
	static Uint32 callbackTimer(Uint32 interval, void* data);
	static Uint32 callbackSingleTimer(Uint32 interval);
	
	static PG_TimerID globalTimerID;
	static map<PG_TimerID, PG_TimerObject*> timermap;
	static Uint32 objectcount;
	static PG_TimerObject* objSingleTimer;
	
	map<PG_TimerID, SDL_TimerID> my_timermap;	
};

#endif // PG_TIMEROBJECT_H
