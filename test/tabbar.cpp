#include "paragui.h"
#include "pgapplication.h"
#include "pgtabbar.h"
#include "pglabel.h"
#include "pgnotebook.h"
#include "pglistbox.h"
#include "pglistboxitem.h"
#include "pgcheckbutton.h"
#include "pgwindow.h"
#include "pglog.h"

bool handleTab(PG_TabBar* bar, PG_Button* button, PG_Pointer* data) {
	PG_Label* l = static_cast<PG_Label*>(data);
	l->SetTextFormat("Tab '%s' selected", button->GetText());
	return true;
}

bool handlePageSelect(PG_NoteBook* notebook, PG_Widget* page) {
	PG_LogMSG("Page with ID '%i' selected.", page->GetID());
	return true;
}

bool handlePageButton(PG_Widget* page) {
	PG_LogMSG("handlePageButton()");
	return true;
}

bool handlePageCustom(PG_Widget* page) {
	PG_LogMSG("handlePageCustom()");
	PG_LogMSG("ObjectSurface: %08x", page->GetWidgetSurface());
	return true;
}

bool handleBigFatButton(PG_Button* b) {
	PG_Window wnd(NULL, PG_Rect(200,200,350,100), "Message");
	PG_Label l(&wnd, PG_Rect(5,40,340,25), "You pressed the 'Big Fat Button'");
	l.SetAlignment(PG_TA_CENTER);
	
	wnd.Show(true);
	wnd.RunModal();
	
	return true;
}


int main( int argc, char **argv )
{
	PG_Application app;
	
	app.LoadTheme( "default" );
	
	app.InitScreen( 640, 480, 0 );
	app.SetEmergencyQuit(true);
	
	PG_Label l( NULL, PG_Rect(10,50,250,25), NULL );
	l.Show();
	
	PG_TabBar bar( NULL, PG_Rect(10, 10, 300, 33) );
	bar.sigTabSelect.connect(slot(handleTab), &l);
	bar.Show();
	
	bar.AddTab("Tab1");
	bar.AddTab("Tab2");
	bar.AddTab("Tab3");
	bar.AddTab("MoreTab1");
	bar.AddTab("MoreTab2");
	bar.AddTab("MoreTab3");
	bar.AddTab("EvenLongerTab1");
	bar.AddTab("Tab4");
	
	PG_NoteBook notebook(NULL, PG_Rect(50, 100, 300, 200));
	
	notebook.sigPageSelect.connect(slot(handlePageSelect));
	
	PG_Button b(NULL, 1, PG_Rect(0,0,10,10), "Big fat button");
	b.sigButtonClick.connect(slot(handleBigFatButton));
	
	notebook.AddPage("button", &b, slot(handlePageButton));
	
	PG_Widget* custom = notebook.CreatePage("custom", slot(handlePageCustom));
	custom->SetID(2);
	PG_Label label(custom, PG_Rect(5,5,100,25), "My Page");
	PG_CheckButton check(custom, -1, PG_Rect(5,35,150,25), "Check me");
	
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

	PG_NoteBook subnotebook(NULL, PG_Rect(0,0,100,100));
	
	PG_Widget* complex = subnotebook.CreatePage("custom2");
	PG_Button b2(complex, -1, PG_Rect(10,10,100,25), "Button");
	
	subnotebook.AddPage("button2", new PG_Button(NULL, -1, 	PG_Rect(0,0,10,10), "Not so big button"));
	
	notebook.AddPage("complex", &subnotebook);
	
	notebook.Show();
	
	app.Run();
	
	return 0;
}
