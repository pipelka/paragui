#ifndef PG_COLORSELECTOR_H
#define PG_COLORSELECTOR_H

#include "pgthemewidget.h"

class DECLSPEC PG_ColorSelector : public PG_ThemeWidget {
public:
	
	PG_ColorSelector(PG_Widget* parent, const PG_Rect&r, const char* style="colorselector");
	~PG_ColorSelector();

protected:
	PG_ThemeWidget* my_colorbox;
	
};

#endif // PG_COLORSELECTOR_H
