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
    Update Date:      $Date: 2002/04/15 13:22:32 $
    Source File:      $Source: /sources/paragui/paragui/include/pglog.h,v $
    CVS/RCS Revision: $Revision: 1.1 $
    Status:           $State 
*/

/**
	\file pglog.h
	ParaGUI logging facility.
	This header declares the PG_LogConsole namespace and all functions for log processing.
*/

#ifndef PGLOG_H
#define PGLOG_H

#include <stdarg.h>
#include "SDL.h"

//! ParaGUI logging level
typedef enum {
	PG_LOG_NONE,  //!< log nothing
	PG_LOG_ERR, //!< only errors
	PG_LOG_WRN, //!< errors and warnings
	PG_LOG_MSG, //!< display errors, warnings and messages
	PG_LOG_DBG //!< log everything
} PG_LOG_LEVEL;

/**
	Logmethod: STDOUT.
	Send all log messages to stdout.
*/
#define	PG_LOGMTH_STDOUT 	1
/**
	Logmethod: STDERR.
	Send all log messages to stderr.
*/
#define	PG_LOGMTH_STDERR	2
/**
	Logmethod: CONSOLE.
	Send all log messages to the console window.
*/
#define	PG_LOGMTH_CONSOLE  	4

#ifdef __cplusplus

/**
	@short logging functions.

	These functions can be used for any purpose logging
*/
namespace PG_LogConsole {
	DECLSPEC void LogVA(PG_LOG_LEVEL id, const char *Text, va_list ap);
	DECLSPEC void Done();
	DECLSPEC void Update();
	DECLSPEC void SetLogLevel(PG_LOG_LEVEL newlevel);
	DECLSPEC void Show();
	DECLSPEC void Hide();
	DECLSPEC void Toggle();
	DECLSPEC void SetMethod(int method);
	DECLSPEC int GetMethod();
};

#endif

#ifdef __cplusplus
extern "C" {
#endif

DECLSPEC void PG_Log(PG_LOG_LEVEL id, const char *Text, ...);
DECLSPEC void PG_LogMSG(const char *fmt, ...);
DECLSPEC void PG_LogERR(const char *fmt, ...);
DECLSPEC void PG_LogWRN(const char *fmt, ...);
DECLSPEC void PG_LogDBG(const char *fmt, ...);

#ifdef __cplusplus
}
#endif

#define PG_LOGCONSOLE_KEY	SDLK_F12

#endif // PGLOG_H

/*
 * Local Variables:
 * c-basic-offset: 8
 * End:
 */
