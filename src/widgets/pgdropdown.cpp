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
    Update Date:      $Date: 2004/03/23 19:06:58 $
    Source File:      $Source: /sources/paragui/paragui/src/widgets/pgdropdown.cpp,v $
    CVS/RCS Revision: $Revision: 1.3.6.3.2.12 $
    Status:           $State: Exp $
*/

#include "pgdropdown.h"
#include "pglog.h"
#include "pglistbox.h"
#include "pglistboxitem.h"

PG_DropDown::PG_DropDown(PG_Widget* parent, const PG_Rect& r, int id, const char* style) : PG_Widget(parent, r),
// needed for AddChild() evaluation - H. C.
my_EditBox(NULL), my_DropButton(NULL), my_DropList(NULL)
{
	PG_Rect rect(0, 0, r.my_width - r.my_height, r.my_height);

	SetID(id);

	my_EditBox = new PG_LineEdit(this, rect, style);
	my_EditBox->sigEditBegin.connect(sigEditBegin.slot());
	my_EditBox->sigEditEnd.connect(sigEditEnd.slot());
	my_EditBox->sigEditReturn.connect(sigEditReturn.slot());

	PG_Rect rbutton(abs(r.my_width - r.my_height), 0, r.my_height, r.my_height);
	my_DropButton = new PG_Button(this, rbutton, NULL, -1, style);
	my_DropButton->SetID(IDDROPDOWN_BOX);
	my_DropButton->sigClick.connect(slot(*this, &PG_DropDown::handleButtonClick));

	PG_Rect rlist(r.my_xpos, r.my_ypos + r.my_height +1, r.my_width, r.my_height /* * 5 */);
	my_DropList = new PG_ListBox(NULL, rlist, style);
	//my_DropList->EnableScrollBar(false);
	my_DropList->sigSelectItem.connect(slot(*this, &PG_DropDown::select_handler));

	LoadThemeStyle(style);
}

PG_DropDown::~PG_DropDown() {
	delete my_DropList;
}

void PG_DropDown::LoadThemeStyle(const char* style) {
	my_EditBox->LoadThemeStyle(style);
	my_DropButton->LoadThemeStyle(style);
	my_DropList->LoadThemeStyle(style);
}

void PG_DropDown::AddChild(PG_Widget* child) {
	if (my_EditBox == NULL || my_DropButton == NULL || my_DropList == NULL) {
		PG_Widget::AddChild(child);	
	}
	else {
		my_DropList->AddChild(child);
		my_DropList->SizeWidget(my_width, my_DropList->GetListHeight() + my_DropList->GetBorderSize()*2);
	}
}

// obsolete -> roadmap
void PG_DropDown::AddItem(const char* text, void* userdata, Uint16 height) {
	Uint16 h = height;

	if(height == 0) {
	    PG_FontEngine::GetTextSize(text, GetFont(), NULL, NULL, NULL, NULL, &h);
	    h += 2;
	}
	
	new PG_ListBoxItem(this, h, text, NULL, userdata);	
	//my_DropList->SizeWidget(my_width, my_DropList->GetListHeight() + my_DropList->GetBorderSize()*2);
}

void PG_DropDown::RemoveAll() {
	my_DropList->RemoveAll();
}

void PG_DropDown::DeleteAll() {
	my_DropList->DeleteAll();
}

void PG_DropDown::eventShow() {
	my_DropList->SetVisible(false);
}

void PG_DropDown::eventHide() {
	my_DropList->Hide();
}

bool PG_DropDown::handleButtonClick(PG_Button* button) {
	if(button->GetID() != IDDROPDOWN_BOX) {
		return false;
	}

	if(my_DropList->IsVisible()) {
		my_DropList->Hide();
	} else {
		my_DropList->MoveRect(my_xpos, my_ypos+my_height);
		my_DropList->Show();
	}

	return true;
}

void PG_DropDown::SetIndent(Uint16 indent) {
	my_DropList->SetIndent(indent);
}

void PG_DropDown::SetEditable(bool edit) {
	my_EditBox->SetEditable(edit);
}

bool PG_DropDown::GetEditable() {
	return my_EditBox->GetEditable();
}

const char* PG_DropDown::GetText() {
	return my_EditBox->GetText();
}

void PG_DropDown::SetText(const char* new_text) {
	my_EditBox->SetText(new_text);
}

bool PG_DropDown::eventSelectItem(PG_ListBoxBaseItem* item) {
	return false;
}

void PG_DropDown::eventSizeWidget(Uint16 w, Uint16 h) {}

void PG_DropDown::eventMoveWidget(int x, int y) {
	if(my_DropList->IsVisible()) {
		my_DropList->Hide();
	}
}

bool PG_DropDown::select_handler(PG_ListBoxBaseItem* item) {
	my_EditBox->SetText(item->GetText());
	item->Select(false);
	my_DropList->SelectItem(NULL);
	my_DropList->Hide();

	eventSelectItem(item);
	sigSelectItem(item);

	return true;
}

bool PG_DropDown::ProcessEvent(const SDL_Event * event, bool bModal) {

	if(bModal && my_DropList->IsVisible()) {
		if(my_DropList->ProcessEvent(event, true)) {
			return true;
		}
	}

	return PG_Widget::ProcessEvent(event, bModal);
}

void PG_DropDown::SelectFirstItem() {
	my_DropList->SelectFirstItem();
}

void PG_DropDown::SelectNextItem() {
	my_DropList->SelectNextItem();
}

void PG_DropDown::SelectPrevItem() {
	my_DropList->SelectPrevItem();
}

void PG_DropDown::SelectItem(const int n) {
	int i;
	
	my_DropList->SelectFirstItem();
	
	for (i=0; i < n; i++)
	  my_DropList->SelectNextItem();
}

Uint16 PG_DropDown::GetIndent() {
	return my_DropList->GetIndent();
}

void PG_DropDown::SetAlignment(PG_Label::TextAlign style) {
	my_DropList->SetAlignment(style);
}

PG_Label::TextAlign PG_DropDown::GetAlignment() {
	return my_DropList->GetAlignment();
}
