#include "paragui.h"
#include "pgapplication.h"

void main() {
    PG_Application app;
    app.LoadTheme("default");
    
    app.InitScreen(640, 480, 0);
    app.SetEmergencyQuit(true);
    
    app.Run();
}
