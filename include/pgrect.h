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
    Source File:      $Source: /sources/paragui/paragui/include/pgrect.h,v $
    CVS/RCS Revision: $Revision: 1.3.6.1.2.2 $
    Status:           $State: Exp $
*/

#ifndef PG_RECT_H
#define PG_RECT_H

#include "SDL.h"
#include "pgpoint.h"

/**
	@author Alexander Pipelka
	@short Encapsulation of the SDL_Rect structure
*/

class DECLSPEC PG_Rect : public SDL_Rect {
public:

	/**
	Create a new PG_Rect object with give values
	@param	x	x-startposition
	@param	y	y-startposition
	@param	w	width
	@param	h	height

	Initializes the created PG_Rect object with x/y postions and width/height
	*/
	PG_Rect(Sint16 x, Sint16 y, Uint16 w, Uint16 h);

	/**
	Create an empty PG_Rect object
	Initializes the created PG_Rect object with x=y=w=h=0
	*/
	PG_Rect();

	/**
	Create a new PG_Rect from a reference
	@param	src	reference rectangle
	 
	Initializes the created PG_Rect object with the position of the reference rectangle
	*/
	PG_Rect(const PG_Rect& src);

	/**
	Create a new PG_Rect from a SDL_Rect structure
	@param	src	source SDL_Rect structure
	 
	Initializes the created PG_Rect object with the position of the SDL_Rect structure
	*/
	PG_Rect(const SDL_Rect& src);

	virtual ~PG_Rect();

	/**
	Set the position of the rectangle
	@param	nx	x-startposition
	@param	ny	y-startposition
	@param	nw	width
	@param	nh	height
	Moves the rectangle to the given values
	*/
	void SetRect(Sint16 nx, Sint16 ny, Uint16 nw, Uint16 nh);

	/**
	*/
	PG_Rect& operator =(const SDL_Rect& src);

	PG_Rect& operator =(const PG_Rect& src);
	
	/**
	*/
	PG_Rect operator / (PG_Rect& b);

	inline operator SDL_Rect() const {
		return *this;
	}

	/**
	Check if a given point is inside a rectangle (boxtest)
	 
	@param	p		the point to test
	@param	r		the rectangle the point should be inside
	@return			true if the point is inside the rectangle
	*/
	inline static bool IsInside(const PG_Point& p, PG_Rect& r) {
		return r.IsInside(p);
	}

	/**
	Check if a given point is inside a rectangle (boxtest)
	 
	@param	p		the point to test
	@return			true if the point is inside the rectangle
	*/
	inline bool IsInside(const PG_Point& p) {
		return ( (x <= p.x) && (p.x <= x + w) && (y <= p.y) && (p.y <= y + h) );
	}

	/**
	Intersect two rectangles
	@param	p					reference rectangle
	@param	c					rectangle to intersect with reference
	@return						resulting intersection rectangle
	*/
	static PG_Rect IntersectRect(const PG_Rect& p, const PG_Rect& c);

	/**
	Intersect two rectangles
	@param	p					rectangle to intersect with
	@return						resulting intersection rectangle
	*/
	PG_Rect IntersectRect(const PG_Rect& p) const;

	/**
	Return the width of the rectangle
	@return			width
	*/
	inline Uint16 Width() {
		return w;
	}

	inline Uint16 Width() const {
		return w;
	}

	/**
	Return the height of the rectangle
	@return			height
	*/
	inline Uint16 Height() {
		return h;
	}

	inline Uint16 Height() const {
		return h;
	}

	inline bool IsNull() {
		return (!Width() && !Height());
	}

	//! Check if two rectangles overlap
	/*!
	\param p, c rectangles to check for overlap
	\return true if the rectangles overlap, false otherwise
	*/
	inline bool OverlapRect(const PG_Rect& p, const PG_Rect& c) {
		return !( (p.x + p.w < c.x) || (p.x > c.x + c.w) || (p.y + p.h < c.y) || (p.y > c.y + c.h)  || (p.IntersectRect(c).IsNull()) );
	}

	//! Check if this rectangle overlap another one
	/*!
	\param p rectangle to check for overlap
	\return true if this rectangle an p overlap, false otherwise
	*/
	inline bool OverlapRect(const PG_Rect& p) {
		return OverlapRect(p, *this);
	}

	//! Check if this rectangle overlap another one
	/*!
	\param p pointer to rectangle to check for overlap
	\return true if this rectangle an p overlap, false otherwise
	*/
	inline bool OverlapRect(PG_Rect* p) {
		return OverlapRect(*p, *this);
	}
	
	Sint16& my_xpos;
	Sint16& my_ypos;
	Uint16& my_width;
	Uint16& my_height;
};

#endif	// PG_RECT_H
