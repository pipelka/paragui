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
    Update Date:      $Date: 2003/11/24 09:17:22 $
    Source File:      $Source: /sources/paragui/paragui/src/draw/pgrect.cpp,v $
    CVS/RCS Revision: $Revision: 1.3.8.1 $
    Status:           $State: Exp $
*/

#include "pgrect.h"

PG_Rect::PG_Rect(Sint16 xv, Sint16 yv, Uint16 wv, Uint16 hv) : 
my_xpos(x), 
my_ypos(y), 
my_width(w), 
my_height(h) {
	SetRect(xv, yv, wv, hv);
}

PG_Rect::PG_Rect() :
my_xpos(x),
my_ypos(y),
my_width(w),
my_height(h) {
	SetRect(0, 0, 0, 0);
}

PG_Rect::PG_Rect(const PG_Rect& src) :
my_xpos(x),
my_ypos(y),
my_width(w),
my_height(h) {
	*this = src;
}

PG_Rect::PG_Rect(const SDL_Rect& src) :
my_xpos(x),
my_ypos(y),
my_width(w),
my_height(h) {
	*this = src;
}

PG_Rect::~PG_Rect() {}

PG_Rect PG_Rect::IntersectRect(const PG_Rect& p, const PG_Rect& c) {
	static int px0,py0,px1,py1;
	static int cx0,cy0,cx1,cy1;
	static int rx0,ry0,rx1,ry1;

	// fill in default (NULL) result rectangle
	PG_Rect result;

	// get coordinates of the rectangles
	px0 = p.my_xpos;
	py0 = p.my_ypos;
	px1 = p.my_xpos + p.my_width - 1;
	py1 = p.my_ypos + p.my_height - 1;

	cx0 = c.my_xpos;
	cy0 = c.my_ypos;
	cx1 = c.my_xpos + c.my_width - 1;
	cy1 = c.my_ypos + c.my_height - 1;

	// check if the rectangles intersect
	if(/*(cx0 < px0) && */(cx1 < px0))
		return result;

	if((cx0 > px1) /*&& (cx1 > px1)*/)
		return result;

	if(/*(cy0 < py0) && */(cy1 < py0))
		return result;

	if((cy0 > py1) /*&& (cy1 > py1)*/)
		return result;

	// intersect x
	if(cx0 <= px0)
		rx0 = px0;
	else
		rx0 = cx0;

	if(cx1 >= px1)
		rx1 = px1;
	else
		rx1 = cx1;

	// intersect y
	if(cy0 <= py0)
		ry0 = py0;
	else
		ry0 = cy0;

	if(cy1 >= py1)
		ry1 = py1;
	else
		ry1 = cy1;

	// fill in result rect
	result.SetRect(
	    rx0,
	    ry0,
	    (rx1-rx0)+1,
	    (ry1-ry0)+1);

	return result;
}

PG_Rect PG_Rect::IntersectRect(const PG_Rect& p) const {
	return IntersectRect(p, *this);
}

PG_Rect& PG_Rect::operator =(const PG_Rect& src) {
	SetRect(src.x, src.y, src.w, src.h);
	return *this;
}

PG_Rect PG_Rect::operator / (PG_Rect& b) {
	return IntersectRect(b);
}

/*SDL_Rect* PG_Rect::SDLRect() {
	return (SDL_Rect*)this;
}*/

void PG_Rect::SetRect(Sint16 nx, Sint16 ny, Uint16 nw, Uint16 nh) {
	x = nx;
	y = ny;
	w = nw;
	h = nh;
}

PG_Rect& PG_Rect::operator =(const SDL_Rect& src) {
	x = src.x;
	y = src.y;
	w = src.w;
	h = src.h;
	return *this;
}
