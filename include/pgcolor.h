//
// C++ Interface: pgcolor
//
// Description: 
//
//
// Author: Alexander Pipelka <pipelka@pipelka.net>, (C) 2003
//
// Copyright: See COPYING file that comes with this distribution
//
//

#ifndef PG_COLOR_H
#define PG_COLOR_H

#include "SDL.h"

class PG_Color : public SDL_Color {
public:
	PG_Color();
	PG_Color(const SDL_Color& c);
	PG_Color(Uint32 c);
	PG_Color(Uint8 r, Uint8 g, Uint8 b);

	PG_Color& operator=(const SDL_Color& c);

	PG_Color& operator=(Uint32 c);

	//operator SDL_Color();
	
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
typedef struct {
	PG_Color colors[4];	//!< array of gradient colors
} PG_Gradient;

#endif // PG_COLOR_H
