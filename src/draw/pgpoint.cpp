#include "pgpoint.h"

PG_Point PG_Point::null;

PG_Point::PG_Point() : x(0), y(0) {
}

PG_Point::PG_Point(Sint16 _x, Sint16 _y) : x(_x), y(_y) {
}
