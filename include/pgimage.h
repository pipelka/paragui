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
    Update Date:      $Date: 2004/04/17 20:39:07 $ 
    Source File:      $Source: /sources/paragui/paragui/include/pgimage.h,v $ 
    CVS/RCS Revision: $Revision: 1.3.6.1.2.3 $ 
    Status:           $State: Exp $ 
*/

/** \file pgimage.h
	Header file of the PG_Image class.
*/

#ifndef PG_IMAGE_H
#define PG_IMAGE_H

#include "pgthemewidget.h"

/**
	@author Jaroslav Vozab 
 
	@short A static (non-resizeable by the end user) frame with image. 
*/

class DECLSPEC PG_Image : public PG_ThemeWidget  {
public:
	/**
	Contructor of the PG_Image class (loading from file)
	@param parent	pointer to the parent widget or NULL
	@param p			position of the PG_Image widget
	@param filename	image-file to load
	@param style		widgetstyle to use
	This constructor creates the widget and loads the image from a file
	*/
	PG_Image(PG_Widget* parent, const PG_Point& p, const char* filename, const char* style = "ThemeWidget");

	/**
	Contructor of the PG_Image class (image from surface)
	@param parent		pointer to the parent widget or NULL
	@param p				position of the PG_Image widget
	@param image		pointer to imagedata (SDL_Surface)
	@param freeimage	if true the imagedata is handled by the widget
	@param style		widgetstyle to use
	*/
	PG_Image(PG_Widget* parent, const PG_Point& p, SDL_Surface* image, bool freeimage = true, const char* style = "ThemeWidget");

	/**
	Contructor of the PG_Image class (loading from file)
	@param parent	pointer to the parent widget or NULL
	@param p		position of the PG_Image widget
	@param filename	image-file to load
	@param	colorkey	colorkey (0xRRGGBB)
	@param style		widgetstyle to use
	This constructor creates the widget and loads the image from a file using a colorkey.
	*/
	PG_Image(PG_Widget* parent, const PG_Point& p, const char* filename, Uint32 colorkey, const char* style);

	/**
	Set the colorkey of the image
	@param key		colorkey (0xRRGGBB);
	*/
	void SetColorKey(Uint32 key);
	
protected:

	/** */
	void eventDraw(SDL_Surface* surface, const PG_Rect& rect);

	/** */
	void eventBlit(SDL_Surface* surface, const PG_Rect& src, const PG_Rect& dst);
};

#endif // PG_IMAGE_H
