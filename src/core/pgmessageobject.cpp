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
    Update Date:      $Date: 2002/04/27 11:57:22 $
    Source File:      $Source: /sources/paragui/paragui/src/core/pgmessageobject.cpp,v $
    CVS/RCS Revision: $Revision: 1.2 $
    Status:           $State: Exp $
*/

#include <iostream>
#include "pgmessageobject.h"
#include "pgwidget.h"
#include "pglog.h"
#include <algorithm>

// static variables for message processing
std::vector<PG_MessageObject*> PG_MessageObject::objectList;
PG_MessageObject* PG_MessageObject::captureObject = NULL;
PG_MessageObject* PG_MessageObject::inputFocusObject = NULL;
PG_Widget* PG_MessageObject::lastwidget = NULL;
bool PG_MessageObject::my_quitEventLoop = false;

/** constructor */

PG_MessageObject::PG_MessageObject() {

	// init vars
	my_canReceiveMessages = true;
	my_oldCapture = NULL;
	my_oldFocus = NULL;

	objectList.push_back(this);

	// init mutexes
	my_mutexSendMessage = SDL_CreateMutex();
	my_mutexReceiveMessage = SDL_CreateMutex();
}


/**  destructor */

PG_MessageObject::~PG_MessageObject() {

	// destroy mutexes
	SDL_DestroyMutex(my_mutexSendMessage);
	my_mutexSendMessage = NULL;

	SDL_DestroyMutex(my_mutexReceiveMessage);
	my_mutexReceiveMessage = NULL;

	RemoveObject(this);

	if (inputFocusObject == this)
		inputFocusObject = NULL;
	if (lastwidget == this)
		lastwidget = NULL;
}

/** enable / disable if object can receive messages */

void PG_MessageObject::EnableReceiver(bool enable) {
	my_canReceiveMessages = enable;
}


/** message dispatcher */

bool PG_MessageObject::ProcessEvent(const SDL_Event* event) {
	SDL_Event e;
	
	if(SDL_mutexP(my_mutexReceiveMessage) == -1)
		return false;

	// check if we are able to process messages
	if(!my_canReceiveMessages) {
		SDL_mutexV(my_mutexReceiveMessage);
		return false;
	}

	if(event->type != SDL_USEREVENT) {
		if(captureObject != this)
			if(!AcceptEvent(event)) {
				SDL_mutexV(my_mutexReceiveMessage);
				return false;
			}
	}

	if((captureObject != NULL) && (captureObject != this)) {
		return false;
	}

	while(SDL_PeepEvents(&e, 1, SDL_GETEVENT, SDL_MOUSEMOTIONMASK) > 0);

	bool rc = false;

	// dispatch message
	switch(event->type) {
		case SDL_ACTIVEEVENT:
			rc = eventActive(&event->active);
			break;

		case SDL_KEYDOWN:
			rc = eventKeyDown(&event->key);
			break;

		case SDL_KEYUP:
			rc = eventKeyUp(&event->key);
			break;

		case SDL_MOUSEMOTION:
			rc = eventMouseMotion(&event->motion);
			break;

		case SDL_MOUSEBUTTONDOWN:
			rc = eventMouseButtonDown(&event->button);
			break;

		case SDL_MOUSEBUTTONUP:
			rc = eventMouseButtonUp(&event->button);
			break;

		case SDL_QUIT:
			rc = eventQuit(PG_IDAPPLICATION, NULL, (unsigned long)&event->quit);
			break;

		case SDL_SYSWMEVENT:
			rc = eventSysWM(&event->syswm);
			break;

		case SDL_VIDEORESIZE:
			rc = eventResize(&event->resize);
			break;

		default:
			rc = false;
			break;
	}

	SDL_mutexV(my_mutexReceiveMessage);

	return rc;
}


/** virtual message handlers */

bool PG_MessageObject::eventResize(const SDL_ResizeEvent* event) {
	return false;
}

bool PG_MessageObject::eventActive(const SDL_ActiveEvent* active) {
	return false;
}


bool PG_MessageObject::eventKeyDown(const SDL_KeyboardEvent* key) {
	return false;
}


bool PG_MessageObject::eventKeyUp(const SDL_KeyboardEvent* key) {
	return false;
}


bool PG_MessageObject::eventMouseMotion(const SDL_MouseMotionEvent* motion) {
	return false;
}


bool PG_MessageObject::eventMouseButtonDown(const SDL_MouseButtonEvent* button) {
	return false;
}


bool PG_MessageObject::eventMouseButtonUp(const SDL_MouseButtonEvent* button) {
	return false;
}


bool PG_MessageObject::eventQuit(int id, PG_MessageObject* widget, unsigned long data) {
	return false;
}

bool PG_MessageObject::eventQuitModal(int id, PG_MessageObject* widget, unsigned long data) {
	return false;
}


bool PG_MessageObject::eventSysWM(const SDL_SysWMEvent* syswm) {
	return false;
}

bool PG_MessageObject::AcceptEvent(const SDL_Event* event) {
	return true;				// PG_MessageObject accepts all events
}

/** capture handling (an object can capture all messages) */

PG_MessageObject* PG_MessageObject::SetCapture() {
	if(captureObject == this)
		return my_oldCapture;

	my_oldCapture = captureObject;
	captureObject = this;
	return my_oldCapture;
}


void PG_MessageObject::ReleaseCapture() {
	if(captureObject != this) {
		return;
	}

	captureObject = my_oldCapture;
}

PG_MessageObject* PG_MessageObject::SetInputFocus() {
	if(inputFocusObject == this)
		return my_oldFocus;

	my_oldFocus = inputFocusObject;

	if(my_oldFocus != NULL) {
		my_oldFocus->eventInputFocusLost(inputFocusObject);
	}

	inputFocusObject = this;
	return my_oldFocus;
}


/** */
void PG_MessageObject::eventInputFocusLost(PG_MessageObject* newfocus) {}


/** */
void PG_MessageObject::ReleaseInputFocus() {
	if(inputFocusObject != this) {
		return;
	}

	inputFocusObject = NULL;
}


/** global event handler */

bool PG_MessageObject::PumpIntoEventQueue(const SDL_Event* event) {
	PG_Widget* widget = NULL;

	// do we have a capture hook?
	if((event->type != SDL_USEREVENT) && (event->type != SDL_VIDEORESIZE) /*&& (event->type != SDL_VIDEOEXPOSE)*/) {
		if(captureObject) {
			return captureObject->ProcessEvent(event);
		}
	}

	switch(event->type) {

		case SDL_KEYDOWN:
		case SDL_KEYUP:
			if(inputFocusObject) {
				// first send it to the focus object
				if(inputFocusObject->ProcessEvent(event)) {
					return true;
				}
				// if the focus object doesn't respond -> pump it into the queue
			}
			break;

		case SDL_MOUSEMOTION:
			widget = PG_Widget::FindWidgetFromPos(event->motion.x, event->motion.y);

			if(lastwidget && (lastwidget != widget)) {
				lastwidget->eventMouseLeave();
				lastwidget = NULL;
			}

			if(widget) {
				lastwidget = widget;
				widget->ProcessEvent(event);
				return true;
			}
			break;

		case SDL_MOUSEBUTTONUP:
		case SDL_MOUSEBUTTONDOWN:
			widget = PG_Widget::FindWidgetFromPos(event->button.x, event->button.y);
			if(widget) {
				widget->ProcessEvent(event);
				return true;
			}
			break;
			/*
					case SDL_VIDEOEXPOSE:
						PG_Widget::UpdateScreen();
						return 0;
			*/
	}

	// send to all receivers
	bool processed = false;
	std::vector<PG_MessageObject*>::iterator list = objectList.begin();
	while(list != objectList.end()) {
		if((*list)->ProcessEvent(event)) {
			processed = true;
			break;		// exit loop if an object responds
		}
		list++;
	}

	return processed;
}


void PG_MessageObject::eventIdle() {
	sigAppIdle(this);
	SDL_Delay(1);
}


SDL_Event PG_MessageObject::WaitEvent(Uint32 delay) {
	static SDL_Event event;

	while(SDL_PollEvent(&event) == 0) {
		//		eventIdle();
		if(delay > 0) {
			SDL_Delay(delay);
		}
	}

	return event;
}


/** Remove an object from the message queue  */

bool PG_MessageObject::RemoveObject(PG_MessageObject* obj) {
	std::vector<PG_MessageObject*>::iterator list = objectList.begin();

	// search the object
	list = std::find(objectList.begin(), objectList.end(), obj);

	// check if object was found
	if(list == objectList.end()) {
		PG_LogWRN("PG_MessageObject::RemoveObject(..)");
		PG_LogWRN("Trying to remove non-existent object from the list !!");
		return false;
	}

	// remove the object from the chain
	objectList.erase(list);

	return true;
}

void PG_MessageObject::TranslateNumpadKeys(SDL_KeyboardEvent *key) {
	// note: works on WIN, test this on other platforms

	// numeric keypad translation
	if (key->keysym.unicode==0) {	 // just optimalisation
		if (key->keysym.mod & KMOD_NUM) {
			// numeric keypad is enabled
			switch (key->keysym.sym) {
				case SDLK_KP0       :
					key->keysym.sym = SDLK_0;
					key->keysym.unicode = SDLK_0;
					break;
				case SDLK_KP1       :
					key->keysym.sym = SDLK_1;
					key->keysym.unicode = SDLK_1;
					break;
				case SDLK_KP2       :
					key->keysym.sym = SDLK_2;
					key->keysym.unicode = SDLK_2;
					break;
				case SDLK_KP3       :
					key->keysym.sym = SDLK_3;
					key->keysym.unicode = SDLK_3;
					break;
				case SDLK_KP4       :
					key->keysym.sym = SDLK_4;
					key->keysym.unicode = SDLK_4;
					break;
				case SDLK_KP5       :
					key->keysym.sym = SDLK_5;
					key->keysym.unicode = SDLK_5;
					break;
				case SDLK_KP6       :
					key->keysym.sym = SDLK_6;
					key->keysym.unicode = SDLK_6;
					break;
				case SDLK_KP7       :
					key->keysym.sym = SDLK_7;
					key->keysym.unicode = SDLK_7;
					break;
				case SDLK_KP8       :
					key->keysym.sym = SDLK_8;
					key->keysym.unicode = SDLK_8;
					break;
				case SDLK_KP9       :
					key->keysym.sym = SDLK_9;
					key->keysym.unicode = SDLK_9;
					break;
				case SDLK_KP_PERIOD :
					key->keysym.sym = SDLK_PERIOD;
					key->keysym.unicode = SDLK_PERIOD;
					break;
				case SDLK_KP_DIVIDE :
					key->keysym.sym = SDLK_BACKSLASH;
					key->keysym.unicode = SDLK_BACKSLASH;
					break;
				case SDLK_KP_MULTIPLY:
					key->keysym.sym = SDLK_ASTERISK;
					key->keysym.unicode = SDLK_ASTERISK;
					break;
				case SDLK_KP_MINUS  :
					key->keysym.sym = SDLK_MINUS;
					key->keysym.unicode = SDLK_MINUS;
					break;
				case SDLK_KP_PLUS   :
					key->keysym.sym = SDLK_PLUS;
					key->keysym.unicode = SDLK_PLUS;
					break;
				case SDLK_KP_ENTER  :
					key->keysym.sym = SDLK_RETURN;
					key->keysym.unicode = SDLK_RETURN;
					break;
				case SDLK_KP_EQUALS :
					key->keysym.sym = SDLK_EQUALS;
					key->keysym.unicode = SDLK_EQUALS;
					break;

				default:
					break;
			}
		} else {
			// numeric keypad is disabled
			switch (key->keysym.sym) {
				case SDLK_KP0       :
					key->keysym.sym = SDLK_INSERT;
					key->keysym.unicode = 0;
					break;
				case SDLK_KP1       :
					key->keysym.sym = SDLK_END;
					key->keysym.unicode = 0;
					break;
				case SDLK_KP2       :
					key->keysym.sym = SDLK_DOWN;
					key->keysym.unicode = 0;
					break;
				case SDLK_KP3       :
					key->keysym.sym = SDLK_PAGEDOWN;
					key->keysym.unicode = 0;
					break;
				case SDLK_KP4       :
					key->keysym.sym = SDLK_LEFT;
					key->keysym.unicode = 0;
					break;
				case SDLK_KP6       :
					key->keysym.sym = SDLK_RIGHT;
					key->keysym.unicode = 0;
					break;
				case SDLK_KP7       :
					key->keysym.sym = SDLK_HOME;
					key->keysym.unicode = 0;
					break;
				case SDLK_KP8       :
					key->keysym.sym = SDLK_UP;
					key->keysym.unicode = 0;
					break;
				case SDLK_KP9       :
					key->keysym.sym = SDLK_PAGEUP;
					key->keysym.unicode = 0;
					break;
				case SDLK_KP_PERIOD :
					key->keysym.sym = SDLK_DELETE;
					key->keysym.unicode = 0;
					break;
				case SDLK_KP_DIVIDE :
					key->keysym.sym = SDLK_BACKSLASH;
					key->keysym.unicode = SDLK_BACKSLASH;
					break;
				case SDLK_KP_MULTIPLY:
					key->keysym.sym = SDLK_ASTERISK;
					key->keysym.unicode = SDLK_ASTERISK;
					break;
				case SDLK_KP_MINUS  :
					key->keysym.sym = SDLK_MINUS;
					key->keysym.unicode = SDLK_MINUS;
					break;
				case SDLK_KP_PLUS   :
					key->keysym.sym = SDLK_PLUS;
					key->keysym.unicode = SDLK_PLUS;
					break;
				case SDLK_KP_ENTER  :
					key->keysym.sym = SDLK_RETURN;
					key->keysym.unicode = SDLK_RETURN;
					break;
				case SDLK_KP_EQUALS :
					key->keysym.sym = SDLK_EQUALS;
					key->keysym.unicode = SDLK_EQUALS;
					break;

				default:
					break;
			}
		}
	}
}

PG_MessageObject* PG_MessageObject::GetCapture() {
	return captureObject;
}

bool PG_MessageObject::IsEnabled() {
	return my_canReceiveMessages;
}
