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
    Source File:      $Source: /sources/paragui/paragui/src/widgets/pgbutton.cpp,v $
    CVS/RCS Revision: $Revision: 1.3.6.3 $
    Status:           $State: Exp $
*/

#include "pgbutton.h"
#include "pgapplication.h"
#include "pgthemewidget.h"
#include "pglog.h"
#include "pgdraw.h"

struct PG_ButtonDataInternal {
	SDL_Surface* srf_normal;
	SDL_Surface* srf_high;
	SDL_Surface* srf_down;
	SDL_Surface* srf_icon[3];

	bool free_icons;

	bool isPressed;
	bool togglemode;

	PG_Gradient gradState[3];
	SDL_Surface* background[3];
	int backMode[3];
	int backBlend[3];
};

PG_Button::PG_Button(PG_Widget* parent, int id, const PG_Rect& r, const char* text, const char* style) : PG_Widget(parent, r) {
	SetDirtyUpdate(false);

	my_internaldata = new PG_ButtonDataInternal;

	my_internaldata->srf_normal = NULL;
	my_internaldata->srf_high = NULL;
	my_internaldata->srf_down = NULL;

	my_internaldata->srf_icon[0] = NULL;
	my_internaldata->srf_icon[1] = NULL;
	my_internaldata->srf_icon[2] = NULL;

	my_internaldata->free_icons = false;

	SetText(text);

	my_internaldata->togglemode = false;
	my_internaldata->isPressed = false;

	SetID(id);

	my_state = BTN_STATE_NORMAL;

	my_pressShift = 1;

	my_bordersize[0] = 1;
	my_bordersize[1] = 1;
	my_bordersize[2] = 1;

	my_transparency[0] = 0;
	my_transparency[1] = 0;
	my_transparency[2] = 0;

	for(int i=0; i<3; i++) {
		my_internaldata->background[i] = NULL;
		my_internaldata->backMode[i] = BKMODE_TILE;
		my_internaldata->backBlend[i] = 0;
	}

	LoadThemeStyle(style);
}

PG_Button::~PG_Button() {
	FreeSurfaces();
	FreeIcons();
	
	delete my_internaldata;
}

void PG_Button::LoadThemeStyle(const char* widgettype) {
	LoadThemeStyle("Button", "Button");
	LoadThemeStyle(widgettype, "Button");
}

void PG_Button::LoadThemeStyle(const char* widgettype, const char* objectname) {
	int b;
	const char* s = NULL;
	PG_Theme* t = PG_Application::GetTheme();

	b = t->FindProperty(widgettype, objectname, "textcolor");
	if(b != -1)
		SetFontColor(b);

	const char  *iconup = 0, *icondown = 0, *iconover = 0;

	switch (GetID()) {
		case BTN_ID_OK:
			iconup = "ok_icon";
			break;

		case BTN_ID_YES:
			iconup = "yes_icon";
			break;

		case BTN_ID_NO:
			iconup = "no_icon";
			break;

		case BTN_ID_APPLY:
			iconup = "apply_icon";
			break;

		case BTN_ID_CANCEL:
			iconup = "cancel_icon";
			break;

		case BTN_ID_CLOSE:
			iconup = "close_icon";
			break;

		case BTN_ID_HELP:
			iconup = "help_icon";
			break;

		default:
			iconup = "iconup";
			icondown = "icondown";
			iconover = "iconover";
			break;
	}

	SetIcon(
	    t->FindSurface(widgettype, objectname, iconup),
	    t->FindSurface(widgettype, objectname, icondown),
	    t->FindSurface(widgettype, objectname, iconover)
	);

	PG_Gradient* g;
	g = t->FindGradient(widgettype, objectname, "gradient0");
	if(g) {
		my_internaldata->gradState[0] = *g;
	}

	g = t->FindGradient(widgettype, objectname, "gradient1");
	if(g) {
		my_internaldata->gradState[1] = *g;
	}

	g = t->FindGradient(widgettype, objectname, "gradient2");
	if(g) {
		my_internaldata->gradState[2] = *g;
	}

	SetBackground(
	    0,
	    t->FindSurface(widgettype, objectname, "background0"),
	    t->FindProperty(widgettype, objectname, "backmode0")
	);

	SetBackground(
	    1,
	    t->FindSurface(widgettype, objectname, "background1"),
	    t->FindProperty(widgettype, objectname, "backmode1")
	);

	SetBackground(
	    2,
	    t->FindSurface(widgettype, objectname, "background2"),
	    t->FindProperty(widgettype, objectname, "backmode2")
	);

	b = t->FindProperty(widgettype, objectname, "blend0");
	if(b != -1)
		my_internaldata->backBlend[0] = b;

	b = t->FindProperty(widgettype, objectname, "blend1");
	if(b != -1)
		my_internaldata->backBlend[1] = b;

	b = t->FindProperty(widgettype, objectname, "blend2");
	if(b != -1)
		my_internaldata->backBlend[2] = b;

	b = t->FindProperty(widgettype, objectname, "shift");
	if(b != -1)
		my_pressShift = b;

	b = t->FindProperty(widgettype, objectname, "bordersize");
	if(b != -1) {
		SetBorderSize(b, b, b);
	}

	SetBorderSize(
	    t->FindProperty(widgettype, objectname, "bordersize0"),
	    t->FindProperty(widgettype, objectname, "bordersize1"),
	    t->FindProperty(widgettype, objectname, "bordersize2")
	);

	SetTransparency(
	    t->FindProperty(widgettype, objectname, "transparency0"),
	    t->FindProperty(widgettype, objectname, "transparency1"),
	    t->FindProperty(widgettype, objectname, "transparency2")
	);

	s = t->FindString(widgettype, objectname, "label");
	if(s != NULL) {
		SetText(s);
	}

	PG_Widget::LoadThemeStyle(widgettype, objectname);
	SizeWidget(Width(), Height());
}

void PG_Button::SetBorderColor(int b, Uint32 color) {
	my_colorBorder[b][0].r = (color >> 16) & 0xFF;
	my_colorBorder[b][0].g = (color >> 8) & 0xFF;
	my_colorBorder[b][0].b = color & 0xFF;
}

/**  */
void PG_Button::eventSizeWidget(Uint16 w, Uint16 h) {

	FreeSurfaces();

	eventButtonSurface(&(my_internaldata->srf_normal), BTN_STATE_NORMAL, w, h);
	if(my_internaldata->srf_normal) {
		if(my_transparency[0] > 0) {
			SDL_SetAlpha(my_internaldata->srf_normal, SDL_SRCALPHA, 255-my_transparency[0]);
		}
	}

	eventButtonSurface(&(my_internaldata->srf_down), BTN_STATE_PRESSED, w, h);
	if(my_internaldata->srf_down) {
		if(my_transparency[1] > 0) {
			SDL_SetAlpha(my_internaldata->srf_down, SDL_SRCALPHA, 255-my_transparency[1]);
		}
	}

	eventButtonSurface(&(my_internaldata->srf_high), BTN_STATE_HIGH, w, h);
	if(my_internaldata->srf_high) {
		if(my_transparency[2] > 0) {
			SDL_SetAlpha(my_internaldata->srf_high, SDL_SRCALPHA, 255-my_transparency[2]);
		}
	}

	return;
}

/**  */
void PG_Button::FreeSurfaces() {
	PG_ThemeWidget::DeleteThemedSurface(my_internaldata->srf_normal);
	my_internaldata->srf_normal = NULL;

	PG_ThemeWidget::DeleteThemedSurface(my_internaldata->srf_high);
	my_internaldata->srf_high = NULL;

	PG_ThemeWidget::DeleteThemedSurface(my_internaldata->srf_down);
	my_internaldata->srf_down = NULL;
}

void PG_Button::FreeIcons() {

	if(!my_internaldata->free_icons) {
		return;
	}

	if(my_internaldata->srf_icon[0]) {
		PG_Application::UnloadSurface(my_internaldata->srf_icon[0]); // false
		my_internaldata->srf_icon[0] = NULL;
	}

	if(my_internaldata->srf_icon[1]) {
		PG_Application::UnloadSurface(my_internaldata->srf_icon[1]); // false
		my_internaldata->srf_icon[1] = NULL;
	}

	if(my_internaldata->srf_icon[2]) {
		PG_Application::UnloadSurface(my_internaldata->srf_icon[2]); // false
		my_internaldata->srf_icon[2] = NULL;
	}

	my_internaldata->free_icons = false;
}

/**  */
void PG_Button::eventMouseEnter() {
	if (!(my_internaldata->togglemode && my_internaldata->isPressed)) {
		my_state = BTN_STATE_HIGH;
	}

	Update();
	PG_Widget::eventMouseEnter();
}

/**  */
void PG_Button::eventMouseLeave() {

	if(my_state == BTN_STATE_HIGH) {
		(my_internaldata->togglemode && my_internaldata->isPressed) ? my_state = BTN_STATE_PRESSED : my_state = BTN_STATE_NORMAL;
	}

	Update();
	PG_Widget::eventMouseLeave();
}

/**  */
bool PG_Button::eventMouseButtonDown(const SDL_MouseButtonEvent* button) {
	if (!button)
		return false;

	if(button->button == 1) {
		my_state = BTN_STATE_PRESSED;
		SetCapture();

		Update();
		return true;
	}

	return false;
}

/**  */
bool PG_Button::eventMouseButtonUp(const SDL_MouseButtonEvent* button) {
	if (!button)
		return false;

	if(button->button != 1) {
		return false;
	}

	if(my_internaldata->togglemode) {
		if(!my_internaldata->isPressed) {
			my_state = BTN_STATE_PRESSED;
			my_internaldata->isPressed = true;
		} else {
			my_state = BTN_STATE_HIGH;
			my_internaldata->isPressed = false;
		}
	} else {
		my_state = BTN_STATE_NORMAL;
		my_internaldata->isPressed = false;
	}

	if(!IsMouseInside()) {
		my_state = BTN_STATE_NORMAL;
		ReleaseCapture();
		Update();
		return false;
	} else {
		if(!my_internaldata->togglemode) {
			my_state = BTN_STATE_HIGH;
		}
	}

	ReleaseCapture();
	Update();

	SendMessage(GetParent(), MSG_BUTTONCLICK, GetID(), 0);
	return true;
}

/**  */
bool PG_Button::SetIcon2(const char* filenameup, const char* filenamedown, const char* filenameover, Uint32 colorkey) {
	if(!SetIcon2(filenameup, filenamedown, filenameover)) {
		return false;
	}

	if(my_internaldata->srf_icon[0] != NULL) {
		SDL_SetColorKey(my_internaldata->srf_icon[0], SDL_SRCCOLORKEY, colorkey);
	}

	if(my_internaldata->srf_icon[1] != NULL) {
		SDL_SetColorKey(my_internaldata->srf_icon[1], SDL_SRCCOLORKEY, colorkey);
	}

	if(my_internaldata->srf_icon[2] != NULL) {
		SDL_SetColorKey(my_internaldata->srf_icon[2], SDL_SRCCOLORKEY, colorkey);
	}

	return true;
}

bool PG_Button::SetIcon2(const char* filenameup, const char* filenamedown, const char* filenameover) {
	SDL_Surface* icon0 = PG_Application::LoadSurface(filenameup);
	SDL_Surface* icon1 = PG_Application::LoadSurface(filenamedown);
	SDL_Surface* icon2 = PG_Application::LoadSurface(filenameover);

	if(icon0 == NULL) {
		return false;
	}

	FreeIcons();

	my_internaldata->srf_icon[0] = icon0;
	my_internaldata->srf_icon[1] = icon1;
	my_internaldata->srf_icon[2] = icon2;
	my_internaldata->free_icons = true;

	Redraw();
	return true;
}


/**  */
bool PG_Button::SetIcon(const char* filenameup, const char* filenamedown) {
	return SetIcon2(filenameup, filenamedown, NULL);
}

bool PG_Button::SetIcon(const char* filenameup, const char* filenamedown, Uint32 colorkey) {
	return SetIcon2(filenameup, filenamedown, NULL, colorkey);
}

/**  */
bool PG_Button::SetIcon(SDL_Surface* icon_up, SDL_Surface* icon_down,SDL_Surface* icon_over) {

	if(!icon_up && !icon_down && !icon_over) {
		return false;
	}

	FreeIcons();

	my_internaldata->srf_icon[0] = icon_up;
	my_internaldata->srf_icon[1] = icon_down;
	my_internaldata->srf_icon[2] = icon_over;

	my_internaldata->free_icons = false;

	return true;
}

bool PG_Button::SetIcon(SDL_Surface* icon_up, SDL_Surface* icon_down) {
	return SetIcon(icon_up, icon_down, NULL);
}

SDL_Surface* PG_Button::GetIcon(Uint8 num) {
	if (num > 2)
		return 0;
	
	return my_internaldata->srf_icon[num];
}

/**  */
void PG_Button::SetBorderSize(int norm, int pressed, int high) {

	if(norm >= 0) {
		my_bordersize[BTN_STATE_NORMAL] = norm;
	}

	if(pressed >= 0) {
		my_bordersize[BTN_STATE_PRESSED] = pressed;
	}

	if(high >= 0) {
		my_bordersize[BTN_STATE_HIGH] = high;
	}
}

/**  */
void PG_Button::SetToggle(bool bToggle) {
	my_internaldata->togglemode = bToggle;
}

/**  */
void PG_Button::SetPressed(bool pressed) {
	if(!my_internaldata->togglemode)
		return;

	my_internaldata->isPressed = pressed;
	my_state = (my_internaldata->isPressed ? BTN_STATE_PRESSED : BTN_STATE_NORMAL);

	Update();
}

/**  */
void PG_Button::SetTransparency(int norm, int pressed, int high) {
	if(norm >= 0 && norm <= 255) {
		my_transparency[0] = norm;
	}

	if(pressed >= 0 && pressed <= 255) {
		my_transparency[1] = pressed;
	}

	if(high >= 0 && high <= 255) {
		my_transparency[2] = high;
	}
}

/**
 * Set the moving distance of the image when we press on it
 */
void PG_Button::SetShift(int pixelshift) {
	my_pressShift = pixelshift;
}


/**  */
void PG_Button::eventButtonSurface(SDL_Surface** surface, int newstate, Uint16 w, Uint16 h) {
	if (!surface)
		return;

	PG_Rect r(0, 0, w, h);

	// remove the old button surface (if there are no more references)
	PG_ThemeWidget::DeleteThemedSurface(*surface);

	// create a new one
	*surface = PG_ThemeWidget::CreateThemedSurface(
	               r,
	               &my_internaldata->gradState[newstate],
	               my_internaldata->background[newstate],
	               my_internaldata->backMode[newstate],
	               my_internaldata->backBlend[newstate]);
}

/**  */
void PG_Button::SetGradient(int state, PG_Gradient& gradient) {
	my_internaldata->gradState[state] = gradient;
}

void PG_Button::SetBackground(int state, SDL_Surface* background, int mode) {

	if(!background) {
		return;
	}

	my_internaldata->background[state] = background;
	my_internaldata->backMode[state] = mode;
}

/**  */
bool PG_Button::GetPressed() {
	if(my_internaldata->togglemode) {
		return my_internaldata->isPressed;
	} else {
		return (my_state == BTN_STATE_PRESSED);
	}
}

void PG_Button::eventBlit(SDL_Surface* srf, const PG_Rect& src, const PG_Rect& dst) {
	PG_Rect rect = *this;
	PG_Rect r;
	PG_Rect my_src, my_dst;

	Uint8 t = 0;

	// get the right surface for the current state
	switch(my_state) {
		case BTN_STATE_NORMAL:
			if(my_internaldata->srf_normal) {
				t = my_transparency[0];
				srf = my_internaldata->srf_normal;
			}
			break;

		case BTN_STATE_PRESSED:
			if(my_internaldata->srf_down) {
				t = my_transparency[1];
				srf = my_internaldata->srf_down;
			}
			break;

		case BTN_STATE_HIGH:
			if(my_internaldata->srf_high) {
				t = my_transparency[2];
				srf = my_internaldata->srf_high;
			}
			break;
	}

	// blit it

	if(t != 255) {
		SDL_SetAlpha(srf, SDL_SRCALPHA, 255-t);
		PG_Draw::BlitSurface(srf, src, my_srfScreen, dst);
	}

	int shift = (((my_state == BTN_STATE_PRESSED) || (my_internaldata->togglemode && my_internaldata->isPressed)) ? 1 : 0) * my_pressShift;

	r.my_xpos = rect.my_xpos + (rect.my_width >> 1) + shift;
	r.my_ypos = rect.my_ypos + (rect.my_height >> 1) + shift;
	r.my_height = 0;

	// check for icon srf
	//
	//SDL_Surface* iconsrf = (my_state == BTN_STATE_PRESSED) ? ((my_internaldata->srf_icon[1] == 0) ? my_internaldata->srf_icon[0] : my_internaldata->srf_icon[1]) : my_internaldata->srf_icon[0];

	SDL_Surface* iconsrf;
	if(my_state ==  BTN_STATE_PRESSED) {
		if(my_internaldata->srf_icon[1] == 0) {
			iconsrf = my_internaldata->srf_icon[0];
		} else {
			iconsrf = my_internaldata->srf_icon[1];
		}
	} else if(my_state ==BTN_STATE_HIGH) {
		if(my_internaldata->srf_icon[2] == 0) {
			iconsrf = my_internaldata->srf_icon[0];
		} else {
			iconsrf = my_internaldata->srf_icon[2];
		}
	} else {
		iconsrf = my_internaldata->srf_icon[0];
	}

	int tw = my_width;

	if(iconsrf) {

		int dx = my_text.empty() ? (rect.my_width - iconsrf->w) >> 1 : 3;
		int dy = (rect.my_height - iconsrf->h) >> 1;

		r.my_xpos = rect.my_xpos + dx + shift;
		r.my_ypos = rect.my_ypos + dy + shift;
		r.my_width = iconsrf->w;
		r.my_height = iconsrf->h;

		// calc new cliprect for icon
		GetClipRects(my_src, my_dst, r);

		// blit the icon
		PG_Draw::BlitSurface(iconsrf, my_src, my_srfScreen, my_dst);

		tw -= (iconsrf->w + 3);
	}

	// draw the text
	if(!my_text.empty()) {
		Uint16 w, h;
		GetTextSize(w, h);

		int tx = ((tw - w)/2) + shift;
		int ty = ((my_height - h)/2) + shift;

		if (iconsrf /*&& tx < (iconsrf->w + 3)*/)
			tx += iconsrf->w + 3;

		DrawText(tx, ty, my_text.c_str());
	}

	int i0, i1;

	if(!my_internaldata->togglemode) {
		i0 = (my_state == BTN_STATE_PRESSED) ? 1 : 0;
		i1 = (my_state == BTN_STATE_PRESSED) ? 0 : 1;
	} else {
		i0 = (my_internaldata->isPressed) ? 1 : 0;
		i1 = (my_internaldata->isPressed) ? 0 : 1;
	}

	DrawBorder(PG_Rect(0, 0, Width(), Height()), my_bordersize[my_state], i1);
}

void PG_Button::SetBlendLevel(int mode, Uint8 blend) {
	my_internaldata->backBlend[mode] = blend;
}

Uint8 PG_Button::GetBlendLevel(int mode) {
	return my_internaldata->backBlend[mode];
}
