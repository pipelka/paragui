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
    Source File:      $Source: /sources/paragui/paragui/include/pgscrollbar.h,v $
    CVS/RCS Revision: $Revision: 1.3.2.2 $
    Status:           $State: Exp $
*/

#ifndef PG_SCROLLBAR_H
#define PG_SCROLLBAR_H

#include "pgthemewidget.h"
#include "pgbutton.h"

/**
	@author Alexander Pipelka
 
	@short A vertical or horizontal scrollbar
 
	Doesn't actually tie itself to any object to be scrolled, just get's told
	it's current state through function calls.
*/

class DECLSPEC PG_ScrollBar : public PG_ThemeWidget {

protected:

#ifndef DOXYGEN_SKIP
class ScrollButton : public PG_Button {
	public:

		ScrollButton(PG_ScrollBar* parent, int id, const PG_Rect& r);
		virtual ~ScrollButton();

		void SetTickMode(bool on);

	protected:

		/**  */
		bool eventMouseButtonDown(const SDL_MouseButtonEvent* button);
		/**  */
		bool eventMouseMotion(const SDL_MouseMotionEvent* motion);
		/**  */
		PG_ScrollBar* GetParent();
		/**  */
		bool eventMouseButtonUp(const SDL_MouseButtonEvent* button);
		/**  */
		int GetPosFromPoint(PG_Point p);

	private:

		/**  */
		PG_Point offset;

		/** */
		bool my_tickMode;

		int my_tempPos;
	};
#endif		// DOXYGEN_SKIP


public:

	// ScrollbarType
	typedef enum {
		VERTICAL,
		HORIZONTAL
	} ScrollDirection;

	/**
	Signal type declaration
	**/
	template<class datatype> class SignalScrollPos : public PG_Signal2<PG_ScrollBar*, datatype> {};
	template<class datatype> class SignalScrollTrack : public PG_Signal2<PG_ScrollBar*, datatype> {};

	/**  */
	PG_ScrollBar(PG_Widget* parent, int id, const PG_Rect& r, ScrollDirection direction = VERTICAL, const char* style="Scrollbar");

	/**  */
	virtual ~PG_ScrollBar();

	void LoadThemeStyle(const char* widgettype);

	/**  */
	void SetPosition(int pos);

	/**  */
	int GetPosition();

	/**  */
	void SetWindowSize(Uint32 wsize);

	/**  */
	void SetRange(Uint32 min, Uint32 max);

	/**  */
	int GetMinRange();

	/**  */
	int GetMaxRange();

	/**  */
	void SetLineSize(int ls);

	/**  */
	void SetPageSize(int ps);

	SignalScrollPos<long> sigScrollPos;
	SignalScrollTrack<long> sigScrollTrack;
	
protected:

	/**  */
	void eventSizeWidget(Uint16 w, Uint16 h);

	/**  */
	bool eventMouseMotion(const SDL_MouseMotionEvent* motion);

	/**  */
	bool eventMouseButtonDown(const SDL_MouseButtonEvent* button);

	/**  */
	bool handleButtonClick(PG_Button* button);

	/**  */
	bool eventMouseButtonUp(const SDL_MouseButtonEvent* button);

	int scroll_min;
	int scroll_max;
	int scroll_current;
	int my_linesize;
	int my_pagesize;

	//int scroll_windowsize;

	PG_Button* scrollbutton[2];
	ScrollButton* dragbutton;
	PG_Rect position[4];

	ScrollDirection sb_direction;
	int id;

	friend class ScrollButton;

private:

	PG_ScrollBar(const PG_ScrollBar&);
	PG_ScrollBar& operator=(PG_ScrollBar&);

};

#endif // PG_SCROLLBAR_H
