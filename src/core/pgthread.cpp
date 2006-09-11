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
 
    Last Update:      $Author$
    Update Date:      $Date$
    Source File:      $Source$
    CVS/RCS Revision: $Revision$
    Status:           $State$
*/

#include "pgthread.h"
#include "pglog.h"

PG_Thread::PG_Thread() : my_thread(NULL), my_running(false) {
	my_mutex = SDL_CreateMutex();
}
	
PG_Thread::~PG_Thread() {
	Stop();
	SDL_DestroyMutex(my_mutex);
}

bool PG_Thread::Start() {
	if(IsRunning()) {
		return false;
	}
	
	my_running = true;
	my_thread = SDL_CreateThread(&PG_Thread::static_pgthread_main, (void*)this);
	
	return true;
}
	
bool PG_Thread::Stop() {
	if(!IsRunning()) {
		return false;
	}

	SDL_mutexP(my_mutex);
	my_running = false;
	SDL_mutexV(my_mutex);

	int status = 0;
	SDL_WaitThread(my_thread, &status);
	return (status == 1);
}

int PG_Thread::static_pgthread_main(void* data) {
	PG_Thread* caller = static_cast<PG_Thread*>(data);

	if(caller->sigThreadMain(caller)) {
		return 1;
	}
	return caller->ThreadMain();
}

bool PG_Thread::IsRunning() {
	bool r;
	
	//SDL_mutexP(my_mutex);
	r = my_running;
	//SDL_mutexV(my_mutex);
	
	return r;
}

bool PG_Thread::ThreadMain() {
	return false;
}
