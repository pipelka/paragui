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
    Update Date:      $Date: 2003/06/29 17:09:49 $
    Source File:      $Source: /sources/paragui/paragui/include/pgrectlist.h,v $
    CVS/RCS Revision: $Revision: 1.3.6.3 $
    Status:           $State: Exp $
*/

#ifndef PG_RECTLIST_H
#define PG_RECTLIST_H

#include "paragui.h"
#include "pgrect.h"
#include <vector>

#ifdef HASH_MAP_INC
#include HASH_MAP_INC
#else
#include <map>
#endif

using namespace std;

/**
	@author Alexander Pipelka
	@short A list derived from vector to handle overlapping and child-widgets
*/

class DECLSPEC PG_RectList : public vector<PG_Widget*> {

public:

	/**
		constructor of the list
	*/
	PG_RectList();

	/**
		destructor
	*/
	virtual ~PG_RectList();

	/**
		add a widget to the list
		@param	rect	pointer to the widget (rect)
	 
		This functions adds the widget to the back of the list.
	*/
	void Add(PG_Widget* rect);

	/**
		remove a widget from the list
		@param	rect pointer to the widget (rect)
		@return	true - if the widget was remove successfully
	 
		This functions removes the given widget from the list
	*/
	bool Remove(PG_Rect* rect);

	/**
		intersect a rectange with all rectangles in the list
		@param	rect	pointer to the rectangle to be tested
		@param	first	index of the first widget to test (default 0)
		@param last	index of the last widget to test (default -1 - end of the list)
		@return	returns a new PG_RectList object
	 
		Performs an intersection with all rectangles in the list from "first" to last and returns a
		PG_RectList object which contains all rectangles that have been successfully
		intersected with the test rectangle. Invisible widgets will be discarded.
	*/
	PG_RectList Intersect(PG_Rect* rect, int first=0, int last=-1);

	/**
		check if a given point is inside any rectangle in the list
		@param p	point to check
		@return		pointer to the first widget that contains the point / NULL if there is no match
	 
		Returns the first visible widget which contains the given point.
	*/
	PG_Widget* IsInside(const PG_Point& p);

	/**
		get the index of a rectangle
		@param	rect	rectangle to look up
		@return index of the rectangle / -1 if the rectangle wasn't found
	*/
	int FindIndexOf(PG_Rect* rect);

	/**
		blit all rectangles in the list to the screen
	 
		This function blits all visible rectangles from the first to the last position to the screen.
	*/
	void Blit();

	/**
		blit all rectangles from the list intersecting a reference rectangle to the screen
		@param	rect	reference rectangle
	 
		Performs an intersection of all visible rectangles in the list with the reference rectangle.
		The resulting list is clipped to the reference and blitted to the screen.
	*/
	void Blit(const PG_Rect& rect);

	/**
		reorder a widget (rectangle) - front
		@param rect	widget to reorder
		@return	true - the rectangle was found and reordered / false - the rectangle isn't in the list.
	 
		Bring the given widget (rectangle) to the front (will overlap all other widgets in the list).
	*/
	bool BringToFront(PG_Widget* rect);

	/**
		reorder a widget (rectangle) - back
		@param rect	widget to reorder
		@return	true - the rectangle was found and reordered / false - the rectangle isn't in the list.
	 
		Send the given widget (rectangle) to the back (will be overlapped by all other widgets in the list).
	*/
	bool SendToBack(PG_Widget* rect);

private:

#ifdef HASH_MAP_INC
	struct rectlist_cmp {
		size_t operator()(const PG_Rect* r) const {
			return reinterpret_cast<unsigned long>(r);
		}
	};

	typedef STL_MAP<PG_Rect*, int, rectlist_cmp> PG_RectListMap;
#else
	struct rectlist_cmp {
		bool operator()(PG_Rect* o1, PG_Rect* o2) const {
			return o1 < o2;
		}
	};

	typedef map<PG_Rect*, int, rectlist_cmp> PG_RectListMap;
#endif

	void UpdateIndexMap();

	PG_RectListMap indexmap;
};

#endif	// PG_RECTLIST_H
