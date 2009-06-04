#include "paragui.h"

#ifdef PARAGUI_GP2X

#include "gp2xapplication.h"
#include "gp2xevents.h"

void GP2X_Application::Run() {
	GP2X_Events* eventsupplier = new GP2X_Events;

	SetEventSupplier(eventsupplier);
	eventsupplier->start();

	PG_Application::Run();

	eventsupplier->stop();
}

#endif // PARAGUI_GP2X
