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
    Update Date:      $Date: 2003/04/16 09:21:39 $
    Source File:      $Source: /sources/paragui/paragui/src/widgets/pgwindow.cpp,v $
    CVS/RCS Revision: $Revision: 1.3.6.7 $
    Status:           $State: Exp $
*/

#include "pgwindow.h"
#include "pgapplication.h"
#include <cstring>

PG_Window::PG_Window(PG_Widget* parent, const PG_Rect& r, const char* windowtext, Uint32 flags, const char* style, int heightTitlebar) : PG_ThemeWidget(parent, r) {

	my_moveMode = false;
	my_heightTitlebar = heightTitlebar;
	my_showCloseButton = flags & WF_SHOW_CLOSE;
	my_showMinimizeButton = flags & WF_SHOW_MINIMIZE;

	PG_Rect rb;

	my_titlebar = new PG_ThemeWidget(this, PG_Rect(0, 0, my_width, my_heightTitlebar), style);
	my_titlebar->EnableReceiver(false);

	my_labelTitle = new PG_Label(my_titlebar, PG_Rect(0, 0, my_width, my_heightTitlebar), windowtext, style);
	my_labelTitle->SetAlignment(PG_TA_CENTER);

	my_buttonClose = new PG_Button(this, PG_WINDOW_CLOSE, rb, NULL);
	my_buttonMinimize = new PG_Button(this, PG_WINDOW_MINIMIZE, rb, NULL);

	LoadThemeStyle(style);
}

PG_Window::~PG_Window() {
}

void PG_Window::SetTitle(const char* title, int alignment) {
	my_labelTitle->SetAlignment(alignment);
	my_labelTitle->SetText(title);

	if (my_showCloseButton)
		my_buttonClose->Update();

	if (my_showMinimizeButton)
		my_buttonMinimize->Update();		
}

const char* PG_Window::GetTitle() {
	return my_labelTitle->GetText();
}

void PG_Window::LoadThemeStyle(const char* widgettype) {
	PG_Theme* t = PG_Application::GetTheme();
	int b;

	PG_ThemeWidget::LoadThemeStyle(widgettype, "Window");

	my_titlebar->LoadThemeStyle(widgettype, "Titlebar");

	b = t->FindProperty(widgettype, "Titlebar", "height");
	if(b != -1)
		my_heightTitlebar = b;

	my_titlebar->SizeWidget(my_width, my_heightTitlebar);
	my_labelTitle->SizeWidget(my_width, my_heightTitlebar);

	long c = t->FindProperty(widgettype, "Titlebar", "textcolor");
	if(c != -1)
		SetColorTitlebar(c);

	b = t->FindProperty(widgettype, "Titlebar", "showclosebutton");
	if(b != -1)
		my_showCloseButton = (b == 1);

	my_buttonClose->LoadThemeStyle(widgettype, "CloseButton");

	b = t->FindProperty(widgettype, "Titlebar", "showminimizebutton");
	if(b != -1)
		my_showMinimizeButton = (b == 1);

	my_buttonMinimize->LoadThemeStyle(widgettype, "MinimizeButton");

	my_buttonClose->MoveWidget(PG_Rect(my_width - my_heightTitlebar, 0, my_heightTitlebar, my_heightTitlebar));
	my_buttonMinimize->MoveWidget(PG_Rect(0, 0, my_heightTitlebar, my_heightTitlebar));
}

void PG_Window::eventSizeWidget(Uint16 w, Uint16 h) {
	my_titlebar->SizeWidget(w, my_heightTitlebar);
	my_labelTitle->SizeWidget(w, my_heightTitlebar);

	my_buttonClose->MoveWidget(PG_Rect(w - my_heightTitlebar, 0, my_heightTitlebar, my_heightTitlebar));
	my_buttonMinimize->MoveWidget(PG_Rect(0, 0, my_heightTitlebar, my_heightTitlebar));

	PG_ThemeWidget::eventSizeWidget(w, h);
}

void PG_Window::eventBlit(SDL_Surface* srf, const PG_Rect& src, const PG_Rect& dst) {
	PG_Rect my_src;
	PG_Rect my_dst;

	PG_ThemeWidget::eventBlit(srf, src, dst);

	PG_Rect client(0, my_heightTitlebar, my_width, my_height-my_heightTitlebar);
	DrawBorder(client, my_bordersize);

	client.my_xpos++;
	client.my_ypos++;
	client.my_width -= 2;
	client.my_height -= 2;

	DrawBorder(client, my_bordersize, false);
}

bool PG_Window::eventMouseButtonDown(const SDL_MouseButtonEvent* button) {
	PG_Rect ta(*this);
	ta.my_width = my_titlebar->w;
	ta.my_height = my_titlebar->h;

	int x,y;
	x = button->x;
	y = button->y;

	if((ta.my_xpos <= x) && (x <= ta.my_xpos + ta.my_width)) {
		if((ta.my_ypos <= y) && (y <= ta.my_ypos + ta.my_height)) {
			my_moveMode = true;
			my_moveDelta.x = ta.my_xpos - x;
			my_moveDelta.y = ta.my_ypos - y;
			Show();
			SetCapture();
			return true;
		}
	}

	Show();
	return false; //PG_Widget::eventMouseButtonDown(button);
}

bool PG_Window::eventMouseButtonUp(const SDL_MouseButtonEvent* button) {
	int x,y;

	x = button->x;
	y = button->y;

	x += my_moveDelta.x;
	y += my_moveDelta.y;

	if(x < 0)
		x=0;
	if(y < 0)
		y=0;
	if(x > (my_srfScreen->w - my_width - 1))
		x = (my_srfScreen->w - my_width - 1);
	if(y > (my_srfScreen->h - my_height - 1))
		y = (my_srfScreen->h - my_height -1);

	if(my_moveMode) {
		my_moveMode = false;
		ReleaseCapture();
		return true;
	}

	return false; //PG_Widget::eventMouseButtonUp(button);
}

bool PG_Window::eventMouseMotion(const SDL_MouseMotionEvent* motion) {
	if(!my_moveMode) {
		return PG_Widget::eventMouseMotion(motion);
	}

	int x,y;
	x = motion->x;
	y = motion->y;

	x += my_moveDelta.x;
	y += my_moveDelta.y;

	if(GetParent() != NULL) {  // Not a top-level-widget
		PG_Point pos = GetParent()->ScreenToClient(x,y);
		x = pos.x;
		y = pos.y;         // Should not be moved out of the parent:
		if(x >= GetParent()->Width() - my_width - 1)
			x = GetParent()->Width() - my_width - 1;
		if(y >= GetParent()->Height() - my_height -1)
			y = GetParent()->Height() - my_height -1;
	} else {                     // A top-level-widget
		if(x > (my_srfScreen->w - my_width - 1))
			x = (my_srfScreen->w - my_width - 1);
		if(y > (my_srfScreen->h - my_height - 1))
			y = (my_srfScreen->h - my_height - 1);
	}

	if(x < 0)
		x=0;
	if(y < 0)
		y=0;

	MoveWidget(x,y);
	return true;
}

bool PG_Window::eventButtonClick(int id, PG_Widget* widget) {
	switch(id) {
		// close window
		case PG_WINDOW_CLOSE:
			Hide();
			SendMessage(NULL, MSG_WINDOWCLOSE, GetID(), 0);
			return true;

		// minimize window
		case PG_WINDOW_MINIMIZE:
			Hide();
			SendMessage(NULL, MSG_WINDOWMINIMIZE, GetID(), 0);
			return true;
	}

	return false;
}

void PG_Window::SetColorTitlebar(const SDL_Color& c) {
	my_labelTitle->SetFontColor(c);
}

void PG_Window::SetColorTitlebar(Uint32 color) {
	SDL_Color c;
	c.r = (color >> 16) & 0xFF;
	c.g = (color >> 8)  & 0xFF;
	c.b = color & 0xFF;

	my_labelTitle->SetFontColor(c);
}

void PG_Window::SetIcon(const char* filename)
{
	my_labelTitle->SetIcon(filename);
}
	
void PG_Window::SetIcon(SDL_Surface* icon)
{
	my_labelTitle->SetIcon(icon);
}

void PG_Window::eventShow() {
	my_buttonClose->SetVisible(my_showCloseButton);
	my_buttonMinimize->SetVisible(my_showMinimizeButton);
}
