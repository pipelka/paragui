/*
    ParaGUI - crossplatform widgetset
    Copyright (C) 2000,2001,2002  Alexander Pipelka
 
    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.
 
    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.
 
    You should have received a copy of the GNU Library General Public
    License along with this library; if not, write to the Free
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 
    Alexander Pipelka
    pipelka@teleweb.at
 
    Last Update:      $Author: braindead $
    Update Date:      $Date: 2003/06/29 17:09:49 $
    Source File:      $Source: /sources/paragui/paragui/src/widgets/pglistbox.cpp,v $
    CVS/RCS Revision: $Revision: 1.3.6.4 $
    Status:           $State: Exp $
*/

#include "pglistbox.h"

PG_ListBox::PG_ListBox(PG_Widget* parent, const PG_Rect& r, const char* style) : PG_WidgetList (parent, r, style) {
	my_multiselect = false;
	my_selectedItem = NULL;
	my_indent = 0;
	my_selectindex = 0;

	PG_ThemeWidget::LoadThemeStyle(style, "ListBox");
}

PG_ListBox::~PG_ListBox() {
}

void PG_ListBox::AddWidget(PG_Widget* w) {
	PG_WidgetList::AddWidget(w);
}

void PG_ListBox::AddItem(PG_ListBoxBaseItem* item) {
    if (!item)
        return;
    
    Sint16 neww = Width() - my_widthScrollbar - (my_bordersize << 1);

    if (neww < 0)
        neww = 0;
    
	item->SizeWidget(neww, item->Height());
	item->SetIndent(my_indent);
	AddWidget(item);
}

void PG_ListBox::SetMultiSelect(bool multi) {
	my_multiselect = multi;
}

bool PG_ListBox::GetMultiSelect() {
	return my_multiselect;
}

void PG_ListBox::SelectItem(PG_ListBoxBaseItem* item, bool select) {

	if(item == NULL) {
		if(my_selectedItem != NULL) {
			my_selectedItem->Select(false);
			my_selectedItem->Update();
			my_selectedItem = NULL;
		}
		return;
	}

	if(!my_multiselect) {
		if((my_selectedItem != NULL) && (my_selectedItem != item)) {
			my_selectedItem->Select(false);
		}

		my_selectedItem = item;
	}

	Update();
	SendMessage(NULL, MSG_SELECTITEM, GetID(), (unsigned long)item);
	eventSelectItem(item);
}

bool PG_ListBox::eventSelectItem(PG_ListBoxBaseItem* item) {
	return false;
}

bool PG_ListBox::eventMouseButtonUp(const SDL_MouseButtonEvent* button) {
	return true;
}

bool PG_ListBox::eventMouseButtonDown(const SDL_MouseButtonEvent* button) {
	return true;
}

bool PG_ListBox::eventMouseMotion(const SDL_MouseMotionEvent* motion) {
	return true;
}

void PG_ListBox::RemoveAll() {
	my_selectedItem = NULL;
	PG_WidgetList::RemoveAll();
}

void PG_ListBox::DeleteAll() {
	my_selectedItem = NULL;
	PG_WidgetList::DeleteAll();
	ScrollToX(0);
	ScrollToY(0);
	Update();
}

PG_ListBoxBaseItem* PG_ListBox::GetSelectedItem() {
	return my_selectedItem;
}

void PG_ListBox::SetIndent(int indent) {
	my_indent = indent;
}

void PG_ListBox::SelectFirstItem() {
	my_selectindex = 0;
	PG_ListBoxBaseItem* item = (PG_ListBoxBaseItem*)FindWidget(0);

	if(item == NULL) {
		return;
	}

	item->Select();
}

void PG_ListBox::SelectNextItem() {
	PG_ListBoxBaseItem* item = (PG_ListBoxBaseItem*)FindWidget(my_selectindex+1);

	if(item == NULL) {
		return;
	}

	my_selectindex++;
	item->Select();
}

void PG_ListBox::SelectPrevItem() {
	PG_ListBoxBaseItem* item = (PG_ListBoxBaseItem*)FindWidget(my_selectindex-1);

	if(item == NULL) {
		return;
	}

	my_selectindex--;
	item->Select();
}

int PG_ListBox::GetSelectedIndex() {
	return my_selectindex;
}

void PG_ListBox::GetSelectedItems(std::vector<PG_ListBoxBaseItem*>& items) {
	for (Uint16 i = 0; i < GetWidgetCount(); ++i)
		items.push_back((PG_ListBoxBaseItem*)FindWidget(i));	
}
