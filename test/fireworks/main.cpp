#include "paragui.h"
#include "pgapplication.h"
#include "blob.h"

#define RESX 800
#define RESY 600

int main(int argc, char* argv[]) {
	char theme[20];
	strcpy(theme, "simple");

  // initial flags for screensurface
	Uint32 flags = SDL_SWSURFACE|SDL_HWPALETTE;
	int bpp = 0;

	int resx = RESX, resy = RESY;
	
	// construct the application object
	PG_Application app;
	
	if(!app.LoadTheme(theme)) {
	    printf("Unable to load theme \"%s\"", theme);
	    return -1;
	}
	
	if(!app.InitScreen(resx, resy, bpp, flags)){
		printf("Resolution %dx%d not supported\n", resx, resy);
		exit(-1);
	}

    Blob fireworks(NULL, PG_Rect(100, 100, 600, 400));
    fireworks.AddTimer(60);
    fireworks.Show();
    
	app.SetEmergencyQuit(true);
    app.Run();

	return EXIT_SUCCESS;
}
