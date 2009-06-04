/*
    ParaGUI - crossplatform widgetset
    Copyright (C) 2000 - 2009 Alexander Pipelka

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
    Update Date:      $Date: 2009/06/04 10:25:02 $
    Source File:      $Source: /sources/paragui/paragui/include/Attic/pgcolor.h,v $
    CVS/RCS Revision: $Revision: 1.1.2.11 $
    Status:           $State: Exp $
*/

#ifndef PG_COLOR_H
#define PG_COLOR_H

#include "SDL.h"

/** \file pgcolor.h
	Header file for the PG_Color class.
*/

/** @class PG_Color

	@short Allows for an abstraction of a particular color.

	The purpose of this is to allow one to create new colors. If one is interested
	in using predefined color constants, see pgcolors.h (note the letter "s" at the end.)
	A PG_Color can be created from an SDL_Color, a Uint32, or RGB based system.

	@author Alexander Pipelka
*/

class DECLSPEC PG_Color : public SDL_Color {
public:
	PG_Color();
	PG_Color(const SDL_Color& c);
	PG_Color(Uint32 c);
	PG_Color(Uint8 r, Uint8 g, Uint8 b);

	PG_Color& operator=(const SDL_Color& c);

	PG_Color& operator=(Uint32 c);

	operator Uint32() const;

	inline Uint32 MapRGB(SDL_PixelFormat* format) const {
		return SDL_MapRGB(format, r, g, b);
	}

	inline Uint32 MapRGBA(SDL_PixelFormat* format, Uint8 a) const {
		return SDL_MapRGBA(format, r, g, b, a);
	}

	inline bool operator!=(const PG_Color& c) const {
		return ((r != c.r) || (g != c.g) || (b != c.b));
	}
};

//! Structure for widget gradients
struct PG_Gradient {
	PG_Color colors[4];	//!< array of gradient colors
	PG_Gradient() {}
	;
	PG_Gradient( PG_Color ul, PG_Color ur, PG_Color ll, PG_Color lr ) {
		colors[0] = ul;
		colors[1] = ur;
		colors[2] = ll;
		colors[3] = lr;
	};
};

#endif // PG_COLOR_H
