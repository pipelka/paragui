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
    Source File:      $Source: /sources/paragui/paragui/include/pgdatacontainer.h,v $
    CVS/RCS Revision: $Revision: 1.3.8.4 $
    Status:           $State: Exp $
*/

/** \file pgdatacontainer.h
	Header file for the PG_DataContainer class.
*/

#ifndef PG_DATACONTAINER
#define PG_DATACONTAINER

#include "paragui.h"

/**
	@short A container for binary data
	@author Alexander Pipelka
	
	This class is a container to hold binary data (imagedata, fonts,...).
*/

class DECLSPEC PG_DataContainer {
public:

	/**
		Constructor
		@param size	number of bytes to allocate

		Creates a container which can hold "size" number of bytes.
	*/
	PG_DataContainer(Uint32 size);

	/**
		Destructor

		Deletes the object and frees to allocated memory.
	*/
	virtual ~PG_DataContainer();

	/**
		return the number of bytes allocated by the container
		@return number of bytes allocated
	*/
	Uint32 size();

	/**
		access to the internal data
		@return pointer to allocated memory
	*/
	char* data();

private:

	char* my_data;

	Uint32 my_size;
};

#endif // PG_DATACONTAINER
