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
    Update Date:      $Date: 2003/11/24 10:43:23 $
    Source File:      $Source: /sources/paragui/paragui/include/pgbutton.h,v $
    CVS/RCS Revision: $Revision: 1.3.6.2.2.3 $
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
#include "pgsignals.h"
#include <string>

/**
	@author Alexander Pipelka
 
	@short Button that uses themes.
 
	Several predefined button IDs exist. All of them are associated with
	default icons used automatically when the given ID is assigned to a
	button:
 
	<blockquote>
	\p PG_Button::OK <img src="images/button_ok_icon.png" alt="OK Icon"><br>
	\p PG_Button::YES <img src="images/button_yes_icon.png" alt="Yes Icon"><br>
	\p PG_Button::NO <img src="images/button_no_icon.png" alt="No Icon"><br>
	\p PG_Button::APPLY <img src="images/button_apply_icon.png" alt="Apply Icon"><br>
	\p PG_Button::CANCEL <img src="images/button_cancel_icon.png" alt="Cancel Icon"><br>
	\p PG_Button::CLOSE <img src="images/button_close_icon.png" alt="Close Icon"><br>
	\p PG_Button::HELP <img src="images/button_help_icon.png" alt="Help Icon">
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
	Standard button IDs
	*/
	enum {
		OK = 0x80000001,
		YES = 0x80000002,
		NO = 0x80000003,
		APPLY = 0x80000004,
		CANCEL = 0x80000005,
		CLOSE = 0x80000006,
		HELP = 0x80000007
	};

	/**
	Button states
	**/
	typedef enum {
		PRESSED,
		UNPRESSED,
		HIGHLITED
	} STATE;

	/**
	Signal type declaration
	**/
	template<class datatype = PG_Pointer> class SignalButtonClick : public PG_Signal1<PG_Button*, datatype> {};
	
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
	void SetGradient(STATE state, const PG_Gradient& gradient);

	/**
		Set the background.
		@param state buttonstate to set
		@param background pointer to background surface
		@param mode background tiling mode

		This member function set's the buttons background and tiling mode for a specific state.
	*/
	void SetBackground(STATE state, SDL_Surface* background, int mode = BKMODE_TILE);

	/**
	Set the color of the border
	@param b	borderindex 0 = upper-left / 1 = lower-right
	@param color	border color (e.g. 0xRRGGBB)
	*/
	void SetBorderColor(int b, const PG_Color& color);

	/**
	Set icons for the button
	@param filenameup icon for unpressed state
	@param filenamedown icon for pressed state
	@return true on success
	*/

	// new in 1.0.2 (file)
	
	bool SetIcon2(const char* filenameup, const char* filenamedown,  const char* filenameover, const PG_Color& colorkey);

	bool SetIcon2(const char* filenameup, const char* filenamedown, const char* filenameover);


	// 1.0.1 versions (file)
		
	bool SetIcon(const char* filenameup, const char* filenamedown = NULL);

	bool SetIcon(const char* filenameup, const char* filenamedown, const PG_Color& colorkey);


	// new in 1.0.2 (surface)
	
	bool SetIcon(SDL_Surface* icon_up, SDL_Surface* icon_down = NULL, SDL_Surface* icon_over = NULL);

	// 1.0.1 versions (surface)
#ifndef SWIG
	bool SetIcon(SDL_Surface* icon_up, SDL_Surface* icon_down = NULL);
#endif

	SDL_Surface* GetIcon(STATE num);	
	
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
	void SetTransparency(Uint8 norm, Uint8 pressed, Uint8 high);

	/**
	 * Set the moving distance of the image when we press on it
	 */
	void SetShift(int pixelshift);

	/**  */
	bool GetPressed();

	/**
	Set the blend-level of gradient and background image
	@param blend blend-level
	@param mode one of BTN_STATE_NORMAL, BTN_STATE_PRESSED, BTN_STATE_HIGH
	This function sets the blend level of gradient and background image.
	
	If the blend-level is 0 only the background image is visible.
	At a level of 255 only the gradient is visible.
	*/
	void SetBlendLevel(STATE mode, Uint8 blend);

	/**
	Get the current blend level.
	@param mode button mode
	@return the current blend level
	*/
	Uint8 GetBlendLevel(STATE mode);

	SignalButtonClick<> sigClick;

protected:

	/**  */
	virtual void eventButtonSurface(SDL_Surface** surface, STATE newstate, Uint16 w, Uint16 h);

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

private:

#ifndef SWIG

	PG_Button(const PG_Button&);
	PG_Button& operator=(const PG_Button&);
#endif

	/**  */
	void FreeSurfaces();

	/**  */
	void FreeIcons();

	PG_ButtonDataInternal* _mid;
};

// Standard button IDs
/**
	Standard button ID: OK.
	DEPRECATED, USE PG_Button::OK
*/
#define BTN_ID_OK PG_Button::OK
/**
	Standard button ID: YES.
	DEPRECATED, USE PG_Button::YES
*/
#define BTN_ID_YES PG_Button::YES
/**
	Standard button ID: NO.
	DEPRECATED, USE PG_Button::NO
*/
#define BTN_ID_NO PG_Button::NO
/**
	Standard button ID: APPLY.
	DEPRECATED, USE PG_Button::APPLY
*/
#define BTN_ID_APPLY PG_Button::APPLY
/**
	Standard button ID: CANCEL.
	DEPRECATED, USE PG_Button::CANCEL
*/
#define BTN_ID_CANCEL PG_Button::CANCEL
/**
	Standard button ID: CLOSE.
	DEPRECATED, USE PG_Button::CLOSE
*/
#define BTN_ID_CLOSE PG_Button::CLOSE
/**
	Standard button ID: HELP.
	DEPRECATED, USE PG_Button::HELP
*/
#define BTN_ID_HELP PG_Button::HELP

#endif // PG_BUTTON_H
