#include "paragui.h"

#ifdef PARAGUI_GP2X

#include "gp2xevents.h"
#include "pglog.h"

GP2X_Events::GP2X_Events() : m_joy(NULL) {
	SDL_InitSubSystem(SDL_INIT_JOYSTICK);
	m_running = false;
	
	m_x = 0;
	m_y = 0;
	m_button = 0;
}

GP2X_Events::~GP2X_Events() {
	stop();
}

int GP2X_Events::GetMouseState(int& x, int& y) {
	x = m_x;
	y = m_y;

	return m_button;
}

int GP2X_Events::thread() {
    static int l_x = 0;
    static int l_y = 0;
    static int l_button = 0;

    while(m_running) {

	    m_dx = 0;
	    m_dy = 0;
	    m_button = 0;

	    // UP	    
	    if(SDL_JoystickGetButton(m_joy, 0)) {
		    m_dy = -1;
	    }
	    
	    // DOWN
	    if(SDL_JoystickGetButton(m_joy, 4)) {
		    m_dy = 1;
	    }

	    // LEFT
	    if(SDL_JoystickGetButton(m_joy, 2)) {
		    m_dx = -1;
	    }

	    // RIGHT
	    if(SDL_JoystickGetButton(m_joy, 6)) {
		    m_dx = 1;
	    }

	    // UP - LEFT
	    if(SDL_JoystickGetButton(m_joy, 1)) {
		    m_dy = -1;
		    m_dx = -1;
	    }

	    // UP - RIGHT
	    if(SDL_JoystickGetButton(m_joy, 7)) {
		    m_dy = -1;
		    m_dx = 1;
	    }

	    // DOWN - LEFT
	    if(SDL_JoystickGetButton(m_joy, 3)) {
		    m_dy = 1;
		    m_dx = -1;
	    }

	    // DOWN - RIGHT
	    if(SDL_JoystickGetButton(m_joy, 5)) {
		    m_dy = 1;
		    m_dx = 1;
	    }

	    // CLICK
	    if(SDL_JoystickGetButton(m_joy, 18)) {
		    m_button |= SDL_BUTTON(1);
	    }

	    // A
	    if(SDL_JoystickGetButton(m_joy, 12)) {
		    m_button |= SDL_BUTTON(2);
	    }

	    // B
	    if(SDL_JoystickGetButton(m_joy, 13)) {
		    m_button |= SDL_BUTTON(3);
	    }

	    // X
	    if(SDL_JoystickGetButton(m_joy, 14)) {
		    m_button |= SDL_BUTTON(1);
	    }

	    m_x += m_dx * 2;
	    m_y += m_dy * 2;

	    if(l_x != m_x || l_y != m_y) {
		    SDL_WarpMouse(m_x, m_y);
		    SDL_Event event;
		    
		    event.type = SDL_MOUSEMOTION;
		    event.motion.type = SDL_MOUSEMOTION;
		    event.motion.state = (m_button & SDL_BUTTON(1)) ? SDL_PRESSED : SDL_RELEASED;
		    event.motion.x = m_x;
		    event.motion.y = m_y;
		    event.motion.xrel = 0;
		    event.motion.yrel = 0;
		    
		    SDL_PushEvent(&event);
	    }
	    
	    if(l_button != m_button) {
		bool l_1 = (l_button & SDL_BUTTON(1)) == SDL_BUTTON(1);
		bool m_1 = (m_button & SDL_BUTTON(1)) == SDL_BUTTON(1);
		bool l_2 = (l_button & SDL_BUTTON(2)) == SDL_BUTTON(2);
		bool m_2 = (m_button & SDL_BUTTON(2)) == SDL_BUTTON(2);
		bool l_3 = (l_button & SDL_BUTTON(3)) == SDL_BUTTON(3);
		bool m_3 = (m_button & SDL_BUTTON(3)) == SDL_BUTTON(3);
		
		SDL_Event event;
		if(l_1 != m_1) {
			event.type = m_1 ? SDL_MOUSEBUTTONDOWN : SDL_MOUSEBUTTONUP;
			event.button.type = event.type;
			event.button.button = SDL_BUTTON_LEFT;
			event.button.state = m_1 ? SDL_PRESSED : SDL_RELEASED;
			event.button.x = m_x;
			event.button.y = m_y;

			SDL_PushEvent(&event);
		}

		if(l_2 != m_2) {
			event.type = m_2 ? SDL_MOUSEBUTTONDOWN : SDL_MOUSEBUTTONUP;
			event.button.type = event.type;
			event.button.button = SDL_BUTTON_MIDDLE;
			event.button.state = m_2 ? SDL_PRESSED : SDL_RELEASED;
			event.button.x = m_x;
			event.button.y = m_y;

			SDL_PushEvent(&event);
		}

		if(l_3 != m_3) {
			event.type = m_3 ? SDL_MOUSEBUTTONDOWN : SDL_MOUSEBUTTONUP;
			event.button.type = event.type;
			event.button.button = SDL_BUTTON_RIGHT;
			event.button.state = m_3 ? SDL_PRESSED : SDL_RELEASED;
			event.button.x = m_x;
			event.button.y = m_y;

			SDL_PushEvent(&event);
		}

	    }

	    l_x = m_x;
	    l_y = m_y;
	    l_button = m_button;

	    SDL_Delay(10);
    }

    return 0;
}

int GP2X_Events::thread_stub(void *data) {
	GP2X_Events* caller = static_cast<GP2X_Events*>(data);
	return caller->thread();
}

bool GP2X_Events::start() {
	if(SDL_NumJoysticks()>0) {
		m_joy = SDL_JoystickOpen(0);
	}
	else {
		PG_LogDBG("failed to open gp2x joystick device");
		return false;
	}
	
	m_running = true;
	SDL_CreateThread(&GP2X_Events::thread_stub, this);
	return true;
}

bool GP2X_Events::stop() {
	if(!SDL_JoystickOpened(0)) {
		return false;
	}

	m_running = false;
	int status;
	SDL_WaitThread(m_thread, &status);

	SDL_JoystickClose(m_joy);

	return true;	
}

#else
#warning GP2X support disabled
#endif // PARAGUI_GP2X
