#include "pgnotebook.h"

PG_NoteBook::PG_NoteBook(PG_Widget* parent, const PG_Rect& r, TabBarPos pos, int BarHeight, const char* style) : PG_Widget(parent, r, style) {
	my_barPos = pos;
	my_tabBar = new PG_TabBar(this, PG_Rect(0,0,r.w,BarHeight), style);
	my_tabBar->sigTabSelect.connect(slot(this, &PG_NoteBook::handleTabSelect));
	
	my_clientRect.SetRect(0, my_tabBar->h, r.w, r.h-my_tabBar->h);
	my_activePage = NULL;
	
	LoadThemeStyle(style);
}

PG_NoteBook::~PG_NoteBook() {
}
	
void PG_NoteBook::AddPage(const char* text, PG_Widget* page) {
	AddChild(page);
	page->MoveWidget(my_clientRect);
	
	PG_Button* btn = my_tabBar->AddTab(text);
	my_pageMap[btn] = page;
	
	page->Hide();
	
	if(my_pageMap.size() == 1) {
		page->Show();
		my_activePage = page;
		sigPageSelect(this, page);
	}
}

void PG_NoteBook::AddPage(const char* text, PG_Widget* page, PG_PageSelectSlot slot) {
	AddPage(text, page);
	my_slotMap[page] = slot;
	if(my_pageMap.size() == 1) {
		slot.call(page);
	}
}

PG_Widget* PG_NoteBook::CreatePage(const char* text) {
	PG_Widget* page = new PG_Widget(NULL, PG_Rect(0,0,10,10));
	AddPage(text, page);
	return page;
}
	
PG_Widget* PG_NoteBook::CreatePage(const char* text, PG_PageSelectSlot slot) {
	PG_Widget* page = CreatePage(text);
	my_slotMap[page] = slot;
	return page;
}

bool PG_NoteBook::handleTabSelect(PG_Button* button) {
	PG_Widget* page = my_pageMap[button];
	
	if(page == NULL) {
		return false;
	}
	
	if(my_activePage == page) {
		return false;
	}
	
	if(my_activePage != NULL) {
		my_activePage->Hide();
	}
	my_activePage = page;
	my_activePage->Show();
	sigPageSelect(this, page);
	my_slotMap[page].call(page);
	
	return true;
}

void PG_NoteBook::eventSizeWidget(Uint16 w, Uint16 h) {
	
	PG_Widget::eventSizeWidget(w, h);
	
	my_tabBar->SizeWidget(w, my_tabBar->h);
	my_clientRect.SetRect(0, 0, w, h - my_tabBar->h);
	
	// set tabbar prosition
	if(my_barPos == top) {
		my_tabBar->MoveWidget(0, 0);
		my_clientRect.x = 0;
		my_clientRect.y = my_tabBar->h;
	}
	else {
		my_tabBar->MoveWidget(0, w - my_tabBar->h);
		my_clientRect.x = 0;
		my_clientRect.y = h - my_tabBar->h;
	}
	
	// resize pages
	for(std::map<PG_Button*, PG_Widget*>::iterator i = my_pageMap.begin(); i != my_pageMap.end(); i++) {
		(*i).second->MoveWidget(my_clientRect);
	}
}
