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
    Update Date:      $Date: 2002/04/15 13:31:30 $
    Source File:      $Source: /sources/paragui/paragui/include/pgcompat.h,v $
    CVS/RCS Revision: $Revision: 1.2 $
    Status:           $State: Exp $
*/

/** \file pgcompat.h
	Compatibility macros.
	This include file defines some macros for source backward compatibility  and
	provides various function replacements used in pre 1.0 development versions.
	Usage of these obsolete functions is deprecated but can be used for porting
	older applications.
*/

#ifndef PG_COMPAT_H
#define PG_COMPAT_H

/**
	compatibility macro.

	This macro is provided for backward source compatibility.
	It replaces the obsolete PG_DrawObject class with the PG_Draw namespace.
*/
#define PG_DrawObject	PG_Draw

/**
	compatibility macro.

	This macro is provided for backward source compatibility.
	It replaces the obsolete PG_DrawLine function with PG_Draw::DrawLine
*/
#define PG_DrawLine PG_Draw::DrawLine

/**
	compatibility macro.

	This macro is provided for backward source compatibility.
	It replaces the obsolete PG_BlitSurface macros with the inlined PG_Draw::BlitSurface function
*/
#define PG_BlitSurface	PG_Draw::BlitSurface

/**
	compatibility macro.

	This macro is provided for backward source compatibility.
	It replaces the obsolete PG_ScaleSurface function with PG_Draw::ScaleSurface
*/
#define PG_ScaleSurface PG_Draw::ScaleSurface

/**
	compatibility macro.

	This macro is provided for backward source compatibility.
	It replaces the obsolete PG_LoadImage function with PG_Application::LoadSurface
*/
#define PG_LoadImage	PG_Application::LoadSurface

/**
	Compatibility macro for PG_Layout::Load.

	This macro provides source backward-compatibility to the
	obsolete function PG_LoadLayout
*/
#define PG_LoadLayout PG_Layout::Load

/**
	Compatibility macro.

	This macro provides source backward-compatibility to the
	obsolete function PG_RenderText
*/
#define PG_RenderText PG_FontEngine::RenderText

/**
	compatibility macro.

	This macro is provided for backward source compatibility.
	It replaces the obsolete PG_UserButton class with PG_Button
*/
#define PG_UserButton PG_Button

/**
	Compatibility macro.

	This macro provides source backward-compatibility to the
	obsolete function PG_GetTextSize
*/
#define PG_GetTextSize PG_FontEngine::GetTextSize

/**
	Compatibility macro.

	This macro provides source backward-compatibility to the
	obsolete function PARAGUI_LoadTheme
*/
#define PARAGUI_LoadTheme PG_Theme::Load

/**
	Compatibility macro.

	This macro provides source backward-compatibility to the
	obsolete function PARAGUI_UnloadTheme
*/
#define PARAGUI_UnloadTheme PG_Theme::Unload

/**
	Compatibility macro.

	This macro provides source backward-compatibility to the
	obsolete class PG_StaticFrame.
*/
#define PG_StaticFrame PG_ThemeWidget

/**
	Compatibility macro.

	This macro provides source backward-compatibility to the
	obsolete class PG_GradientWidget.
*/
#define PG_GradientWidget PG_ThemeWidget

#endif // PG_COMPAT_H
