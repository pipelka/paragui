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
    Update Date:      $Date: 2003/11/24 09:17:21 $
    Source File:      $Source: /sources/paragui/paragui/include/pgtheme.h,v $
    CVS/RCS Revision: $Revision: 1.3.2.1 $
    Status:           $State: Exp $
*/

#ifndef PG_THEME_H
#define PG_THEME_H

#ifdef SWIG
%module theme
%{
#include "pgtheme.h"
%}
#endif

#include "paragui.h"

/**
	@short Theme/style definition class
*/

class DECLSPEC PG_Theme {
public:

	virtual ~PG_Theme() {};

	virtual const char* FindDefaultFontName() = 0;
	virtual int FindDefaultFontSize() = 0;
	virtual int FindDefaultFontStyle() = 0;
	virtual const char* FindFontName(const char* widgettype, const char* objectname) = 0;
	virtual int FindFontSize(const char* widgettype, const char* objectname) = 0;
	virtual int FindFontStyle(const char* widgettype, const char* objectname) = 0;
	virtual SDL_Surface* FindSurface(const char* widgettype, const char* object, const char* name) = 0;
	virtual PG_Gradient* FindGradient(const char* widgettype, const char* object, const char* name) = 0;
	virtual void GetProperty(const char* widgettype, const char* object, const char* name, long& prop) = 0;
	virtual void GetProperty(const char* widgettype, const char* object, const char* name, Uint8& prop) = 0;
	virtual void GetProperty(const char* widgettype, const char* object, const char* name, bool& prop) = 0;
	virtual void GetProperty(const char* widgettype, const char* object, const char* name, int& prop) = 0;
	inline void GetProperty(const char* widgettype, const char* object, const char* name, Uint16& prop) {
		long b=-1;
		GetProperty(widgettype, object, name, b);
		if(b == -1) {
			return;
		}
		prop = (Uint16)b;
	}
	virtual void GetColor(const char* widgettype, const char* object, const char* name, PG_Color& color) = 0;
	virtual const char* FindString(const char* widgettype, const char* object, const char* name) = 0;

	/**
	Load and process a XML theme definition file.

	@param xmltheme The file name for the theme. The extension ".theme" is assumed.
	@return pointer to a newly created PG_Theme object or NULL if the operation failed

	Given the name of a file that contains the theme definition, it loads
	the Theme into ParaGUI's system
	*/
	static PG_Theme* Load(const char* xmltheme);

	/**
	*/
	static void Unload(PG_Theme* theme);
};

#endif // PG_THEME_H
