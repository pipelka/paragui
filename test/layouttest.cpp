#include "paragui.h"
#include "pgapplication.h"
#include "pgwindow.h"

int main( int argc, char **argv ) {

	// construct the application object
	PG_Application app;

	app.EnableBackground(true);
	app.LoadTheme("default");
	
	// init 1024x768
	if(!app.InitScreen(800,600, 0, SDL_SWSURFACE)){
		printf("Resolution not supported\n");
		exit(-1);
	}

	app.LoadLayout("pokus.xml");
	
	// Enter main loop 
	app.Run();

	return EXIT_SUCCESS;
}
