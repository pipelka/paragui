#include <cstdio>
#include "pgapplication.h"
#include "pgthemewidget.h"
#include "pgwindow.h"
#include "pgmessagebox.h"
#include "pgdropdown.h"

class CMyWindow : public PG_Window

{
public:
	CMyWindow(PG_Widget *parent,const PG_Rect& r,char *text,WindowFlags flags,const char* style = "Window");
};

CMyWindow::CMyWindow(PG_Widget *parent,const PG_Rect& r,char *text, WindowFlags flags,const char* style) : PG_Window(parent,r,text,flags,style)

{
}

class CMyWidget : public PG_ThemeWidget

{
	public:
		CMyWidget(PG_Widget *parent,PG_Rect rect);
};

CMyWidget::CMyWidget(PG_Widget *parent,PG_Rect rect) : PG_ThemeWidget(parent,rect, true)

{
	CMyWindow *mywindow = new CMyWindow(this, PG_Rect(50,50,150,100), "Fenster", PG_Window::DEFAULT);
	AddChild(mywindow);
}



int main(int argc,char *argv[])

{
	// Change window test to be dynamic allocation for app, mywidget, and msgbox
	PG_Application *app;
	CMyWidget *mywidget;
	PG_MessageBox *msgbox;

	app=new PG_Application();
	app->SetEmergencyQuit(true);
	app->LoadTheme("simple");
	app->InitScreen(800,600,0,SDL_SWSURFACE);

	mywidget=new CMyWidget(NULL,PG_Rect(200,200,350,250));
	mywidget->Show();

	msgbox=new PG_MessageBox(
		NULL,
		PG_Rect(200,50,240,200),
		"Modal Messagebox", "Click \"Ok\" to close me",
		PG_Rect(90, 120, 50, 50),
		"Ok",
		PG_Label::CENTER);
		
	PG_DropDown* drop = new PG_DropDown(msgbox, PG_Rect(5, 60, 200,25));
	drop->SetIndent(5);
	drop->AddItem("Under construction");
	drop->AddItem("Item 1");
	drop->AddItem("Item 2");
	drop->AddItem("Item 3");

	msgbox->Show();
	msgbox->SetTitle("New Title");
	msgbox->WaitForClick();
	msgbox->Hide();
	
	app->Run();
	
	// Get rid of mywidget, msgbox, and app buttons and context
	delete mywidget;
	delete msgbox;
	delete app;
	

	// Start the process over exactly the same

	app=new PG_Application();
	app->SetEmergencyQuit(true);
	app->LoadTheme("simple");
	app->InitScreen(800,600,0,SDL_SWSURFACE);

	mywidget=new CMyWidget(NULL,PG_Rect(200,200,350,250));
	mywidget->Show();

	msgbox=new PG_MessageBox(
		NULL,
		PG_Rect(200,50,240,200),
		"Modal Messagebox", "Click \"Ok\" to close me",
		PG_Rect(90, 120, 50, 50),
		"Ok",
		PG_Label::CENTER);
		
	msgbox->Show();
	msgbox->WaitForClick();

	// Get rid of mywidget, msgbox, and app buttons and context
	delete mywidget;
	delete msgbox;
	delete app;
		
	return 0;
}
