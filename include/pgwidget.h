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
    Update Date:      $Date: 2003/12/02 15:27:58 $
    Source File:      $Source: /sources/paragui/paragui/include/pgwidget.h,v $
    CVS/RCS Revision: $Revision: 1.3.6.3.2.3 $
    Status:           $State: Exp $
*/

#ifndef PG_WIDGET_H
#define PG_WIDGET_H

#include "pgmessageobject.h"
#include "pgrectlist.h"
#include "pgfont.h"

#include MAP_INC

class PG_Widget;
class PG_WidgetDataInternal;

/**
	@author Alexander Pipelka
	
	@short Base class of all widgets.
 
	Provides graphics context and message handling functionality.
 
	\anchor theme_PG_Widget
 
	<h2>Theme support</h2><p>
 
	This class provides themeing capabilities only for subclassed widgets.<p>
 
	<b>widget type:</b>		none (managed through subclass)<br>
	<b>object name:</b>		none (managed through subclass)<br>
 
	<h3>Theme sample:</h3>
 
	\code
	<widget>
		<type value="xxx"/>
			<object>
			<name value="xxx"/>
			<property color="textcolor" value="0x00FFFFFF"/>
			<property color="bordercolor0" value="0x00202020"/>
			<property color="bordercolor1" value="0x00E0E0E0"/>
		</object>
	</widget>
	\endcode
	<p>
	<h2>Code:</h2><p>
*/

class DECLSPEC PG_Widget : public PG_MessageObject, public PG_Rect  {
public:


	//! Keyevent actions
	typedef enum {
		ACT_ACTIVATE,	//!< Widget got the input focus
		ACT_DEACTIVATE,	//!< Widget has lost the input focus
		ACT_OK,	//!< Widget action event (e.g. button press on a PG_Button object)
		ACT_CANCEL,	//!< Widget cancel-action
		ACT_LEFT,	//!< Cursor left was pressed
		ACT_RIGHT,	//!< Cursor right was pressed
		ACT_UP,	//!< Cursor up was pressed
		ACT_DOWN	//!< Cursor down was pressed
	} KeyAction;

	/**
	Creates a PG_Widget without an object-surface

	@param parent	the parentobject for the new widget or NULL if it is a toplevel widget
	@param rect	initial position for the widget

	This is the constructor for the PG_Widget class (really!)
	*/
	PG_Widget(PG_Widget* parent, const PG_Rect& rect);

	/**
	Creates a PG_Widget with an internal object surface

	@param parent		the parentobject for the new widget or NULL if it is a toplevel widget
	@param rect		initial position for the widget
	@param bObjectSurface	flag if a surface for the object should be created
	*/
	PG_Widget(PG_Widget* parent, const PG_Rect& rect, bool bObjectSurface);

	/**
	Destroys a PG_Widget

	This is the destructor for the PG_Widget class
	*/
	virtual ~PG_Widget();

	/**
	Load a style from the theme definition

	@param widgettype	name of the widgettype

	Loads the defined style for a given widgettype
	*/
	void LoadThemeStyle(const char* widgettype);

	/**
	Load a style from the theme definition

	@param widgettype	name of the widgettype
	@param objectname	name of the object

	Loads the defined style of a given widgettype and objectname.
	*/
	virtual void LoadThemeStyle(const char* widgettype, const char* objectnmae);

	/**
	Start to drag a widget

	StartWidgetDrag prepares to widget to be dragged.
	*/
	void StartWidgetDrag();

	/**
	Drag the widget to a given position (in screen coordinates)

	@param x	x-position
	@param y	y-position
	*/
	void WidgetDrag(int x, int y);

	/**
	Finishes a drag operation

	@param x	x endposition
	@param y	y endposition
	*/
	void EndWidgetDrag(int x, int y);

	/**
	Move a widget

	@param x	new x-position (in parent context)
	@param y	new y-position (in parent context)
	@return		function succeeded

	This function moves the widget
	*/
	bool MoveWidget(int x, int y);

	/**
	Move a widget -- OBSOLETE

	@param x	new x-position (in parent context)
	@param y	new y-position (in parent context)
	@return		function succeeded

	This function moves the widget.
	CAUTION: This function will be removed in the final version. Please use MoveWidget(int x, int y)
	*/
	bool MoveWindow(int x, int y);

	/**
	Move and resize widget

	@param r	new widget rectangle (client coordinates)
	@return		function succeeded

	This function moves and resizes the widget to fit the given rectangle.
	*/
	bool MoveWidget(const PG_Rect& r);

	/**
	Move and resize widget -- OBSOLETE

	@param r	new widget rectangle (client coordinates)
	@return		function succeeded

	This function moves and resizes the widget to fit the given rectangle.
	CAUTION: This function will be removed in the final version. Please use MoveWidget(const PG_Rect& r)
	*/
	bool MoveWindow(const PG_Rect& r);

	/**
	Resize a widget -- OBSOLETE

	@param w	new widget-width
	@param w	new widget-height
	@return		function succeeded

	This function resizes the widget. This member function will be removed in the final version.
	Please use SizeWidget().
	*/
	virtual bool SizeWindow(Uint16 w, Uint16 h);

	/**
	Resize a widget

	@param w	new widget-width
	@param w	new widget-height
	@return		function succeeded

	This function resizes the widget
	*/
	virtual bool SizeWidget(Uint16 w, Uint16 h);

	/**
	Convert a client (widget) coordinate to a screen position

	@param x	x - widgetcoordinate
	@param y	y - widgetcoordinate
	@return		PG_Point structure with the screen position
	*/
	PG_Point ClientToScreen(int x, int y);

	/**
	Convert a screen position to a client (widget) coordinate

	@param x	x - screenposition
	@param y	y - screenposition
	@return		PG_Point structure with the client position
	*/
	PG_Point ScreenToClient(int x, int y);

	/**
	Return the pointer to the widget's drawing surface

	@return SDL_Surface pointer to the drawing surface
	*/
	SDL_Surface* GetWidgetSurface();

	/**
	Return the pointer to the screen surface

	@return	SDL_Surface pointer to the screen surface
	*/
	SDL_Surface* GetScreenSurface();

	/**
	Check if the object is visible
	@return							true if object is visible
	*/
	bool IsVisible();

	/**
	Get the parentwidget of a widget	

	@return	a pointer to the parentwidget or NULL if there is no parentwidget
	*/
	PG_Widget* GetParent();

	/**
	Add a clientwidget (which will be embedded into this widget)

	@param child	the widget to add
	*/
	virtual void AddChild(PG_Widget* child);

	/**
	Process a native PG_ event

	@param event	PG_ event to process
	@return		true if the event was sucessfully processed

	ProcessEvent asks the widget to process a given event.
	*/
	virtual bool ProcessEvent(const SDL_Event* event, bool bModal = false);

	/**
	Set the widgetid

	@param id	a number which can be used to identify the widget

	This id can be used in callbacks or eventhandlers to identify the
	widget. It can also be used to find a child within the group of
	children.
	*/
	void SetID(int id);

	/**
	Return the widgetid
	@return	id of the widget
	*/
	int GetID();

	/**
	Find a child that is identified by the given ID.
	@param id   the id of the child to return
	@return A pointer to the child with the given ID or 0 if no such child exists.
	*/
	PG_Widget* FindChild(int id);

	/**
	Find a child that is identified by the given name.
	@param name   the name of the child to return
	@return A pointer to the child with the given name or 0 if no such child exists.
	*/
	PG_Widget* FindChild(const char *name);

	/**
	Check if the mousepointer is currently inside the widget
	@return	true if the mousepointer is inside
	*/
	bool IsMouseInside();

	/**
	Redraw the widget and all embedded child widgets
	@param	update	if true Update() is called after the redraw
	@return		true if the redraw operation succeeded
	*/
	bool Redraw(bool update = true);

	/**
	Blit the widget to the screen
	@param recursive	if true all embedded widget will also be blitted to screen
	@param restore		restore the background before blitting if true
	This function only performs a SDL_BlitSurface() the screen content will NOT be updated
	*/
	virtual void Blit(bool recursive = true, bool restore = true);

	/**
	Update the widget's screen area
	@param doBlit	if true a Blit() operation is done before the update
	*/
	void Update(bool doBlit = true);

	/**
	Update a screen area
	@param r	update rectangle
	*/
	static void UpdateRect(const PG_Rect& r);

	/**
	Update (render) the whole application screen
	*/
	static void UpdateScreen();

	/**
	Make a widget visible
	@param fade	do a smooth fade in if true
	*/
	void Show(bool fade = false);

	/**
	Hide a widget
	@param fade	do a smooth fade out if true
	*/
	void Hide(bool fade = false);

	/**
	Check if the widget is in front of another one
	*/
	bool IsInFrontOf(PG_Widget*);

	/**
	Send the widget back to the end of the list
	*/
	void SendToBack();

	/**
	Reorder the widget in front of all others
	*/
	void BringToFront();

	/**
	Get the toplevel widget
	*/
	PG_Widget* GetToplevelWidget();

	/**
	Hide all widgets of an application
	*/
	static void HideAll();

	void RecalcClipRect();

	/**
	Restore the background (all widgets behind this one)
	@param clip clipping rectangle
	@param force force to redraw the background even if dirty updates are enabled.
	*/
	virtual bool RestoreBackground(PG_Rect* clip = NULL, bool force = false);

	static PG_Widget* FindWidgetFromPos(int x, int y);

	/**
	Set the visiblility of a widget with updating the screen contents
	@param visible	true - visible / false - invisible
	*/
	void SetVisible(bool visible);

	/**
	Set the number of steps for fading in/out widgets
	@param steps	number of steps
	*/
	void SetFadeSteps(int steps);

	/**
	Set the transparency of all child widgets
	@param t	transparency 0 - opaque / 255 - full transparent
	*/
	void SetChildTransparency(Uint8 t);

	/**
	Get a list of child widgets

	@return	pointer to childlist
	*/
	PG_RectList* GetChildList();

	/**
	Get the number of childwidgets

	@return	number of childwidgets
	*/
	int GetChildCount();

	/**  */
	void MoveRect(int x, int y);

	/** */
	static void BulkUpdate();

	/** */
	static void BulkBlit();

	// Navigation

	/** */
	virtual bool Action(KeyAction action);

	/**
	   Get a list of all toplevel widgets
	   @return pointer to a PG_RectList object
	*/
	static PG_RectList* GetWidgetList();
	
	/**
	   Set the name for the widget
	   @param name	Name of the widget - size of the name is defined in PG_NAMESIZE
	*/
	void SetName(const char *name);

	/**
	Get the name for the widget
	@return	name of the widget
	*/
	const char* GetName();

	/**
	Load layout from the XML file to the current widget
	@param name	name of the xml file
	@return returns non-zero on success or 0 if not succes
	*/
	bool LoadLayout(const char *name);

	/**
	Load layout from the XML file to the current widget
	@param name	name of the xml file
	@param WorkCallback	address of function to show progress of loading layout
	@return returns non-zero on success or 0 if not succes
	*/
	bool LoadLayout(const char *name, void (* WorkCallback)(int now, int max));

	/**
	Load layout from the XML file to the current widget
	@param name	name of the xml file
	@param WorkCallback	address of function to show progress of loading layout
	@param UserSpace address of user data witch are passed to Processing Instruction handler etc.
	@return returns non-zero on success or 0 if not succes
	*/
	bool LoadLayout(const char *name, void (* WorkCallback)(int now, int max), void *UserSpace);

	/**
	Removes all childs
	*/
	void RemoveAllChilds();

	/**
	Sets user data to the widget (malloc inside)
	@param userdata	points to data to copy in
	@param size	size of data
	*/
	void SetUserData(void *userdata, int size);

	/**
	Sets user data to the widget (malloc inside)
	@return	size of stored user data (0 = no data stored in)
	*/
	virtual int GetUserDataSize();

	/**
	Gets user data from the widget
	@param userdata where to write data (must be allocated space with size from GetUserDataSize())
	*/
	virtual void GetUserData(void *userdata);

	/**
	Releases user data
	*/
	void ReleaseUserData();

	/**	*/
	bool RemoveChild(PG_Widget* child);

	/**
	Sets text
	@param text	Set the widget text and update widget
	*/
	virtual void SetText(const char* text);

	/**
	Adds text
	@param text	Add text to the widget text
	@param update Do the update
	*/
	void AddText(const char* text, bool update = false);

	/**
	Sets formated text
	@param text	Set the widget text (like printf) and update widget
	*/
	virtual void SetTextFormat(const char* text, ...);

	/** Returns text
	@return	Pointer to the text of the widget (read-only)
	*/
	virtual const char* GetText();

	void GetTextSize(Uint16& w, Uint16& h, const char* text = NULL);

	static void GetTextSize(Uint16& w, Uint16& h, const char* text, PG_Font* font);

	int GetTextWidth();

	int GetTextHeight();

	int GetFontAscender();

	int GetFontHeight();

	/**
	Return the current text color
	@return	PG_Color
	*/
	PG_Color GetFontColor();

	/**
	Set font color
	@param	Color PG_Color class contains color information (RGB)
	*/
	void SetFontColor(const PG_Color& Color);

	/**
	Set font transparency (!!!)
	@param	Alpha	Value 0 - 255 (0 = invisible, 255 = fully visible)
	@param	bRecursive alter all child widgets
	*/
	void SetFontAlpha(int Alpha, bool bRecursive = false);

	/**
	Set font style
	@param	Style	Binary combination (OR) of PG_FSTYLE_NORMAL, PG_FSTYLE_BOLD, PG_FSTYLE_ITALIC and PG_FSTYLE_UNDERLINE
	@param	bRecursive alter all child widgets
	*/
	void SetFontStyle(int Style, bool bRecursive = false);

	/**
	Set font size
	@param	Size	size of the font
	@param	bRecursive alter all child widgets
	*/
	void SetFontSize(int Size, bool bRecursive = false);

	/**
	Set font index
	@param	Index	Index of the desired font face in the font file (usualy 0)
	@param	bRecursive alter all child widgets
	*/
	void SetFontIndex(int Index, bool bRecursive = false);

	/**
	Set font name
	@param	Name	Filename of the font (this function don`t load the font - or check presention of the file !!!)
	@param	bRecursive alter all child widgets
	*/
	void SetFontName(const char *Name, bool bRecursive = false);

	/**
	Set widget size by size of text (should be used before Show() or AddWidget())
	@param	Width	Value witch is added to text width (default = 0)
	@param	Height	Value witch is added to text height  (default = 0)
	@param	Text	Text to get size from, if NULL my_text is used
	*/
	void SetSizeByText(int Width = 0, int Height = 0, const char *Text = NULL);

	/**
	Get the size of the font
	*/
	int GetFontSize();

	/**
	Get the current font parameters
	@return	pointer to the PG_Font object
	*/
	PG_Font* GetFont();

	/**
	Set the current font parameters
	@param	font	pointer to PG_Font object
	*/
	void SetFont(PG_Font* font);

	/**
	Render text inside the widget
	@param rect rectangle where the text should appear
	@param text pointer to text string
	*/
	void DrawText(const PG_Rect& rect, const char* text);

	/**
	Render text inside the widget
	@param x x-position where the text should appear
	@param x y-position where the text should appear
	@param text pointer to text string
	*/
	void DrawText(int x, int y, const char* text);

	/**
	Render text inside the widget and clip to a given clipping rectangle
	@param x x-position where the text should appear
	@param x y-position where the text should appear
	@param text pointer to text string
	@param cliprect text bounding rectangle
	*/
	void DrawText(int x, int y, const char* text, const PG_Rect& cliprect);

	/**
	Render text inside the widget and set the font color
	@param rect rectangle where the text should appear
	@param text pointer to text string
	@param color color of the rendered text
	*/
	void DrawText(const PG_Rect& rect, const char* text, const PG_Color& c);

	/**
	Render text inside the widget and set the font color
	@param x x-position where the text should appear
	@param x y-position where the text should appear
	@param text pointer to text string
	@param color color of the rendered text
	*/
	void DrawText(int x, int y, const char* text, const PG_Color& c);

	/**  */
	void DrawBorder(const PG_Rect& r, int size, bool up = true);

	/**
	Set the transparency of the drawing object
	@param	t						transparency (0 - opaque / 255 - fully transparent)
	*/
	virtual void SetTransparency(Uint8 t);

	/**
	Get the transparency of the drawing object
	@return							transparency (0 - opaque / 255 - fully transparent)
	*/
	Uint8 GetTransparency();

	/**
	Set the clipping rectangle for the object
	@param	x					x-position in client coordinates
	@param	y					y-position in client coordinates
	@param	w					width of the clipping rectangle
	@param	h					height of the clipping rectangle
	*/
	void SetClipRect(PG_Rect& r);

	/**
	Get the current clipping rectangle
	@return						the clipping rectangle
	*/
	PG_Rect* GetClipRect();

	/**
	Check if there is a clipping rectangle assigned to the object
	@return						true / false
	*/
	bool IsClippingEnabled();

	/**  */
	void GetClipRects(PG_Rect& src, PG_Rect& dst);

	/**  */
	void GetClipRects(PG_Rect& src, PG_Rect& dst, const PG_Rect& displayrect);

	/**  */
	void SetPixel(int x, int y, const PG_Color& c);

	/**  */
	void DrawHLine(int x, int y, int w, const PG_Color& c);

	/**  */
	void DrawVLine(int x, int y, int h, const PG_Color& c);

	/**  */
	void DrawRectWH(int x, int y, int w, int h, const PG_Color& c);

	/**  */
	void DrawLine(Uint32 x0, Uint32 y0, Uint32 x1, Uint32 y1, const PG_Color& color, Uint8 width=1);

	/**
	Enter modal mode
	*/
	virtual int RunModal();

	/**
	Quit modal mode
	*/
	void QuitModal();

	bool WillQuitModal();

	void StopQuitModal();
	
	/**
	Set the dirty update mode
	@param bDirtyUpdate true - enable / false - disable
	This function sets the dirty update mode of a widget. This greatly improves the rendering speed
	because the underlying widgets are not redrawn if the widgets transparency is equal to 0.
	It will cause render failures wrong if there is an alpha channel in the widget's drawing surface.
	If you encounter problems with activated dirty updates simple disable it.
	*/
	void SetDirtyUpdate(bool bDirtyUpdate);
	
	/**
	return if the dirty update mode is enabled
	@return true - dirty updates enabled
	*/
	bool GetDirtyUpdate();
	
	/**
		eventhandler for mouse movements.
		This overrideable handler is called everytime the mouse cursor is leaving the widget area.
	*/
	virtual void eventMouseLeave();
	
	/**
		eventhandler for mouse movements.
		This overrideable handler is called everytime the mouse cursor is entering the widget area.
	*/
	virtual void eventMouseEnter();

	void SetHidden(bool hidden);
	
	bool IsHidden();
	
protected:

	/**
		main eventhandler for messages
		@param msg pointer to a MSG_MESSAGE structure
		@return this eventhandler should return "true" if the message was proccessed.
		This messagehandler can be overridden to perform custom operations.
	*/	
	//bool eventMessage(MSG_MESSAGE* msg);

	/**
	Callback for the MoveWidget event
	@param x new x position
	@param y new y position
	This virtual function can be used to implement custom behavior for
	MoveWidget events.
	*/
	virtual void eventMoveWidget(int x, int y);

	/**
	Callback for the MoveWidget event -- OBSOLETE
	@param x new x position
	@param y new y position
	This virtual function can be used to implement custom behavior for
	MoveWidget events.
	CAUTION: This function will be removed in the final version
	*/
	virtual void eventMoveWindow(int x, int y);

	/**
	Callback for the SizeWidget event
	@param w new width
	@param h new height
	This virtual function can be used to implement custom behavior for
	SizeWidget events.
	*/
	virtual void eventSizeWidget(Uint16 w, Uint16 h);

	/**
	Callback for the SizeWidget event
	@param w new width
	@param h new height
	This virtual function can be used to implement custom behavior for
	SizeWidget events.
	CAUTION: This function will be removed in the final version
	*/
	virtual void eventSizeWindow(Uint16 w, Uint16 h);

	/**
	overridable eventhandler to draw the object surface
	@param surface the widgets drawing surface.
	@param rect rectangle to draw within.
	This eventhandler is called whenevener the widget contents should be redrawn.
	@Note Only widgets with drawing surfaces (see the constructor) will call this eventhandler.
	*/
	virtual void eventDraw(SDL_Surface* surface, const PG_Rect& rect);

	/**
	overridable eventhandler to blit the widget contents to the screen
	@param srf surface to be blitted
	@param src source rectangle (client coordinates)
	@param dst destination rectangle (screen coordinates)
	Override this eventhandler to perform custom blitting behaviour (without drawing onto the widget surface).
	*/
	virtual void eventBlit(SDL_Surface* srf, const PG_Rect& src, const PG_Rect& dst);

	/**
	overridable eventhandler called whenever the widget gets shown.
	*/
	virtual void eventShow();

	/**
	overridable eventhandler called whenever the widget gets hidden.
	*/
	virtual void eventHide();

	/**
	overridable eventhandler called when leaving a modal eventloop
	@param id	id of the widget that send the quit signal
	@param widget pointer to the widget
	@param data event specific data
	@return true if the message was processed
	*/
	virtual bool eventQuitModal(int id, PG_MessageObject* widget, unsigned long data);

	/**  */
	void FadeOut();

	/**  */
	void FadeIn();

	/**  */
	bool AcceptEvent(const SDL_Event* event);

	/**  */
	void RemoveFromWidgetList();

	/**  */
	void AddToWidgetList();

	/**
	pointer to the widgets drawing surface or NULL
	*/
	SDL_Surface* my_srfObject;

	/**
	pointer to the screen surface
	*/
	SDL_Surface* my_srfScreen;

	/**
	text attached to the widget
	*/
	string my_text;

	/**
	array of border colors
	*/
	PG_Color my_colorBorder[2][2];

private:

	void InitWidget(PG_Widget* parent, bool bObjectSurface);
	//void AddChildToCache(PG_Widget *child, const char *name);
	//void AddChildToCache(PG_Widget *child, int id);
    
	PG_Widget(const PG_Widget&);
	PG_Widget& operator=(const PG_Widget&);

	static bool bBulkUpdate;
	static int my_ObjectCounter;
	static PG_RectList widgetList;

	// this is a bit rude but neccessary for future binary compatibility
	// because adding non-static data members would break the ABI.
	// For this we put all private data into a dynamically created struct.
	PG_WidgetDataInternal* my_internaldata;
};

#endif // PG_WIDGET_H
