#include "paragui.h"
#include "pgapplication.h"
#include "pgwindow.h"

int main() {

	// construct the application object
	PG_Application app;

	app.EnableBackground(true);
	app.LoadTheme("default");
	
	// init 1024x768
	if(!app.InitScreen(800,600, 0, SDL_SWSURFACE)){
		printf("Resolution not supported\n");
		exit(-1);
	}

	PG_Window wnd(NULL, PG_Rect(0,0,400,300), "Test");
	wnd.LoadLayout("pokus.xml");

	SDL_Delay(2000);
	wnd.Show();
	
	// Enter main loop 
	app.Run();

	return EXIT_SUCCESS;
}
