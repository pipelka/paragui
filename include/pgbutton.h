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
    Update Date:      $Date: 2002/04/15 13:22:31 $
    Source File:      $Source: /sources/paragui/paragui/include/pgbutton.h,v $
    CVS/RCS Revision: $Revision: 1.1 $
    Status:           $State: Exp $
*/

/** \file pgbutton.h
	Header file for the PG_Button class.
	This include file defines the standard button ID's and the PG_Button class.
*/

#ifndef PG_BUTTON_H
#define PG_BUTTON_H

#ifdef SWIG
%include "swigcommon.h"
%module pgbutton
%{
#include "pgbutton.h"
%}
#endif

#include "pgwidget.h"
#include <string>

/**
	@author Alexander Pipelka
 
	@short Button that uses themes.
 
	Several predefined button IDs exist. All of them are associated with
	default icons used automatically when the given ID is assigned to a
	button:
 
	<blockquote>
	\p BTN_ID_OK <img src="images/button_ok_icon.png" alt="OK Icon"><br>
	\p BTN_ID_YES <img src="images/button_yes_icon.png" alt="Yes Icon"><br>
	\p BTN_ID_NO <img src="images/button_no_icon.png" alt="No Icon"><br>
	\p BTN_ID_APPPLY <img src="images/button_apply_icon.png" alt="Apply Icon"><br>
	\p BTN_ID_CANCEL <img src="images/button_cancel_icon.png" alt="Cancel Icon"><br>
	\p BTN_ID_CLOSE <img src="images/button_close_icon.png" alt="Close Icon"><br>
	\p BTN_ID_HELP <img src="images/button_help_icon.png" alt="Help Icon">
	</blockquote>
    
	\anchor theme_PG_Button
 
	<h2>Theme support</h2><p>
 
	<b>widget type:</b>		Button (default)<br>
	<b>object name:</b>		Button<br>
 
	<h3>Parent theme:</h3>
 
	\ref theme_PG_Widget "PG_Widget" theme<br>
 
	<h3>Theme sample:</h3>
 
	\code
	<widget>
		<type value="Button"/>
		<object>
			<name value="Button"/>
			<filename name="background0" value="default/button_unpressed.png"/>
			<filename name="background1" value="default/button_pressed.png"/>
			<filename name="background2" value="default/button_highlighted.png"/>
			<color name="textcolor" value="0x00ff9807"/>
			<property name="backmode0" value="TILE"/>
			<property name="backmode1" value="TILE"/>
			<property name="backmode2" value="TILE"/>
			<gradient name="gradient0"
				color0="0x000000FF"
				color1="0x000000FF"
				color2="0x000000FF"
				color3="0x000000FF"/>
			<gradient name="gradient1"
				color0="0x000000FF"
				color1="0x000000FF"
				color2="0x000000FF"
				color3="0x000000FF"/>
			<gradient name="gradient2"
				color0="0x000000FF"
				color1="0x000000FF"
				color2="0x000000FF"
				color3="0x000000FF"/>
			<property name="blend0" value="0"/>
			<property name="blend1" value="0"/>
			<property name="blend2" value="0"/>
			<property name="bordersize0" value="0"/>
			<property name="bordersize1" value="0"/>
			<property name="bordersize2" value="0"/>
			<property name="transparency0" value="0"/>
			<property name="transparency1" value="0"/>
			<property name="transparency2" value="0"/>
			<filename name="iconup" value="none"/>
			<filename name="icondown" value="none"/>
		</object>
	</widget>
	\endcode
	<p>
	<h2>Code:</h2><p>
*/

struct PG_ButtonDataInternal;

class DECLSPEC PG_Button : public PG_Widget  {
public:

	/**
	Constructor for the PG_Button class
	@param parent	pointer to the parent widget or NULL
	@param id id of the button (can be used in callbacks)
	@param r screen position of the button
	@param text button label
	@param style themestyle of the button
	*/
	PG_Button(PG_Widget* parent, int id, const PG_Rect& r, const char* text = NULL, const char* style="Button");

	/**  */
	virtual ~PG_Button();

	/**  */
	void LoadThemeStyle(const char* widgettype);

#ifndef SWIG
	/**  */
	void LoadThemeStyle(const char* widgettype, const char* objectname);
#endif

	/**
		Set the gradient.
		@param state buttonstate to set
		@param gradient gradient to set

		This member function set's the buttons gradient for a specific state.
	*/
	void SetGradient(int state, PG_Gradient& gradient);

	/**
		Set the gbackground.
		@param state buttonstate to set
		@param background pointer to background surface
		@param mode background tiling mode

		This member function set's the buttons background and tiling mode for a specific state.
	*/
	void SetBackground(int state, SDL_Surface* background, int mode = BKMODE_TILE);

	/**
	Set the color of the border
	@param b	borderindex 0 = upper-left / 1 = lower-right
	@param color	border color (e.g. 0xRRGGBB)
	*/
	void SetBorderColor(int b, Uint32 color);

	/**
	Set icons for the button
	@param filenameup icon for unpressed state
	@param filenamedown icon for pressed state
	@return true on success
	*/
	bool SetIcon(const char* filenameup, const char* filenamedown = NULL);

	/**
	Set icons for the button
	@param filenameup icon for unpressed state
	@param filenamedown icon for pressed state
	@param colorkey	colorkey (e.g. 0xRRGGBB)
	@return true on success
	*/
#ifdef SWIG
	%name(SetIconColorkey) bool SetIcon(const char* filenameup, const char* filenamedown, Uint32 colorkey);
#else
	bool SetIcon(const char* filenameup, const char* filenamedown, Uint32 colorkey);
#endif

	/**
	Set icons for the button
	@param icon_up pointer to icon for unpressed state
	@param icon_down pointer to icon for unpressed state
	@return true on success
	*/
#ifdef SWIG
	%name(SetIconSurface) bool SetIcon(SDL_Surface* icon_up, SDL_Surface* icon_down = NULL);
#else
	bool SetIcon(SDL_Surface* icon_up, SDL_Surface* icon_down = NULL);
#endif

	/**
	Set the bordersize of the button
	@param norm	bordersize for unpressed state
	@param pressed	bordersize for pressed state
	@param high	bordersize for highlighted state
	*/
	void SetBorderSize(int norm, int pressed, int high);

	/**
	*/
	void SetToggle(bool bToggle);

	/**  */
	void SetPressed(bool pressed);

	/**  */
	void SetTransparency(int norm, int pressed, int high);

	/**  */
	bool GetPressed();

protected:

	/**  */
	virtual void eventButtonSurface(SDL_Surface** surface, int newstate, Uint16 w, Uint16 h);

	/**  */
	void eventBlit(SDL_Surface* srf, const PG_Rect& src, const PG_Rect& dst);

	/**  */
	void eventSizeWidget(Uint16 w, Uint16 h);

	/**  */
	void eventMouseLeave();

	/**  */
	void eventMouseEnter();

	/**  */
	bool eventMouseButtonUp(const SDL_MouseButtonEvent* button);

	/**  */
	bool eventMouseButtonDown(const SDL_MouseButtonEvent* button);

	int my_bordersize[3];
	int my_transparency[3];
	int my_state;
	//int id;
	int my_pressShift;

private:

#ifndef SWIG
	PG_Button(const PG_Button&);
	PG_Button& operator=(const PG_Button&);
#endif

	/**  */
	void FreeSurfaces();

	/**  */
	void FreeIcons();

	PG_ButtonDataInternal* my_internaldata;
};

// Standard button IDs
/**
	Standard button ID: OK.
*/
#define BTN_ID_OK      0x80000001
/**
	Standard button ID: YES.
*/
#define BTN_ID_YES     0x80000002
/**
	Standard button ID: NO.
*/
#define BTN_ID_NO      0x80000003
/**
	Standard button ID: APPLY.
*/
#define BTN_ID_APPLY   0x80000004
/**
	Standard button ID: CANCEL.
*/
#define BTN_ID_CANCEL  0x80000005
/**
	Standard button ID: CLOSE.
*/
#define BTN_ID_CLOSE   0x80000006
/**
	Standard button ID: HELP.
*/
#define BTN_ID_HELP    0x80000007

#endif // PG_BUTTON_H
