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
    Update Date:      $Date: 2002/05/02 08:45:35 $
    Source File:      $Source: /sources/paragui/paragui/include/paraconfig.h,v $
    CVS/RCS Revision: $Revision: 1.3.6.1 $
    Status:           $State: Exp $
*/

#ifndef CONFIG_INCLUDED
#define CONFIG_INCLUDED

#undef PACKAGE
#undef VERSION

#if (defined(WIN32) || defined(__WIN32__)) && (defined(_MSC_VER) || defined(__BCPLUSPLUS__))
#include "paraconfig_win32.h"
#else // GNU
#include "paraconfig_gnu.h"

// For C++ compliance (required with gcc 3.0)
#ifndef SWIG
using std::cerr;
using std::cout;
using std::endl;
using std::ios;
#ifndef _STLPORT_VERSION
using std::strcpy;
using std::strcmp;
using std::strchr;
using std::strlen;
using std::strcat;
using std::strncpy;
#endif // _STLPORT_VERSION
#endif // SWIG
#endif // GNU

// Some stuff needed for Win32
#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN
#include<windows.h>
extern int SDL_RegisterApp(char*, Uint32, void*);
#undef SendMessage
#endif // WIN32

// STL std::map / std::hash_map

#if defined(HAVE_HASH_MAP)
#define HASH_MAP_INC <hash_map>
#define MAP_INC <hash_map>
#define STL_MAP std::hash_map
#elif defined(HAVE_EXT_HASH_MAP)
#define HASH_MAP_INC <ext/hash_map>
#define MAP_INC <ext/hash_map>
#define STL_MAP std::hash_map
#else
#define MAP_INC <map>
#define STL_MAP std::map
#endif

//
// Modelled after g++ stdc++ v3
//
#if defined(EXCEPTIONS_ENABLED) || defined(__EXCEPTIONS)
#define PG_TRY try
#define PG_CATCH_ALL catch(...)
#define PG_THROW(_ex_) throw _ex_
#define PG_RETHROW throw
#define PG_NOTHROW throw()
#define PG_UNWIND(action) catch(...) {action; throw;}
#define PG_CATCH(_ex_, _name_) catch(_ex_& _name_)
#else
#define PG_TRY
#define PG_CATCH_ALL if (false)
#define PG_THROW(_ex_)
#define PG_RETHROW
#define PG_NOTHROW
#define PG_UNWIND
#define PG_CATCH(_ex_, _name_) if (false)
#endif

//
// Replacement for strdup
//
#ifndef HAVE_STRDUP
extern "C" {
char* strdup(char* s);
}
#endif

#endif // CONFIG_INCLUDED
