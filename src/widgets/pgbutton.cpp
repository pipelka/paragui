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
    Update Date:      $Date: 2003/12/02 15:27:59 $
    Source File:      $Source: /sources/paragui/paragui/src/widgets/pgbutton.cpp,v $
    CVS/RCS Revision: $Revision: 1.3.6.3.2.4 $
    Status:           $State: Exp $
*/

#include "pgbutton.h"
#include "pgapplication.h"
#include "pgthemewidget.h"
#include "pglog.h"
#include "pgdraw.h"
#include "pgtheme.h"

struct PG_ButtonDataInternal {
	bool free_icons;

	bool isPressed;
	bool togglemode;
	PG_Button::STATE my_state;
	int my_pressShift;

	std::map<PG_Button::STATE, SDL_Surface*> srf;
	std::map<PG_Button::STATE, SDL_Surface*> srf_icon;
	std::map<PG_Button::STATE, Uint8> my_bordersize;
	std::map<PG_Button::STATE, Uint8> my_transparency;
	std::map<PG_Button::STATE, PG_Gradient> gradState;
	std::map<PG_Button::STATE, SDL_Surface*> background;
	std::map<PG_Button::STATE, int> backMode;
	std::map<PG_Button::STATE,int> backBlend;
};

PG_Button::PG_Button(PG_Widget* parent, int id, const PG_Rect& r, const char* text, const char* style) : PG_Widget(parent, r) {
	SetDirtyUpdate(false);

	_mid = new PG_ButtonDataInternal;

	_mid->srf[UNPRESSED] = NULL;
	_mid->srf[HIGHLITED] = NULL;
	_mid->srf[PRESSED] = NULL;

	_mid->srf_icon[UNPRESSED] = NULL;
	_mid->srf_icon[HIGHLITED] = NULL;
	_mid->srf_icon[PRESSED] = NULL;

	_mid->free_icons = false;

	SetText(text);

	_mid->togglemode = false;
	_mid->isPressed = false;

	SetID(id);

	_mid->my_state = UNPRESSED;

	_mid->my_pressShift = 1;

	_mid->my_bordersize[UNPRESSED] = 1;
	_mid->my_bordersize[HIGHLITED] = 1;
	_mid->my_bordersize[PRESSED] = 1;

	_mid->my_transparency[UNPRESSED] = 0;
	_mid->my_transparency[HIGHLITED] = 0;
	_mid->my_transparency[PRESSED] = 0;

	_mid->background[UNPRESSED] = NULL;
	_mid->background[HIGHLITED] = NULL;
	_mid->background[PRESSED] = NULL;
	_mid->backMode[UNPRESSED] = BKMODE_TILE;
	_mid->backMode[HIGHLITED] = BKMODE_TILE;
	_mid->backMode[PRESSED] = BKMODE_TILE;
	_mid->backBlend[UNPRESSED] = 0;
	_mid->backBlend[HIGHLITED] = 0;
	_mid->backBlend[PRESSED] = 0;

	LoadThemeStyle(style);
}

PG_Button::~PG_Button() {
	FreeSurfaces();
	FreeIcons();
	
	delete _mid;
}

void PG_Button::LoadThemeStyle(const char* widgettype) {
	LoadThemeStyle("Button", "Button");
	LoadThemeStyle(widgettype, "Button");
}

void PG_Button::LoadThemeStyle(const char* widgettype, const char* objectname) {
	const char* s = NULL;
	PG_Theme* t = PG_Application::GetTheme();

	PG_Color fontcolor = GetFontColor();
	t->GetColor(widgettype, objectname, "textcolor", fontcolor);
	SetFontColor(fontcolor);

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
		_mid->gradState[UNPRESSED] = *g;
	}

	g = t->FindGradient(widgettype, objectname, "gradient1");
	if(g) {
		_mid->gradState[HIGHLITED] = *g;
	}

	g = t->FindGradient(widgettype, objectname, "gradient2");
	if(g) {
		_mid->gradState[PRESSED] = *g;
	}

	SDL_Surface* background;
	background = t->FindSurface(widgettype, objectname, "background0");
	t->GetProperty(widgettype, objectname, "backmode0", _mid->backMode[UNPRESSED]);
	SetBackground(UNPRESSED, background, _mid->backMode[UNPRESSED]);

	background = t->FindSurface(widgettype, objectname, "background1");
	t->GetProperty(widgettype, objectname, "backmode1", _mid->backMode[PRESSED]);
	SetBackground(PRESSED, background, _mid->backMode[PRESSED]);

	background = t->FindSurface(widgettype, objectname, "background2");
	t->GetProperty(widgettype, objectname, "backmode2", _mid->backMode[HIGHLITED]);
	SetBackground(HIGHLITED, background, _mid->backMode[HIGHLITED]);

	t->GetProperty(widgettype, objectname, "blend0", _mid->backBlend[UNPRESSED]);
	t->GetProperty(widgettype, objectname, "blend1", _mid->backBlend[PRESSED]);
	t->GetProperty(widgettype, objectname, "blend2", _mid->backBlend[HIGHLITED]);

	t->GetProperty(widgettype, objectname, "shift", _mid->my_pressShift);

	t->GetProperty(widgettype, objectname, "bordersize", _mid->my_bordersize[UNPRESSED]);
	t->GetProperty(widgettype, objectname, "bordersize", _mid->my_bordersize[PRESSED]);
	t->GetProperty(widgettype, objectname, "bordersize", _mid->my_bordersize[HIGHLITED]);

	t->GetProperty(widgettype, objectname, "bordersize0", _mid->my_bordersize[UNPRESSED]);
	t->GetProperty(widgettype, objectname, "bordersize1", _mid->my_bordersize[PRESSED]);
	t->GetProperty(widgettype, objectname, "bordersize2", _mid->my_bordersize[HIGHLITED]);

	t->GetProperty(widgettype, objectname, "transparency0", _mid->my_transparency[UNPRESSED]);
	t->GetProperty(widgettype, objectname, "transparency1", _mid->my_transparency[PRESSED]);
	t->GetProperty(widgettype, objectname, "transparency2", _mid->my_transparency[HIGHLITED]);

	s = t->FindString(widgettype, objectname, "label");
	if(s != NULL) {
		SetText(s);
	}

	PG_Widget::LoadThemeStyle(widgettype, objectname);
	SizeWidget(Width(), Height());
}

void PG_Button::SetBorderColor(int b, const PG_Color& color) {
	my_colorBorder[b][0] = color;
}

/**  */
void PG_Button::eventSizeWidget(Uint16 w, Uint16 h) {

	FreeSurfaces();

	eventButtonSurface(&(_mid->srf[UNPRESSED]), UNPRESSED, w, h);
	if(_mid->srf[UNPRESSED]) {
			SDL_SetAlpha(_mid->srf[UNPRESSED], SDL_SRCALPHA, 255-_mid->my_transparency[UNPRESSED]);
	}

	eventButtonSurface(&(_mid->srf[PRESSED]), PRESSED, w, h);
	if(_mid->srf[PRESSED]) {
		SDL_SetAlpha(_mid->srf[PRESSED], SDL_SRCALPHA, 255-_mid->my_transparency[PRESSED]);
	}

	eventButtonSurface(&(_mid->srf[HIGHLITED]), HIGHLITED, w, h);
	if(_mid->srf[HIGHLITED]) {
		SDL_SetAlpha(_mid->srf[HIGHLITED], SDL_SRCALPHA, 255-_mid->my_transparency[HIGHLITED]);
	}

	return;
}

/**  */
void PG_Button::FreeSurfaces() {
	PG_ThemeWidget::DeleteThemedSurface(_mid->srf[UNPRESSED]);
	_mid->srf[UNPRESSED] = NULL;

	PG_ThemeWidget::DeleteThemedSurface(_mid->srf[HIGHLITED]);
	_mid->srf[HIGHLITED] = NULL;

	PG_ThemeWidget::DeleteThemedSurface(_mid->srf[PRESSED]);
	_mid->srf[PRESSED] = NULL;
}

void PG_Button::FreeIcons() {

	if(!_mid->free_icons) {
		return;
	}

	if(_mid->srf_icon[UNPRESSED]) {
		PG_Application::UnloadSurface(_mid->srf_icon[UNPRESSED]); // false
		_mid->srf_icon[UNPRESSED] = NULL;
	}

	if(_mid->srf_icon[HIGHLITED]) {
		PG_Application::UnloadSurface(_mid->srf[HIGHLITED]); // false
		_mid->srf_icon[HIGHLITED] = NULL;
	}

	if(_mid->srf_icon[PRESSED]) {
		PG_Application::UnloadSurface(_mid->srf_icon[PRESSED]); // false
		_mid->srf_icon[PRESSED] = NULL;
	}

	_mid->free_icons = false;
}

/**  */
void PG_Button::eventMouseEnter() {
	if (!(_mid->togglemode && _mid->isPressed)) {
		_mid->my_state = HIGHLITED;
	}

	Update();
	PG_Widget::eventMouseEnter();
}

/**  */
void PG_Button::eventMouseLeave() {

	if(_mid->my_state == HIGHLITED) {
		(_mid->togglemode && _mid->isPressed) ? _mid->my_state = PRESSED : _mid->my_state = UNPRESSED;
	}

	Update();
	PG_Widget::eventMouseLeave();
}

/**  */
bool PG_Button::eventMouseButtonDown(const SDL_MouseButtonEvent* button) {
	if (!button)
		return false;

	if(button->button == 1) {
		_mid->my_state = PRESSED;
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

	if(_mid->togglemode) {
		if(!_mid->isPressed) {
			_mid->my_state = PRESSED;
			_mid->isPressed = true;
		} else {
			_mid->my_state = HIGHLITED;
			_mid->isPressed = false;
		}
	} else {
		_mid->my_state = UNPRESSED;
		_mid->isPressed = false;
	}

	if(!IsMouseInside()) {
		_mid->my_state = UNPRESSED;
		ReleaseCapture();
		Update();
		return false;
	} else {
		if(!_mid->togglemode) {
			_mid->my_state = HIGHLITED;
		}
	}

	ReleaseCapture();
	Update();

	sigClick(this);
	return true;
}

/**  */
bool PG_Button::SetIcon(const char* filenameup, const char* filenamedown, const char* filenameover, const PG_Color& colorkey) {
	if(!SetIcon(filenameup, filenamedown, filenameover)) {
		return false;
	}

	if(_mid->srf_icon[UNPRESSED] != NULL) {
		SDL_SetColorKey(_mid->srf_icon[UNPRESSED], SDL_SRCCOLORKEY, colorkey);
	}

	if(_mid->srf_icon[HIGHLITED] != NULL) {
		SDL_SetColorKey(_mid->srf_icon[HIGHLITED], SDL_SRCCOLORKEY, colorkey);
	}

	if(_mid->srf_icon[PRESSED] != NULL) {
		SDL_SetColorKey(_mid->srf_icon[PRESSED], SDL_SRCCOLORKEY, colorkey);
	}

	return true;
}

bool PG_Button::SetIcon(const char* filenameup, const char* filenamedown, const char* filenameover) {
	SDL_Surface* icon0 = PG_Application::LoadSurface(filenameup);
	SDL_Surface* icon1 = PG_Application::LoadSurface(filenameover);
	SDL_Surface* icon2 = PG_Application::LoadSurface(filenamedown);

	if(icon0 == NULL) {
		return false;
	}

	FreeIcons();

	_mid->srf_icon[UNPRESSED] = icon0;
	_mid->srf_icon[HIGHLITED] = icon1;
	_mid->srf_icon[PRESSED] = icon2;
	_mid->free_icons = true;

	Redraw();
	return true;
}


/**  */
bool PG_Button::SetIcon(SDL_Surface* icon_up, SDL_Surface* icon_down,SDL_Surface* icon_over) {

	if(!icon_up && !icon_down && !icon_over) {
		return false;
	}

	FreeIcons();

	_mid->srf_icon[UNPRESSED] = icon_up;
	_mid->srf_icon[HIGHLITED] = icon_over;
	_mid->srf_icon[PRESSED] = icon_down;

	_mid->free_icons = false;

	return true;
}

SDL_Surface* PG_Button::GetIcon(STATE num) {
	return _mid->srf_icon[num];
}

/**  */
void PG_Button::SetBorderSize(int norm, int pressed, int high) {

	if(norm >= 0) {
		_mid->my_bordersize[UNPRESSED] = norm;
	}

	if(pressed >= 0) {
		_mid->my_bordersize[PRESSED] = pressed;
	}

	if(high >= 0) {
		_mid->my_bordersize[HIGHLITED] = high;
	}
}

/**  */
void PG_Button::SetToggle(bool bToggle) {
	_mid->togglemode = bToggle;
}

/**  */
void PG_Button::SetPressed(bool pressed) {
	if(!_mid->togglemode)
		return;

	_mid->isPressed = pressed;
	_mid->my_state = (_mid->isPressed ? PRESSED : UNPRESSED);

	Update();
}

/**  */
void PG_Button::SetTransparency(Uint8 norm, Uint8 pressed, Uint8 high) {
	_mid->my_transparency[UNPRESSED] = norm;
	_mid->my_transparency[PRESSED] = pressed;
	_mid->my_transparency[HIGHLITED] = high;
}

/**
 * Set the moving distance of the image when we press on it
 */
void PG_Button::SetShift(int pixelshift) {
	_mid->my_pressShift = pixelshift;
}


/**  */
void PG_Button::eventButtonSurface(SDL_Surface** surface, STATE newstate, Uint16 w, Uint16 h) {
	if (!surface)
		return;

	PG_Rect r(0, 0, w, h);

	// remove the old button surface (if there are no more references)
	PG_ThemeWidget::DeleteThemedSurface(*surface);

	// create a new one
	*surface = PG_ThemeWidget::CreateThemedSurface(
	               r,
	               &_mid->gradState[newstate],
	               _mid->background[newstate],
	               _mid->backMode[newstate],
	               _mid->backBlend[newstate]);
}

/**  */
void PG_Button::SetGradient(STATE state, const PG_Gradient& gradient) {
	_mid->gradState[state] = gradient;
}

void PG_Button::SetBackground(STATE state, SDL_Surface* background, int mode) {

	if(!background) {
		return;
	}

	_mid->background[state] = background;
	_mid->backMode[state] = mode;
}

/**  */
bool PG_Button::GetPressed() {
	if(_mid->togglemode) {
		return _mid->isPressed;
	} else {
		return (_mid->my_state == PRESSED);
	}
}

void PG_Button::eventBlit(SDL_Surface* srf, const PG_Rect& src, const PG_Rect& dst) {
	PG_Rect rect = *this;
	PG_Rect r;
	PG_Rect my_src, my_dst;

	Uint8 t = 0;

	// get the right surface for the current state
	switch(_mid->my_state) {
		case UNPRESSED:
			if(_mid->srf[UNPRESSED]) {
				t = _mid->my_transparency[UNPRESSED];
				srf = _mid->srf[UNPRESSED];
			}
			break;

		case PRESSED:
			if(_mid->srf[PRESSED]) {
				t = _mid->my_transparency[PRESSED];
				srf = _mid->srf[PRESSED];
			}
			break;

		case HIGHLITED:
			if(_mid->srf[HIGHLITED]) {
				t = _mid->my_transparency[HIGHLITED];
				srf = _mid->srf[HIGHLITED];
			}
			break;
	}

	// blit it

	if(t != 255) {
		SDL_SetAlpha(srf, SDL_SRCALPHA, 255-t);
		PG_Draw::BlitSurface(srf, src, my_srfScreen, dst);
	}

	int shift = (((_mid->my_state == PRESSED) || (_mid->togglemode && _mid->isPressed)) ? 1 : 0) * _mid->my_pressShift;

	r.my_xpos = rect.my_xpos + (rect.my_width >> 1) + shift;
	r.my_ypos = rect.my_ypos + (rect.my_height >> 1) + shift;
	r.my_height = 0;

	// check for icon srf
	//
	//SDL_Surface* iconsrf = (my_state == BTN_STATE_PRESSED) ? ((_mid->srf_icon[1] == 0) ? _mid->srf_icon[0] : _mid->srf_icon[1]) : _mid->srf_icon[0];

	SDL_Surface* iconsrf;
	if(_mid->my_state == PRESSED) {
		if(_mid->srf_icon[PRESSED] == 0) {
			iconsrf = _mid->srf_icon[UNPRESSED];
		} else {
			iconsrf = _mid->srf_icon[PRESSED];
		}
	} else if(_mid->my_state == HIGHLITED) {
		if(_mid->srf_icon[HIGHLITED] == 0) {
			iconsrf = _mid->srf_icon[UNPRESSED];
		} else {
			iconsrf = _mid->srf_icon[HIGHLITED];
		}
	} else {
		iconsrf = _mid->srf_icon[UNPRESSED];
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

	if(!_mid->togglemode) {
		i0 = (_mid->my_state == PRESSED) ? 1 : 0;
		i1 = (_mid->my_state == PRESSED) ? 0 : 1;
	} else {
		i0 = (_mid->isPressed) ? 1 : 0;
		i1 = (_mid->isPressed) ? 0 : 1;
	}

	DrawBorder(PG_Rect(0, 0, Width(), Height()), _mid->my_bordersize[_mid->my_state], i1);
}

void PG_Button::SetBlendLevel(STATE mode, Uint8 blend) {
	_mid->backBlend[mode] = blend;
}

Uint8 PG_Button::GetBlendLevel(STATE mode) {
	return _mid->backBlend[mode];
}
