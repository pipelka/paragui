#include "paragui.h"
#include "pgapplication.h"

void main() {
    PG_Application app;
    
    app.InitScreen(640, 480, 0);
    app.LoadTheme("default");
    app.SetEmergencyQuit(true);
    
    app.Run();
}
