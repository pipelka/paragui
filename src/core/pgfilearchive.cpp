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
    Source File:      $Source: /sources/paragui/paragui/src/core/pgfilearchive.cpp,v $
    CVS/RCS Revision: $Revision: 1.2.4.14.2.5 $
    Status:           $State: Exp $
*/

#include "physfs.h"
#include "pgfilearchive.h"
#include "pgapplication.h"
#include "pglog.h"
#include "pgfont.h"

#include "SDL_loadso.h"
#include "physfsrwops.h"
#include <iostream>
#include "paragui.h"

Uint32 PG_FileArchive::my_instance_count = 0;
PG_SurfaceCache PG_FileArchive::my_cache;
static void* SDL_image_obj = NULL;

typedef SDL_Surface* (*IMG_Load_RW_FT)(SDL_RWops* src, int freesrc);
static IMG_Load_RW_FT IMG_Load_RW_FUNC = NULL;

PG_FileArchive::PG_FileArchive() {

	// increment instance count
	my_instance_count++;

	// First instance ? -> initialize PhysFS
	if(my_instance_count == 1) {
		if(PHYSFS_init("paragui") == 0) {
			cerr << "Unable to initialize PhysicsFS !" << endl;
			return;
		}

		// try different names to find SDL_image
		SDL_image_obj = SDL_LoadObject(SDLIMAGE_LIB);
		if(SDL_image_obj == NULL) {
			PG_LogMSG("SDL_image not found! Only bmp images can be loaded!");
		}
		else {
			IMG_Load_RW_FUNC = (IMG_Load_RW_FT)SDL_LoadFunction(SDL_image_obj, "IMG_Load_RW");
			if(IMG_Load_RW_FUNC == NULL) {
				PG_LogERR("Unable to load IMG_Load_RW function. SDL_image disabled!");
				SDL_UnloadObject(SDL_image_obj);
				SDL_image_obj = NULL;
			}
		}
	}

}

PG_FileArchive::~PG_FileArchive() {

	if(my_instance_count == 0) {
		return;
	}
	
	// decrement instance count
	my_instance_count--;

	if(my_instance_count == 0) {
		Deinit();
		if(SDL_image_obj != NULL) {
			SDL_UnloadObject(SDL_image_obj);
			SDL_image_obj = NULL;
		}
	}
}

void PG_FileArchive::Deinit() {
	PHYSFS_deinit();
}

string *PG_FileArchive::PathToPlatform(const char *path) {
	string *newpath;
	const char* sep = GetDirSeparator();
	string::size_type pos = 0, incr;
	newpath = new string(path);
	incr = strlen(sep);
	if(incr == 1 && sep[0] == '/')
		return newpath;

#ifdef __MACOS__
	while( (pos = newpath->find(":", pos)) != string::npos) {
#else
	while( (pos = newpath->find("/", pos)) != string::npos) {
#endif
		newpath->replace(pos, 1, sep);
		pos += incr;
	}
	return newpath;
}


bool PG_FileArchive::AddArchive(const char* arch, bool append) {
	string *newpath = PathToPlatform(arch);
	bool ret = (PHYSFS_addToSearchPath(newpath->c_str(),  append) != 0);
	delete newpath;
	return ret;
}

bool PG_FileArchive::RemoveArchive(const char* arch) {
	string *newpath = PathToPlatform(arch);
	bool ret = (PHYSFS_removeFromSearchPath(newpath->c_str()) != 0);
	delete newpath;
	return ret;
}

char **PG_FileArchive::EnumerateFiles(const char *dir) {
	return PHYSFS_enumerateFiles(dir);
}

PG_FileList* PG_FileArchive::GetFileList(const char *dir, const char* wildcard) {
	char **tempList = EnumerateFiles(dir);
	
	if( tempList == NULL ) {
		return NULL;
	}

	PG_FileList* retVal = new PG_FileList;
	
	for( char** i = tempList; *i != NULL; i++) {
		if(fnmatch(wildcard, *i, FNM_PATHNAME) == 0) {
			retVal->push_back(string(*i));
		}
	}
	
	// Clean up.
	PHYSFS_freeList(tempList);
	
	return retVal;
}

bool PG_FileArchive::Exists(const char *filename) {
	return PHYSFS_exists(filename);
}

bool PG_FileArchive::IsDirectory(const char *filename) {
	return PHYSFS_isDirectory(filename);
}

const char* PG_FileArchive::GetDirSeparator() {
	return PHYSFS_getDirSeparator();
}

const char* PG_FileArchive::GetRealDir(const char* filename) {
	return PHYSFS_getRealDir(filename);
}

const char* PG_FileArchive::GetLastError() {
	return PHYSFS_getLastError();
}

const char* PG_FileArchive::GetBaseDir() {
	return PHYSFS_getBaseDir();
}

const char* PG_FileArchive::GetUserDir() {
	return PHYSFS_getUserDir();
}

const char* PG_FileArchive::GetWriteDir() {
	return PHYSFS_getWriteDir();
}

PG_File* PG_FileArchive::OpenFile(const char* filename, Mode mode) {
	PHYSFS_file* file = 0;
	switch(mode) {
	case READ:
		file = PHYSFS_openRead(filename);
		break;
	case WRITE:
		file = PHYSFS_openWrite(filename);
		break;
	case APPEND:
		file = PHYSFS_openAppend(filename);
		break;
	}
	if(file == NULL) {
		return NULL;
	}

	return new PG_File(file);
}

SDL_RWops* PG_FileArchive::OpenFileRWops(const char* filename, Mode mode) {
	SDL_RWops* file = NULL;
	switch(mode) {
	case READ:
		file = PHYSFSRWOPS_openRead(filename);
		break;
	case WRITE:
		file = PHYSFSRWOPS_openWrite(filename);
		break;
	case APPEND:
		file = PHYSFSRWOPS_openAppend(filename);
		break;
	}
	
	return file;
}

bool PG_FileArchive::MakeDir(const char* dir) {
	return PHYSFS_mkdir(dir) == 1;
}
bool PG_FileArchive::SetWriteDir(const char* dir) {
	if(PHYSFS_setWriteDir(dir)) {
		return PHYSFS_addToSearchPath(dir, 0) == 1;
	} else {
		return false;
	}
}

bool PG_FileArchive::SetSaneConfig(const char *organization,
				   const char* appName,
				  const char* archiveExt,
				  bool includeCdRoms,
				  bool archivesFirst)
{
	if(!appName || !organization) {
		return false;
	}
	return PHYSFS_setSaneConfig(organization, appName, archiveExt,
				    includeCdRoms, archivesFirst) == 1;
}


PG_DataContainer* PG_FileArchive::ReadFile(const char* filename) {
	PG_File *file = OpenFile(filename);

	if(!file) {
		return 0;
	}

	int size = file->fileLength();

	if(size <= 0) {
		delete file;
		return 0;
	}

	PG_DataContainer* data = new PG_DataContainer(size);

	if(file->read(data->data(), size, 1) != 1) {
		delete data;
		delete file;
		return NULL;
	}

	delete file;

	return data;
}

SDL_Surface* PG_FileArchive::LoadSurface(const char* filename, bool convert) {
	return LoadSurface(filename, false, 0, convert);
}

SDL_Surface* PG_FileArchive::LoadSurface(const char* filename, bool usekey, Uint32 colorkey, bool convert) {
	if(filename == NULL) {
		return NULL;
	}

	string fn = filename;

	if(fn == "none") {
		return NULL;
	}

	// take a look into the cache
	SDL_Surface* surface = my_cache.FindSurface(fn);

	// return the cache surface if it has been found
	if(surface != NULL) {
		my_cache.IncRef(fn);
		return surface;
	}

	surface = NULL;
	SDL_RWops *rw = OpenFileRWops(filename);

	if(rw == NULL) {
		PG_LogWRN("Unable to open '%s' !", filename);
		return NULL;
	}

	if(IMG_Load_RW_FUNC != NULL) {
		surface = IMG_Load_RW_FUNC(rw, 1);
	}
	else {
		surface = SDL_LoadBMP_RW(rw, 1);
	}

	if(surface == NULL) {
		PG_LogWRN("Failed to load imagedata from '%s' !", filename);
		return NULL;
	}
	
	if(surface == NULL) {
		PG_LogERR("Unable to load imagedata from '%s'", filename);
		PG_LogERR("PhysFS reported: '%s'", PG_FileArchive::GetLastError());
		PG_LogERR("SDL reported: '%s'", SDL_GetError());
	}

	if(usekey == true) {
		SDL_SetColorKey(surface, SDL_SRCCOLORKEY, colorkey);
	}

	if(convert && !PG_Application::GetGLMode()) {
		SDL_Surface* tmpsrf = NULL;
		if (surface->flags & SDL_SRCALPHA)
			tmpsrf = SDL_DisplayFormatAlpha(surface);			
		else
			tmpsrf = SDL_DisplayFormat(surface);
			
		if(tmpsrf) {
			SDL_FreeSurface(surface);
			surface = tmpsrf;
		}
	}

	// add the loaded surface to the cache
	return my_cache.AddSurface(fn, surface);

	// return the pointer to the surface
	//return surface;
}

bool PG_FileArchive::UnloadSurface(SDL_Surface* surface, bool bDeleteIfNotExists) {
	my_cache.DeleteSurface(surface, bDeleteIfNotExists);
	return true;
}

bool PG_FileArchive::RemoveAllArchives() {
	char** i = GetSearchPath();
	char** d;
	bool success = true;

	for(d = i; *d != NULL; d++) {
		if(!RemoveArchive(*d)) {
			PG_LogWRN("Unable to remove '%s' from searchpath!", *d);
			success = false;
		}
	}

	FreeList(i);
	return success;
}

char** PG_FileArchive::GetSearchPath() {
	return PHYSFS_getSearchPath();
}

PG_FileList* PG_FileArchive::GetSearchPathList() {
	char **tempList = PHYSFS_getSearchPath();
	
	if( tempList == NULL ) {
		return NULL;
	}
	
	PG_FileList* retVal = NULL;
	
	// Scan through to get the length of the listing to get the proper vector size.
	Uint32 size = 0;
	for(; tempList[ size ] != NULL; ++size) {}
	
	// Now we're ready to initialize everything.
	retVal = new vector< string >;
	retVal->reserve( size );
	for( Uint32 i = 0; i < size; ++i ) {
		retVal->push_back(string(tempList[ i ]));
	}
	
	// Clean up.
	PHYSFS_freeList(tempList);
	
	return retVal;
}

void PG_FileArchive::FreeList(void* list) {
	PHYSFS_freeList(list);
}

void PG_FileArchive::EnableSymlinks(bool followSymlinks) {
	PHYSFS_permitSymbolicLinks(followSymlinks);
}

/*
 * Local Variables:
 * c-basic-offset: 8
 * End:
 */
