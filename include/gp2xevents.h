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
