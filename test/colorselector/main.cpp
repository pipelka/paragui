#include "pgcolorselector.h"
#include "pgapplication.h"

int main(int argc, char* argv[]) {
	char theme[20];
	strcpy(theme, "simple");

	// initial flags for screensurface
	Uint32 flags = SDL_SWSURFACE|SDL_HWPALETTE;
	int bpp = 0;

	// construct the application object
	PG_Application app;
	
	if(!app.LoadTheme(theme)) {
	    printf("Unable to load theme \"%s\"", theme);
	    return -1;
	}
	
	if(!app.InitScreen(640, 480, bpp, flags)){
		printf("Resolution not supported\n");
		exit(-1);
	}

	PG_ColorSelector colorsel(NULL, PG_Rect(10,10,300,150));
	colorsel.Show();
	
	app.SetEmergencyQuit(true);
    app.Run();

	return EXIT_SUCCESS;
}
