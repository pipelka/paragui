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
    Update Date:      $Date: 2003/01/25 16:53:57 $
    Source File:      $Source: /sources/paragui/paragui/include/pgthemewidget.h,v $
    CVS/RCS Revision: $Revision: 1.3.6.4 $
    Status:           $State: Exp $
*/

#ifndef PG_THEMEWIDGET_H
#define PG_THEMEWIDGET_H

#ifdef SWIG
%include "swigcommon.h"
%module pgthemewidget
%{
#include "pgthemewidget.h"
%}
#endif

#include "pgwidget.h"

struct PG_WidgetDataInternal;

/**
	@author Alexander Pipelka

	@short Base class for themed widgets

	This class is the base class for all themed widgets.<br>
	It handles various combinations of gradients and background images.

	\anchor theme_PG_ThemeWidget

	<h2>Theme support</h2><p>

	<b>widget type:</b>		ThemeWidget (default)<br>
	<b>object name:</b>		ThemeWidget<br>

	<h3>Parent theme:</h3>

	\ref theme_PG_Widget "PG_Widget" theme<br>

	<h3>Theme sample:</h3>

	\code
	<widget>
		<type value="ThemeWidget"/>
			<object>
			<name value="ThemeWidget"/>
			<filename name="background" value="default/back.bmp"/>
			<property name="backmode" value="TILE"/>
			<gradient name="gradient"
				color0="0x00B0B1B6"
				color1="0x0083838D"
				color2="0x007B7B83"
				color3="0x00585765"/>
			<property name="blend" value="200"/>
			<property name="transparency" value="0"/>
			<property name="bordersize" value="1"/>
		</object>
	</widget>
	\endcode
	<p>
	<h2>Code:</h2><p>
*/

class DECLSPEC PG_ThemeWidget : public PG_Widget  {
public:

	/**
	Create a new PG_ThemeWidget object
	@param parent	Pointer to parent widget
	@param r			Position of the widget (related to parent or screen)
	@param style		Widgetstyle to load. This style should be defined at your theme file (default = "ThemeWidget")
	This constructor creates a themed widget without any drawing surface.
	All drawing operations can be done via the eventBlit() callback handler.
	*/
	PG_ThemeWidget(PG_Widget* parent, const PG_Rect& r, const char* style="ThemeWidget");	

	/**
	*/
#ifdef SWIG
	%name(PG_ThemeWidgetEx) PG_ThemeWidget(PG_Widget* parent, const PG_Rect& r, bool bCreateSurface, const char* style="ThemeWidget");
#else
	/**
	Create a new PG_ThemeWidget object
	@param parent	Pointer to parent widget
	@param r			Position of the widget (related to parent or screen)
	@param bCreateSurface true - create a drawing surface for the widget.
	@param style		Widgetstyle to load. This style should be defined at your theme file (default = "ThemeWidget")
	This constructor creates a themed widget with an internal drawing surface.
	All drawing operations can be done via the eventDraw() callback handler.
	Additional blitting can be done via the eventBlit() callback. eventBlit() will NOT draw onto the
	internal drawing surface. Blitting will be done on the screen surface.
	*/
	PG_ThemeWidget(PG_Widget* parent, const PG_Rect& r, bool bCreateSurface, const char* style="ThemeWidget");
#endif

	/**
	*/
	~PG_ThemeWidget();

	/**
	Load a specific themestyle
	@param	widgettype		name of widget type to load
	*/
	void LoadThemeStyle(const char* widgettype);

#ifndef SWIG
	void LoadThemeStyle(const char* widgettype, const char* objectname);
#endif

	/**
	Load the background image from a file
	@param	filename		path to background image file
	@param	mode			BKMODE_TILE | BKMODE_STRETCH
	*/
	/**  */
#ifdef SWIG
	%name(SetBackgroundFile) bool SetBackground(const char* filename, int mode=BKMODE_TILE);
#else
	bool SetBackground(const char* filename, int mode=BKMODE_TILE);
#endif


	/**
	Load the background image from a file and set the colorkey
	@param	filename		path to background image file
	@param	colorkey		colorkey (0x00RRGGBB)
	@param	mode			BKMODE_TILE | BKMODE_STRETCH
	*/
	/**  */
#ifdef SWIG
	%name(SetBackgroundColorKey) bool SetBackground(const char* filename, int mode, Uint32 colorkey);
#else
	bool SetBackground(const char* filename, int mode, Uint32 colorkey);
#endif

	/**
	Define a surface as background image (will not be freed)
	@param	surface		pointer to background surface
	@param	mode			BKMODE_TILE | BKMODE_STRETCH
	@return						true on success
	*/
	bool SetBackground(SDL_Surface* surface, int mode=BKMODE_TILE);

	/**
	Defines the "blend-level" of gradient & background
	@param	backblend	0 - background image fully visible / 255 - gradient fully visible
	*/
	void SetBackgroundBlend(Uint8 backblend);

	/**
	Set the background gradient
	@param grad				a PG_Gradient structure describing the gradient
	*/
	void SetGradient(PG_Gradient& grad);

	/**
	Get the background gradient
	@return the background gradient
	*/
	PG_Gradient GetGradient();
	
	/**
	Set the bordersize of the widget
	param	b	bordersize in pixels (currently 0,1,2)
	*/
	void SetBorderSize(int b);

	/**
	Display an image in the widget
	@param filename		name of the image file to load
	@return				true on success
	With this function you can define an image to be displayed at the upper left corner
	of the widget. Image data will be erased when deleting the widget or loading / setting
	a new image.
	*/
	bool LoadImage(const char* filename);

	/**
	Display an image in the widget using a colorkey
	@param filename		name of the image file to load
	@param key			the colorkey (0xRRGGBB)
	@return				true on success
	With this function you can define an image with a colorkey to be displayed at the upper left corner
	of the widget. Image data will be erased when deleting the widget or loading / setting
	a new image.
	*/
	bool LoadImage(const char* filename, Uint32 key);
	
	/**
	Display an image in the widget
	@param image		pointer to surface to display
	@param bFreeImage    true if the image should be freed by the widget (default = true)
	@return				true on success
	With this function you can define an image to be displayed at the upper left corner
	of the widget.
	*/
	bool SetImage(SDL_Surface* image, bool bFreeImage = true);

	/**
	Set the fransparency of the widget
	@param t	transparency value (0 - opaque / 255 - fully transparent)
	*/
	void SetTransparency(Uint8 t);

	/**
	Create a 'themed' surface

	@param r					the dimensions of the surface to create
	@param gradient		pointer to a gradient structure (may be NULL)
	@param background	pointer to a background surface (may be NULL)
	@param bkmode		the mode how to fill in the background surface (BKMODE_TILE | BKMODE_STRETCH)
	@param blend				the blend-level between gradient an background
	@return 						the newly created surface

	The generated surface is managed by the surfacecache. Don't delete these surface with SDL_FreeSurface. Please use DeleteThemedSurface.
	*/
	static SDL_Surface* CreateThemedSurface(const PG_Rect& r, PG_Gradient* gradient, SDL_Surface* background, int bkmode, Uint8 blend);

	/**
	Delete a themed surface
	@param	surface		pointer to surface
	*/
	static void DeleteThemedSurface(SDL_Surface* surface);

	void SetSimpleBackground(bool simple);
	
	void SetBackgroundColor(const SDL_Color& c);
	
protected:

	/** */
	void eventSizeWidget(Uint16 w, Uint16 h);

	/** */
	void eventDraw(SDL_Surface* surface, const PG_Rect& rect);

	/** */
	void eventBlit(SDL_Surface* srf, const PG_Rect& src, const PG_Rect& dst);


	bool my_has_gradient;
	PG_Gradient my_gradient;
	SDL_Surface* my_background;
	SDL_Surface* my_image;

	Uint8 my_blendLevel;
	bool my_backgroundFree;
	int my_backgroundMode;
	int my_bordersize;

private:

#ifndef SWIG
	PG_ThemeWidget(const PG_ThemeWidget&);
	PG_ThemeWidget& operator=(const PG_ThemeWidget&);
#endif

	void Init(const char* style);

	void CreateSurface(Uint16 w = 0, Uint16 h = 0);

	/**
	This function frees background surface if possible
	*/
	void FreeSurface();

	void FreeImage();

	// this is a bit rude but neccessary for future binary compatibility
	// because adding non-static data members would break the ABI.
	// For this we put all private data into a dynamically created struct.
	PG_WidgetDataInternal* my_internaldata;
};

#endif // PG_THEMEWIDGET_H
