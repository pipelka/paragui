#include "paragui.h"
#include "pgapplication.h"
#include "pgwindow.h"

int main( int argc, char **argv )
{
   PG_Application app;

   app.LoadTheme( "default" );

   app.InitScreen( 640, 480 );

   PG_Window a( NULL, PG_Rect( 10, 10, 100, 100 ), "Window 98, the most reliable window yet.");
   PG_Window b( NULL, PG_Rect( 60, 110, 100, 100 ), "Window XP, .");

   a.SizeWidget( 400, 200 );
   b.SizeWidget( 400, 200 );

   a.Show();
   b.Show();

   app.Run();

   return 0;
}
