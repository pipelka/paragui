/*
This sample app demonstrates a really ugly bug
Submitted by: Andrew Ford <andrewhford@yahoo.com>
*/

#include "paragui.h"
#include "pgdropdown.h"
#include "pgapplication.h"

int main( int argc, char **argv )
{
   PG_Application app;
   app.LoadTheme( "default" );
   app.InitScreen( 640, 480 );

   PG_DropDown *dd1, *dd2;

   dd1 = new PG_DropDown(NULL, PG_Rect( 10, 10, 100, 20 ));
   dd2 = new PG_DropDown(NULL, PG_Rect( 120, 10,100, 20 ));

   for( int i = 0; i < 10; i++ )
   {
      dd1->AddItem( "poop" );
      dd2->AddItem( "yeah" );
   }
    
   dd1->Show();
   dd2->Show();

   app.Run();

   return 0;
}
