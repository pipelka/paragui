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
    Source File:      $Source: /sources/paragui/paragui/include/Attic/gp2xapplication.h,v $
    CVS/RCS Revision: $Revision: 1.1.2.2 $
    Status:           $State: Exp $
*/

#include "paragui.h"

#ifdef PARAGUI_GP2X

#include "pgapplication.h"

#ifndef GP2X_APPLICATION_H
#define GP2X_APPLICATION_H

class GP2X_Application : public PG_Application {

	/**
	Run the applications main eventloop (GP2X version).
	If theaded is false this function will exit when the eventloop quits (MSG_QUIT). If threaded is true
	it will return immediately and a thread processing events is started.
	This function will create and activate a GP2X_Event eventsupplier object. You will get a full
	cursor / mouse emulation on the GP2X
	*/
	void Run();

};

#endif // GP2X_APPLICATION_H

#else

#error "You need to compile ParaGUI with support for the GP2X !"

#endif
