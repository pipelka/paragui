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
    Update Date:      $Date: 2002/04/15 13:31:31 $ 
    Source File:      $Source: /sources/paragui/paragui/src/widgets/pgimage.cpp,v $ 
    CVS/RCS Revision: $Revision: 1.2 $ 
    Status:           $State: Exp $ 
*/

#include "pgimage.h"

PG_Image::PG_Image(PG_Widget* parent, const PG_Point& p, const char* filename, const char* style) : PG_ThemeWidget(parent, PG_Rect(p.x, p.y, 1, 1), style) {
	LoadImage(filename);

	if(my_image != NULL) {
		SizeWidget(my_image->w, my_image->h);
	}
}

PG_Image::PG_Image(PG_Widget* parent, const PG_Point& p, SDL_Surface* image, bool freeimage, const char* style) : PG_ThemeWidget(parent, PG_Rect(p.x, p.y, 1, 1), style) {
	SetImage(image, freeimage);

	if(my_image != NULL) {
		SizeWidget(my_image->w, my_image->h);
	}
}

void PG_Image::eventDraw(SDL_Surface* surface, const PG_Rect& rect) {}

void PG_Image::eventBlit(SDL_Surface* srf, const PG_Rect& src, const PG_Rect& dst) {
	if(my_image == NULL) {
		return;
	}

	if(my_image->w != 0 && my_image->h != 0) {
		PG_Rect my_src;
		PG_Rect my_dst;

		GetClipRects(my_src, my_dst, *this);
		PG_Widget::eventBlit(my_image, my_src, my_dst);
	}
}
