#include "paragui.h"
#include "pgapplication.h"
#include "pglistbox.h"
#include "pglistboxitem.h"

PARAGUI_CALLBACK(handleListBoxItem) {
	static int counter = 1;
	char text[20];
	
	PG_ListBoxItem* item = reinterpret_cast<PG_ListBoxItem*>(data);
	PG_ListBox* list = item->GetParent();
	
	list->DeleteAll();
	
	for(int i=0; i<10; i++) {
		sprintf(text,"NewItem %i", counter++);
		list->AddItem(new PG_ListBoxItem(25, text));
	}

	list->Update();	
	return true;
}

int main( int argc, char **argv )
{
	PG_Application app;
	
	app.LoadTheme( "default" );
	
	app.InitScreen( 640, 480, 0 );
	app.SetEmergencyQuit(true);
	
	PG_ListBox listbox(NULL, PG_Rect(10,10,300,100));
	listbox.SetEventCallback(MSG_SELECTITEM, handleListBoxItem);
	
	listbox.AddItem(new PG_ListBoxItem(25, "Item1"));
	listbox.AddItem(new PG_ListBoxItem(25, "Item2"));
	listbox.AddItem(new PG_ListBoxItem(25, "Item3"));
	listbox.AddItem(new PG_ListBoxItem(25, "Item4"));
	listbox.AddItem(new PG_ListBoxItem(25, "Item5"));
	listbox.AddItem(new PG_ListBoxItem(25, "Item6"));
	listbox.AddItem(new PG_ListBoxItem(25, "Item7"));
	listbox.AddItem(new PG_ListBoxItem(25, "Item8"));
	listbox.AddItem(new PG_ListBoxItem(25, "Item9"));
	listbox.AddItem(new PG_ListBoxItem(25, "Item10"));
	listbox.Show();
	

	app.Run();
	
	return 0;
}
