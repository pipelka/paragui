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
    Update Date:      $Date: 2003/06/29 17:09:49 $
    Source File:      $Source: /sources/paragui/paragui/include/pglabel.h,v $
    CVS/RCS Revision: $Revision: 1.3.6.2 $
    Status:           $State: Exp $
*/

#ifndef PG_LABEL_H
#define PG_LABEL_H

#ifdef SWIG
%include "swigcommon.h"
%module pglabel
%{
#include "pglabel.h"
%}
#endif

#include "pgwidget.h"
#include "pgapplication.h"

/**
	@author Alexander Pipelka
 
	@short Text label.
 
	A text label (unmodifiable by end user).  Has attributes for font style,
	alignment, etc.
*/

class DECLSPEC PG_Label : public PG_Widget {
public:

	/** Only constructor
	@param parent			Parent widget.
	@param r				Rectangle to draw in, relative to parent.
	@param text				Text displayed by label.
	@param style			initial widget style (from xml theme)
	*/
	PG_Label(PG_Widget* parent, const PG_Rect& r, const char* text, const char* style="Label");

	/** Only destructor */
	~PG_Label();

	/** */
	void LoadThemeStyle(const char* style);

#ifndef SWIG
	/** */
	void LoadThemeStyle(const char* widgettype, const char* object);
#endif

	/** Sets text alignment */
	void SetAlignment(int a);

#ifdef SWIG

	%name(SetIconFile) SDL_Surface* SetIcon(const char* filename);
#else
	/** */
	SDL_Surface* SetIcon(const char* filename);
#endif

	/** */
	SDL_Surface* SetIcon(SDL_Surface* icon);

	SDL_Surface* GetIcon();
	
	/**
	Set the text indentation
	@param	indent		number of pixels for text indentation
	*/
	void SetIndent(int indent);

protected:

	/** Draw event handler
	@param surface	Surface to draw to.
	@param rect		Rectangle to draw in, relative to surface.
	*/
	void eventDraw(SDL_Surface* surface, const PG_Rect& rect);

	/** */
	void eventBlit(SDL_Surface* srf, const PG_Rect& src, const PG_Rect& dst);

	SDL_Surface* my_srfIcon;

private:
#ifndef SWIG

	PG_Label(const PG_Label&);
	PG_Label& operator=(const PG_Label&);
#endif

	int my_alignment;
	int my_indent;
	bool my_freeicon;

	PG_Rect my_rectLabel;
};

#endif // PG_LABEL_H
