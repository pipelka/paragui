#include "paragui.h"
#include "pgapplication.h"
#include "pgtabbar.h"

int main( int argc, char **argv )
{
   PG_Application app;

   app.LoadTheme( "default" );

   app.InitScreen( 640, 480 );

   PG_TabBar bar( NULL, PG_Rect(10, 10, 200, 25) );

   bar.Show();

   bar.AddTab("Tab1", 1);
   bar.AddTab("Tab2", 2);
   bar.AddTab("Tab3", 3);
   bar.AddTab("MoreTab1", 4);
   bar.AddTab("MoreTab2", 5);
   bar.AddTab("MoreTab3", 6);
   bar.AddTab("EvelLongerTab1", 7);
   bar.AddTab("Tab4", 8);
      
   app.Run();

   return 0;
}
