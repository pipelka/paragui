
/* Simple program:  Move N sprites around on the screen as fast as possible */

#include "pgapplication.h"
#include "pgwidget.h"
#include "pglog.h"
#include "pgbutton.h"
#include "pglabel.h"
#include "pgcheckbutton.h"
#include "pgtheme.h"

#include <ctime>

#define NUM_SPRITES	100
#define MAX_SPEED 	1

SDL_Surface *sprite;
int numsprites;
SDL_Rect *sprite_rects;
SDL_Rect *positions;
SDL_Rect *velocities;
int sprites_visible;
int done = 0;
int bForeground = 0;

bool handle_quit() {
	done = 1;
	return true;
}

bool handle_toggle() {
	bForeground = 1-bForeground;
	return true;
}

int LoadSprite(SDL_Surface *screen, char *file)
{
	/* Load the sprite image */
	sprite = PG_FileArchive::LoadSurface(file, false);
	if ( sprite == NULL ) {
		PG_LogMSG( "Couldn't load %s: %s", file, SDL_GetError());
		return(-1);
	}

	/* Set transparent pixel as the pixel at (0,0) */
	if ( sprite->format->palette ) {
		SDL_SetColorKey(sprite, (SDL_SRCCOLORKEY|SDL_RLEACCEL),
						*(Uint8 *)sprite->pixels);
	}

	/* We're ready to roll. :) */
	return(0);
}

void MoveSprites(SDL_Surface *screen, Uint32 background)
{
	int i, nupdates;
	SDL_Rect area, *position, *velocity;

	nupdates = 0;

	SDL_SetAlpha(sprite, 0, 0);

	/* Move the sprite, bounce at the wall, and draw */
	for ( i=0; i<numsprites; ++i ) {
		position = &positions[i];
		velocity = &velocities[i];
		position->x += velocity->x;
		if ( (position->x < 0) || (position->x >= screen->w) ) {
			velocity->x = -velocity->x;
			position->x += velocity->x;
		}
		position->y += velocity->y;
		if ( (position->y < 0) || (position->y >= screen->h) ) {
			velocity->y = -velocity->y;
			position->y += velocity->y;
		}

		/* Blit the sprite onto the screen */
		area = *position;
		SDL_BlitSurface(sprite, NULL, screen, &area);
		sprite_rects[nupdates++] = area;
	}

	sprites_visible = 1;
}

/* This is a way of telling whether or not to use hardware surfaces */
Uint32 FastestFlags(Uint32 flags, int width, int height, int bpp)
{
	const SDL_VideoInfo *info;

	/* Hardware acceleration is only used in fullscreen mode */
	flags |= SDL_FULLSCREEN;

	/* Check for various video capabilities */
	info = SDL_GetVideoInfo();
	if ( info->blit_hw_CC && info->blit_fill ) {
		/* We use accelerated colorkeying and color filling */
		flags |= SDL_HWSURFACE;
	}
	/* If we have enough video memory, and will use accelerated
	   blits directly to it, then use page flipping.
	 */
	if ( (flags & SDL_HWSURFACE) == SDL_HWSURFACE ) {
		/* Direct hardware blitting without double-buffering
		   causes really bad flickering.
		 */
		if ( info->video_mem*1024 > (Uint32)(height*width*bpp/8) ) {
			flags |= SDL_DOUBLEBUF;
		} else {
			flags &= ~SDL_HWSURFACE;
		}
	}

	/* Return the flags */
	return(flags);
}

int main(int argc, char *argv[])
{
	SDL_Surface *screen;
	Uint8 *mem;
	int width, height;
	Uint8  video_bpp;
	Uint32 videoflags;
	Uint32 background;
	int    i;
	SDL_Event event;
	Uint32 then, now, frames;

	PG_Application app;

	numsprites = NUM_SPRITES;
	videoflags = SDL_SWSURFACE|SDL_DOUBLEBUF | SDL_ANYFORMAT;
	width = 640;
	height = 480;
	video_bpp = 16;
	while ( argc > 1 ) {
		--argc;
		if ( strcmp(argv[argc-1], "-width") == 0 ) {
			width = atoi(argv[argc]);
			--argc;
		} else
		if ( strcmp(argv[argc-1], "-height") == 0 ) {
			height = atoi(argv[argc]);
			--argc;
		} else
		if ( strcmp(argv[argc-1], "-bpp") == 0 ) {
			video_bpp = atoi(argv[argc]);
			videoflags &= ~SDL_ANYFORMAT;
			--argc;
		} else
		if ( strcmp(argv[argc], "-fast") == 0 ) {
			videoflags = FastestFlags(videoflags, width, height, video_bpp);
		} else
		if ( strcmp(argv[argc], "-hw") == 0 ) {
			videoflags ^= SDL_HWSURFACE;
		} else
		if ( strcmp(argv[argc], "-flip") == 0 ) {
			videoflags ^= SDL_DOUBLEBUF;
		} else
		if ( strcmp(argv[argc], "-fullscreen") == 0 ) {
			videoflags ^= SDL_FULLSCREEN;
		} else
		if ( isdigit(argv[argc][0]) ) {
			numsprites = atoi(argv[argc]);
		} else {
			PG_LogMSG(
	"Usage: %s [-bpp N] [-hw] [-flip] [-fast] [-fullscreen] [numsprites]",
								argv[0]);
			exit(1);
		}
	}

	/* Set video mode */
	if(!app.InitScreen(width, height, video_bpp, videoflags)) {
		PG_LogERR("Couldn't set %dx%d video mode: %s",
					width, height, SDL_GetError());
		exit(2);
	}

	PG_LogConsole::SetConsoleKey((SDLKey)0);
	
	app.SetBulkMode(true);
	app.LoadTheme("default");

	app.LoadLayout("dblbuffer.xml");
	app.SetCursor(app.GetTheme()->FindSurface("Pointer", "Pointer", "normal"));
	app.ShowCursor(PG_Application::SOFTWARE);

	// get a pointer to the "quit" button
	PG_Button* btn = app.GetWidget<PG_Button>("quit");
	btn->sigClick.connect(slot(handle_quit));

	// get the checkbutton
	PG_CheckButton* toggle = app.GetWidget<PG_CheckButton>("toggle");
	toggle->sigClick.connect(slot(handle_toggle));

	// get the label
	PG_Label* fps = app.GetWidget<PG_Label>("fps");

	screen = app.GetScreen();

	/* Load the sprite */
	if ( LoadSprite(screen, "icon.bmp") < 0 ) {
		exit(1);
	}

	/* Allocate memory for the sprite info */
	mem = (Uint8 *)malloc(4*sizeof(SDL_Rect)*numsprites);
	if ( mem == NULL ) {
		PG_LogMSG("Out of memory!");
		exit(2);
	}
	sprite_rects = (SDL_Rect *)mem;
	positions = sprite_rects;
	sprite_rects += numsprites;
	velocities = sprite_rects;
	sprite_rects += numsprites;
	srand(time(NULL));
	for ( i=0; i<numsprites; ++i ) {
		positions[i].x = rand()%screen->w;
		positions[i].y = rand()%screen->h;
		positions[i].w = sprite->w;
		positions[i].h = sprite->h;
		velocities[i].x = 0;
		velocities[i].y = 0;
		while ( ! velocities[i].x && ! velocities[i].y ) {
			velocities[i].x = (rand()%(MAX_SPEED*2+1))-MAX_SPEED;
			velocities[i].y = (rand()%(MAX_SPEED*2+1))-MAX_SPEED;
		}
	}
	background = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);

	/* Print out information about our surfaces */
	PG_LogMSG("Screen is at %d bits per pixel",screen->format->BitsPerPixel);
	if ( (screen->flags & SDL_HWSURFACE) == SDL_HWSURFACE ) {
		PG_LogMSG("Screen is in video memory");
	} else {
		PG_LogMSG("Screen is in system memory");
	}
	if ( (screen->flags & SDL_DOUBLEBUF) == SDL_DOUBLEBUF ) {
		PG_LogMSG("Screen has double-buffering enabled");
	}
	if ( (sprite->flags & SDL_HWSURFACE) == SDL_HWSURFACE ) {
		PG_LogMSG("Sprite is in video memory");
	} else {
		PG_LogMSG("Sprite is in system memory");
	}
	/* Run a sample blit to trigger blit acceleration */
	{ SDL_Rect dst;
		dst.x = 0;
		dst.y = 0;
		dst.w = sprite->w;
		dst.h = sprite->h;
		SDL_BlitSurface(sprite, NULL, screen, &dst);
		SDL_FillRect(screen, &dst, background);
	}
	if ( (sprite->flags & SDL_HWACCEL) == SDL_HWACCEL ) {
		PG_LogMSG("Sprite blit uses hardware acceleration");
	}
	if ( (sprite->flags & SDL_RLEACCEL) == SDL_RLEACCEL ) {
		PG_LogMSG("Sprite blit uses RLE acceleration");
	}

	/* Loop, blitting sprites and waiting for a keystroke */
	frames = 0;
	then = SDL_GetTicks();
	done = 0;
	sprites_visible = 0;

	while ( !done ) {
		/* Check for events */
		++frames;

		while ( SDL_PollEvent(&event) ) {
			app.PumpIntoEventQueue(&event);
		}
		now = SDL_GetTicks();
		if ( now > then+1000 ) {
				fps->SetTextFormat("%2.2f FPS",  ((double)frames*1000)/(now-then));

				if((now-then) > 1000) {
					then = now;
					frames=0;
				}
		}

		/* Erase all the sprites if necessary */
		if ( sprites_visible ) {
			SDL_FillRect(screen, NULL, background);
		}
		
		if(bForeground) {
			PG_Widget::BulkBlit();
			MoveSprites(screen, background);
		}
		else {
			MoveSprites(screen, background);
			PG_Widget::BulkBlit();
		}

		/* Update the screen! */
		SDL_Flip(screen);
	}
	free(mem);

	/* Print out some timing information */
	now = SDL_GetTicks();
	if ( now > then ) {
		PG_LogMSG("%2.2f frames per second",
					((double)frames*1000)/(now-then));
	}
	return(0);
}
