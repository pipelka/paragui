#include "pgcolorselector.h"

PG_ColorSelector::PG_ColorSelector(PG_Widget* parent, const PG_Rect&r, const char* style) : PG_ThemeWidget(parent, r, style)  {
	my_colorbox = new PG_ThemeWidget(this, PG_Rect(5,5,r.h-10,r.h-10));
	
	PG_Gradient g;
	g.colors[0].r = 255;
	g.colors[0].g = 0;
	g.colors[0].b = 0;
	
	g.colors[1].r = 0;
	g.colors[1].g = 255;
	g.colors[1].b = 0;
	
	g.colors[2].r = 0;
	g.colors[2].g = 0;
	g.colors[2].b = 255;
	
	g.colors[3].r = 255;
	g.colors[3].g = 255;
	g.colors[3].b = 255;
	
	my_colorbox->SetGradient(g);
	my_colorbox->SetBackground((SDL_Surface*)NULL);
	my_colorbox->SetSimpleBackground(false);
}

PG_ColorSelector::~PG_ColorSelector() {
}
