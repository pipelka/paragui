#include "keyboard.h"
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

	TKeyAlpha_LineEdit edit(NULL, PG_Rect(200,300,300,25));
	edit.Init();
	edit.Show();
		
	app.SetEmergencyQuit(true);
	app.Run();

	return EXIT_SUCCESS;
}
