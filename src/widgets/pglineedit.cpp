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
    Update Date:      $Date: 2003/01/04 21:13:41 $
    Source File:      $Source: /sources/paragui/paragui/src/widgets/pglineedit.cpp,v $
    CVS/RCS Revision: $Revision: 1.3.6.1 $
    Status:           $State: Exp $
*/

#include "pglineedit.h"
#include "pgapplication.h"
#include <cstring>
#include <stdarg.h>

PG_LineEdit::PG_LineEdit(PG_Widget* parent, const PG_Rect& r, const char* style, int _my_maximumLength) : PG_ThemeWidget(parent, r, style) {

	my_buffer = "";
	my_cursorPosition = 0;
	my_maximumLength  = _my_maximumLength;
	my_isCursorVisible = false;
	my_isEditable = true;
	my_offsetX = 0;
	my_srfTextCursor = NULL;
	my_startMark = -1;
	my_endMark   = -1;
	my_passchar = 0;

	LoadThemeStyle("LineEdit");
}

PG_LineEdit::~PG_LineEdit() {
}

void PG_LineEdit::eventBlit(SDL_Surface* surface, const PG_Rect& src, const PG_Rect& dst) {
	PG_ThemeWidget::eventBlit(surface, src, dst);

	DrawText(dst);
}

void PG_LineEdit::DrawText(const PG_Rect& dst) {
	int x, y;

	x = 3;
	y = (my_height - GetFontHeight()) >> 1;

	// should we draw the cursor ?
	if(my_isCursorVisible) {

		if(my_cursorPosition < my_offsetX) {
			my_offsetX = my_cursorPosition;
		}

		// check if my_cursorPosition is visible
		if(x + GetCursorXPos() > (my_width - 2)) {
			my_offsetX++;
			DrawText(dst);
			return;
		}

		DrawTextCursor();
	}

	// draw text
	PG_Widget::DrawText(x, y, GetDrawText());
}

void PG_LineEdit::DrawTextCursor() {
	int x = my_xpos + 1;
	int y = my_ypos + 1;
	int h = my_height - 2;

	// draw simple cursor
	if(my_srfTextCursor == NULL) {
		DrawVLine(GetCursorXPos() + 2, 2, h-4, 0,0,0);
	}

	// draw a nice cursor bitmap
	else {
		PG_Rect src, dst;
		PG_Rect rect(x + GetCursorXPos(), y + (Height() - my_srfTextCursor->h)/2, my_srfTextCursor->w, my_srfTextCursor->h);
		GetClipRects(src, dst, rect);
		PG_Widget::eventBlit(my_srfTextCursor, src, dst);
	}

}

Uint16 PG_LineEdit::GetCursorXPos() {
	Uint16 w;
	const char* drawtext = GetDrawText();
	int newpos = my_cursorPosition - my_offsetX;

	if(newpos == 0)
		return 0;

	if(drawtext[0] == 0)
		return 0;

	char* temp = new char[newpos+1];

	strncpy(temp, drawtext, newpos);
	temp[newpos] = 0;

	PG_FontEngine::GetTextSize(temp, GetFont(), &w);
	delete[] temp;

	return w;
}

int PG_LineEdit::GetCursorPosFromScreen(int x, int y) {
	int min_dist = 1000000;
	int min_pos = 0;
	int dist = 0;
	int old = my_cursorPosition;

	// loop all cursor positions
	for(Uint16 c=my_offsetX; c<=my_text.size(); c++) {

		my_cursorPosition = c;

		// get distance between screen point and cursor position
		dist = abs(x - (my_xpos + 3 + GetCursorXPos()));

		// store the minimum distance
		if(dist < min_dist) {
			min_dist = dist;
			min_pos = c;
		}
	}

	my_cursorPosition = old;

	// result should be stored in min_pos
	return min_pos;
}

const char* PG_LineEdit::GetDrawText() {
	static string passtext;

	if (my_passchar == 0)
		return my_text.c_str()+my_offsetX;
	passtext = "";

	for (unsigned int i=0;i<my_text.length();i++)
		passtext += my_passchar;

	return passtext.c_str()+my_offsetX;
}

void PG_LineEdit::EditBegin() {
	SetInputFocus();
	my_isCursorVisible = true;
	Update();

	SendMessage(this, MSG_EDITBEGIN, GetID(), 0);
	eventEditBegin(GetID(), this, 0,0);
}

void PG_LineEdit::EditEnd() {
	my_offsetX = 0;
	my_cursorPosition = 0;
	my_isCursorVisible = false;
	Update();
	ReleaseInputFocus();

	SendMessage(this, MSG_EDITEND, GetID(), 0);
	eventEditEnd(GetID(), this, 0,0);
}

bool PG_LineEdit::eventKeyDown(const SDL_KeyboardEvent* key) {
	char c;

	if(!my_isCursorVisible) {
		return false;
	}

	SDL_KeyboardEvent key_copy = *key; // copy key structure
	TranslateNumpadKeys(&key_copy);
	// from now, we use key_copy which was copied or translated from key

    //
    // Maybe it would be a good idea to support the windoze CUI keyboard
    // bindings as well?
    //  /grendel, Nov 06
    //
	if(key_copy.keysym.mod & KMOD_CTRL) {
		// Handle std emacs bindings
		switch(key_copy.keysym.sym) {
			case SDLK_a: // Beginning of Line
				SetCursorPos(0);
				return true;

			case SDLK_e: // End of Line
				SetCursorPos(my_text.length());
				return true;

			case SDLK_SPACE: // Set mark start
				StartMark(my_cursorPosition);
				return true;

			case SDLK_w: // Cut from start mark
				if(!my_isEditable) {
					return false;
				}
				EndMark(my_cursorPosition);
				CopyText(true);
				return true;

			case SDLK_k: // Delete all after point
				if(!my_isEditable) {
					return false;
				}
				StartMark(my_cursorPosition);
				EndMark(my_text.length());
				CopyText(true);
				return true;

			case SDLK_y: // Paste buffer at point
				if(!my_isEditable) {
					return false;
				}
				PasteText(my_cursorPosition);
				return true;

			case SDLK_f: // Forward char
				SetCursorPos(++my_cursorPosition);
				return true;

			case SDLK_b: // Backward char
				SetCursorPos(--my_cursorPosition);
				return true;

			case SDLK_d:
				if(!my_isEditable) {
					return false;
				}
				if(eventFilterKey(key)) {
					return false;
				}
				SendDel();
				return true;

			default:
				return false;
		}
	} else if(key_copy.keysym.mod & (KMOD_ALT | KMOD_META)) {

		// Handle std emacs bindings
		switch(key_copy.keysym.sym) {

			case SDLK_w: // Copy from start mark
				EndMark(my_cursorPosition);
				CopyText();
				return true;

			default:
				return false;
		}
	}

	switch(key_copy.keysym.sym) {

		case SDLK_TAB:
			return false;

		case SDLK_LEFT:

			SetCursorPos(--my_cursorPosition);
			return true;

		case SDLK_RIGHT:

			SetCursorPos(++my_cursorPosition);
			return true;

		case SDLK_RETURN:
			if(!my_isEditable) {
				return false;
			}
			EditEnd();
			SendMessage(this, MSG_RETURN, GetID(), 0);
			return true;

		case SDLK_HOME:
			SetCursorPos(0);
			return true;

		case SDLK_END:
			SetCursorPos(my_text.length());
			return true;

		case SDLK_BACKSPACE:
			if(!my_isEditable) {
				return false;
			}
			if(eventFilterKey(key)) {
				return false;
			}
			SendBackspace();
			return true;

		case SDLK_DELETE:
			if(!my_isEditable) {
				return false;
			}
			if(eventFilterKey(key)) {
				return false;
			}
			SendDel();
			return true;

		default:
			if(!my_isEditable) {
				return false;
			}

			if(key_copy.keysym.unicode == 0) {
				return false;
			}

			if(eventFilterKey(key)) {
				return false;
			}

			if ((key_copy.keysym.unicode & 0xFF80) == 0) {
				c = key_copy.keysym.unicode & 0x7F;

				if(!IsValidKey(c)) {
					return false;
				}

				InsertChar(&c);
				return true;
			} else {
				c = key_copy.keysym.unicode & 0xFF;

				if(!IsValidKey(c)) {
					return false;
				}

				InsertChar(&c);
				return true;
			}

			return false;
	}

	return false;
}

void PG_LineEdit::eventInputFocusLost(PG_MessageObject* newfocus) {
	EditEnd();
}

void PG_LineEdit::SetCursorPos(int p) {

	if(p < 0) {
		p = 0;
	}

	if(p > (int)my_text.size()) {
		p = (int)my_text.size();
	}

	if (p > my_maximumLength) {
		p = my_maximumLength;
	}

	my_cursorPosition = p;

	if(my_offsetX > my_cursorPosition) {
		my_offsetX = my_cursorPosition;
	}

	Update();
}

int PG_LineEdit::GetCursorPos() {
	return my_cursorPosition;
}

bool PG_LineEdit::eventMouseButtonDown(const SDL_MouseButtonEvent* button) {
	if(!my_isEditable) {
		return false;
	}

	if(!my_isCursorVisible) {
		EditBegin();
	}

	int p = GetCursorPosFromScreen(button->x, button->y);
	SetCursorPos(p);
	return true;
}

void PG_LineEdit::InsertChar(const char* c) {
	if (my_cursorPosition < my_maximumLength) {
		my_text.insert(my_cursorPosition, c, 1);
		SetCursorPos(++my_cursorPosition);
	}
}

/** */
void PG_LineEdit::DeleteChar(Uint16 pos) {
	my_text.erase(pos, 1);
}

/** */
void PG_LineEdit::StartMark(Uint16 pos) {
	my_startMark = pos;
	my_endMark   = -1;
}

/** */
void PG_LineEdit::EndMark(Uint16 pos) {
	my_endMark = pos;
}

/** */
void PG_LineEdit::CopyText(bool del) {
	int start, len;
	if(my_endMark == -1) {
		my_endMark = my_cursorPosition;
	}
	if(my_startMark == my_endMark ||
	        my_startMark == -1) {
		// No text is marked
		return;
	}
	if(my_startMark > my_endMark) {
		start = my_endMark;
		len   = my_startMark - start;
	} else {
		start = my_startMark;
		len   = my_endMark - start;
	}
	my_buffer = my_text.substr(start, len);
	if(del) {
		my_text.erase(start, len);
		SetCursorPos(my_cursorPosition); // If end was > start
		Update();
	}
	my_startMark = my_endMark = -1; // Reset mark
}

/** */
void PG_LineEdit::PasteText(Uint16 pos) {
	if(!my_buffer.length()) {
		return;
	}
	my_text.insert(pos, my_buffer);
	my_cursorPosition += my_buffer.length();
	my_startMark = my_endMark = -1;
	Update();
}

void PG_LineEdit::SetText(const char* new_text) {
	my_cursorPosition = 0;
	my_offsetX = 0;
	PG_Widget::SetText(new_text);
}

void PG_LineEdit::eventEditBegin(int id, PG_Widget* widget, unsigned long data, void *clientdata) {}

void PG_LineEdit::eventEditEnd(int id, PG_Widget* widget, unsigned long data, void *clientdata) {}

bool PG_LineEdit::IsCursorVisible() {
	return my_isCursorVisible;
}

bool PG_LineEdit::eventFilterKey(const SDL_KeyboardEvent* key) {
	return false;
}

void PG_LineEdit::LoadThemeStyle(const char* widgettype) {
	PG_ThemeWidget::LoadThemeStyle(widgettype, "LineEdit");
	LoadThemeStyle(widgettype, "LineEdit");
}

void PG_LineEdit::LoadThemeStyle(const char* widgettype, const char* objectname) {
	PG_Theme* t = PG_Application::GetTheme();

	my_srfTextCursor = t->FindSurface(widgettype, objectname, "textcursor");

	const char* keys = t->FindString(widgettype, objectname, "validkeys");

	if(keys != NULL) {
		SetValidKeys(keys);
	}
}

void PG_LineEdit::SendChar(char c) {
	if(!IsValidKey(c)) {
		return;
	}

	InsertChar(&c);
}

void PG_LineEdit::SendDel() {
	DeleteChar(my_cursorPosition);
	SetCursorPos(my_cursorPosition);
}

void PG_LineEdit::SendBackspace() {
	if(my_cursorPosition > 0) {
		DeleteChar(my_cursorPosition-1);
		SetCursorPos(--my_cursorPosition);
	}
}

void PG_LineEdit::SetValidKeys(const char* keys) {
	my_validkeys = keys;
}

bool PG_LineEdit::IsValidKey(char c) {
	if(my_validkeys.size() == 0) {
		return true;
	}

	return (my_validkeys.find(c) != string::npos);
}

void PG_LineEdit::eventHide() {
	if(my_isCursorVisible) {
		EditEnd();
	}
}

void PG_LineEdit::SetEditable(bool edit) {
	my_isEditable = edit;
}

bool PG_LineEdit::GetEditable() {
	return my_isEditable;
}

bool PG_LineEdit::Action(PG_ACTION action) {

	switch(action) {
		case PG_ACT_OK:
			EditBegin();
			return true;
		case PG_ACT_CANCEL:
			EditEnd();
			return true;
		default:
			break;
	}

	return PG_Widget::Action(action);
}

void PG_LineEdit::SetPassHidden(char passchar) {
	my_passchar = passchar;
}

char PG_LineEdit::GetPassHidden(void) {
	return my_passchar;
}
