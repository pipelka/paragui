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
	listbox.Show();

	PG_ListBoxItem* items[10];
	int i;
	
	for(i=0; i<10; i++) {
		items[i] = new PG_ListBoxItem(25, "");
		items[i]->SetTextFormat("Item %i", i+1);
		listbox.AddItem(items[i]);
	}
	
	listbox.RemoveAll();
	listbox.Update();
	
	for(i=0; i<10; i++) {
		listbox.AddItem(items[i]);
	}
	listbox.Update();

	app.Run();
	
	return 0;
}
