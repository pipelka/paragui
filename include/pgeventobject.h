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
    Update Date:      $Date: 2003/11/21 12:27:51 $
    Source File:      $Source: /sources/paragui/paragui/include/Attic/pgeventobject.h,v $
    CVS/RCS Revision: $Revision: 1.3.2.1 $
    Status:           $State: Exp $
*/

/** \file pgeventobject.h
	Header file of the PG_EventObject class.
*/

#ifndef PG_EVENTOBJECT_H
#define PG_EVENTOBJECT_H

#ifdef SWIG
%include "swigcommon.h"
%module pgeventobject
%{
#include "pgeventobject.h"
%}
#endif

#include "paragui.h"
#include "pgsignals.h"

/**
	@author Alexander Pipelka
	
	@short Base class for all objects that define callback members
 
	If you want to define a callback function as a member of a class you
	have to subclass your objects from PG_EventObject. This is necessary
	because member callbacks are handled differently from plain "C" callbacks.
*/

class DECLSPEC PG_EventObject {
public:

	/** */
	PG_EventObject();

	/** */
	virtual ~PG_EventObject();
};

#endif	// PG_EVENTOBJECT_H
