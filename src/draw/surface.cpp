/*
    ParaGUI - crossplatform widgetset
    surface - surface creation and manipulation functions

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
    Update Date:      $Date: 2002/04/15 13:35:35 $
    Source File:      $Source: /sources/paragui/paragui/src/draw/surface.cpp,v $
    CVS/RCS Revision: $Revision: 1.3 $
    Status:           $State: Exp $
*/

#include "pgdraw.h"

SDL_Surface* PG_Draw::CreateRGBSurface(Uint16 w, Uint16 h, int flags) {
	SDL_Surface* screen = SDL_GetVideoSurface();

	return SDL_CreateRGBSurface (
				flags,
				w, h,
				screen->format->BitsPerPixel,
				screen->format->Rmask,
				screen->format->Gmask,
				screen->format->Bmask,
				0);
}

void PG_Draw::DrawThemedSurface(SDL_Surface* surface, const PG_Rect& r, PG_Gradient* gradient,
                                      SDL_Surface* background, int bkmode, Uint8 blend) {
	static PG_Rect srcrect;
	static PG_Rect dstrect;
	int x,y,i;
	bool bColorKey = false;
	Uint32 uColorKey;
	Uint32 c;
		
	// check if we have anything to do
	if(!gradient && !background) {
		return;
	}

	if (!r.h || !r.w)
        	return;

	// draw the gradient first
	if((background == NULL) || (background && (blend > 0))) {
		if(gradient != NULL) {
			DrawGradient(surface, r, *gradient);
		}
	}

	if(!background)
		return;
	
	if (!background->w || !background->h)
            return;

	int yc;
	int xc;
	SDL_Surface* temp;
	int w,h;

	bColorKey = (background->flags & SDL_SRCCOLORKEY);
	Uint8 rc,gc,bc;
	
	SDL_GetRGB(background->format->colorkey, background->format, &rc, &gc, &bc);
	uColorKey = (rc << 16) | (gc << 8) | bc;
	
	if(((gradient == NULL) || (blend == 0)) && bColorKey) {
		SDL_SetColorKey(background, 0, 0);
	}
	
	switch(bkmode) {

		//
		// BKMODE_TILE
		//

		case BKMODE_TILE:
			// tile the background image over the r in surface
			dstrect = r;

			srcrect.SetRect(0, 0, background->w, background->h);

			yc = (r.my_height / background->h) +1;
			xc = (r.my_width / background->w) +1;

			for(y=0; y<yc; y++) {
				for(x=0; x<xc; x++) {

					dstrect.SetRect(
					    r.my_xpos + background->w * x,
					    r.my_ypos + background->h * y,
					    background->w,
					    background->h);

					srcrect.my_width = background->w;
					srcrect.my_height = background->h;

					if((dstrect.my_xpos + dstrect.my_width -1) > r.my_width) {
						dstrect.my_width = r.my_width - dstrect.my_xpos;
					}

					if((dstrect.my_ypos + dstrect.my_height -1) > r.my_height) {
						dstrect.my_height = r.my_height - dstrect.my_ypos;
					}

					srcrect.my_width = dstrect.my_width;
					srcrect.my_height = dstrect.my_height;
    	
					if(blend > 0) {
						SDL_SetAlpha(background, SDL_SRCALPHA, 255-blend);
					} else {
						SDL_SetAlpha(background, 0, 0);
					}
					PG_Draw::BlitSurface(background, srcrect, surface, dstrect);
				}
			}
			break;

		//
		// BKMODE_STRETCH
		//

		case BKMODE_STRETCH:
			// stretch the background to fit the surface

			// Scale the background to fit this widget, using
			// anti-aliasing
			temp = PG_Draw::ScaleSurface(background, r);

			// set per surface alpha
			if(blend > 0) {
				SDL_SetAlpha(temp, SDL_SRCALPHA, 255-blend);
			} else {
				SDL_SetAlpha(temp, 0, 0);
			}

			// blit it
			SDL_BlitSurface(temp, NULL, surface, (PG_Rect*)&r);

			// free the temp surface
			SDL_FreeSurface(temp);
			break;

		//
		// BKMODE_3TILEH
		//

		case BKMODE_3TILEH:
			// source rectangles
			h = r.h;
			w = (int)( ( (double)h / (double)background->h) * (double)background->w );
			srcrect.SetRect(0,0,w,h);
			w /= 3;

            if (!w)
                    break;

			// rescale surface

			if(h == background->h) {
				temp = background;
			}
			else {
				temp = PG_Draw::ScaleSurface(background, srcrect);
			}

			// set per surface alpha
			if(blend > 0) {
				SDL_SetAlpha(temp, SDL_SRCALPHA, 255-blend);
			} else {
				SDL_SetAlpha(temp, 0, 0);
			}

			// blit part 1 (left)

			SDL_SetClipRect(surface, NULL);
			dstrect.SetRect(r.x,r.y,w,h);
			srcrect.SetRect(0, 0, w, h);
			PG_Draw::BlitSurface(temp, srcrect, surface, dstrect);

			// blit part 2 (middle)

			// set cliprect
			dstrect.SetRect(r.x+w, r.y, r.w-w*2, h);
			SDL_SetClipRect(surface, &dstrect);

			// blit it
			srcrect.SetRect(w, 0, w, h);
			for(i = 1; i<(r.w/w); i++) {
				dstrect.SetRect(r.x+w*i, r.y, w, h);
				PG_Draw::BlitSurface(temp, srcrect, surface, dstrect);
			}
			SDL_SetClipRect(surface, NULL);

			// blit part 3 (right)

			dstrect.SetRect(r.x+r.w-w, r.y,w,h);
			srcrect.SetRect(w*2, 0, w, h);
			PG_Draw::BlitSurface(temp, srcrect, surface, dstrect);

			// free temp surface
			if(h != background->h) {
				SDL_FreeSurface(temp);
			}

			break;

		//
		// BKMODE_3TILEV
		//

		case BKMODE_3TILEV:
			// source rectangles
			w = r.w;
			h = (int)( ( (double)w / (double)background->w) * (double)background->h );
			srcrect.SetRect(0,0,w,h);
			h /= 3;

            if (!h)
                    break;

			// rescale surface

			if(w == background->w) {
				temp = background;
			}
			else {
				temp = PG_Draw::ScaleSurface(background, srcrect);
			}

			// set per surface alpha
			if(blend > 0) {
				SDL_SetAlpha(temp, SDL_SRCALPHA, 255-blend);
			} else {
				SDL_SetAlpha(temp, 0, 0);
			}

			// blit part 1 (top)

			SDL_SetClipRect(surface, NULL);
			dstrect.SetRect(r.x,r.y,w,h);
			srcrect.SetRect(0, 0, w, h);
			PG_Draw::BlitSurface(temp, srcrect, surface, dstrect);

			// blit part 2 (middle)

			// set cliprect
			dstrect.SetRect(r.x,r.y+h,w,r.h-h*2);
			SDL_SetClipRect(surface, &dstrect);

			// blit it
			srcrect.SetRect(0, h, w, h);
			for(i = 1; i<(r.h/h); i++) {
				dstrect.SetRect(r.x, r.y+h*i, w, h);
				PG_Draw::BlitSurface(temp, srcrect, surface, dstrect);
			}
			SDL_SetClipRect(surface, NULL);

			// blit part 3 (bottom)

			dstrect.SetRect(r.x,r.y+r.h-h,w,h);
			srcrect.SetRect(0, h*2, w, h);
			PG_Draw::BlitSurface(temp, srcrect, surface, dstrect);

			// free temp surface
			if(w != background->w) {
				SDL_FreeSurface(temp);
			}

			break;

	}

	if(((gradient == NULL) || (blend == 0)) && bColorKey) {
    		c = SDL_MapRGB(
			background->format,
			(uColorKey>>16) & 0xFF,
			(uColorKey>>8) & 0xFF,
			uColorKey & 0xFF);
		SDL_SetColorKey(background, SDL_SRCCOLORKEY, c);
		
    		c = SDL_MapRGB(
			surface->format,
			(uColorKey>>16) & 0xFF,
			(uColorKey>>8) & 0xFF,
			uColorKey & 0xFF);
		SDL_SetColorKey(surface, SDL_SRCCOLORKEY, c);
	}
}
