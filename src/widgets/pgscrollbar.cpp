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
    Update Date:      $Date: 2004/02/28 18:49:06 $
    Source File:      $Source: /sources/paragui/paragui/src/widgets/pgscrollbar.cpp,v $
    CVS/RCS Revision: $Revision: 1.3.6.1.2.4 $
    Status:           $State: Exp $
*/

#include "pgscrollbar.h"
#include "pgapplication.h"

PG_ScrollBar::PG_ScrollBar(PG_Widget* parent, const PG_Rect& r, ScrollDirection direction, int id, const char* style) : PG_ThemeWidget(parent, r, style) {
	sb_direction = direction;

	SetID(id);

	scroll_min = 0;
	scroll_max = 4;
	scroll_current = 0;

	my_linesize = 1;
	my_pagesize = 5;
	//scroll_windowsize = 1;

	if(direction == VERTICAL) {
		position[0].x = 0;
		position[0].y = 0;
		position[0].w = r.my_width;
		position[0].h = r.my_width;

		position[1].x = 0;
		position[1].y = r.my_height-r.my_width;
		position[1].w = r.my_width;
		position[1].h = r.my_width;

		position[2].x = 0;
		position[2].y = r.my_width;
		position[2].w = r.my_width;
		position[2].h = r.my_height-(r.my_width*2+1);
        if ((Sint16)position[2].h < 0)
            position[2].h = 0;
		position[3].x = 0;
		position[3].w = r.my_width;
		position[3].h = (Uint16)((double)position[2].h / 2.0);
		position[3].y = (Uint16)(r.my_width + (((double)position[2].h - (double)position[3].h) / (double)(scroll_max - scroll_min)) * (double)scroll_current);
	} else {
		position[0].x = 0;
		position[0].y = 0;
		position[0].w = r.my_height;
		position[0].h = r.my_height;

		position[1].x = r.my_width - r.my_height;
		position[1].y = 0;
		position[1].w = r.my_height;
		position[1].h = r.my_height;

		position[2].x = r.my_height;
		position[2].y = 0;
		position[2].w = r.my_width-(r.my_height*2+1);
		if ((Sint16)position[2].w < 0) {
		       position[2].w = 0;
		}
		       
		position[2].h = r.my_height;

		position[3].y = 0;
		position[3].w = (Uint16)((double)position[2].w / 2.0);
		position[3].h = r.my_height;
		position[3].x = (Uint16)(r.my_height + (((double)position[2].w - (double)position[3].w) / (double)(scroll_max - scroll_min)) * (double)scroll_current);
	}

	scrollbutton[0] = new PG_Button(this, position[0]);
	scrollbutton[0]->SetID((direction == VERTICAL) ? IDSCROLLBAR_UP : IDSCROLLBAR_LEFT);
	scrollbutton[0]->sigClick.connect(slot(*this, &PG_ScrollBar::handleButtonClick));
	
	scrollbutton[1] = new PG_Button(this, position[1]);
	scrollbutton[1]->SetID((direction == VERTICAL) ? IDSCROLLBAR_DOWN : IDSCROLLBAR_RIGHT);
	scrollbutton[1]->sigClick.connect(slot(*this, &PG_ScrollBar::handleButtonClick));

	dragbutton = new ScrollButton(this, IDSCROLLBAR_DRAG, position[3]);
	dragbutton->sigClick.connect(slot(*this, &PG_ScrollBar::handleButtonClick));

	if(strcmp(style, "Scrollbar") != 0) {
		LoadThemeStyle("Scrollbar");
	}
	LoadThemeStyle(style);
}

PG_ScrollBar::~PG_ScrollBar() {}

void PG_ScrollBar::LoadThemeStyle(const char* widgettype) {

	PG_ThemeWidget::LoadThemeStyle(widgettype, "Scrollbar");

	if(sb_direction == VERTICAL) {
		scrollbutton[0]->LoadThemeStyle(widgettype, "ScrollbarUp");
		scrollbutton[1]->LoadThemeStyle(widgettype, "ScrollbarDown");
	} else {
		scrollbutton[0]->LoadThemeStyle(widgettype, "ScrollbarLeft");
		scrollbutton[1]->LoadThemeStyle(widgettype, "ScrollbarRight");
	}

	dragbutton->LoadThemeStyle(widgettype, "ScrollbarDrag");

	if(sb_direction == VERTICAL) {
		dragbutton->LoadThemeStyle(widgettype, "ScrollbarDragV");
		PG_ThemeWidget::LoadThemeStyle(widgettype, "ScrollbarV");
	} else {
		dragbutton->LoadThemeStyle(widgettype, "ScrollbarDragH");
		PG_ThemeWidget::LoadThemeStyle(widgettype, "ScrollbarH");
	}
}

/**  */
void PG_ScrollBar::eventSizeWidget(Uint16 w, Uint16 h) {

	PG_ThemeWidget::eventSizeWidget(w, h);

	if(sb_direction == VERTICAL) {
		position[0].x = 0;
		position[0].y = 0;
		position[0].w = w;
		position[0].h = w;

		position[1].x = 0;
		position[1].y = abs(h-w);
		position[1].w = w;
		position[1].h = w;

		position[2].x = 0;
		position[2].y = w;
		position[2].w = w;
		position[2].h = abs(h-(w*2+1));

		position[3].x = 0;
		position[3].w = w;
		position[3].h = (position[2].h / 2); //(scroll_max - scroll_min)) * scroll_windowsize;

		if((scroll_max - scroll_min) == 0) {
			position[3].y = position[2].y;
		} else {
			position[3].y = ((position[2].h - position[3].h) / (scroll_max - scroll_min)) * scroll_current;
		}

		scrollbutton[0]->MoveWidget(PG_Rect(0, 0, w, w), false);
		scrollbutton[1]->MoveWidget(PG_Rect(0, abs(h-w), w, w), false);

		dragbutton->SizeWidget(position[3].w, position[3].h, false);
	} else {
		position[0].x = 0;
		position[0].y = 0;
		position[0].w = h;
		position[0].h = h;

		position[1].x = abs(w - h);
		position[1].y = 0;
		position[1].w = h;
		position[1].h = h;

		position[2].x = h;
		position[2].y = 0;
		position[2].w = abs(w-(h*2+1));
		position[2].h = h;

		position[3].y = 0;
		position[3].w = (Uint16)((double)position[2].w / 2.0);
		position[3].h = h;

		if((scroll_max - scroll_min) == 0) {
			position[3].x = position[2].x;
		} else {
			position[3].x = ((position[2].w - position[3].w) / (scroll_max - scroll_min)) * scroll_current;
		}

		scrollbutton[0]->MoveWidget(PG_Rect(0, 0, h, h), false);
		scrollbutton[1]->MoveWidget(PG_Rect(abs(w-h), 0, h, h), false);

		dragbutton->SizeWidget(position[3].w, position[3].h, false);
	}

	SetPosition(scroll_current);
	return;
}

/**  */
bool PG_ScrollBar::eventMouseMotion(const SDL_MouseMotionEvent* motion) {
	return PG_ThemeWidget::eventMouseMotion(motion);
}

/**  */
bool PG_ScrollBar::eventMouseButtonUp(const SDL_MouseButtonEvent* button) {
	int x;
	int y;
	int mx = dragbutton->my_xpos + dragbutton->my_width / 2;
	int my = dragbutton->my_ypos + dragbutton->my_height / 2;

	SDL_GetMouseState(&x, &y);

	switch (button->button) {
		case 1:
			if(sb_direction == VERTICAL) {
				if(y < my) {
					SetPosition(scroll_current - my_pagesize);
				} else {
					SetPosition(scroll_current + my_pagesize);
				}
			} else {
				if(x < mx) {
					SetPosition(scroll_current - my_pagesize);
				} else {
					SetPosition(scroll_current + my_pagesize);
				}
			}

			sigScrollPos(this, scroll_current);
			return true;

		case 4:
			if(scroll_current <= scroll_min + my_linesize) {
				SetPosition(scroll_min);
			} else {
				SetPosition(scroll_current - my_linesize);
			}
			sigScrollPos(this, scroll_current);
			return true;

		case 5:
			SetPosition(scroll_current + my_linesize);
			sigScrollPos(this, scroll_current);
			return true;
	}

	return PG_ThemeWidget::eventMouseButtonUp(button);
}


PG_ScrollBar::ScrollButton::ScrollButton(PG_ScrollBar* parent, int id, const PG_Rect& r) : PG_Button(parent, r) {
	SetID(id);
	my_tickMode = false;
}

PG_ScrollBar::ScrollButton::~ScrollButton() {}

/**  */
bool PG_ScrollBar::ScrollButton::eventMouseMotion(const SDL_MouseMotionEvent* motion) {
	PG_Point p;

	if(GetPressed()) {

		//SDL_GetMouseState(&x, &y);
		p = GetParent()->ScreenToClient(motion->x, motion->y);

		if(GetParent()->sb_direction == VERTICAL) {
			p.y -= offset.y;

			if(p.y < GetParent()->position[2].y) {
				p.y = GetParent()->position[2].y;
			}

			int maxy;
			if(!my_tickMode) {
				maxy = GetParent()->position[2].y + (GetParent()->position[2].h) - my_height;
			} else {
				maxy = GetParent()->my_height - my_height;
			}

			if(p.y > maxy) {
				p.y = maxy;
			}

			MoveWidget(0, p.y);
		} else {
			p.x -= offset.x;

			if(p.x < GetParent()->position[2].x) {
				p.x = GetParent()->position[2].x;
			}

			int maxx;
			if(!my_tickMode) {
				maxx = GetParent()->position[2].x + (GetParent()->position[2].w) - (my_width);
			} else {
				maxx = GetParent()->my_width - my_width;
			}

			if(p.x > maxx) {
				p.x = maxx;
			}

			MoveWidget(p.x, 0);
		}

		my_tempPos = GetPosFromPoint(p);

		int pos = GetPosFromPoint(p);
		if(GetParent()->scroll_current != pos || my_tickMode) {
			GetParent()->scroll_current = pos;
			GetParent()->sigScrollTrack(GetParent(), pos);
		}

	}

	return true; //PG_Button::eventMouseMotion(motion);
}

/**  */
bool PG_ScrollBar::ScrollButton::eventMouseButtonDown(const SDL_MouseButtonEvent* button) {
	int x,y;

	if(button->button == 1) {
		SDL_GetMouseState(&x, &y);
		offset = ScreenToClient(x, y);
	}

	return PG_Button::eventMouseButtonDown(button);
}

/**  */
PG_ScrollBar* PG_ScrollBar::ScrollButton::GetParent() {
	return (PG_ScrollBar*)PG_Button::GetParent();
}

/**  */
void PG_ScrollBar::SetPosition(int pos) {

	if(pos < scroll_min) {
		pos = scroll_min;
	}

	if(pos > scroll_max) {
		pos = scroll_max;
	}

	scroll_current = pos;
	pos -= scroll_min;

	// check if we are currently in a drag operation
	if(dragbutton->GetPressed()) {
		return;
	}

	if(sb_direction == VERTICAL) {
		position[3].x = 0;
		position[3].h = (Uint16)((double)position[2].h / ((double)position[2].h / (double)position[3].h));
		position[3].y = (Uint16)(position[0].h + (((double)position[2].h - (double)position[3].h) / (double)(scroll_max - scroll_min)) * (double)pos);
	} else {
		position[3].y = 0;
		position[3].w = (Uint16)((double)position[2].w / ((double)position[2].w / (double)position[3].w) );
		position[3].x = (Uint16)(position[0].w + (((double)position[2].w - (double)position[3].w) / (double)(scroll_max - scroll_min)) * (double)pos);
	}

	dragbutton->MoveWidget(position[3].x, position[3].y);
}

int PG_ScrollBar::GetPosition() {
	return scroll_current;
}

/**  */
bool PG_ScrollBar::handleButtonClick(PG_Button* button) {

	if(button == scrollbutton[0]) {		// UP | LEFT
		if(scroll_current == scroll_min) {
			return false;
		}
		SetPosition(scroll_current - my_linesize);
		sigScrollPos(this, scroll_current);
		return true;
	}

	if(button == scrollbutton[1]) {		// DOWN | RIGHT
		if(scroll_current == scroll_max) {
			return false;
		}
		SetPosition(scroll_current + my_linesize);
		sigScrollPos(this, scroll_current);
		return true;

	}

	return false;
}

/**  */
bool PG_ScrollBar::eventMouseButtonDown(const SDL_MouseButtonEvent* button) {
	return false;
}

/**  */
bool PG_ScrollBar::ScrollButton::eventMouseButtonUp(const SDL_MouseButtonEvent* button) {
	int pos = GetParent()->scroll_current; //my_tempPos;

	if(button->button != 1) {
		return false;
	}

	PG_Button::eventMouseButtonUp(button);

	//GetParent()->SetPosition(pos);
	GetParent()->sigScrollPos(GetParent(), pos);

	return true;
}

void PG_ScrollBar::ScrollButton::SetTickMode(bool on) {
	my_tickMode = on;
}

/**  */
void PG_ScrollBar::SetWindowSize(Uint32 wsize) {
	/*
	scroll_windowsize = wsize;

	if(scroll_windowsize > (scroll_max - scroll_min)){
		scroll_windowsize = (scroll_max - scroll_min);
}
	*/

	//SizeWidget(displayrect.w, displayrect.h);
}

/**  */
void PG_ScrollBar::SetRange(Uint32 min, Uint32 max) {
	scroll_min = min;
	scroll_max = max;
	if (scroll_current < scroll_min) {
		SetPosition(scroll_min);
	}
	if (scroll_current > scroll_max) {
		SetPosition(scroll_max);
	}
}

int PG_ScrollBar::GetMinRange() {
	return scroll_min;
}

/**  */
int PG_ScrollBar::GetMaxRange() {
	return scroll_max;
}

/**  */
int PG_ScrollBar::ScrollButton::GetPosFromPoint(PG_Point p) {
	Uint32 range = (GetParent()->scroll_max - GetParent()->scroll_min);
	int pos = 0;

	if(p.x < 0)
		p.x = 0;
	if(p.y < 0)
		p.y = 0;

	if(!my_tickMode) {
		if(GetParent()->sb_direction == VERTICAL) {
			pos = (int)( (((double)(p.y - GetParent()->position[3].w)) * (double)(range)) / ( (double)GetParent()->position[2].h - (double)GetParent()->position[3].h) + .5 );
		} else {
			pos = (int)( (((double)(p.x - GetParent()->position[3].h)) * (double)(range)) / ( (double)GetParent()->position[2].w - (double)GetParent()->position[3].w) + .5 );
		}
	} else {
		if(GetParent()->sb_direction == VERTICAL) {
			pos = (int)( (((double)(p.y)) * (double)(range)) / ( (double)GetParent()->position[2].h - (double)GetParent()->position[3].h) + .5 );
		} else {
			pos = (int)( (((double)(p.x)) * (double)(range)) / ( (double)GetParent()->position[2].w - (double)GetParent()->position[3].w) + .5 );
		}
	}

	if(pos < 0)
		pos = 0;

	pos = GetParent()->scroll_min+pos;

	if(pos > GetParent()->scroll_max) {
		pos = GetParent()->scroll_max;
	}

	if(pos < GetParent()->scroll_min) {
		pos = GetParent()->scroll_min;
	}

	return pos;
}

void PG_ScrollBar::SetLineSize(int ls) {
	my_linesize = ls;
}

void PG_ScrollBar::SetPageSize(int ps) {
	my_pagesize = ps;
}
