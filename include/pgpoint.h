#ifndef PG_POINT_H
#define PG_POINT_H

#include "SDL.h"

class PG_Point {
public:
	
	PG_Point();
	PG_Point(Sint16 _x, Sint16 _y);
	
	Sint16 x;	//!< screen X-Coordinate
	Sint16 y;	//!< screen Y-Coordinate
};

#endif // PG_POINT_H
