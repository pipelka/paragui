#include "paragui.h"
#include "pgapplication.h"
#include "pgthemewidget.h"
#include "pglabel.h"

class PG_ArrayWidget : public PG_ThemeWidget {
public:

	PG_ArrayWidget(PG_Widget* parent, const PG_Rect& r) : PG_ThemeWidget(parent, r) {
		for(int i=0; i<50; i++) {
			lines[i] = new PG_Label(this, PG_Rect(0,i*25,150,25), "line");
		}
	}
	
protected:
	PG_Label* lines[50];
};

int main( int argc, char **argv )
{
	PG_Application app;
	
	app.LoadTheme( "default" );
	
	app.InitScreen( 640, 480, 0 );
	app.SetEmergencyQuit(true);
	
	PG_ArrayWidget* a = new PG_ArrayWidget(NULL, PG_Rect(50,50,150,250));	
	a->Show();
	app.Run();
	delete a;
	
	return 0;
}
