/*
    ParaGUI - crossplatform widgetset
    Copyright (C) 2000,2001  Alexander Pipelka
 
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
    Update Date:      $Date: 2002/04/15 13:35:36 $
    Source File:      $Source: /sources/paragui/paragui/src/themes/theme_priv.h,v $
    CVS/RCS Revision: $Revision: 1.3 $
    Status:           $State: Exp $
*/

#ifndef THEME_PRIV_H
#define THEME_PRIV_H

#include "paragui.h"

#include <string>
#include <vector>

#include "pgfilearchive.h"
#include "pgtheme.h"
#include "pgfont.h"

#ifdef HASH_MAP_INC
#include HASH_MAP_INC
#else
#include <map>
#endif

class THEME_FONT {
public:
	THEME_FONT() {
		size = 14;
		index = 0;
		style = 0;
	}
	std::string name;
	std::string value;
	int size;
	int index;
	int style;
};

class THEME_COLOR {
public:
	SDL_Color c;
	Uint32 val;
};

class THEME_STRING {
public:
	virtual ~THEME_STRING() {}

	std::string name;
	std::string value;
};

class THEME_FILENAME {
public:
	THEME_FILENAME() {
		surface = NULL;
	}

	virtual ~THEME_FILENAME() {
		PG_FileArchive::UnloadSurface(surface);
	}

	std::string name;
	std::string value;
	Uint32 colorkey;
	bool hasColorKey;
	SDL_Surface* surface;
};

class THEME_PROPERTY {
public:
	std::string name;
	long value;
};

class THEME_GRADIENT {
public:
	std::string name;
	THEME_COLOR color[4];
	PG_Gradient gradient;
};

#ifdef HASH_MAP_INC
// Why go through the extra job of creating strings for comparision instead
// of using char * directly?
struct pg_hashstr {
	size_t operator()(std::string s1) const {
		return std::hash<const char *>()(s1.c_str());
	}
};
#endif

class THEME_OBJECT {
public:

	THEME_OBJECT();
	virtual ~THEME_OBJECT();

	SDL_Surface* FindSurface(const char* name);
	PG_Gradient* FindGradient(const char* name);
	long FindProperty(const char* name);
	const char* FindString(const char* name);
	THEME_FONT* font;

	std::string type;
	std::string name;

	std::vector<THEME_STRING*> strings;

#ifdef HASH_MAP_INC
	typedef std::hash_map<std::string, THEME_FILENAME*, pg_hashstr> MAP_FILENAME;
	typedef std::hash_map<std::string, THEME_GRADIENT*, pg_hashstr> MAP_GRADIENT;
	typedef std::hash_map<std::string, THEME_PROPERTY*, pg_hashstr> MAP_PROPERTY;
#else
	typedef std::map<std::string, THEME_FILENAME*> MAP_FILENAME;
	typedef std::map<std::string, THEME_GRADIENT*> MAP_GRADIENT;
	typedef std::map<std::string, THEME_PROPERTY*> MAP_PROPERTY;
#endif

	MAP_FILENAME filename;
	MAP_GRADIENT gradient;
	MAP_PROPERTY property;
};

class THEME_WIDGET {
public:

	THEME_WIDGET() {}
	;
	virtual ~THEME_WIDGET();

	THEME_OBJECT* FindObject(const char* objectname);

	std::string type;

#ifdef HASH_MAP_INC
	typedef std::hash_map<std::string, THEME_OBJECT*, pg_hashstr> MAP_OBJECT;
#else
	typedef std::map<std::string, THEME_OBJECT*> MAP_OBJECT;
#endif

	MAP_OBJECT object;
};

class THEME_THEME : public PG_Theme {
public:

	THEME_THEME() {
		defaultfont = NULL;
	};

	virtual ~THEME_THEME();

	const char* FindDefaultFontName();
	int FindDefaultFontSize();
	int FindDefaultFontStyle();

	const char* FindFontName(const char*, const char*);
	int FindFontSize(const char*, const char*);
	int FindFontStyle(const char*, const char*);

	SDL_Surface* FindSurface(const char* widgettype, const char* object, const char* name);
	PG_Gradient* FindGradient(const char* widgettype, const char* object, const char* name);
	long FindProperty(const char* widgettype, const char* object, const char* name);
	SDL_Color* FindColor(const char* widgettype, const char* object, const char* name);
	const char* FindString(const char* widgettype, const char* object, const char* name);

	THEME_FONT* defaultfont;

	std::string title;
	std::string description;
	std::string author;
	std::string email;

#ifdef HASH_MAP_INC
	typedef std::hash_map<std::string, THEME_WIDGET*, pg_hashstr> MAP_WIDGET;
#else
	typedef std::map<std::string, THEME_WIDGET*> MAP_WIDGET;
#endif

	MAP_WIDGET widget;

	THEME_WIDGET* FindWidget(const char* widgettype);
	THEME_OBJECT* FindObject(const char* widgettype, const char* objectname);
};

#endif // THEME_PRIV_H
