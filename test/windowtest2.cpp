#include "pgapplication.h"
#include "pgthemewidget.h"
#include "pgwindow.h"
#include "pgbutton.h"

int main(int argc,char *argv[])
{
	PG_Application app;
	app.SetEmergencyQuit(true);
	app.LoadTheme("simple");
	app.InitScreen(800,600,0,SDL_SWSURFACE);

	PG_Window* window = new PG_Window( NULL,PG_Rect(200,200,350,250));
	new PG_Label( window, PG_Rect(20,100,100,30), "Hello World" );
	PG_Button* button = new PG_Button( window, PG_Rect(10,50,300,100), "Button" );
	button->SetTransparency(100,100,100);
	window->Show();
	
	app.Run();
}
