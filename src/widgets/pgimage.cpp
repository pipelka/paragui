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
    Update Date:      $Date: 2004/09/05 10:51:41 $ 
    Source File:      $Source: /sources/paragui/paragui/src/widgets/pgimage.cpp,v $ 
    CVS/RCS Revision: $Revision: 1.3.6.2.2.1 $ 
    Status:           $State: Exp $ 
*/

#include "pgimage.h"

PG_Image::PG_Image(PG_Widget* parent, const PG_Point& p, const char* filename, Uint32 colorkey, Uint8 drawmode, const char* style) : PG_ThemeWidget(parent, PG_Rect(p.x, p.y, 1, 1), style), my_cachedSrf(NULL) {
	LoadImage(filename, colorkey);

	my_DrawMode = drawmode;
	
	if(my_image != NULL) {
		if(drawmode != BKMODE_STRETCH) {
		SizeWidget(my_image->w, my_image->h);
	}
		else {
			SizeWidget(parent->my_width, parent->my_height);
		}
	}
}
	
PG_Image::PG_Image(PG_Widget* parent, const PG_Point& p, const char* filename, Uint8 drawmode, const char* style) : PG_ThemeWidget(parent, PG_Rect(p.x, p.y, 1, 1), style), my_cachedSrf(NULL) {
	LoadImage(filename);

	my_DrawMode = drawmode;
	
	if(my_image != NULL) {
		if(drawmode != BKMODE_STRETCH) {
		SizeWidget(my_image->w, my_image->h);
	}
		else {
			SizeWidget(parent->my_width, parent->my_height);
		}
	}
}

PG_Image::PG_Image(PG_Widget* parent, const PG_Point& p, SDL_Surface* image, bool freeimage, Uint8 drawmode, const char* style) : PG_ThemeWidget(parent, PG_Rect(p.x, p.y, 1, 1), style), my_cachedSrf(NULL) {
	SetImage(image, freeimage);

	my_DrawMode = drawmode;
	
	if(my_image != NULL) {
		if(drawmode == BKMODE_STRETCH) {
		SizeWidget(my_image->w, my_image->h);
	}
		else {
			SizeWidget(parent->my_width, parent->my_height);
		}
	}
}

PG_Image::~PG_Image() {
	DeleteThemedSurface(my_cachedSrf);
}

void PG_Image::eventDraw(SDL_Surface* surface, const PG_Rect& rect) {}

void PG_Image::eventBlit(SDL_Surface* srf, const PG_Rect& src, const PG_Rect& dst) {
	
	if(my_cachedSrf != NULL) {
		PG_Rect my_src;
		PG_Rect my_dst;

		GetClipRects(my_src, my_dst, *this);
		PG_Widget::eventBlit(my_cachedSrf, my_src, my_dst);
		return;
	}
	
	if(my_image == NULL) {
		return;                                                      
	}

	if(my_image->w != 0 && my_image->h != 0) {
		PG_Rect my_src;
		PG_Rect my_dst;

		GetClipRects(my_src, my_dst, *this);
		if(my_DrawMode != BKMODE_STRETCH) {
		PG_Widget::eventBlit(my_image, my_src, my_dst);
			return;
		}

		my_cachedSrf = CreateThemedSurface(PG_Rect(0, 0, my_width, my_height), 0, my_background, my_DrawMode, my_blendLevel);	                      
		PG_Draw::DrawThemedSurface(my_cachedSrf, PG_Rect(0, 0, my_src.w, my_src.h), 0, my_image, my_DrawMode, my_blendLevel);		

		PG_Widget::eventBlit(my_cachedSrf, my_src, my_dst);
	}
}

void PG_Image::SetColorKey(Uint32 key) {
	SDL_SetColorKey(my_image, SDL_SRCCOLORKEY, key);
	DeleteThemedSurface(my_cachedSrf);
	my_cachedSrf = NULL;
}

void PG_Image::SetDrawMode(Uint8 mode) {
	if(mode != my_DrawMode) {
		my_DrawMode = mode;
		DeleteThemedSurface(my_cachedSrf);
		my_cachedSrf = NULL;
	}
}

bool PG_Image::LoadImage(const char* filename) {
	DeleteThemedSurface(my_cachedSrf);
	my_cachedSrf = NULL;

	if(PG_ThemeWidget::LoadImage(filename)) {
		if(my_DrawMode != BKMODE_STRETCH) {
			SizeWidget(my_image->w, my_image->h);
		}
		else {
			SizeWidget(GetParent()->my_width, GetParent()->my_height);
		}
		
		return true;
	}
	
	return false;
}

bool PG_Image::LoadImage(const char* filename, Uint32 key) {
	DeleteThemedSurface(my_cachedSrf);
	my_cachedSrf = NULL;
	
	if(PG_ThemeWidget::LoadImage(filename, key)) {
		if(my_DrawMode != BKMODE_STRETCH) {
			SizeWidget(my_image->w, my_image->h);
		}
		else {
			SizeWidget(GetParent()->my_width, GetParent()->my_height);
		}
		
		return true;
	}
	
	return false;
}

bool PG_Image::SetImage(SDL_Surface* image, bool bFreeImage) {
	DeleteThemedSurface(my_cachedSrf);
	my_cachedSrf = NULL;

	if(PG_ThemeWidget::SetImage(image, bFreeImage)) {
		if(my_DrawMode != BKMODE_STRETCH) {
			SizeWidget(my_image->w, my_image->h);
		}
		else {
			SizeWidget(GetParent()->my_width, GetParent()->my_height);
		}
		
		return true;
	}
	
	return false;
}
