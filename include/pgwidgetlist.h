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
    Update Date:      $Date: 2004/02/28 18:49:06 $
    Source File:      $Source: /sources/paragui/paragui/include/pgwidgetlist.h,v $
    CVS/RCS Revision: $Revision: 1.3.6.3.2.6 $
    Status:           $State: Exp $
*/

#ifndef PG_WIDGETLIST_H
#define PG_WIDGETLIST_H

#include "pgthemewidget.h"
#include "pgscrollbar.h"
#include "pgscrollarea.h"

#include <vector>

/**
	@author Alexander Pipelka
 
	@short A group of widgets arranged in a specific way graphically
 
	Generally used to make a large 'pane' of widgets that can be scrolled
	through in a smaller 'portal' with scrollbars.
*/

struct PG_WidgetListDataInternal;
	
class DECLSPEC PG_WidgetList : public PG_ThemeWidget  {
public:

	enum {
		IDWIDGETLIST_SCROLL = PG_WIDGETID_INTERNAL + 10
	};

	/**
	Constructor of the PG_Widget class
	*/
	PG_WidgetList(PG_Widget* parent, const PG_Rect& r = PG_Rect::null, const char* style="WidgetList");

	/**
	Destructor of the PG_Widget class
	*/
	~PG_WidgetList();

	/**  */
	void LoadThemeStyle(const char* widgettype);

	/**
	Add a widget to the list

	@param	w			pointer to a widget
	*/
	virtual void AddWidget(PG_Widget* w);

	/**
	Remove a widget from the list

	@param	w			pointer to a widget
	@param shiftx	reposition all widgets to the right of the removed widget
	@param shifty	reposition all widgets below
	*/
	//virtual bool RemoveWidget(PG_Widget* w, bool shiftx = false, bool shifty = false);

	/**
	Remove a widget from the list

	@param index	index of the widget
	@param shiftx	reposition all widgets to the right of the removed widget
	@param shifty	reposition all widgets below
	*/
	bool RemoveWidgetAt(int index);

	/**
	Remove and delete a widget from the list

	@param w pointer to a widget
	@param shiftx	reposition all widgets to the right of the removed widget
	@param shifty	reposition all widgets below
	*/
	//bool DeleteWidget(PG_Widget* w, bool shiftx = false, bool shifty = false);

	/**
	Remove and delete a widget from the list

	@param	index		index of the widget
	*/
	bool DeleteWidgetAt(int index);

	/**
	Find a widget by a given index

	@param	index		index of the widget to find
	@return					pointer to the widget
	*/
	PG_Widget* FindWidget(int index);

	/**
	Find the index of a given widget

	@param	widget		pointer to the widget
	@return				index of the widget
	*/
	int FindIndex(PG_Widget* widget);

	/**
	Enable / disable the Scrollbar (override automatic display)
	@param enable true - enable scrollbar / false - disable scrollbar
	@param direction modified scrollbar (PG_ScrollBar::VERTICAL | PG_ScrollBar::HORIZONTAL)
	*/
	void EnableScrollBar(bool enable, PG_ScrollBar::ScrollDirection direction = PG_ScrollBar::VERTICAL);

	/**
	Scroll the list to a widget
	@param	widget
	@param direction scroll direction (PG_ScrollBar::VERTICAL | PG_ScrollBar::HORIZONTAL)
	*/
	void ScrollTo(PG_Widget* widget, PG_ScrollBar::ScrollDirection direction = PG_ScrollBar::VERTICAL);

	/**
	Scroll the list to a given index
	@param index index of the widget to scroll to
	@param direction scroll direction (PG_ScrollBar::VERTICAL | PG_ScrollBar::HORIZONTAL)
	*/
	void ScrollTo(int index, PG_ScrollBar::ScrollDirection direction = PG_ScrollBar::VERTICAL);

	/**
	Scroll one page up
	*/
	void PageUp();
	
	/**
	Scroll one page down
	*/
	void PageDown();

	Uint16 GetListHeight();

	Uint16 GetListWidth();

	Uint16 GetWidgetCount();

protected:

	/**  */
	void eventSizeWidget(Uint16 w, Uint16 h);

	/**  */
	bool handleScrollPos(PG_ScrollBar* widget, long data);

	/**  */
	bool handleScrollTrack(PG_ScrollBar* widget, long data);

	bool handleAreaChangedHeight(PG_ScrollArea* area, Uint16 h);

	bool handleAreaChangedWidth(PG_ScrollArea* area, Uint16 w);

	void AddChild(PG_Widget* child);

	/**
	Search for a widget at a given y-position

	@param	y			the position
	@return				pointer to the widget or NULL
	*/
	PG_Widget* GetWidgetFromPos(Sint32 y);

	PG_ScrollBar* my_objVerticalScrollbar;
	PG_ScrollBar* my_objHorizontalScrollbar;
	PG_ScrollArea* my_scrollarea;

	PG_Rect my_rectVerticalScrollbar;
	PG_Rect my_rectHorizontalScrollbar;
	PG_Rect my_rectList;

	int my_widthScrollbar;
	int my_heightHorizontalScrollbar;

	bool my_enableVerticalScrollbar;
	bool my_enableHorizontalScrollbar;

	//virtual void UpdateScrollBarsPos();
	void CheckScrollBars();

private:

	PG_WidgetList(const PG_WidgetList&);
	PG_WidgetList& operator=(const PG_WidgetList&);

	void RecalcPositions(bool bV, bool bH);

	PG_WidgetListDataInternal* my_internaldata;
};

#endif // PG_WIDGETLIST_H
