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
    Update Date:      $Date: 2004/03/08 16:52:39 $
    Source File:      $Source: /sources/paragui/paragui/include/Attic/pgscrollwidget.h,v $
    CVS/RCS Revision: $Revision: 1.1.2.2 $
    Status:           $State: Exp $
*/

#ifndef PG_SCROLLWIDGET_H
#define PG_SCROLLWIDGET_H

#include "pgthemewidget.h"
#include "pgscrollbar.h"

class PG_ScrollArea;

/**
	@author Alexander Pipelka
 
	@short Encapsulation of the PG_ScrollArea widget providing scrollbars.
 
	Generally used to make a large 'pane' of widgets that can be scrolled
	through in a smaller 'portal' with scrollbars.
*/

class DECLSPEC PG_ScrollWidget : public PG_ThemeWidget  {
public:

	enum {
		IDWIDGETLIST_SCROLL = PG_WIDGETID_INTERNAL + 10
	};

	/**
	Constructor of the PG_Widget class
	*/
	PG_ScrollWidget(PG_Widget* parent, const PG_Rect& r = PG_Rect::null, const char* style="ScrollWidget");

	/**
	Destructor of the PG_Widget class
	*/
	~PG_ScrollWidget();

	/**  */
	void LoadThemeStyle(const char* widgettype);

	/**
	Enable / disable the Scrollbar (override automatic display)
	@param enable true - enable scrollbar / false - disable scrollbar
	@param direction modified scrollbar (PG_ScrollBar::VERTICAL | PG_ScrollBar::HORIZONTAL)
	*/
	void EnableScrollBar(bool enable, PG_ScrollBar::ScrollDirection direction = PG_ScrollBar::VERTICAL);

	/**
	scroll to a give X/Y-Coordinate within the client area.
	@param x X-Position
	@param y Y-Position
	*/
	void ScrollTo(Uint16 x, Uint16 y);

	/**
	Scroll to a widget
	@param widget the target widget
	@param bVertical scroll direction
	*/
	void ScrollToWidget(PG_Widget* widget, bool bVertical = true);

	Uint16 GetListHeight();

	Uint16 GetListWidth();

	Uint16 GetWidgetCount();

	PG_Widget* GetFirstInList();

	void AddChild(PG_Widget* child);

protected:

	/**  */
	void eventSizeWidget(Uint16 w, Uint16 h);

	/**  */
	bool handleScrollPos(PG_ScrollBar* widget, long data);

	/**  */
	bool handleScrollTrack(PG_ScrollBar* widget, long data);

	bool handleAreaChangedHeight(PG_ScrollArea* area, Uint16 h);

	bool handleAreaChangedWidth(PG_ScrollArea* area, Uint16 w);

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

	void CheckScrollBars();

private:

	PG_ScrollWidget(const PG_ScrollWidget&);
	PG_ScrollWidget& operator=(const PG_ScrollWidget&);

	void RecalcPositions(bool bV, bool bH);
};

#endif // PG_SCROLLWIDGET_H
