#include "paragui.h"
#include "pgapplication.h"
#include "pgthemewidget.h"
#include "pgbutton.h"
#include "pgwindow.h"
#include "pglabel.h"
#include "pgfactory.h"

int main( int argc, char **argv ) {

    // create custom factory. key is "unsigned long"
    typedef PG_FactoryHolder<unsigned long> MyFactory;

    PG_Application app;

    app.LoadTheme( "default" );
    app.InitScreen( 640, 480, 0 );
    app.SetEmergencyQuit(true);

    // register classes (default factory, key "std::string")
    PG_Factory::RegisterClass<PG_ThemeWidget>("themewidget");
    PG_Factory::RegisterClass<PG_Button>("button");
    PG_Factory::RegisterClass<PG_Window>("window");
    PG_Factory::RegisterClass<PG_Label>("label");

    // register classes (custom factory)
    MyFactory::RegisterClass<PG_Label>(1);
    
    // create PG_ThemeWidget object
    PG_Widget* w = PG_Factory::CreateObject("themewidget");
    w->MoveWidget(PG_Rect(10,10,300,200));
    w->Show();

    // create PG_Button object
    PG_Widget* b = PG_Factory::CreateObject("button", w);
    b->MoveWidget(PG_Rect(100,100,150,30));
    b->SetText("Factory");
    b->Show();

    // create PG_Window object
    PG_Widget* wnd = PG_Factory::CreateObject("window");
    wnd->MoveWidget(PG_Rect(100,100,200,300));
    wnd->SetText("Window");

    // create PG_Label object (custom factory)
    PG_Widget* l = MyFactory::CreateObject(1, wnd);
    l->MoveWidget(PG_Rect(50,50,100,20));
    l->SetText("Label");
	
    wnd->Show();
	
    app.Run();

    return 0;
}
