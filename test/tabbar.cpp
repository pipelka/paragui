#include "paragui.h"
#include "pgapplication.h"
#include "pgtabbar.h"

int main( int argc, char **argv )
{
   PG_Application app;

   app.LoadTheme( "default" );

   app.InitScreen( 640, 480 );

   PG_TabBar bar( NULL, PG_Rect(10, 10, 300, 25) );

   bar.Show();

   bar.AddTab("Tab1");
   bar.AddTab("Tab2");
   bar.AddTab("Tab3");
   bar.AddTab("MoreTab1");
   bar.AddTab("MoreTab2");
   bar.AddTab("MoreTab3");
   bar.AddTab("EvelLongerTab1");
   bar.AddTab("Tab4");
      
   app.Run();

   return 0;
}
