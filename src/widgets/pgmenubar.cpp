#include "pgmenubar.h"
#include "pgbutton.h"
#include "pgpopupmenu.h"

PG_MenuBar::PG_MenuBar(PG_Widget* parent, const PG_Rect& rect, const char* style) : PG_ThemeWidget(parent, rect, style) {
	my_btnOffsetY = 2;
	my_style = style;
	my_active = NULL;
}

PG_MenuBar::~PG_MenuBar() {
	Cleanup();
}

void PG_MenuBar::Add(const char* text, PG_PopupMenu* menu, Uint16 indent, Uint16 width) {
	MenuBarItem* last = NULL;
	Uint16 xpos = 0;
	Uint16 height = 0;

	if(menu == NULL) {
		return;
	}

	if(ItemList.size() > 0) {
		last = ItemList.back();
	}

	if(last != NULL) {
		xpos = (last->button->x + last->button->w) - my_xpos;
	}

	xpos += indent;

	if(width == 0) {
		GetTextSize(width, height, text);
		width += 6;
	}
	
	last = new MenuBarItem;

	last->button = new PG_Button(
							this,
							PG_Rect(xpos, my_btnOffsetY, width, my_height - my_btnOffsetY*2),
							text, -1,
							my_style.c_str());

	last->button->SetFontSize(GetFontSize());

	last->button->sigClick.connect(slot(*this, &PG_MenuBar::handle_button), (PG_Pointer)last);

	last->popupmenu = menu;

	ItemList.push_back(last);
}

bool PG_MenuBar::handle_button(PG_Button* button, PG_Pointer last) {
	MenuBarItem* item = static_cast<MenuBarItem*>(last);

	// check if we are visible
	if(item->popupmenu->IsVisible()) {
		item->popupmenu->Hide();
		my_active = NULL;
		return true;
	}

	if(my_active != NULL) {
		my_active->Hide();
		my_active = NULL;
	}

	my_active = item->popupmenu;
	my_active->trackMenu(button->x, button->y + button->h);

	return true;
}

void PG_MenuBar::Cleanup() {
	for(std::vector<MenuBarItem*>::iterator i = ItemList.begin(); i != ItemList.end(); i = ItemList.begin()) {
		delete (*i)->button;
		delete (*i);
		ItemList.erase(i);
	}
}
