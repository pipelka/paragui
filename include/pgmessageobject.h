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
    Update Date:      $Date: 2002/05/02 08:45:36 $
    Source File:      $Source: /sources/paragui/paragui/include/pgmessageobject.h,v $
    CVS/RCS Revision: $Revision: 1.3.6.1 $
    Status:           $State: Exp $
*/

#ifndef PG_MESSAGEOBJECT_H
#define PG_MESSAGEOBJECT_H

#ifdef SWIG
%include "swigcommon.h"
%module pgmessageobject
%{
#include "pgmessageobject.h"
%}
#endif

#include "paragui.h"
#include <vector>

class PG_Widget;

/**
	@author Alexander Pipelka
	
	@short Base class of all objects (provides message handling).
 
	Provides a message pump and global handlers for all other PG_MessageObject instances.
*/

class DECLSPEC PG_MessageObject {

public:
	/**
	Creates a PG_MessageObject
	*/
	PG_MessageObject();

	/**
	Destroys a PG_MessageObject and removes it from the global object list.
	*/
	virtual ~PG_MessageObject();

	/**
	This function enables or disables receiving of SDL_Event messages.

	@param enable	Enable or disable the ability of receiving messages. When set to false
			no event handlers will be called for this object

	*/
	void EnableReceiver(bool enable);

	/**
	Set a message capture for this object. This object will receive all SDL_Event messages regardless
	if it is able to process them or not.
	*/
	PG_MessageObject* SetCapture();

	/**
	Releases a previous capture.
	*/
	void ReleaseCapture();

	/**
	Return the current capture object.
	*/
	PG_MessageObject* GetCapture();

	/**
	Set an inputfocus for this object
	@return	pointer to the object that had the inputfocus till now
	If the inputfocus is set all key events will be sent to this object
	*/
	PG_MessageObject* SetInputFocus();

	/**
	Release the inputfocus
	*/
	void ReleaseInputFocus();

	/**
	Check if the object can receive messages
	@return	true/false
	returns true when the object can receive messages or false if not.
	*/
	bool IsEnabled();

	/**
	Send a message to an object
	@param	target		object which will receive the message
	@param	type			type of the message (MSG_TYPE)
	@param	id
	@param	data			message specific data value
	*/
	bool SendMessage(PG_MessageObject* target, PG_MSG_TYPE type, MSG_ID id, MSG_DATA data);

	/**
	Set a callback function for an event
	@param	type				message type to trigger
	@param	cbfunc			the function to call when the defined event is triggerd
	@param	clientdata	client specific message data
	*/
	void SetEventCallback(PG_MSG_TYPE type, MSG_CALLBACK cbfunc, void *clientdata = NULL);

	/**
	Set an object member function for an event
	@param	type				message type to trigger
	@param	calledobj		pointer to called object
	@param	cbfunc			member function to call
	@param	clientdata	client specific message data
	*/
	void SetEventObject(PG_MSG_TYPE type, PG_EventObject* calledobj, MSG_CALLBACK_OBJ cbfunc, void *clientdata = NULL);

	/**
	Sends an event to the global message queue.

	@param event SDL_Event message
	@return true - the message was processed by the framework
	*/

	static bool PumpIntoEventQueue(const SDL_Event* event);

	/** */
	static SDL_Event WaitEvent(Uint32 delay=0);

	/**
	Translates numeric keypad keys into other keys in dependency of NUM_LOCK state.
	 Should be called in eventKeyDown() for proper numeric keypad behaviour.

	@param key SDL_KeyboardEvent* key to translate
	 */
	void TranslateNumpadKeys(SDL_KeyboardEvent *key);

	/**
	Sends an event directly to an object.

	@param event SDL_Event message

	@return Notifies the message pump if this message is processed by this object or it should be routed to the next message receiver.
	*/
	virtual bool ProcessEvent(const SDL_Event* event);

protected:

	/**
	Overridable Eventhandler for the SDL_ActiveEvent message.
	The default implementation returns 'false' which indicates that this message is not processed by this object.

	@param active SDL_ActiveEvent message

	@return Notifies the message pump if this message is processed by this object or it should be routed to the next message receiver.
	*/
	virtual bool eventActive(const SDL_ActiveEvent* active);

	/**
	Overridable Eventhandler for a SDL_KeyboardEvent message.
	This handler is called when a key changed it's state from unpressed to pressed.
	The default implementation returns 'false' which indicates that this message is not processed by this object.

	@param key SDL_KeyboardEvent message

	@return Notifies the message pump if this message is processed by this object or it should be routed to the next message receiver.
	*/
	virtual bool eventKeyDown(const SDL_KeyboardEvent* key);

	/**
	Overridable Eventhandler for a SDL_KeyboardEvent message.
	This handler is called when a key changed it's state from pressed to unpressed.
	The default implementation returns 'false' which indicates that this message is not processed by this object.

	@param key SDL_KeyboardEvent message

	@return Notifies the message pump if this message is processed by this object or it should be routed to the next message receiver.
	*/
	virtual bool eventKeyUp(const SDL_KeyboardEvent* key);

	/**
	Overridable Eventhandler for a SDL_MouseMotionEvent message.
	This handler is called when mouse movement is detected.
	The default implementation returns 'false' which indicates that this message is not processed by this object.

	@param motion SDL_MouseMotionEvent message

	@return Notifies the message pump if this message is processed by this object or it should be routed to the next message receiver.
	*/
	virtual bool eventMouseMotion(const SDL_MouseMotionEvent* motion);

	/**
	Overridable Eventhandler for a SDL_MouseButtonEvent message.
	This handler is called when a mouse button is pressed.
	The default implementation returns 'false' which indicates that this message is not processed by this object.

	@param button SDL_MouseButtonEvent message

	@return Notifies the message pump if this message is processed by this object or it should be routed to the next message receiver.
	*/
	virtual bool eventMouseButtonDown(const SDL_MouseButtonEvent* button);

	/**
	Overridable Eventhandler for a SDL_MouseButtonEvent message.
	This handler is called when a mouse button is released.
	The default implementation returns 'false' which indicates that this message is not processed by this object.

	@param button SDL_MouseButtonEvent message

	@return Notifies the message pump if this message is processed by this object or it should be routed to the next message receiver.
	*/
	virtual bool eventMouseButtonUp(const SDL_MouseButtonEvent* button);

	/**
	Overridable Eventhandler for a SDL_QuitEvent message.
	The default implementation returns 'false' which indicates that this message is not processed by this object.

	@param id		id of the sending widget
	@param widget	pointer to the widget
	@param data	event specific data

	@return Notifies the message pump if this message is processed by this object or it should be routed to the next message receiver.
	*/
	virtual bool eventQuit(int id, PG_MessageObject* widget, unsigned long data);

	/**
	Overridable Eventhandler for a MSG_QUITMODAL message.
	The default implementation returns 'false' which indicates that this message is not processed by this object.

	@param id		id of the sending widget
	@param widget	pointer to the widget
	@param data	event specific data

	@return Notifies the message pump if this message is processed by this object or it should be routed to the next message receiver.
	*/
	virtual bool eventQuitModal(int id, PG_MessageObject* widget, unsigned long data);

	/**
	Overridable Eventhandler for a SDL_SysWMEvent message.
	The default implementation returns 'false' which indicates that this message is not processed by this object.

	@param syswm SDL_SysWMEvent message

	@return Notifies the message pump if this message is processed by this object or it should be routed to the next message receiver.
	*/
	virtual bool eventSysWM(const SDL_SysWMEvent* syswm);

	/**
	Overridable Eventhandler for a SDL_ResizeEvent message.
	The default implementation returns 'false' which indicates that this message is not processed by this object.

	@param event SDL_ResizeEvent message

	@return Notifies the message pump if this message is processed by this object or it should be routed to the next message receiver.
	*/
	virtual bool eventResize(const SDL_ResizeEvent* event);

	/**
	Overridable Eventhandler for a SDL_SysUserEvent message.
	The default implementation returns 'false' which indicates that this message is not processed by this object.

	@param event SDL_SysUserEvent message

	@return Notifies the message pump if this message is processed by this object or it should be routed to the next message receiver.
	*/
	virtual bool eventMessage(MSG_MESSAGE* msg);

	/** */
	virtual void eventInputFocusLost(PG_MessageObject* newfocus);

	/** */
	virtual void eventIdle();

	/**
	Overridable message filter function. Derivated classes can filter special events.
	The default implementation returns 'false' which indicates that this message is not processed by this object.

	@param event SDL_Event message

	@return Notifies the message pump if this message is processed by this object or it should be routed to the next message receiver.
	*/
	virtual bool AcceptEvent(const SDL_Event* event);

	static bool my_quitEventLoop;

#ifndef SWIG
	static std::vector<PG_MessageObject*> objectList;
#endif

	static PG_MessageObject* captureObject;

	// mutexes -- unused, but still here to keep binary compatibility
	SDL_mutex* my_mutexSendMessage;
	SDL_mutex* my_mutexReceiveMessage;

private:

#ifndef SWIG
	PG_MessageObject(const PG_MessageObject&);
	PG_MessageObject& operator=(const PG_MessageObject&);
#endif

	bool RemoveObject(PG_MessageObject* obj);

	static PG_MessageObject* inputFocusObject;
	static PG_Widget* lastwidget;

	PG_MessageObject* my_oldCapture;
	PG_MessageObject* my_oldFocus;

	bool my_canReceiveMessages;

#ifndef SWIG
	friend class PG_Application;
#endif
};


#ifdef SWIG

// Grab a Python function object as a Python object.
%typemap(python,in) PyObject *pyfunc {
	if (!PyCallable_Check($source)) {
		PyErr_SetString(PyExc_TypeError, "Need a callable object!");
		return NULL;
	}
	$target = $source;
}

%addmethods PG_MessageObject {

	// This function matches the prototype of the normal C callback
	// function for our widget. However, we use the clientdata pointer
	// for holding a reference to a Python callable object.

	static bool PythonCallBack(int id, PG_Widget *widget, unsigned long data, void *clientdata) {
		PyObject *func, *arglist;
		PyObject *result;
		bool     res = 0;

		func = (PyObject *) clientdata;               // Get Python function
		arglist = Py_BuildValue("(ill)",id,widget,data);// Build argument list
		result = PyEval_CallObject(func,arglist);     // Call Python
		Py_DECREF(arglist);                           // Trash arglist
		if (result) {                                 // If no errors, return double
			res = PyInt_AsLong(result);
		}
		Py_XDECREF(result);
		return res;
	}

	// Attach a new method to our plot widget for adding Python functions
	// Set a Python function object as a callback function
	// Note : PyObject *pyfunc is remapped with a typempap

	void set_pymethod(PG_MSG_TYPE type, PyObject *pyfunc) {
		self->SetEventCallback(type, PG_MessageObject_PythonCallBack, (void *) pyfunc);
		Py_INCREF(pyfunc);
	}
}

#endif

#endif // PG_MESSAGEOBJECT_H
