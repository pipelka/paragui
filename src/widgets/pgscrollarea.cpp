#include "pgscrollarea.h"

PG_ScrollArea::PG_ScrollArea(PG_Widget* parent, const PG_Rect& r) : PG_Widget(parent, r),
my_shiftx(false), my_shifty(false) {
}

PG_ScrollArea::~PG_ScrollArea() {
}

void PG_ScrollArea::ScrollTo(Uint16 x, Uint16 y) {
	Sint32 dx = my_area.x - x;
	Sint32 dy = my_area.y - y;

	if(GetChildList() == NULL) {
		return;
	}

	for(PG_Widget* i = GetChildList()->first(); i != NULL; i = i->next()) {
		i->MoveRect(i->x + dx, i->y + dy);
	}

	my_area.x = x;
	my_area.y = y;

	Update();
}

void PG_ScrollArea::AddChild(PG_Widget* child) {
	PG_Widget::AddChild(child);
	child->MoveRect(child->x - my_area.x, child->y - my_area.y);

	if(child->x+child->w+my_area.x-my_xpos > my_area.w) {
		my_area.w = child->x+child->w+my_area.x-my_xpos;
		sigAreaChangedWidth(this, my_area.w);
	}
	if(child->y+child->h+my_area.y-my_ypos > my_area.h) {
		my_area.h = child->y+child->h+my_area.y-my_ypos;
		sigAreaChangedHeight(this, my_area.h);
	}

	if(IsVisible()) {
		child->Show();
	}
}

bool PG_ScrollArea::RemoveChild(PG_Widget* child) {

	// recalc scrollarea
	Uint16 w = 0;
	Uint16 h = 0;

	if(GetChildList() == NULL) {
		return false;
	}

	// remove widget
	PG_Rect r = *child;
	if(!PG_Widget::RemoveChild(child)) {
		return false;
	}

	for(PG_Widget* i = GetChildList()->first(); i != NULL; i = i->next()) {

		// check if i should move the widget (x)
		if(my_shiftx && (i->x >= r.x+r.w)) {
			i->MoveRect(i->x - r.w, i->y);
		}

		// check if i should move the widget (y)
		if(my_shifty && (i->y >= r.y+r.h)) {
			i->MoveRect(i->x, i->y - r.h);
		}

		// recalc new scrollarea
		if(i->x+i->w+my_area.x-my_xpos > w) {
			w = i->x+i->w+my_area.x-my_xpos;
		}
		if(i->y+i->h+my_area.y-my_ypos > h) {
			h = i->y+i->h+my_area.y-my_ypos;
		}
	}

	// signal changes
	if(w != my_area.w) {
		my_area.w = w;
		sigAreaChangedWidth(this, my_area.w);
	}

	if(h != my_area.h) {
		my_area.h = h;
		sigAreaChangedHeight(this, my_area.h);
	}

	Update();
	return true;
}

void PG_ScrollArea::RemoveAll() {
	if(GetChildList() == NULL) {
		return;
	}
	GetChildList()->clear();
	Update();
}

void PG_ScrollArea::DeleteAll() {
	if(GetChildList() == NULL) {
		return;
	}

	PG_Widget* list = GetChildList()->first();

	GetChildList()->clear();
	Update();

	for(; list != NULL; ) {
		PG_Widget* w = list;
		list = list->next();
		w->SetVisible(false);
		delete w;
	}
	my_area.w = 0;
	my_area.h = 0;
}

Uint16 PG_ScrollArea::GetWidgetCount() {
	if(GetChildList() == NULL) {
		return 0;
	}

	return GetChildList()->size();
}

Uint16 PG_ScrollArea::GetScrollPosX() {
	return my_area.x;
}

Uint16 PG_ScrollArea::GetScrollPosY() {
	return my_area.y;
}

void PG_ScrollArea::SetShiftOnRemove(bool shiftx, bool shifty) {
	my_shiftx = shiftx;
	my_shifty = shifty;
}

void PG_ScrollArea::SetAreaWidth(Uint16 w) {
	if(my_area.w == w) {
		return;
	}
	my_area.w = w;
	sigAreaChangedWidth(this, my_area.w);
}

void PG_ScrollArea::SetAreaHeight(Uint16 h) {
	if(my_area.h == h) {
		return;
	}
	my_area.h = h;
	sigAreaChangedHeight(this, my_area.h);
}
