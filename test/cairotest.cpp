#include <cstdio>
#include "pgapplication.h"
#include "pgthemewidget.h"
#include "pgwindow.h"
#include "pgmessagebox.h"
#include "pgdropdown.h"

#include <cairo.h>

// currently global (nasty, i know), needs to be integrated into cairoified ParaGUI
cairo_t* cr;

class CMyWidget : public PG_ThemeWidget {
public:
	CMyWidget(PG_Widget *parent,PG_Rect rect);
	
protected:
	void eventBlit(SDL_Surface* srf, const PG_Rect& src, const PG_Rect& dst);
	
	double linewidth;
};

CMyWidget::CMyWidget(PG_Widget *parent,PG_Rect rect) : PG_ThemeWidget(parent,rect, true){
	linewidth = 10;
}

void CMyWidget::eventBlit(SDL_Surface* srf, const PG_Rect& src, const PG_Rect& dst) {
	//PG_ThemeWidget::eventBlit(srf, src, dst);
	PG_Rect* clip = GetClipRect();
		
	cairo_save(cr);

	// set clipping rectangle
	/*cairo_rectangle(cr, clip->x, clip->y, clip->w, clip->h);
	cairo_clip(cr);
	cairo_new_path(cr);*/

	/*cairo_pattern_t* pat = cairo_pattern_create_linear (x, y,  w, h);
	cairo_pattern_add_color_stop (pat, 0, 1, 1, 1, 0);
	cairo_pattern_add_color_stop (pat, h, .1, .1, .1, .9);*/

	cairo_rectangle (cr, x,y,w,h);
	//cairo_set_pattern (cr, pat);
	cairo_fill (cr);
	//cairo_pattern_destroy(pat);

	// set caps
	cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);
	cairo_set_line_join(cr, CAIRO_LINE_JOIN_ROUND);

	// create path
	cairo_set_alpha(cr, 1);
	cairo_move_to(cr, x+linewidth, y+linewidth);
	cairo_line_to(cr, x + w - linewidth, y+linewidth);
	cairo_curve_to(cr, x+w/2, y+h-linewidth, x+w/2, y+h-linewidth, x+linewidth, y+linewidth);
	cairo_close_path(cr);

	// stroke
	cairo_set_alpha(cr, 0.8);
	cairo_set_line_width(cr, linewidth*1.7);
	cairo_set_rgb_color(cr, 0, 0, 0);
	cairo_stroke(cr);
	
	cairo_restore(cr);
}


class CMyWindow : public PG_Window {
public:
	CMyWindow(PG_Widget *parent,const PG_Rect& r,char *text,WindowFlags flags,const char* style = "Window");

protected:
	CMyWidget* mywidget;
};

CMyWindow::CMyWindow(PG_Widget *parent,const PG_Rect& r,char *text, WindowFlags flags,const char* style) : PG_Window(parent,r,text,flags,style) {
	mywidget = new CMyWidget(this, PG_Rect(5, 30, r.w-10, r.h-35));
	SetDirtyUpdate(false);
	SetTransparency(255);
}



int main(int argc,char *argv[])

{
	// init application, pretty usual
	PG_Application app;
	app.SetEmergencyQuit(true);
	app.LoadTheme("default");
	app.InitScreen(800,600,32,SDL_SWSURFACE);

	// init cairo, more interesting
	cr = cairo_create();
	char* image = (char*)PG_Application::GetScreen()->pixels;
	int width = PG_Application::GetScreenWidth();
	int height = PG_Application::GetScreenHeight();
	int stride = PG_Application::GetScreen()->pitch;
	
	cairo_set_target_image(cr, image, CAIRO_FORMAT_ARGB32, width, height, stride);
	
	CMyWindow win1(NULL, PG_Rect(200,200,360,290), "CAIRO sample", PG_Window::DEFAULT);
	win1.Show();

	CMyWindow win2(NULL, PG_Rect(50,50,200,350), "CAIRO sample", PG_Window::DEFAULT);
	win2.Show();

	CMyWindow win3(NULL, PG_Rect(100,80,400,200), "CAIRO sample", PG_Window::DEFAULT);
	win3.Show();

	app.Run();
	
	return 0;
}
