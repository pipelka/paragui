#include "pgtabbar.h"
#include "pglog.h"

PG_TabBar::PG_TabBar(PG_Widget* parent, const PG_Rect r, const char* style) : PG_Widget(parent, r) {

	my_tabList = new PG_WidgetListEx(this, PG_Rect(0,0,r.w-50,r.h), style);
	my_tabList->EnableScrollBar(false, PG_SB_VERTICAL);
	my_tabList->EnableScrollBar(false, PG_SB_HORIZONTAL);

	my_btnPrev = new PG_Button(this, -1, PG_Rect(0,r.w-50,25,h), "<");
	my_btnPrev->sigButtonClick.connect(slot(this, &PG_TabBar::handleTabNav));
	my_btnPrev->Hide();
	
	my_btnNext = new PG_Button(this, -1, PG_Rect(0,r.w-25,25,h), ">");
	my_btnNext->sigButtonClick.connect(slot(this, &PG_TabBar::handleTabNav));
	my_btnNext->Hide();
	
	my_selectedTab = NULL;
	
	SizeWidget(r.w, r.h);
}

PG_TabBar::~PG_TabBar() {
}
	
PG_Button* PG_TabBar::AddTab(const char* text) {
	Uint16 height = 0;
	Uint16 width = 0;
	
	GetTextSize(width, height, text);
	width += 6;
	
	PG_Button* b = new PG_Button(NULL, -1, PG_Rect(my_tabList->GetListWidth(), 0, width, my_height), text);
	b->SetToggle(true);
	b->sigButtonClick.connect(slot(this, &PG_TabBar::handleTabClick));
	
	my_tabList->AddWidget(b);
	
	if(my_tabList->GetListWidth() > my_width) {
		SizeWidget(my_width, my_height);
	}
	Update();
	
	int c = my_tabList->GetWidgetCount();
	
	if(c == 1) {
		b->SetPressed(true);
		my_selectedTab = b;
	}
	return b;
}

PG_Button* PG_TabBar::AddTab(const char* text, PG_TabSelectSlot slot) {
	PG_Button* b = AddTab(text);
	b->sigButtonClick.connect(slot);
	
	return b;
}

void PG_TabBar::eventSizeWidget(Uint16 w, Uint16 h) {
	
	Uint16 listw = w - ((my_tabList->GetListWidth() <= w) ? 0 : (my_btnPrev->w + my_btnNext->w));
	
	my_tabList->SizeWidget(listw, h);
	my_tabList->Update();
	
	if(my_tabList->GetListWidth() <= w) {
		my_btnNext->Hide();
		my_btnPrev->Hide();
		return;
	}

	my_btnPrev->MoveWidget(PG_Rect(listw, 0, my_btnPrev->w, h));

	listw += my_btnPrev->w;
	my_btnNext->MoveWidget(PG_Rect(listw, 0, my_btnNext->w, h));


	my_btnNext->Show();
	my_btnPrev->Show();
}

bool PG_TabBar::handleTabClick(PG_Button* button) {
	if(my_selectedTab == button) {
		my_selectedTab->SetPressed(true);
		return false;
	}
	
	if(my_selectedTab != NULL) {
		my_selectedTab->SetPressed(false);
	}
	
	my_selectedTab = button;
	my_selectedTab->SetPressed(true);
	
	sigTabSelect(this, button);
	
	return true;
}

bool PG_TabBar::handleTabNav(PG_Button* button) {
	int index = -1;
	int dir = 0;
	
	if(button == my_btnPrev) {
		index = my_tabList->FindIndex(my_selectedTab);
		dir = -1;
	}

	if(button == my_btnNext) {
		index = my_tabList->FindIndex(my_selectedTab);
		dir = +1;
	}

	if(index == -1) {
		return false;
	}
	
	index += dir;
	PG_Widget* w = my_tabList->FindWidget(index);
	
	if(w == NULL) {
		return false;
	}
	
	my_tabList->ScrollTo(w, PG_SB_HORIZONTAL);
	PG_Button* b = static_cast<PG_Button*>(w);
	handleTabClick(b);
	
	return true;
}
