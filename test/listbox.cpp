#include "paragui.h"
#include "pgapplication.h"
#include "pglistbox.h"
#include "pglistboxitem.h"

bool handleListBoxItem(PG_ListBoxBaseItem* item) {
	static int counter = 1;
	char text[20];
	
	PG_ListBox* list = item->GetParent();
	
	list->DeleteAll();
	
	for(int i=0; i<10; i++) {
		sprintf(text,"NewItem %i", counter++);
		new PG_ListBoxItem(list, 25, text);
	}

	return true;
}

int main( int argc, char **argv )
{
	PG_Application app;
	
	app.LoadTheme( "default" );
	
	app.InitScreen( 640, 480, 0 );
	app.SetEmergencyQuit(true);
	
	PG_ListBox listbox(NULL, PG_Rect(10,10,300,100));
	listbox.sigSelectItem.connect(slot(handleListBoxItem));
	listbox.Show();

	PG_ListBoxItem* item;
	int i;
	
	for(i=0; i<10; i++) {
		item = new PG_ListBoxItem(&listbox, 25, "");
		item->SetTextFormat("Item %i", i+1);
	}

	app.Run();
	
	return 0;
}
