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
	PG_Application app(argv[0]);
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

	if(!app.LoadTheme(theme)) {
	    PG_LogERR("Unable to load theme \"%s\"", theme);
	    return -1;
	}

	if(!app.InitScreen(resx, resy, 16, flags)){
		printf("Resolution %dx%d not supported\n", resx, resy);
		exit(-1);
	}

	
	SDL_Surface* src = PG_Application::LoadSurface("rgb.png");

	SDL_Surface* surf = SDL_CreateRGBSurface(SDL_SWSURFACE, src->w, src->h, 24, 0,0,0,0);
	SDL_BlitSurface(src, NULL, surf, NULL);

	SDL_Surface* screen = PG_Application::GetScreen();

	PG_Draw::RectStretch(
		    surf,
		    0,0,
		    surf->w-1,surf->h-1,
		    screen,
		    0,0,screen->w-1, screen->h-1,
		    NULL);

	SDL_UpdateRect(screen, 0, 0, screen->w, screen->h);

	// Enter main loop 
	app.Run();

	return EXIT_SUCCESS;
}
