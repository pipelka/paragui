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
    Update Date:      $Date: 2002/04/15 13:35:36 $
    Source File:      $Source: /sources/paragui/paragui/src/widgets/Attic/pgbuttongroup.cpp,v $
    CVS/RCS Revision: $Revision: 1.3 $
    Status:           $State: Exp $
*/

#include "pgbuttongroup.h"
#include "pglog.h"

PG_ButtonGroup::PG_ButtonGroup(PG_Widget* parent, int id, const PG_Rect& r, int x, int y, int d) : PG_ThemeWidget(parent, r),
btnArray(NULL),
actArray(NULL),
count_x(x),
count_y(y),
count_d(d),
current_depth(0)
{
	SetID(id);
	PG_Rect br;
    bool    warn = false;
    
    //
    // It is better to enforce some value than to have either SIGFPE or
    // SIGSEGV later on...
    //
    if (!x) {
        x = 1;
        warn = true;
    }
    
    if (!y) {
        y = 1;
        warn = true;
    }
    
    if (!d) {
        d = 1;
        warn = true;
    }

    if (warn)
        PG_LogWRN("PG_ButtonGroup - any of x, y, d set to default value");
    
    int dw = r.w / x;
	int dh = r.h / y;

	btnArray = new PG_Button*[x * y * d];
	actArray = new Uint8[x * y * d];

    int i = 0;
	for(int bd=0; bd<d; bd++) {
		for(int by=0; by<y; by++) {
			for(int bx=0; bx<x; bx++) {

				br.x = dw*bx;
				br.y = dh*by;
				br.w = dw;
				br.h = dh;

				i = GetIndex(bx, by, bd);
				actArray[i] = 0;
				btnArray[i] = new PG_Button(this, id*1000+i, br);
			}
		}
	}
}

PG_ButtonGroup::~PG_ButtonGroup() {
	if(btnArray)
		delete[] btnArray;

	if(actArray)
		delete[] actArray;
}


void PG_ButtonGroup::Show() {
	int i=0;

	SetVisible(true);

	for(int y=0; y<count_y; y++)
		for(int x=0; x<count_x; x++) {
			i = GetIndex(x, y, current_depth);
			if(actArray[i] == 0) {			// make button invisible
				if(btnArray[i]->IsVisible()) {
					btnArray[i]->Hide();
				}
			}

			if(actArray[i] == 1) {			// make button visible
				if(!btnArray[i]->IsVisible()) {
					btnArray[i]->Show();
				}
			}
		}

	return;
}

inline int PG_ButtonGroup::GetIndex(int x, int y, int d) {
	return x + y*count_x + d*count_x*count_y;
}

void PG_ButtonGroup::Activate(int x, int y, int d) {
	actArray[GetIndex(x,y,d)] = 1;
}

void PG_ButtonGroup::Deactivate(int x, int y, int d) {
	actArray[GetIndex(x,y,d)] = 0;
}

void PG_ButtonGroup::SwitchTo(int d) {
	int i=0;

	if(current_depth != d) {
		for(int y=0; y<count_y; y++)
			for(int x=0; x<count_x; x++) {
				i = GetIndex(x,y,current_depth);
				btnArray[i]->Hide();
			}

		current_depth = d;
	}
	Show();
}

void PG_ButtonGroup::BlendTo(int d) {
	int i;

	for(i=0; i<255; i+=10) {
		SetChildTransparency(i);
		SDL_Delay(5);
	}
	SetChildTransparency(255);

	SwitchTo(d);

	for(i=0; i<255; i+=10) {
		SetChildTransparency(255-i);
		SDL_Delay(5);
	}
	SetChildTransparency(0);

}

void PG_ButtonGroup::SetText(int x, int y, int d, char* text) {
	int i = GetIndex(x,y,d);
	btnArray[i]->SetText(text);
	btnArray[i]->Redraw(false);
}

PG_Button* PG_ButtonGroup::GetButton(int x, int y, int d) {
	return btnArray[GetIndex(x,y,d)];
}

bool PG_ButtonGroup::eventButtonClick(int id, PG_Widget* widget) {
	int x,y,d;
	GetPosFromId(id, x,y,d);

	return OnButton(x,y,d, widget);
}

bool PG_ButtonGroup::OnButton(int x, int y, int d, PG_Widget* widget) {
	return false;
}

void PG_ButtonGroup::GetPosFromId(int id, int& x, int& y, int& d) {
	int index = id - GetID()*1000;

	d = index / (count_x*count_y);
	y = (index - d*count_x*count_y) / count_x;
	x = index - (y*count_x + d*count_x*count_y);
}
