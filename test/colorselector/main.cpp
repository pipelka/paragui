#include "pgcolorselector.h"
#include "pgapplication.h"

int main(int argc, char* argv[]) {
	char theme[20];
	strcpy(theme, "simple");

	// initial flags for screensurface
	Uint32 flags = SDL_SWSURFACE|SDL_HWPALETTE;
	int bpp = 16;

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

	PG_ColorSelector colorsel1(NULL, PG_Rect(10,10,300,150));
	colorsel1.Show();

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
	
	PG_ColorSelector colorsel2(NULL, PG_Rect(10,170,300,150));
	colorsel2.SetColorGradient(g);
	colorsel2.Show();
	
	app.SetEmergencyQuit(true);
    app.Run();

	return EXIT_SUCCESS;
}
