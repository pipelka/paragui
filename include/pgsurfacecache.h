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
    Update Date:      $Date: 2004/01/31 16:14:08 $
    Source File:      $Source: /sources/paragui/paragui/include/pgsurfacecache.h,v $
    CVS/RCS Revision: $Revision: 1.3.6.1.2.2 $
    Status:           $State: Exp $
*/

#ifndef PG_SURFACECACHE_H
#define PG_SURFACECACHE_H

#include "paragui.h"
#include "pgcolor.h"
#include <string>

using namespace std;

typedef struct {
	int refcount;
	SDL_Surface* surface;
	string key;
}
pg_surface_cache_t;

class DECLSPEC PG_SurfaceCache {
public:

	PG_SurfaceCache();
	virtual ~PG_SurfaceCache();

	void CreateKey(string &key, Uint16 w, Uint16 h,
	               PG_Gradient* gradient, SDL_Surface* background,
	               Sint8 bkmode, Uint8 blend);
	SDL_Surface* FindSurface(const string &key);
	SDL_Surface* AddSurface(const string &key, SDL_Surface* surface);
	void DeleteSurface(SDL_Surface* surface, bool bDeleteIfNotExists = true);

	void IncRef(const string &key);

	void Cleanup();

private:

	pg_surface_cache_t* FindByKey(const string &key);
	pg_surface_cache_t* FindBySurface(SDL_Surface* surface);

	void* my_surfacemap;
	void* my_surfacemap_index;
};

#endif	// SURFACECACHE_H
