#include "pgapplication.h"
#include "pgthemewidget.h"
#include "pgwindow.h"
#include "pgbutton.h"
#include "pgcheckbutton.h"

class MyWindow: public PG_Window {
	public:
		MyWindow( PG_Widget* parent, const PG_Rect& r = PG_Rect::null ) : PG_Window( parent, r ) 
		{};
		bool click( PG_RadioButton* a, bool b )
		{
			UpdateOverlappingSiblings( b, true );
			return true;
		};
};
	

int main(int argc,char *argv[])
{
	PG_Application app;
	app.SetEmergencyQuit(true);
	app.LoadTheme("simple");
	app.InitScreen(800,600,0,SDL_SWSURFACE);

	MyWindow* window = new MyWindow( NULL,PG_Rect(200,200,350,300));
	new PG_Label( window, PG_Rect(20, 30,300,30), "not overlapping the button" );
	new PG_Label( window, PG_Rect(20,100,300,30), "behind button" );
	PG_Button* button = new PG_Button( window, PG_Rect(60,70,250,100), "Button" );
	button->SetTransparency(40,40,40);
	new PG_Label( window, PG_Rect(20,130,300,30), "in front of button" );
	new PG_Label( window, PG_Rect(20,180,300,30), "not overlapping the button" );
	PG_CheckButton* c = new PG_CheckButton( window, PG_Rect( 20, 220, 300, 30 ), "UpdateOverlappingSiblings" );
	c->SetPressed();
	c->sigClick.connect( SigC::slot( *window, &MyWindow::click ));
	window->Show();
	
	app.Run();
}
