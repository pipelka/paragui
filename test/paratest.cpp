#include "paragui.h"

#include "pgapplication.h"
#include "pgbutton.h"
#include "pgwidgetlist.h"
#include "pglabel.h"
#include "pgwindow.h"
#include "pgmaskedit.h"
#include "pgscrollbar.h"
#include "pgprogressbar.h"
#include "pgradiobutton.h"
#include "pgthemewidget.h"
#include "pgcheckbutton.h"
#include "pgslider.h"
#include "pglistbox.h"
#include "pgcolumnitem.h"
#include "pgdropdown.h"
#include "pgpopupmenu.h"
#include "pgspinnerbox.h"
#include "pglog.h"
#include "pgmenubar.h"

#define RESX 800
#define RESY 600

void Splash() {
    PG_ThemeWidget splash(NULL, PG_Rect(100,100,600,400), true);
    splash.Show();
    SDL_Delay(1000);
    splash.Hide();
}

bool handle_popup(PG_Button* button, PG_Pointer* data) {
	PG_PopupMenu* pop = static_cast<PG_PopupMenu*>(data);

	pop->trackMenu(10, 10);
	
	return true;
}

bool handle_exit(PG_Pointer* data) {
	PG_Application* app = static_cast<PG_Application*>(data);
	app->Quit();
	return true;
}

// A new widget with a callback member

class MySliderLabel : public PG_Label {
public:
	MySliderLabel(PG_Widget* parent, const PG_Rect& r, char* text) : PG_Label(parent,r,text) {
	};

	bool handle_slide(long pos) {
		SetTextFormat("%i", (int)pos);
		return true;
	}
};

// A testwindow class

class TestWindow : public PG_Window {
public:

	TestWindow(PG_Widget* parent, const PG_Rect& r, char* windowtext);
	virtual ~TestWindow() {};

	void Dummy() {};

	/** a new style callback member */
	bool handle_show_window(PG_Button* button, PG_Pointer* data) {
		Show(true);
		return true;
	}

	/** callback handler in another flavor */
	bool handle_slide_btntrans(PG_Slider* slider, long pos, PG_Pointer* data) {
		PG_Button* b = static_cast<PG_Button*>(data);
	
		// set transparency of passed in button
		b->SetTransparency((Unit8)pos, (Unit8)pos, (Unit8)pos);
		b->Update();

		// set transparency of class member (progress)
		progress->SetTransparency(data);
		progress->Update();
		return true;
	}

protected:

	bool handleButton(PG_Button* widget, PG_Pointer* data);
	
	bool handleScrollPos(PG_ScrollBar* widget, long pos);
	bool handleScrollTrack(PG_ScrollBar* widget, long pos);

private:
	PG_ProgressBar* progress;
	PG_WidgetList* WidgetList;
};
	

TestWindow::TestWindow(PG_Widget* parent, const PG_Rect& r, char* windowtext) :
PG_Window(parent, r, windowtext, WF_SHOW_CLOSE | WF_SHOW_MINIMIZE)
{
	WidgetList = new PG_WidgetList(this, PG_Rect(30, 40, 220, 250));
	WidgetList->SetDirtyUpdate(false);
	WidgetList->SetTransparency(0);
	WidgetList->SetBackground("default/wnd_close.bmp", BKMODE_TILE, 0xFF);
	WidgetList->SetBackgroundBlend(0);
			
	WidgetList->EnableScrollBar(true, PG_SB_VERTICAL);
	WidgetList->EnableScrollBar(true, PG_SB_HORIZONTAL);
		
	PG_Button* add = new PG_Button(this, 100, PG_Rect(260,130,110,30), "<< ADD");
	add->sigButtonClick.connect(slot(this, &TestWindow::handleButton));
	
	PG_Button* remove = new PG_Button(this, 101, PG_Rect(260,165,110,30), ">> REMOVE");
	remove->sigButtonClick.connect(slot(this, &TestWindow::handleButton));
	
	PG_Button* b = new PG_Button(NULL, BTN_ID_YES, PG_Rect(0,0, 400,50), "YES");
	b->SetTransparency(128,128,128);
	b->SetFontName("qnx/font.ttf");
	WidgetList->AddWidget(b);

	PG_Slider* s = new PG_Slider(NULL, 20, PG_Rect(0, 0, 200,20), PG_SB_HORIZONTAL);
	s->SetRange(0,255);
	s->SetTransparency(200);
	s->SetPosition(50);

	s->sigSlide.connect(slot(this, &TestWindow::handle_slide_btntrans), &b);

	WidgetList->AddWidget(s);
		
	WidgetList->AddWidget(new PG_LineEdit(NULL, PG_Rect(0,0,80,30)));

	PG_CheckButton* check = new PG_CheckButton(NULL, 10, PG_Rect(0,0,200,25), "CheckButton 2");
	WidgetList->AddWidget(check);

	progress = new PG_ProgressBar(this, PG_Rect(260, 90, 150, 25));
	progress->SetTransparency(128);
	progress->SetName("MyProgressBar");
	progress->SetID(1001);
	progress->SetFontAlpha(128);
		
	PG_ScrollBar* scroll = new PG_ScrollBar(this, 1, PG_Rect(415,90,20,150));
	scroll->SetRange(0, 100);
	scroll->sigScrollTrack.connect(slot(this, &TestWindow::handleScrollTrack));
	scroll->sigScrollPos.connect(slot(this, &TestWindow::handleScrollPos));

	PG_ScrollBar* scroll1 = new PG_ScrollBar(this, 2, PG_Rect(435,90,20,150));
	scroll1->SetRange(0, 255);
	scroll1->sigScrollTrack.connect(slot(this, &TestWindow::handleScrollTrack));
	scroll1->sigScrollPos.connect(slot(this, &TestWindow::handleScrollPos));

	PG_DropDown* drop = new PG_DropDown(this, 15, PG_Rect(260, 60, 200,25));
	drop->SetIndent(5);
	drop->AddItem("Under construction");
	drop->AddItem("Item 1");
	drop->AddItem("Item 2");
	drop->AddItem("Item 3");
	drop->AddItem("Item 4");
	drop->AddItem("Item 5");
	drop->AddItem("Item 6");
}

bool TestWindow::handleScrollPos(PG_ScrollBar* widget, long pos){
	int id = widget->GetID();
	
	if(id == 1){
		progress->SetProgress(pos);
		return true;
	}

	if(id == 2){
		SetTransparency((Uint8)pos);
		Update();
		return true;
	}

	return false;
}

bool TestWindow::handleScrollTrack(PG_ScrollBar* widget, long pos) {
	int id = widget->GetID();
	
	if(id == 1){
		progress->SetProgress(pos);
		return true;
	}

	if(id == 2){
		SetTransparency((Uint8)pos);
		Update();
		return true;
	}

	return false;
}

bool TestWindow::handleButton(PG_Button* widget, PG_Pointer* data) {
	static int label=0;

	if(widget->GetID() == 100) {
		PG_Label* l = new PG_Label(NULL, PG_Rect(0,0,220,25), "");
		l->SetAlignment(PG_TA_CENTER);
		l->SetTextFormat("Label %i", ++label);
		WidgetList->AddWidget(l);
	
		return true;
	}

	if(widget->GetID() == 101) {
		PG_Widget* w = WidgetList->FindWidget(4);
		if(w != NULL) {
			WidgetList->RemoveWidget(w, true, true);
			delete w;
		}
		
		return true;
	}
	
	return false;
}

bool handle_menu_click(PG_MenuItem* item, PG_Pointer* data) {
	std::cout << "menu item '" << item->getId() << "' (\""
		<< item->getCaption() << "\") clicked" << std::endl;

	switch (item->getId()) {
		case 5:
			static_cast<TestWindow*>(data)->Show();
			break;

		case 6:
			static_cast<PG_Application*>(data)->Quit();
			break;
	}

	return true;
}

void PrintChildObjects(PG_RectList *RectList, char *TabSpace) {
	char tab[20];
	strcpy(tab, TabSpace);

    if (RectList == NULL) {
		return;
	}

    PG_RectList::iterator list = RectList->begin();
	const char* name = NULL;

    while(list != RectList->end()) {
		name = (*list)->GetName();

		PG_LogMSG("%s %s",TabSpace,name);

		sprintf(tab,"  %s",TabSpace);	
		PrintChildObjects((*list)->GetChildList(), tab);

		list++;
	}
    
}

bool handle_list() {

	PG_LogMSG(" ---- List of objects ----\n");
	PrintChildObjects(PG_Widget::GetWidgetList(),"  +");
	PG_LogMSG(" ---- End of list ----\n");

	return true;
}

int main(int argc, char* argv[]) {
	char theme[20];

	strcpy(theme, "default");
	
	// initial flags for screensurface
	Uint32 flags = SDL_SWSURFACE;
	int bpp = 0;

	int resx = RESX, resy = RESY;
	
	// construct the application object
	PG_Application app;
	
	for(int c=1; c<argc; c++) {

		if(argv[c][0] != '-') {
			strcpy(theme, argv[c]);
		}

		if(strcmp(argv[c], "-f") == 0) {
			flags |= SDL_FULLSCREEN;
		}

		if(strcmp(argv[c], "-bpp") == 0) {
			bpp = atoi(argv[++c]);
		}
		
		if(strcmp(argv[c], "-x") == 0) {
		        resx = atoi(argv[++c]);
		}
		
		if(strcmp(argv[c], "-y") == 0) {
		        resy = atoi(argv[++c]);
		}
	}

	Uint32 start_ticks = SDL_GetTicks();
	
	if(!app.LoadTheme(theme)) {
	    PG_LogERR("Unable to load theme \"%s\"", theme);
	    return -1;
	}

	PG_LogMSG("Loaded theme in %i ms", SDL_GetTicks() - start_ticks);

	if(!app.InitScreen(resx, resy, bpp, flags)){
		printf("Resolution %dx%d not supported\n", resx, resy);
		exit(-1);
	}

	PG_LogMSG("screen initialized after %i ms", SDL_GetTicks() - start_ticks);

	app.SetCursor(app.GetTheme()->FindSurface("Pointer", "Pointer", "normal"));

	SDL_Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;

	PG_LogMSG("creating 'wnd' after %i ms", SDL_GetTicks() - start_ticks);

	// create the testwindow
	TestWindow wnd(NULL, PG_Rect(100,100,500,300), "My first Testwindow");
	wnd.SetTransparency(0);
	wnd.SetName("WindowOne");
	wnd.SetID(100);
	
	PG_LogMSG("creating 'wnd1' after %i ms", SDL_GetTicks() - start_ticks);

	TestWindow wnd1(NULL, PG_Rect(50,50,500,300), "My 2nd Testwindow");
	wnd1.SetTransparency(0);
	wnd1.SetName("WindowTwo");
	wnd1.SetID(101);
	
	//PG_Draw::DrawLine(0,0, app.GetScreenWidth()-1, app.GetScreenHeight()-1, color,1, app.GetScreen());
	
	// create 2 radiobutton groups
	PG_RadioButton radio1(NULL, 1, PG_Rect(50,0,200,25), "RadioButton 1");
	PG_RadioButton radio2(NULL, 2, PG_Rect(50,25,200,25), "RadioButton 2", &radio1);
	PG_RadioButton radio3(NULL, 3, PG_Rect(50,50,200,25), "RadioButton 3", &radio1);
	
	PG_RadioButton radio4(NULL, 4, PG_Rect(50,90,200,25), "RadioButton 4");
	PG_RadioButton radio5(NULL, 5, PG_Rect(50,115,200,25), "RadioButton 5", &radio4);
	PG_RadioButton radio6(NULL, 6, PG_Rect(50,140,200,25), "RadioButton 6", &radio4);

	PG_CheckButton check1(NULL, 7, PG_Rect(300,140,180,25), "CheckButton 1");
	PG_PopupMenu   popmenu(NULL, 425, 140, "My Menu");
	PG_PopupMenu   submenu(NULL, 425, 140, "My SubMenu");
	PG_PopupMenu   subsubmenu(NULL, 425, 140, "");
	
	submenu.sigMenuItemSelect.connect(slot(handle_menu_click));
	subsubmenu.sigMenuItemSelect.connect(slot(handle_menu_click));

	subsubmenu.addMenuItem("Mordor", 1).
	    addMenuItem("Minas Morgul", 2).
		addMenuItem("Orodruin", 3);
		
	submenu.addMenuItem("Grendel", 1).
		addMenuItem("Beowulf", 2).
		addMenuItem("Hrothgar", 3).
        addMenuItem("Long ago", &subsubmenu);
		
    popmenu.addMenuItem("Tasty", 1, slot(handle_menu_click)).
        addMenuItem("Even tastier", 2, slot(handle_menu_click)).
        addMenuItem("I'm third here...", 3, slot(handle_menu_click)).
        addMenuItem("And I'm fourth", 4, slot(handle_menu_click)).
		addMenuItem("Saga", &submenu).
        addSeparator().
        addMenuItem("Open Window", 5, slot(handle_menu_click), &wnd).
        addMenuItem("Quit", 6, slot(handle_menu_click), &app);
    
	popmenu.disableItem(2);
	
	PG_MenuBar menubar(NULL, PG_Rect(resx-300, 0, 300, 30));
	menubar.Add("PopMe 2", &popmenu);

	PG_PopupMenu editmenu(NULL, 0 ,0, NULL);
	editmenu.addMenuItem("Cut", 1);
	editmenu.addMenuItem("Copy", 2);
	editmenu.addMenuItem("Paste", 3);
	menubar.Add("Edit", &editmenu);

	menubar.Show();
	
	radio1.Show();
	radio2.Show();
	radio3.Show();
	
	radio4.Show();
	radio5.Show();
	radio6.Show();

	check1.Show();

	PG_ScrollBar scroll(NULL, 10, PG_Rect(50, 200, 300, 20), PG_SB_HORIZONTAL );
	scroll.Show();

	PG_MaskEdit edit(NULL, PG_Rect(260,0,200,25));
	edit.SetMask("###.###.###.###");
	edit.SetValidKeys("1234567890");
	edit.Show();
	
	// our new label with the callback member
	MySliderLabel slider_label(NULL, PG_Rect(360, 250, 50,20), "5");
	slider_label.Show();

	// create the slider
	PG_Slider slider(NULL, 11, PG_Rect(50, 250, 300,20), PG_SB_HORIZONTAL);
	slider.SetRange(5,20);

	// connect the "MSG_SLIDE" event with "handler_slider" of slider_label (see macro above, just for testing)
	slider.sigSlide.connect(slot(&slider_label, &MySliderLabel::handle_slide));
	
	slider.Show();

	PG_Button popbtn(NULL, 20, PG_Rect(430, 250,100,25), "Pop me");
	popbtn.sigButtonClick.connect(slot(handle_popup), &popmenu);
	popbtn.Show();

	PG_SpinnerBox spin(NULL, PG_Rect(550,250,130,25));
	spin.Show();

	PG_DropDown drop(NULL, 14, PG_Rect(50, 280, 300,25));
	drop.SetIndent(5);
	drop.AddItem("Under construction");
	drop.AddItem("Item 1");
	drop.AddItem("Item 2");
	drop.AddItem("Item 3");
	drop.AddItem("Item 4");
	drop.AddItem("Item 5");
	drop.AddItem("Item 6");
	drop.Show();

	PG_Button list(NULL, BTN_ID_OK, PG_Rect(400,450,100,30), "List");
	list.sigButtonClick.connect(slot(handle_list));
	list.Show();

	PG_Button quit(NULL, BTN_ID_CLOSE, PG_Rect(600,450,100,30), "Quit");
	quit.sigButtonClick.connect(slot(handle_exit), &app);
	quit.Show();

	PG_Button show_wnd(NULL, BTN_ID_APPLY, PG_Rect(500,450,100,30), "Window");
	show_wnd.sigButtonClick.connect(slot(&wnd, &TestWindow::handle_show_window));
    
	show_wnd.Show();

	// show the testwindow
	wnd.Show();
	wnd1.Show();
	
	PG_LogMSG("app ready after %i ms", SDL_GetTicks() - start_ticks);
	app.ShowCursor(PG_CURSOR_SOFTWARE);

	PG_LogMSG("testing the widget finding methods");
	PG_Widget *tmp;
	
	tmp = PG_Application::GetWidgetByName("WindowOne");
	if (tmp)
	    PG_LogMSG("'WindowOne' found by name (id %d)", tmp->GetID());
	    
	tmp = PG_Application::GetWidgetById(100);
	if (tmp)
	    PG_LogMSG("'100' found by ID (name '%s')", tmp->GetName());
	    
	tmp = PG_Application::GetWidgetByName("WindowTwo");
	if (tmp)
	    PG_LogMSG("'WindowTwo' found by name (id %d)", tmp->GetID());
	    
	tmp = PG_Application::GetWidgetById(101);
	if (tmp)
	    PG_LogMSG("'101' found by ID (name '%s')", tmp->GetName());

	PG_LogMSG("testing the child finding methods");
	tmp = wnd.FindChild("MyProgressBar");
	if (tmp)
	    PG_LogMSG("sought for 'MyProgressBar' and found it (id '%d')",
	              tmp->GetID());
	tmp = wnd.FindChild(1001);
	if (tmp)
	    PG_LogMSG("sought for '1001' and found it (name '%s')",
	              tmp->GetName());

	
	// PG_Notebook   pgn(0, PG_Rect(50, 320, 300, 150));
	// pgn.AddPage("Test", 0x01);
	// pgn.AddPage("Second", 0x02);
	// pgn.Show();
		
	// Enter main loop 
	app.Run();

	return EXIT_SUCCESS;
}
