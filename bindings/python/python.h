#ifdef SWIG

%include "paragui.h"

// Grab a Python function object as a Python object.
%typemap(python,in) PyObject *pyfunc {
	if (!PyCallable_Check($input)) {
		PyErr_SetString(PyExc_TypeError, "Need a callable object!");
		return NULL;
	}
	$1 = $input;
}

%module pgmessageobject

%extend PG_MessageObject {

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
