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
    Update Date:      $Date: 2002/04/15 13:35:36 $
    Source File:      $Source: /sources/paragui/paragui/src/widgets/pgthemewidget.cpp,v $
    CVS/RCS Revision: $Revision: 1.3 $
    Status:           $State: Exp $
*/

#include "pgthemewidget.h"
#include "pgdraw.h"
#include "pgapplication.h"
#include "pglog.h"

static PG_SurfaceCache my_SurfaceCache;

struct PG_WidgetDataInternal{
	SDL_Surface* cachesurface;
	SDL_Color backgroundcolor;

	bool freeimage;
	bool simplebackground;
	bool nocache;

};

PG_ThemeWidget::PG_ThemeWidget(PG_Widget* parent, const PG_Rect& r, const char* style) : PG_Widget(parent, r) {
	Init(style);
}

PG_ThemeWidget::PG_ThemeWidget(PG_Widget* parent, const PG_Rect& r, bool bCreateSurface, const char* style) : PG_Widget(parent, r, bCreateSurface) {
	Init(style);
}

void PG_ThemeWidget::Init(const char* style) {
	SetDirtyUpdate(true);
	
	my_internaldata = new PG_WidgetDataInternal;
	
	my_backgroundFree = false;
	my_background = NULL;
	my_blendLevel = 0;
	my_backgroundMode = BKMODE_TILE;
	my_bordersize = 0;
	my_has_gradient = false;

	my_image = NULL;
	my_internaldata->freeimage = false;
	my_internaldata->simplebackground = false;
	my_internaldata->nocache = false;

	my_internaldata->backgroundcolor.r = 128;
	my_internaldata->backgroundcolor.g = 128;
	my_internaldata->backgroundcolor.b = 128;

	my_internaldata->cachesurface = NULL;

	LoadThemeStyle(style);
}

PG_ThemeWidget::~PG_ThemeWidget() {
	
	// free surfaces
	FreeSurface();
	FreeImage();
	
	// remove the cachesurface
	DeleteThemedSurface(my_internaldata->cachesurface);
	
	// delete internal data
	delete my_internaldata;
}

void PG_ThemeWidget::LoadThemeStyle(const char* widgettype) {
	if(strcmp(widgettype, "ThemeWidget") != 0) {
		PG_ThemeWidget::LoadThemeStyle("ThemeWidget", "ThemeWidget");
	}
	PG_ThemeWidget::LoadThemeStyle(widgettype, "ThemeWidget");
}

void PG_ThemeWidget::LoadThemeStyle(const char* widgettype, const char* objectname) {
	int b;
	PG_Theme* t = PG_Application::GetTheme();

	if(my_srfObject == NULL) {
		if(strcmp(objectname, "ThemeWidget") != 0) {
			PG_ThemeWidget::LoadThemeStyle(widgettype, "ThemeWidget");
		}

		b = t->FindProperty(widgettype, objectname, "simplebackground");
		my_internaldata->simplebackground = (b != -1) ? b : my_internaldata->simplebackground;

		b = t->FindProperty(widgettype, objectname, "nocache");
		my_internaldata->nocache = (b != -1) ? b : my_internaldata->nocache;

		SDL_Color* c = t->FindColor(widgettype, objectname, "backgroundcolor");
		if(c != NULL) {
			my_internaldata->backgroundcolor = *c;
		}
	}

	const char *font = t->FindFontName(widgettype, objectname);
	int fontsize = t->FindFontSize(widgettype, objectname);
	int fontstyle = t->FindFontStyle(widgettype, objectname);

	if(font != NULL)
		SetFontName(font);
	if(fontsize > 0)
		SetFontSize(fontsize);
	if(fontstyle >= 0)
		SetFontStyle(fontstyle);

	SetBackground(t->FindSurface(widgettype, objectname, "background"));

	b = t->FindProperty(widgettype, objectname, "blend");

	if(b != -1) {
		SetBackgroundBlend(b);
	}

	b = t->FindProperty(widgettype, objectname, "bordersize");

	if(b != -1) {
		my_bordersize = b;
	}

	b = t->FindProperty(widgettype, objectname, "backmode");

	if(b != -1) {
		my_backgroundMode = b;
	}

	PG_Gradient* g = t->FindGradient(widgettype, objectname, "gradient");

	if(g) {
		my_gradient = *g;
		my_has_gradient = true;
	}
	
	b = t->FindProperty(widgettype, objectname, "transparency");
	if(b != -1)
		SetTransparency((Uint32)b);

	PG_Widget::LoadThemeStyle(widgettype, objectname);

	int w = t->FindProperty(widgettype, objectname, "width");
	if (w==-1)
		w=Width();
	int h = t->FindProperty(widgettype, objectname, "height");
	if (h==-1)
		h=Height();

	if(w <=0 || h <= 0) {
		return;
	}

	if((w != Width()) || (h != Height())) {
		SizeWidget(w, h);
	}
}

void PG_ThemeWidget::eventDraw(SDL_Surface* surface, const PG_Rect& rect) {
	if(my_srfObject == NULL) {
		return;
	}

	PG_Draw::DrawThemedSurface(
	    surface,
	    rect,
	    my_has_gradient ? &my_gradient : 0,
	    my_background,
	    my_backgroundMode,
	    my_blendLevel);

	if(my_bordersize > 0) {
		DrawBorder(rect, my_bordersize);
	}
}

bool PG_ThemeWidget::SetBackground(const char* filename, int mode, Uint32 colorkey) {
	// try to load the file
	SDL_Surface* temp = PG_Application::LoadSurface(filename, true);

	// success ?
	if(!temp) {
		return false;
	}

	// free previous surface
	FreeSurface();

	// mark my_background to be freed on destruction
	my_backgroundFree = true;
	my_backgroundMode = mode;
	my_background = temp;

	if(my_background == NULL) {
		return false;
	}

	Uint32 c = SDL_MapRGB(
		my_background->format, 
		(colorkey>>16) & 0xFF,
		(colorkey>>8) & 0xFF,
		colorkey & 0xFF);
		
	SDL_SetColorKey(my_background, SDL_SRCCOLORKEY, c);
	 
	if(my_srfObject == NULL) {
		CreateSurface();
	}

	return (my_background != NULL);
}

bool PG_ThemeWidget::SetBackground(const char* filename, int mode) {

	// try to load the file
	SDL_Surface* temp = PG_Application::LoadSurface(filename, true);

	// success ?
	if(!temp) {
		return false;
	}

	// free previous surface
	FreeSurface();

	// mark my_background to be freed on destruction
	my_backgroundFree = true;
	my_backgroundMode = mode;
	my_background = temp;

	if(my_background == NULL) {
		return false;
	}

	if(my_srfObject == NULL) {
		CreateSurface();
	}

	return (my_background != NULL);
}


bool PG_ThemeWidget::SetBackground(SDL_Surface* surface, int mode) {

	if(!surface) {
		return false;
	}

	FreeSurface();

	my_background = surface;
	my_backgroundFree = false;
	my_backgroundMode = mode;

	return true;
}

void PG_ThemeWidget::SetBackgroundBlend(Uint8 backblend) {
	my_blendLevel = backblend;
}

void PG_ThemeWidget::FreeSurface() {

	// check if we have to free a previous surface

	if (my_backgroundFree && my_background != NULL) {
		PG_Application::UnloadSurface(my_background);
		my_background = NULL;
		my_backgroundFree = false;
	}
}

void PG_ThemeWidget::SetGradient(PG_Gradient& grad) {
	my_gradient = grad;
	my_has_gradient = true;
}

void PG_ThemeWidget::SetBorderSize(int b) {
	my_bordersize = b;
}

void PG_ThemeWidget::FreeImage() {

	if(my_internaldata->freeimage) {
		PG_Application::UnloadSurface(my_image); // false
	}

	my_internaldata->freeimage = false;
	my_image = NULL;
	return;
}

bool PG_ThemeWidget::SetImage(SDL_Surface* image, bool bFreeImage) {
	if(image == NULL) {
		return false;
	}

	if(image == my_image) {
		return true;
	}

	FreeImage();
	my_internaldata->freeimage = bFreeImage;
	my_image = image;

	Update();
	return true;
}

bool PG_ThemeWidget::LoadImage(const char* filename) {
	SDL_Surface* image = PG_Application::LoadSurface(filename);

	if(image == NULL) {
		return false;
	}

	FreeImage();
	my_internaldata->freeimage = true;
	my_image = image;

	Update();
	return true;
}

void PG_ThemeWidget::eventSizeWidget(Uint16 w, Uint16 h) {

	if((w == Width()) && (h == Height())) {
		return;
	}

	CreateSurface(w, h);
}

void PG_ThemeWidget::CreateSurface(Uint16 w, Uint16 h) {
	if(my_internaldata->simplebackground) {
		return;
	}

	DeleteThemedSurface(my_internaldata->cachesurface);

	if(w == 0 || h == 0) {
		my_internaldata->cachesurface = NULL;
		return;
	}

	PG_Rect r(my_xpos, my_ypos, w, h);

	my_internaldata->cachesurface = CreateThemedSurface(
	                      r,
	                      my_has_gradient ? &my_gradient : 0,
	                      my_background,
	                      my_backgroundMode,
	                      my_blendLevel);
}

void PG_ThemeWidget::eventBlit(SDL_Surface* srf, const PG_Rect& src, const PG_Rect& dst) {

	if(my_srfObject != NULL) {
		PG_Widget::eventBlit(srf, src, dst);
		return;
	}

	if(!my_internaldata->simplebackground && !my_internaldata->nocache) {
		if(my_internaldata->cachesurface == NULL) {
			CreateSurface(Width(), Height());
		}
		PG_Widget::eventBlit(my_internaldata->cachesurface, src, dst);
	} else if (my_internaldata->simplebackground) {
		if(GetTransparency() < 255) {
			Uint32 c = SDL_MapRGBA(
			               my_srfScreen->format,
			               my_internaldata->backgroundcolor.r,
			               my_internaldata->backgroundcolor.g,
			               my_internaldata->backgroundcolor.b,
			               255-GetTransparency());
			SDL_FillRect(my_srfScreen, (SDL_Rect*)&dst, c);
		}
	} else if (my_internaldata->nocache) {
		my_internaldata->cachesurface = CreateThemedSurface(
		                      *this,
		                      my_has_gradient ? &my_gradient : 0,
		                      my_background,
		                      my_backgroundMode,
		                      my_blendLevel);
		PG_Widget::eventBlit(my_internaldata->cachesurface, src, dst);
		DeleteThemedSurface(my_internaldata->cachesurface);
		my_internaldata->cachesurface = NULL;
	}

	if(my_bordersize > 0) {
		DrawBorder(PG_Rect(0, 0, Width(), Height()), my_bordersize, true);
	}

	if(my_image != NULL) {
		PG_Rect my_src;
		PG_Rect my_dst;

		GetClipRects(my_src, my_dst, *this);
		PG_Widget::eventBlit(my_image, my_src, my_dst);
	}
}

void PG_ThemeWidget::SetTransparency(Uint8 t) {
	if(my_internaldata->simplebackground || my_internaldata->nocache) {
		PG_Widget::SetTransparency(t);
		return;
	}

	if(t == 255) {
		DeleteThemedSurface(my_internaldata->cachesurface);
		my_internaldata->cachesurface = NULL;
	} else if(GetTransparency() == 255) {
		CreateSurface();
	}
	PG_Widget::SetTransparency(t);
}

SDL_Surface* PG_ThemeWidget::CreateThemedSurface(const PG_Rect& r, PG_Gradient* gradient, SDL_Surface* background, int bkmode, Uint8 blend) {
	SDL_Surface* cache_surface = NULL;
	SDL_Surface* screen = PG_Application::GetScreen();
	std::string key;

	if(r.w == 0 || r.h == 0) {
		return NULL;
	}

	// create a key for the surface
	my_SurfaceCache.CreateKey(key, r.my_width, r.my_height,  gradient, background, bkmode, blend);

	// lookup the surface in cache
	cache_surface = my_SurfaceCache.FindSurface(key);

	// draw the cached surface :)
	if(cache_surface != NULL) {
		// increase the reference count
		my_SurfaceCache.IncRef(key);
		return cache_surface;
	}

	Uint8 bpp = screen->format->BitsPerPixel;
	Uint32 Rmask = screen->format->Rmask;
	Uint32 Gmask = screen->format->Gmask;
	Uint32 Bmask = screen->format->Bmask;
	Uint32 Amask = 0;

	if(background != NULL) {
		if((background->format->Amask != 0) || ((bpp < background->format->BitsPerPixel) && (bpp <= 8))) {
			bpp = background->format->BitsPerPixel;
			Rmask = background->format->Rmask;
			Gmask = background->format->Gmask;
			Bmask = background->format->Bmask;
			Amask = background->format->Amask;
		}
	}

	SDL_Surface *surface = SDL_CreateRGBSurface(
	                           SDL_SWSURFACE,
	                           r.my_width,
	                           r.my_height,
	                           bpp,
	                           Rmask,
	                           Gmask,
	                           Bmask,
	                           Amask
	                       );
			       
	if ( bpp == 8 )
		SDL_SetPalette ( surface, SDL_LOGPAL, screen->format->palette->colors, 0, 256 );

	if(surface) {
		if(background || gradient) {
			PG_Draw::DrawThemedSurface(surface, PG_Rect(0, 0, r.my_width, r.my_height), gradient, background, bkmode, blend);
		} else {
			SDL_SetColorKey(surface, SDL_SRCCOLORKEY, 0);
		}
	}
	
	my_SurfaceCache.AddSurface(key, surface);
	return surface;
}

void PG_ThemeWidget::DeleteThemedSurface(SDL_Surface* surface) {
	if(surface == NULL) {
		return;
	}
	my_SurfaceCache.DeleteSurface(surface);
}
