#include "paragui.h"
#include "pgapplication.h"
#include "pgtabbar.h"
#include "pglabel.h"
#include "pgnotebook.h"
#include "pglistbox.h"
#include "pglistboxitem.h"
#include "pglog.h"

bool handleTab(PG_TabBar* bar, PG_Button* button, PG_Pointer* data) {
	PG_Label* l = static_cast<PG_Label*>(data);
	l->SetTextFormat("Tab '%s' selected", button->GetText());
	return true;
}

bool handlePageSelect(PG_NoteBook* notebook, PG_Widget* page) {
	PG_LogMSG("Page with ID '%i' selected.", page->GetID());
}

bool handlePageButton(PG_Widget* page) {
	PG_LogMSG("handlePageButton()");
}

bool handlePageCustom(PG_Widget* page) {
	PG_LogMSG("handlePageCustom()");
}

int main( int argc, char **argv )
{
	PG_Application app;
	
	app.LoadTheme( "default" );
	
	app.InitScreen( 640, 480, 0 );
	app.SetEmergencyQuit(true);
	
	PG_Label l( NULL, PG_Rect(10,50,250,25), NULL );
	l.Show();
	
	PG_TabBar bar( NULL, PG_Rect(10, 10, 300, 25) );
	bar.sigTabSelect.connect(slot(handleTab), &l);
	bar.Show();
	
	bar.AddTab("Tab1");
	bar.AddTab("Tab2");
	bar.AddTab("Tab3");
	bar.AddTab("MoreTab1");
	bar.AddTab("MoreTab2");
	bar.AddTab("MoreTab3");
	bar.AddTab("EvelLongerTab1");
	bar.AddTab("Tab4");
	
	PG_NoteBook notebook(NULL, PG_Rect(50, 100, 300, 200));
	
	notebook.sigPageSelect.connect(slot(handlePageSelect));
	
	notebook.AddPage("button", new PG_Button(NULL, 1, PG_Rect(0,0,10,10), "Big fat button"), slot(handlePageButton));
	
	PG_Widget* custom = notebook.CreatePage("custom", slot(handlePageCustom));
	custom->SetID(2);
	PG_Label label(custom, PG_Rect(5,5,100,25), "My Page");
	
	PG_ListBox listpage(NULL, PG_Rect(0,0,300,100));
	listpage.AddItem(new PG_ListBoxItem(25, "Item1"));
	listpage.AddItem(new PG_ListBoxItem(25, "Item2"));
	listpage.AddItem(new PG_ListBoxItem(25, "Item3"));
	listpage.AddItem(new PG_ListBoxItem(25, "Item4"));
	listpage.AddItem(new PG_ListBoxItem(25, "Item5"));
	listpage.AddItem(new PG_ListBoxItem(25, "Item6"));
	listpage.AddItem(new PG_ListBoxItem(25, "Item7"));
	listpage.AddItem(new PG_ListBoxItem(25, "Item8"));
	listpage.AddItem(new PG_ListBoxItem(25, "Item9"));
	listpage.AddItem(new PG_ListBoxItem(25, "Item10"));
	listpage.SetID(3);
	
	notebook.AddPage("list", &listpage);
	
	notebook.Show();
	
	app.Run();
	
	return 0;
}
