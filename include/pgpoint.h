#ifndef PG_POINT_H
#define PG_POINT_H

#include "SDL.h"

class DECLSPEC PG_Point {
public:
	PG_Point();
	PG_Point(Sint16 _x, Sint16 _y);

	Sint16 x;
	Sint16 y;

	static PG_Point null;
};

#endif // PG_POINT_H
