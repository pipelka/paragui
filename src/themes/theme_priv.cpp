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
    Update Date:      $Date: 2004/03/13 13:45:39 $
    Source File:      $Source: /sources/paragui/paragui/src/themes/theme_priv.cpp,v $
    CVS/RCS Revision: $Revision: 1.3.6.2.2.9 $
    Status:           $State: Exp $
*/

#include "theme_priv.h"
#include "pgcolor.h"

THEME_THEME::~THEME_THEME() {
	// clean up
	for(MAP_WIDGET::iterator i = widget.begin(); i != widget.end(); i++) {
		delete (*i).second;
	}
	widget.clear();

	delete defaultfont;
}

THEME_WIDGET* THEME_THEME::FindWidget(const char* widgettype) {
	if (!widgettype)
		return NULL;

	MAP_WIDGET::iterator i = widget.find(widgettype);
	if(i == widget.end()) {
		return NULL;
	}
	
	return (*i).second;
	//return widget[widgettype];
}

THEME_OBJECT* THEME_THEME::FindObject(const char* widgettype, const char* objectname) {
	THEME_WIDGET* widget = FindWidget(widgettype);

	if(widget == NULL) {
		return NULL;
	}

	THEME_OBJECT* object = widget->FindObject(objectname);

	return object;
}

SDL_Surface* THEME_THEME::FindSurface(const char* widgettype, const char* objectname, const char* name) {
	THEME_OBJECT* object = FindObject(widgettype, objectname);

	if(object == NULL) {
		return NULL;
	}

	return object->FindSurface(name);
}

PG_Gradient* THEME_THEME::FindGradient(const char* widgettype, const char* objectname, const char* name) {
	THEME_OBJECT* object = FindObject(widgettype, objectname);

	if(object == NULL) {
		return NULL;
	}

	return object->FindGradient(name);
}

void THEME_THEME::GetProperty(const char* widgettype, const char* objectname, const char* name, long& prop) {
	THEME_OBJECT* o = FindObject(widgettype, objectname);

	if(o == NULL) {
		return;
	}

	long n = o->FindProperty(name);
	if(n == -1) {
		return;
	}
	
	prop = n;
}

void THEME_THEME::GetProperty(const char* widgettype, const char* objectname, const char* name, Uint8& prop) {
	THEME_OBJECT* o = FindObject(widgettype, objectname);

	if(o == NULL) {
		return;
	}

	long n = o->FindProperty(name);
	if(n == -1) {
		return;
	}
	
	prop = (Uint8)n;
}

void THEME_THEME::GetProperty(const char* widgettype, const char* objectname, const char* name, bool& prop) {
	THEME_OBJECT* o = FindObject(widgettype, objectname);

	if(o == NULL) {
		return;
	}

	long n = o->FindProperty(name);
	if(n == -1) {
		return;
	}
	
	prop = (n == 1);
}

void THEME_THEME::GetProperty(const char* widgettype, const char* objectname, const char* name, int& prop) {
	THEME_OBJECT* o = FindObject(widgettype, objectname);

	if(o == NULL) {
		return;
	}

	long n = o->FindProperty(name);
	if(n == -1) {
		return;
	}
	
	prop = (int)n;
}

/*Uint8 THEME_THEME::FindTransparency(const char* widgettype, const char* objectname, const char* name, Uint8 def) {
	int result = FindProperty(widgettype, objectname, name, def);
	if(result == -1) {
		return def;
	}
	
	return (Uint8)result;
}*/

const char* THEME_THEME::FindString(const char* widgettype, const char* objectname, const char* name) {
	THEME_OBJECT* object = FindObject(widgettype, objectname);

	if(object == NULL) {
		return NULL;
	}

	return object->FindString(name);
}

const char* THEME_THEME::FindDefaultFontName() {
	if(!defaultfont) {
		return NULL;
	}

	return defaultfont->value.c_str();
}

int THEME_THEME::FindDefaultFontSize() {
	if(!defaultfont) {
		return 14;
	}

	return defaultfont->size;
}

PG_Font::Style THEME_THEME::FindDefaultFontStyle() {
	if(!defaultfont) {
		return PG_Font::NORMAL;
	}

	return defaultfont->style;
}

const char *THEME_THEME::FindFontName(const char* widgettype, const char* objectname) {
	THEME_OBJECT* o = FindObject(widgettype, objectname);

	if(o == NULL) {
		return NULL;
	}

	if(!o->font) {
		return NULL;
	}

	if(o->font->value.empty()) {
		return NULL;
	}

	return o->font->value.c_str();
}

int THEME_THEME::FindFontSize(const char* widgettype, const char* objectname) {
	THEME_OBJECT* o = FindObject(widgettype, objectname);

	if(o == NULL) {
		return 0;
	}

	if(!o->font) {
		return 0;
	}

	return o->font->size;
}

PG_Font::Style THEME_THEME::FindFontStyle(const char* widgettype, const char* objectname) {
	THEME_OBJECT* o = FindObject(widgettype, objectname);

	if(o == NULL) {
		return PG_Font::NORMAL;
	}

	if(!o->font) {
		return PG_Font::NORMAL;
	}

	return o->font->style;
}

THEME_WIDGET::~THEME_WIDGET() {
	for(MAP_OBJECT::iterator i = object.begin(); i != object.end(); i++) {
		delete (*i).second;
	}
	object.clear();
}

THEME_OBJECT* THEME_WIDGET::FindObject(const char* objectname) {
	if (!objectname)
		return NULL;

	THEME_OBJECT* result = object[objectname];

	if(result == NULL) {
		return NULL;
	}

	return result;
}

THEME_OBJECT::THEME_OBJECT() {
	font = NULL;
}

THEME_OBJECT::~THEME_OBJECT() {
	for(MAP_FILENAME::iterator f = filename.begin(); f != filename.end(); f++) {
		delete (*f).second;
	}
	filename.clear();

	for(MAP_GRADIENT::iterator g = gradient.begin(); g != gradient.end(); g++) {
		delete (*g).second;
	}
	gradient.clear();

	for(MAP_PROPERTY::iterator p = property.begin(); p != property.end(); p++) {
		delete (*p).second;
	}
	property.clear();

	for(Uint32 i=0; i<strings.size(); i++) {
		delete strings[i];
		strings[i] = NULL;
	}
	strings.clear();
	
	delete font;
}

SDL_Surface* THEME_OBJECT::FindSurface(const char* name) {
	if (!name)
		return NULL;

	THEME_FILENAME* result = filename[name];

	if(result == NULL) {
		return NULL;
	}

	return result->surface;
}

PG_Gradient* THEME_OBJECT::FindGradient(const char* name) {
	if (!name)
		return NULL;

	THEME_GRADIENT* result = gradient[name];

	if(result == NULL) {
		return NULL;
	}

	return static_cast<PG_Gradient*>(result);
}

void THEME_THEME::GetAlignment(const char* widgettype, const char* object, const char* name, PG_Label::TextAlign& align) {
	long b = -1;
	GetProperty(widgettype, object, name, b);

	if(b == -1) {
		return;
	}

	switch(b) {
		case 0:
			align = PG_Label::LEFT;
			break;
		case 1:
			align = PG_Label::CENTER;
			break;
		case 2:
			align = PG_Label::RIGHT;
			break;
	}

	return;
}

void THEME_THEME::GetColor(const char* widgettype, const char* object, const char* name, PG_Color& color) {
	long b = -1;
	GetProperty(widgettype, object, name, b);

	if(b == -1) {
		return;
	}

	color = (Uint32)b;
}

long THEME_OBJECT::FindProperty(const char* name) {
	if (!name)
		return -1;

	MAP_PROPERTY::iterator result = property.find(name);

	if(result == property.end()) {
		return -1;
	}

	return (*result).second->value;
}

const char* THEME_OBJECT::FindString(const char* name) {
	if (!name)
		return NULL;

	for(Uint32 i=0; i<strings.size(); i++) {
		if(strings[i]->name == (std::string)name) {
			return strings[i]->value.c_str();
		}
	}

	return NULL;
}
