#include "pgcolorselector.h"

PG_ColorSelector::PG_ColorBox::PG_ColorBox(PG_ColorSelector* parent, const PG_Rect& r) : PG_ThemeWidget(parent, r) {
	my_btndown = false;

	p.x = r.w/2;
	p.y = r.h/2;
}
		
bool PG_ColorSelector::PG_ColorBox::eventMouseMotion(const SDL_MouseMotionEvent* motion) {
	if(!my_btndown) {
		return false;
	}
	
	p = ScreenToClient(motion->x, motion->y);
	Update();
	GetParent()->SetBaseColor(GetBaseColor());
	return true;
}

bool PG_ColorSelector::PG_ColorBox::eventMouseButtonDown(const SDL_MouseButtonEvent* button) {
	if(my_btndown) {
		return false;
	}
	
	my_btndown = true;
	p = ScreenToClient(button->x, button->y);
	Update();
	GetParent()->SetBaseColor(GetBaseColor());
	return true;
}

bool PG_ColorSelector::PG_ColorBox::eventMouseButtonUp(const SDL_MouseButtonEvent* button) {
	my_btndown = false;
	return true;
}

void PG_ColorSelector::PG_ColorBox::eventBlit(SDL_Surface* srf, const PG_Rect& src, const PG_Rect& dst) {
	PG_ThemeWidget::eventBlit(srf, src, dst);
	
	// draw crosshair
	DrawHLine(0, p.y, w, 255,255,255);
	DrawVLine(p.x, 0, h, 255,255,255);
}

SDL_Color PG_ColorSelector::PG_ColorBox::GetBaseColor() {
	SDL_Color result;
	
	SDL_Color cy1, cy2;
	SDL_Color r,g,b,w;
	PG_Gradient gr = GetGradient();
	
	r = gr.colors[0];
	g = gr.colors[1];
	b = gr.colors[2];
	w = gr.colors[3];
	
	// cy1 = ( (b - r) / h ) * y
	
	cy1.r = (Uint8)((float)r.r + (((float)b.r - (float)r.r) / (float)my_height) * (float)p.y);
	cy1.g = (Uint8)((float)r.g + (((float)b.g - (float)r.g) / (float)my_height) * (float)p.y);
	cy1.b = (Uint8)((float)r.b + (((float)b.b - (float)r.b) / (float)my_height) * (float)p.y);
	
	// cy2 = ( (w - g) / h ) * y
	
	cy2.r = (Uint8)((float)g.r + (((float)w.r - (float)g.r) / (float)my_height) * (float)p.y);
	cy2.g = (Uint8)((float)g.g + (((float)w.g - (float)g.g) / (float)my_height) * (float)p.y);
	cy2.b = (Uint8)((float)g.b + (((float)w.b - (float)g.b) / (float)my_height) * (float)p.y);
	
	// result = ( (cy2 - cy1) / w ) * x

	result.r = (Uint8)((float)cy1.r + (((float)cy2.r - (float)cy1.r) / (float)my_width) * (float)p.x);
	result.g = (Uint8)((float)cy1.g + (((float)cy2.g - (float)cy1.g) / (float)my_width) * (float)p.x);
	result.b = (Uint8)((float)cy1.b + (((float)cy2.b - (float)cy1.b) / (float)my_width) * (float)p.x);
	
	return result;
}

PG_ColorSelector::PG_ColorSelector(PG_Widget* parent, const PG_Rect&r, const char* style) : PG_ThemeWidget(parent, r, style)  {
	PG_Gradient g;

	my_color.r = 255;
	my_color.g = 255;
	my_color.b = 255;

	my_colorbox = new PG_ColorBox(this, PG_Rect(5,5,r.h-10,r.h-10));
	
	g.colors[0].r = 255;
	g.colors[0].g = 255;
	g.colors[0].b = 0;
	
	g.colors[1].r = 0;
	g.colors[1].g = 255;
	g.colors[1].b = 255;
	
	g.colors[2].r = 255;
	g.colors[2].g = 0;
	g.colors[2].b = 255;
	
	g.colors[3].r = 255;
	g.colors[3].g = 255;
	g.colors[3].b = 255;
	
	my_colorbox->SetGradient(g);
	my_colorbox->SetBackground((SDL_Surface*)NULL);
	my_colorbox->SetSimpleBackground(false);

	my_colorslider = new PG_Slider(this, -1, PG_Rect(r.h, 5, 20, r.h-10), PG_SB_VERTICAL);
	my_colorslider->SetRange(0, 255);

	my_colorslider->SetBackground((SDL_Surface*)NULL);
	my_colorslider->SetSimpleBackground(false);

	SetBaseColor(my_color);

}

PG_ColorSelector::~PG_ColorSelector() {
}

void PG_ColorSelector::SetColor(const SDL_Color& c) {
	my_color = c;
}

void PG_ColorSelector::SetBaseColor(const SDL_Color& c) {
	PG_Gradient g;
	my_basecolor = c;

	g.colors[0].r = my_basecolor.r;
	g.colors[0].g = my_basecolor.g;
	g.colors[0].b = my_basecolor.b;

	g.colors[1].r = my_basecolor.r;
	g.colors[1].g = my_basecolor.g;
	g.colors[1].b = my_basecolor.b;
	
	g.colors[2].r = 0;
	g.colors[2].g = 0;
	g.colors[2].b = 0;
	
	g.colors[3].r = 0;
	g.colors[3].g = 0;
	g.colors[3].b = 0;

	my_colorslider->SetGradient(g);
}
