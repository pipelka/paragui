#include "paragui.h"

#include "pgapplication.h"
#include "pgbutton.h"
#include "pgwidgetlist.h"
#include "pglabel.h"
#include "pgwindow.h"
#include "pgmaskedit.h"
#include "pgscrollbar.h"
#include "pgprogressbar.h"
#include "pgradiobutton.h"
#include "pgthemewidget.h"
#include "pgcheckbutton.h"
#include "pgslider.h"
#include "pglistbox.h"
#include "pgcolumnitem.h"
#include "pgdropdown.h"
#include "pgpopupmenu.h"
#include "pgspinnerbox.h"
#include "pglog.h"
#include "pgmenubar.h"
#include "pgtheme.h"

#define RESX 800
#define RESY 600

bool handle_exit(PG_Pointer clientdata) {
	PG_Application* app = (PG_Application*)clientdata;
	app->Quit();
	return true;
}

int main(int argc, char* argv[]) {
	char theme[20];

	strcpy(theme, "default");
	
	// initial flags for screensurface
	Uint32 flags = SDL_SWSURFACE;
	int bpp = 0;

	int resx = RESX, resy = RESY;
	
	// construct the application object
	PG_Application app;
	app.SetEmergencyQuit(true);
		
	for(int c=1; c<argc; c++) {

		if(argv[c][0] != '-') {
			strcpy(theme, argv[c]);
		}

		if(strcmp(argv[c], "-f") == 0) {
			flags |= SDL_FULLSCREEN;
		}

		if(strcmp(argv[c], "-bpp") == 0) {
			bpp = atoi(argv[++c]);
		}
		
		if(strcmp(argv[c], "-x") == 0) {
		        resx = atoi(argv[++c]);
		}
		
		if(strcmp(argv[c], "-y") == 0) {
		        resy = atoi(argv[++c]);
		}
	}

	Uint32 start_ticks = SDL_GetTicks();
	
	if(!app.LoadTheme(theme)) {
	    PG_LogERR("Unable to load theme \"%s\"", theme);
	    return -1;
	}

	PG_LogMSG("Loaded theme in %i ms", SDL_GetTicks() - start_ticks);

	if(!app.InitScreen(resx, resy, bpp, flags)){
		printf("Resolution %dx%d not supported\n", resx, resy);
		exit(-1);
	}

	PG_LogMSG("screen initialized after %i ms", SDL_GetTicks() - start_ticks);

	app.SetCursor(app.GetTheme()->FindSurface("Pointer", "Pointer", "normal"));

	int xw = resx/32;
	int yw = resy/32;

	PG_Widget container(NULL, PG_Rect(0,0,resx,resy));	
	PG_ThemeWidget* b = NULL;
	
	for(int x=0; x<33; x++) {
		for(int y=0; y<33; y++) {
			b = new PG_ThemeWidget(&container, PG_Rect(x*xw, y*yw, xw, yw));
		}
	}

	container.Show();
		
	PG_LogMSG("app ready after %i ms", SDL_GetTicks() - start_ticks);
	app.ShowCursor(PG_Application::SOFTWARE);

	// Enter main loop 
	app.Run();

	return EXIT_SUCCESS;
}
