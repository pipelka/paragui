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
#include "pgtheme.h"
#include "pgmultilineedit.h"

#include <iostream>

#define RESX 800
#define RESY 600

void Splash() {
    PG_ThemeWidget splash(NULL, PG_Rect(100,100,600,400), true);
    PG_ThemeWidget splash1(&splash, PG_Rect(10,10,580,380));
    PG_ThemeWidget splash2(&splash1, PG_Rect(10,10,560,340));
    PG_Label l(&splash2, PG_Rect(10,10,540,320), "I'm a splash screen");
    l.SetAlignment(PG_Label::CENTER);
        
    splash.Show();
    SDL_Delay(5000);
    splash.Hide();
}

bool handle_popup(PG_Pointer clientdata) {
	PG_PopupMenu* pop = (PG_PopupMenu*)clientdata;

	pop->trackMenu(10, 10);
	
	return true;
}

bool handle_exit(PG_Pointer clientdata) {
	PG_Application* app = (PG_Application*)clientdata;
	app->Quit();
	return true;
}

bool handle_toggle(PG_Pointer clientdata) {
	PG_Button* b = (PG_Button*)clientdata;
	if (b->GetPressed()) {
		PG_LogMSG("Button pressed");
	}
	else {
		PG_LogMSG("Button released");
	}
	return true;
}
	

bool hande_slideIndent(PG_ScrollBar* s, long pos, PG_Pointer data)  {
	PG_DropDown* drop = static_cast<PG_DropDown*>(data);
	drop->SetIndent(pos);
	return true;
}

// A new widget with a callback member

class MySliderLabel : public PG_Label {
public:
	MySliderLabel(PG_Widget* parent, const PG_Rect& r, char* text) : PG_Label(parent,r,text) {
	};

	bool handler_slider(long data) {
		SetTextFormat("%i", (int)data);
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
	bool handle_show_window() {
		Show(true);
		return true;
	}

	/** callback handler in another flavor */
	bool handler_slider_btntrans(long data) {
		// set transparency of passed in button
		b->SetTransparency(static_cast<Uint8>(data));
		b->Update();

		// set transparency of class member (progress)
		progress->SetTransparency(static_cast<Uint8>(data));
		progress->Update();
		return true;
	}

protected:

	bool handleButtonClick(PG_Button* button);
	bool handleScrollPos(PG_ScrollBar* widget, long data);
	bool handleScrollTrack(PG_ScrollBar* widget, long data);

private:
	PG_ProgressBar* progress;
	PG_WidgetList* WidgetList;
	PG_Button* b;
};
	

TestWindow::TestWindow(PG_Widget* parent, const PG_Rect& r, char* windowtext) :
PG_Window(parent, r, windowtext, DEFAULT)
{
	WidgetList = new PG_WidgetList(this, PG_Rect(30, 40, 220, 250));
	WidgetList->SetDirtyUpdate(false);
	WidgetList->SetTransparency(0);
	WidgetList->SetBackground("default/wnd_close.bmp", BKMODE_TILE, 0xFF);
	WidgetList->SetBackgroundBlend(0);
			
	WidgetList->EnableScrollBar(true, PG_ScrollBar::VERTICAL);
	WidgetList->EnableScrollBar(true, PG_ScrollBar::HORIZONTAL);
		
	(new PG_Button(this, PG_Rect(260,130,110,30), "<< ADD", 100))->sigClick.connect(slot(*this, &TestWindow::handleButtonClick));
	
	(new PG_Button(this, PG_Rect(260,165,110,30), ">> REMOVE", 101))->sigClick.connect(slot(*this, &TestWindow::handleButtonClick));
	
	b = new PG_Button(WidgetList, PG_Rect(0,0, 400,50), "YES", PG_Button::YES);
	b->SetTransparency(128,128,128);
	b->SetFontName("qnx/font.ttf");

	PG_Slider* s = new PG_Slider(WidgetList, PG_Rect(0, 0, 200,20), PG_ScrollBar::HORIZONTAL);
	s->SetRange(0,255);
	s->SetTransparency(200);
	s->SetPosition(50);

	s->sigSlide.connect(slot(*this, &TestWindow::handler_slider_btntrans));
	s->sigSlideEnd.connect(slot(*this, &TestWindow::handler_slider_btntrans));

	new PG_LineEdit(WidgetList, PG_Rect(0,0,80,30));
	new PG_CheckButton(WidgetList, PG_Rect(0,0,200,25), "CheckButton 2");

	progress = new PG_ProgressBar(this, PG_Rect(260, 90, 150, 25));
	progress->SetTransparency(128);
	progress->SetName("MyProgressBar");
	progress->SetID(1001);
	progress->SetFontAlpha(128);
		
	PG_ScrollBar* scroll = new PG_ScrollBar(this, PG_Rect(415,90,20,150));
	scroll->SetID(1);
	scroll->sigScrollPos.connect(slot(*this, &TestWindow::handleScrollPos));
	scroll->sigScrollTrack.connect(slot(*this, &TestWindow::handleScrollPos));
	scroll->SetRange(0, 100);

	PG_ScrollBar* scroll1 = new PG_ScrollBar(this, PG_Rect(435,90,20,150));
	scroll1->SetID(2);
	scroll1->sigScrollPos.connect(slot(*this, &TestWindow::handleScrollPos));
	scroll1->sigScrollTrack.connect(slot(*this, &TestWindow::handleScrollPos));
	scroll1->SetRange(0, 255);

	PG_DropDown* drop = new PG_DropDown(this, PG_Rect(260, 60, 200,25));
	drop->SetIndent(5);
	drop->SetAlignment(PG_Label::CENTER);
	drop->AddItem("Under construction");
	drop->AddItem("Item 1");
	drop->AddItem("Item 2");
	drop->AddItem("Item 3");
	drop->AddItem("Item 4");
	drop->AddItem("Item 5");
	drop->AddItem("Item 6");
	//drop->Hide();
}

bool TestWindow::handleScrollPos(PG_ScrollBar* widget, long data){
	int id = widget->GetID();

	if(id == 1){
		progress->SetProgress(data);
		return true;
	}

	if(id == 2){
		SetTransparency((unsigned char)data);
		Update();
		return true;
	}

	return false;
}

bool TestWindow::handleScrollTrack(PG_ScrollBar* widget, long data) {
	int id = widget->GetID();

	if(id == 1){
		progress->SetProgress(data);
		return true;
	}

	if(id == 2){
		SetTransparency((unsigned char)data);
		Update();
		return true;
	}

	return false;
}

bool TestWindow::handleButtonClick(PG_Button* button) {
	static int label=0;
	int id = button->GetID();

	PG_Window::handleButtonClick(button);
	
	if(id == 100) {
		PG_Label* l = new PG_Label(WidgetList, PG_Rect(0,0,220,25), "");
		l->SetAlignment(PG_Label::CENTER);
		l->SetTextFormat("Label %i", ++label);
		return true;
	}

	if(id == 101) {
		PG_Widget* w = WidgetList->FindWidget(4);
		PG_LogDBG("FindWidget(4) = %p", w);
		if(w != NULL) {
			delete w;
		}
		
		return true;
	}
	
	return false;
}

bool handle_menu_click(PG_PopupMenu::MenuItem* item, PG_Pointer clientdata) {
	std::cout << "menu item '" << item->getId() << "' (\""
		<< item->getCaption() << "\") clicked" << std::endl;

	switch (item->getId()) {
		case 5:
			static_cast<TestWindow*>(clientdata)->Show();
			break;

		case 6:
			static_cast<PG_Application*>(clientdata)->Quit();
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

    PG_Widget* list = RectList->first();
	const char* name = NULL;

    while(list != NULL) {
		name = list->GetName();

		PG_LogMSG("%s %s",TabSpace,name);

		sprintf(tab,"  %s",TabSpace);	
		PrintChildObjects(list->GetChildList(), tab);

		list = list->next();
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
	bool bTestMode = false;

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

		if(strcmp(argv[c], "-t") == 0) {
			bTestMode = true;
		}

		if(strcmp(argv[c], "-hw") == 0) {
			flags |= SDL_HWSURFACE;
			flags ^= SDL_SWSURFACE;
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

	//Splash();
	
	PG_Color color(255,255,255);

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
	
	// create 2 radiobutton groups
	PG_RadioButton radio1(NULL, PG_Rect(50,0,200,25), "RadioButton 1");
	PG_RadioButton radio2(NULL, PG_Rect(50,25,200,25), "RadioButton 2", &radio1);
	PG_RadioButton radio3(NULL, PG_Rect(50,50,200,25), "RadioButton 3", &radio1);
	radio3.SetSizeByText();
	radio1.SetAlignment(PG_Label::RIGHT);
	
	PG_RadioButton radio4(NULL, PG_Rect(50,90,200,25), "RadioButton 4");
	PG_RadioButton radio5(NULL, PG_Rect(50,115,200,25), "RadioButton 5", &radio4);
	PG_RadioButton radio6(NULL, PG_Rect(50,140,200,25), "RadioButton 6", &radio4);

	PG_CheckButton check1(NULL, PG_Rect(300,140,180,25), "CheckButton 1");
	PG_PopupMenu popmenu(NULL, 425, 140, "My Menu");
	PG_PopupMenu submenu(NULL, 425, 140, "My SubMenu");
	PG_PopupMenu subsubmenu(NULL, 425, 140, "");
	
	submenu.sigSelectMenuItem.connect(slot(handle_menu_click), NULL);
	subsubmenu.sigSelectMenuItem.connect(slot(handle_menu_click), NULL);

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

	PG_ScrollBar scroll(NULL, PG_Rect(50, 200, 300, 20), PG_ScrollBar::HORIZONTAL );
	scroll.Show();

	PG_MaskEdit edit(NULL, PG_Rect(260,0,200,25));
	edit.SetMask("###.###.###.###");
	edit.SetValidKeys("1234567890");
	edit.Show();
	
	// our new label with the callback member
	MySliderLabel slider_label(NULL, PG_Rect(360, 250, 50,20), "5");
	slider_label.Show();

	// create the slider
	PG_Slider slider(NULL, PG_Rect(50, 250, 300,20), PG_ScrollBar::HORIZONTAL);
	slider.SetRange(5,50);

	// connect the "MSG_SLIDE" event with "handler_slider" of slider_label
	slider.sigSlide.connect(slot(slider_label, &MySliderLabel::handler_slider));
	slider.sigSlideEnd.connect(slot(slider_label, &MySliderLabel::handler_slider));

	slider.Show();

	PG_Button popbtn(NULL, PG_Rect(430, 250,100,25), "Pop me");
	popbtn.sigClick.connect(slot(handle_popup), (PG_Pointer)&popmenu);
	popbtn.Show();

	PG_SpinnerBox spin(NULL, PG_Rect(550,250,130,25));
	spin.Show();

	PG_DropDown drop(NULL, PG_Rect(50, 280, 300,25));
	
	//<obsolete>
	drop.AddItem("Under construction");
	drop.AddItem("Item 1");
	drop.AddItem("Item 2");
	drop.AddItem("Item 3");
	drop.AddItem("Item 4");
	drop.AddItem("Item 5");
	drop.AddItem("Item 6");
	//</obsolete>
	// creating static objects and inserting them into the list
	// isn't a good idea (the list will try to delete the objects
	// and the static objects will be destroyed when leaving the
	// application). Let's use dynamic objects.
	new PG_ListBoxItem(&drop, 25, "Item 7");
	new PG_ListBoxItem(&drop, 25, "Item 8");
	new PG_ListBoxItem(&drop, 25, "Item 9");
	drop.SetIndent(5);

	slider.sigSlide.connect(slot(hande_slideIndent), (PG_Pointer)&drop);
	slider.sigSlideEnd.connect(slot(hande_slideIndent), (PG_Pointer)&drop);
	drop.Show();

	PG_Button toggle(NULL, PG_Rect(200, 350, 100, 30), "Toggle me");
	toggle.sigClick.connect(slot(handle_toggle), (PG_Pointer)&toggle);
	toggle.SetToggle(true);
	toggle.Show();
	
	PG_Button list(NULL, PG_Rect(400,450,100,30), "List", PG_Button::OK);
	list.sigClick.connect(slot(handle_list));
	list.Show();

	PG_Button quit(NULL, PG_Rect(600,450,100,30), "Quit", PG_Button::CLOSE);
	quit.sigClick.connect(slot(handle_exit), (PG_Pointer)&app);
	quit.Show();

	PG_Button show_wnd(NULL, PG_Rect(500,450,100,30), "Window", PG_Button::APPLY);
	show_wnd.sigClick.connect(slot(wnd, &TestWindow::handle_show_window));
    
	show_wnd.Show();

	PG_MultiLineEdit text(NULL, PG_Rect(resx - 300, 35, 300, 150));
	text.SetText("Once upon a time, in a galaxy far far away...\n...\n...\n...\n...\n...\n...\nand they lived happily till once upon a time, in a galaxy far far away...\n[INSERT STORY HERE]");
	text.Show();
	
	// show the testwindow
	wnd.Show();
	wnd1.Show();
	
	PG_LogMSG("app ready after %i ms", SDL_GetTicks() - start_ticks);
	app.ShowCursor(PG_Application::SOFTWARE);

	PG_LogMSG("testing the widget finding methods");
	PG_Widget *tmp;
	
	tmp = PG_Application::GetWidgetByName("WindowOne");
	if (tmp)
	    PG_LogMSG("'WindowOne' found by name (id %d)", tmp->GetID());
	    
	tmp = PG_Application::GetWidgetById(100);
	if (tmp)
	    PG_LogMSG("'100' found by ID (name '%s')", tmp->GetName());
	    
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

	if(!bTestMode) {
		// Enter main loop
		app.Run();
		return EXIT_SUCCESS;
	}
	
	PG_LogMSG("Starting benchmark ... Wait");
	start_ticks = SDL_GetTicks();
	int iter = 500;
	
	for(int i=0; i<iter; i++) {
		PG_Widget::UpdateScreen();
	}

	int ticks = SDL_GetTicks() - start_ticks;
	PG_LogMSG("did %i iterations in %i ms", iter, ticks);
	PG_LogMSG("~%2.2fms per iteration", (float)ticks/(float)iter);
	
	return EXIT_SUCCESS;	
}
