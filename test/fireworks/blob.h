#ifndef BLOB_EXPLOSION_H
#define BLOB_EXPLOSION_H

#include "pgthemewidget.h"
#include "pgtimerobject.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define MOUSEFRAC 2
#define MAXBLOBS 255
#define BLOBFRAC 6
#define BLOBGRAVITY 5
#define THRESHOLD 20
#define SMALLSIZE 3
#define BIGSIZE 6
#define RATE 1
#define ABS(x) ((x)<0 ? -(x) : (x))

#define XSIZE 600 
#define YSIZE 400

struct explosion {
	struct explosion *blobnext;
	int blobx;
	int bloby;
	int blobdx;
	int blobdy;
	int bloblife;
	int blobsize;
};

class Blob: public PG_ThemeWidget, public PG_TimerObject {
public:
    //the constructor
    Blob(PG_Widget * parent, PG_Rect r);
    
    //the destructor
    ~Blob();
    
    Uint32 eventTimer(PG_TimerObject::ID id, Uint32 interval);

protected:
    //our custom event handler to redraw our stuff
    void eventBlit(SDL_Surface* surface, const PG_Rect& scr, const PG_Rect& dst);

   
      
    //error for low memory
    void nomem(void);
    
    //fire the blobs
    void fire(unsigned char *p1, unsigned char *p2, int pitch, char *colormap);
    
    //dunno
    void disk(int x,int y,int rad);
    
    //add a blob to the list
    void addblob(void);
    //move the blobs
    void moveblobs(void);
    void putblobs(void);
    
    //visual effects
    void normal(char *colormap);
    void bright(char *colormap);
    
    //update the color map
    void updatemap(void);
    
    //load a color
    void loadcolor(int n, int r, int g, int b);
    //load a particular color
    void loadcolors(Uint8 which);
   

private:
    struct explosion *blobs,*freeblobs,*activeblobs;      
    int explodenum;
    unsigned char **mul640;
    int oldmode;
    
    int starttimer;
    
    PG_Color themap[256];
    
    unsigned char *vmem1, *vmem2;

    char *remap,*remap2;

    int flash;
    int whichmap;
    int now;
   
    
    unsigned char *p1, *p2;

    SDL_Surface *explosion_surface;

};
#endif
