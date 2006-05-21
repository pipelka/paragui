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
