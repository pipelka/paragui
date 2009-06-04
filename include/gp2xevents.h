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
    Update Date:      $Date: 2009/06/04 10:25:02 $
    Source File:      $Source: /sources/paragui/paragui/include/Attic/gp2xevents.h,v $
    CVS/RCS Revision: $Revision: 1.1.2.2 $
    Status:           $State: Exp $
*/

#include "paragui.h"

#ifdef PARAGUI_GP2X

#ifndef GP2X_EVENTS_H
#define GP2X_EVENTS_H


#include "pgsdleventsupplier.h"
#include "SDL_thread.h"

class GP2X_Events : public PG_SDLEventSupplier {
public:

	GP2X_Events();

	~GP2X_Events();

	int GetMouseState(int& x, int& y);

	bool start();

	bool stop();

protected:

	int thread();

	static int thread_stub(void *data);

	SDL_Joystick* m_joy;

	SDL_Thread* m_thread;

	bool m_running;

	int m_button;

	int m_x;

	int m_y;

	int m_dx;

	int m_dy;
};

#endif // GP2X_EVENTS_H

#else

#error "You need to compile ParaGUI with support for the GP2X !"

#endif // PARAGUI_GP2X
