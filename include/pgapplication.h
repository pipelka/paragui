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
    Update Date:      $Date: 2003/01/04 21:13:37 $
    Source File:      $Source: /sources/paragui/paragui/include/pgapplication.h,v $
    CVS/RCS Revision: $Revision: 1.3.6.5 $
    Status:           $State: Exp $
*/

/** \file pgapplication.h
	Header file for the PG_Application class.
	This include file defines the PG_Application class the PG_Main function and some macros for source backward compatibility.
*/

#ifndef PG_APPLICATION_H
#define PG_APPLICATION_H

#ifdef SWIG
%include "swigcommon.h"
%module pgapplication
%{
#include "pgapplication.h"
%}
#endif

#include "pgmessageobject.h"
#include "pgfilearchive.h"
#include "pgfont.h"
#include "pgtheme.h"

/**
	@author Alexander Pipelka
 
	@short The class that represent an application in ParaGUI. It handles the main loop, screen attibutes etc.
 
	An application must have a maximum of one PG_Application. If you try to create more than one PG_Application
	the constructor will exit your application with an console error message.
 
        Every Paragui application needs to have a <code>PG_Application</code> object. The Application object is
        the controller for events, screen initialization, theme support and main loop.
        Here is an example of the steps necesary for creating a simple Paragui application that opens a 640x480
        window with a button in the middle.
 
        <pre>
        \code		
        #include <paragui.h>
        #include <pgapplication.h>
        #include <pgbutton.h>
        
        
        // Event handler for button click 
        PARAGUI_CALLBACK(buttonHandler) { 
          cout << "Ouch !\\n";
          return true;
        } 
          
        
        int main(  int argc, char **argv ) { 
          const int WIDTH  = 640; 
          const int HEIGHT = 480; 
          
          PG_Application app; 
          
          app.LoadTheme("qnx");                      // Load the QNX theme 
          app.InitScreen(640,480,16,SDL_SWSURFACE);  // SDL_SURFACE | SDL_FULLSCREEN for full screen support
 
          PG_Button btnOK(NULL,0, PG_Rect((WIDTH-100)/2,(HEIGHT-20)/2,100,20),"Push me !");
 
          btnOK.SetEventCallback(MSG_BUTTONCLICK,buttonHandler); // Set the event handler
          btnOK.Show(); 
           
          app.Run();                                 // Application loop, exit with Esc by default 
        } 
 
        \endcode
        </pre>
*/

class DECLSPEC PG_Application : public PG_MessageObject, public PG_FileArchive, public PG_FontEngine  {
public:

	/**  */
	PG_Application();

	/**  */
	~PG_Application();

	/**
	Initialize the screen

	@param	w	screenwidth in pixels
	@param	h	screenheight in pixels
	@param	depth	screendepth in bits per pixel
	@param	flags	PG_ screen initialization flags
	*/
#ifdef SWIG
	// swig messes up the default arguments
	bool InitScreen(int w, int h, int depth, unsigned int flags);
#else

	bool InitScreen(int w, int h, int depth=DISPLAY_DEPTH, Uint32 flags = SDL_SWSURFACE /* | SDL_FULLSCREEN*/ | SDL_HWPALETTE);
#endif

	/**
	Load a widget theme

	@param	xmltheme	name of the theme (e.g. default)
	@param	asDefault	apply the theme as default widgettheme
	@param	searchpath	path where the themefile is located
	*/
	PG_Theme* LoadTheme(const char* xmltheme, bool asDefault = true, const char* searchpath = NULL);

	/**
	Run the applications main eventloop

	@param	threaded	run the eventloop in a separate thread
	@return			pointer to event thread
	If theaded is false this function will exit when the eventloop quits (MSG_QUIT). If threaded is true
	it will return immediately and a thread processing events is started.
	CAUTION: Threaded eventloops are unsuported under Win32 (windows specific behavior)
	*/
	SDL_Thread* Run(bool threaded = false);

	/**
	Run the modal message pump. This function will exit when the main window was closed.
	*/
	static int RunEventLoop(void* data);

	/**
	Exit the main eventloop
	*/
	void Quit();

	/**
	Set a custom screen surface

	@param	screen	pointer to a surface
	@return		pointer the new screen surface
	*/
	SDL_Surface* SetScreen(SDL_Surface* screen);

	/**
	Get the current screen surface

	@return	pointer the screen surface
	*/
	static SDL_Surface* GetScreen();

	/**
	Set a lock on the screen surface (to avoid concurrent drawing operations)

	@return	true - the lock was established successfully
	*/
#ifndef WIN32
	inline static bool LockScreen() {
		return (SDL_mutexP(mutexScreen) == 0);
	}
#else
	static bool LockScreen();
#endif

	/**
	Unlock the screen surface

	@return	true - the unlock operation was successful
	*/
#ifndef WIN32
	inline static bool UnlockScreen() {
		return (SDL_mutexV(mutexScreen) == 0);
	}
#else
	static bool UnlockScreen();
#endif


	/**
	Set the application's background image

	@param	filename	path to a bitmap file
	@param	mode		background mode (BKMODE_TILE | BKMODE_STRETCH)
	@return			true - background image was altered successfully
	*/
	bool SetBackground(const char* filename, int mode=BKMODE_TILE);

	/**
	Set the application's background image

	@param	surface	pointer to a background surface
	@param	mode	background mode (BKMODE_TILE | BKMODE_STRETCH)
	@return		true - background image was altered successfully
	*/
#ifdef SWIG
	%name(SetBackground2) bool SetBackground(SDL_Surface* surface, int mode=BKMODE_TILE);
#else

	bool SetBackground(SDL_Surface* surface, int mode=BKMODE_TILE);
#endif

	/**
	Redraw the application background
	*/
	static void RedrawBackground(const PG_Rect& rect);

	/**
	Enable / disable the emergency quit key ("ESC")

	@param	esc	true - "ESC" key actiavted
	*/
	void SetEmergencyQuit(bool esc);

	/**
	Add an application search path

	@param	path	the application will search for file (images,...) in this path,
								as well as in all pathes previously added.
	*/
	static void SetApplicationPath(const char* path);

	/**
	Return the current application path

	@return	the current path
	*/
	static const char* GetApplicationPath();

	/**
	Tries to find a specifies file

	@param	file	file to look for
	@return		path where the file was found (of NULL if nor found)
	*/
	static const char* GetRelativePath(const char* file);

	/**
	Get the current screen (or window) height

	@return	height in pixels
	*/
	static int GetScreenHeight();

	/**
	Get the current screen (or window) width

	@return	width in pixels
	*/
	static int GetScreenWidth();

	/**
	Do a page flip (only for double buffered screens)
	*/
	static void FlipPage();

	/**  */
#ifndef SWIG
	void PrintVideoTest();
#endif

	/**
	Get the current default widgettheme

	@return	pointer to PG_Theme definition
	*/
	static PG_Theme* GetTheme();

	/**
	Check if the application is currently in bulk mode

	@return	true / false
	Bulkmode means that all widget are always blitted at once.
	*/
	static bool GetBulkMode();

	static void SetBulkMode(bool bulk = true);

	static bool GetGLMode();

	void EnableBackground(bool enable = true);

	void EnableAppIdleCalls(bool enable = true);

	/**
	Set application`s window-manager icon

	@param filename image file to load
	Set icon for application`s window-manager window. You must use bitmap  
	with sizes dividable by 8 transparent color with palete.
	Transparent color is the color of first up-left pixel.
	THIS FUNCTION MUST BE PROCESSED BEFORE PG_Application::InitScreen()
	*/
	void SetIcon(const char *filename);

	/**
	Set application`s window-manager title and icon name.

	@param title title name
	@param icon icon name
	Sets the title-bar and icon name of the display window.
	*/
	void SetCaption(const char *title, const char *icon);

	/**
	Get application`s window-manager title and icon name.

	@param title return place for title name pointer
	@param icon return place for icon name pointer
	Set pointers to the window title and icon name.
	*/
	void GetCaption(char **title, char **icon);

	/**
	Iconify/Minimise the window-manager window

	@return   returns non-zero on success or 0 if iconification is not support or was refused by the window manager.
	If the application is running in a window managed environment Iconify attempts to iconify/minimise it.=20
	*/
	int Iconify(void);

	/**
	Load layout from the XML file
	@param name name of the xml file
	@return   returns non-zero on success or 0 if not succes
	*/
	static bool LoadLayout(const char *name);

	/**
	Load layout from the XML file
	@param name name of the xml file
	@param WorkCallback address of the progress callback function
	@return   returns non-zero on success or 0 if not succes
	*/
#ifndef SWIG
	static bool LoadLayout(const char *name, void (* WorkCallback)(int now, int max));
#endif

	/**
	Load layout from the XML file
	@param name name of the xml file
	@param WorkCallback address of the progress callback function
	@param UserSpace address of user data with are returned by Processing instruction etc.
	@return   returns non-zero on success or 0 if not succes
	*/
#ifndef SWIG
	static bool LoadLayout(const char *name, void (* WorkCallback)(int now, int max), void *UserSpace);
#endif

	/**
	Get widget by name
	@param Name name of the widget
	@return   pointer to the requested widget or null if failed
	*/
	static PG_Widget *GetWidgetByName(const char *Name);

	template<class T>
	static T* GetWidget(const char* Name) {
		return static_cast<T*>(GetWidgetByName(Name));
	}

	template<class T>
	static T* GetWidget(int id) {
		return static_cast<T*>(GetWidgetById(Name));
	}

	/**
       Get widget by id.

       @param id  id of the widget

       @return pointer to the requested widget or 0 if failed
	*/
	static PG_Widget *GetWidgetById(int id);
    
	/**
	Set default font color
	@param	Color SDL_Color structure contains color information (RGB)
	@return   0 when OK
	*/
	static void SetFontColor(const SDL_Color& Color);

	/**
	Set default font color
	@param	Red	Red color value 0 - 255
	@param	Green	Green color value 0 - 255
	@param	Blue	Blue color value 0 - 255
	@return   0 when OK
	*/
#ifdef SWIG
	%name(SetFontColorRGB) static void SetFontColor(int Red, int Green, int Blue);
#else
	static void SetFontColor(int Red, int Green, int Blue);
#endif

	/**
	Set default font color
	@param	Color Value of the color 0x00RRGGBB (RGB)
	@return   0 when OK
	*/
#ifdef SWIG
	%name(SetFontColor32) static void SetFontColor(int Color);
#else
	static void SetFontColor(int Color);
#endif

	/**
	Set default font transparency (!!!)
	@param	Alpha	Value 0 - 255 (0 = invisible, 255 = fully visible)
	@return   0 when OK
	*/
	static void SetFontAlpha(int Alpha);

	/**
	Set default font style
	@param	Style	Binary combination (OR) of PG_FSTYLE_NORMAL, PG_FSTYLE_BOLD, PG_FSTYLE_ITALIC and PG_FSTYLE_UNDERLINE
	@return   0 when OK
	*/
	static void SetFontStyle(int Style);

	/**
	Set default font size
	@param	Size	size of the font
	@return   0 when OK
	*/
	static void SetFontSize(int Size);

	/**
	Set default font index
	@param	Index	Index of the desired font face in the font file (usualy 0)
	@return   0 when OK
	*/
	static void SetFontIndex(int Index);

	/**
	Set default font name
	@param	Name	Filename of the font (this function don`t load the font - or check presention of the file !!!)
	@return   0 when OK
	*/
	static void SetFontName(const char *Name);

	//! Set a graphical mouse cursor.
	/*!

	  This function makes the cursor use software rendering with
	  the image specified. Note that this can be slow and result
	  in sluggish mouse performance. Note that calling this
	  function doesn't enable software rendering. An additional
	  call to PG_ShowCursor is required.

	  \note The image will receive an additional reference and
	  should be freed by the caller using SDL_FreeSurface when the
	  caller is done using it.
	  
	  \note If image is zero, the hardware cursor will be
	  restored. Note however that the cursor mode will remain at
	  PG_CURSOR_SOFTWARE, so any subsequent calls to this function
	  will reenable the software cursor automatically.

	  \param image the new cursor
	  \sa PG_ShowCursor, PG_DrawCursor
	*/
	static void SetCursor(SDL_Surface *image);
	
	//! Update the graphical mouse cursor
	/*!
	  This will redraw the graphical curser pointer, if enabled. You
	  might need to call this if you stop the normal event loop from running.
	*/
	static void DrawCursor();
	
	//! Set or query the type of mouse cursor to use.
	/*!
	  This function is used to set or query the type of mouse cursor used.
	  See the documentation for PG_CURSOR_MODE for more details.
	\param mode the new mode for the request
	\return the previous cursor mode 
	*/
	static PG_CURSOR_MODE ShowCursor(PG_CURSOR_MODE mode);

	//! Disable dirty widget updates
	/*!
	 This function is used to disable dirty widget updates globally.
	 Dirty updates are usually used to speed up blitting. However, it can cause
	 problems with 'semitransparent' widgets.
	\param disable disable ditry updates
	
	\note All widgets created after this call wont use the dirty update anymore.
	Widgets created before will still use this mode if enabled.
	*/
	static void DisableDirtyUpdates(bool disable);
	
	//! Check if the 'dirty update' mode is disabled globally
	/*!
	\return true - if the 'dirty update' mode is disabled globally
	*/
	static bool GetDirtyUpdatesDisabled();

	static PG_Application* GetApp();
	
	static PG_Font* DefaultFont;

protected:

	/**
	Cleanup the application data
	*/
	void Shutdown();

	static void ClearOldMousePosition();

	/**  */
	bool eventKeyUp(const SDL_KeyboardEvent* key);

	/**  */
	bool eventKeyDown(const SDL_KeyboardEvent* key);

	/**  */
	bool eventQuit(int id, PG_MessageObject* widget, unsigned long data);

	/**  */
	bool eventResize(const SDL_ResizeEvent* event);

	/**  */
	virtual void eventInit();

private:

#ifndef SWIG
	// disable the copy operators
	PG_Application(const PG_Application&);
	PG_Application& operator=(const PG_Application&);
#endif

	bool my_freeBackground;
	static SDL_Surface* my_background;
	static SDL_Surface* my_scaled_background;
	static SDL_Color my_backcolor;
	static int my_backmode;
	
	static PG_Theme* my_Theme;

#ifndef SWIG
	static string app_path;
#endif

	static PG_Application* pGlobalApp;
	static SDL_Surface* screen;

	static bool bulkMode;
	static bool glMode;
	static bool emergencyQuit;
	static bool enableBackground;
	static bool enableAppIdleCalls;

	static SDL_Surface *my_mouse_pointer;
	static PG_Rect my_mouse_position;
	static PG_CURSOR_MODE my_mouse_mode;
	static SDL_mutex* mutexScreen;
	static bool disableDirtyUpdates;
};

/**
	runs the ParaGUI main loop.
	@param argc argument count (from main)
	@param argv array of arguments (from main)
	@param app the PG_Application object
	@return status code.

	This function is an encapsulation of app->Run().
	It also handles exceptions (if enabled).
*/
int PG_main(int argc, char **argv, PG_Application *app);

#endif // PG_APPLICATION_H
