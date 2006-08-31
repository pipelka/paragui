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

#ifndef PG_THREAD_H
#define PG_THREAD_H

#include "SDL_thread.h"
#include "pgsignals.h"

class PG_Thread : public virtual SigC::Object {

public:

	PG_Thread();
	
	virtual ~PG_Thread();

	bool Start();
	
	bool Stop();

	PG_Signal1<PG_Thread*> sigThreadMain;

protected:

	virtual bool ThreadMain();

	bool IsRunning();

private:

	static int static_pgthread_main(void* data);

	SDL_mutex* my_mutex;
	
	SDL_Thread* my_thread;

	bool my_running;

};

#endif // PG_THREAD_H
