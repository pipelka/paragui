
#include "blob.h"
#include "pgdraw.h"

char sizes[]={2,3,4,5,8,5,4,3};
char sqrttab[]={
0,1,1,1,2,2,2,2,2,3,3,3,3,3,3,3,
4,4,4,4,4,4,4,4,4,5,5,5,5,5,5,5,
5,5,5,5,6,6,6,6,6,6,6,6,6,6,6,6,
6,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
8,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
9,9,9,9,10,10,10,10,10,10,10,10,10,10,10,10,
10,10,10,10,10,10,10,10,10,11,11,11,11,11,11,11,
11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,
12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,
12,12,12,12,12,12,12,12,12,13,13,13,13,13,13,13,
13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,
13,13,13,13,14,14,14,14,14,14,14,14,14,14,14,14,
14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,
14,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15
};

Blob::Blob(PG_Widget* parent, PG_Rect r): PG_ThemeWidget(parent, r, true){

    starttimer = 0;
    
  	vmem1=NULL;
	vmem2= (unsigned char *)malloc(XSIZE*YSIZE);
	if(!vmem2) nomem();
	mul640= (unsigned char **)malloc(YSIZE*sizeof(char *));
	if(!mul640) nomem();
	remap= (char *)malloc(16384);
	if(!remap) nomem();
	remap2=(char *)malloc(16384);
	if(!remap2) nomem();
	blobs= (explosion *)malloc(MAXBLOBS*sizeof(struct explosion));
	if(!blobs) nomem();

  	freeblobs=activeblobs=0;
	for(int i=0;i<MAXBLOBS;i++)
	{
		blobs[i].blobnext=freeblobs;
		freeblobs=blobs+i;
	}

	normal(remap);
	bright(remap2);

    explosion_surface = SDL_CreateRGBSurface(SDL_SWSURFACE, my_width, my_height, 8, 0,0,0,0);
    
	flash=0;
	whichmap=0;
	loadcolors(whichmap);
	//addblob();
	now=0;
	
  
}

Blob::~Blob(){
    //here we could do some cleanup
   delete[] vmem2;
   delete[] mul640;
   delete[] remap;
   delete[] remap2;
   delete blobs;
   delete explosion_surface;
   
}


void Blob::nomem(void){
    printf("Not enough low memory!\n");
	SDL_Quit();
	exit(1);
}

void Blob::fire(unsigned char *p1,unsigned char *p2,int pitch,char *colormap)
{
    int x,y;
    unsigned char *p3, *p4;

	for(y=2;y<YSIZE;y++)
	{
		for(x=0;x<XSIZE;x++)
		{
			p3 = p1+y*XSIZE+x;
			p4 = p2+y*pitch+x;
			*p4=colormap[*p3+p3[-XSIZE]+p3[-XSIZE-1]+p3[-XSIZE+1]+p3[-1]+p3[1]+p3[-XSIZE-XSIZE-1]+p3[-XSIZE-XSIZE]+p3[-XSIZE-XSIZE+1]];
		}
	}
}

void Blob::disk(int x,int y,int rad)
{
    unsigned char *p;
    int i,j,k,aj;
    int rady=0;
    rady=rad*rad;
    int w;

    for(j=-rad;j<=rad;j++)
	{
		w=sqrttab[rady-j*j];
		aj=ABS(j)<<2;
		if(w)
		{
			p=mul640[y+j]+x-w;
			k=w+w+1;
			i=-w;
			while(k--) {*p++=255-(ABS(i)<<2)-aj;i++;}
		}
	}
}

void Blob::addblob(void)
{
    int dx,dy;
    struct explosion *ablob;

	if(!freeblobs) return;
	dx=(rand()&255)-128;
	dy=(rand()%200)+340;
	ablob=freeblobs;
	freeblobs=freeblobs->blobnext;
	ablob->bloblife=(rand()&511)+256;
	ablob->blobdx=dx;
	ablob->blobdy=dy;
	ablob->blobx=(256+(rand()&127))<<BLOBFRAC;
	ablob->bloby=2<<BLOBFRAC;
	ablob->blobnext=activeblobs;
	ablob->blobsize=BIGSIZE;
	activeblobs=ablob;
}

void Blob::moveblobs(void)
{
struct explosion **lastblob,*ablob;
int x,y;

	lastblob=&activeblobs;
	while((ablob = *lastblob) != NULL)
	{
		x=ablob->blobx>>BLOBFRAC;
		y=ablob->bloby>>BLOBFRAC;
		if(!--ablob->bloblife || y<0 || x<10 || x>XSIZE-10)
		{
			*lastblob=ablob->blobnext;
			ablob->blobnext=freeblobs;
			freeblobs=ablob;
			continue;
		}
		ablob->blobx+=ablob->blobdx;
		ablob->bloby+=ablob->blobdy;
		ablob->blobdy-=BLOBGRAVITY;
		lastblob=&ablob->blobnext;
	}
}

void Blob::putblobs(void)
{
struct explosion *ablob,*ablob2,*temp;
int x,y,dy;
int i,size;
long x2,y2,vel;

	ablob=activeblobs;
	activeblobs=0;
	while(ablob)
	{
		dy=ablob->blobdy;
		if(ablob->blobsize!=SMALLSIZE && (dy>-THRESHOLD && dy<THRESHOLD && !(rand()&7) || (rand()&127)==63))
		{
			i=explodenum;
			while(i-- && freeblobs)
			{
				ablob2=freeblobs;
				freeblobs=freeblobs->blobnext;
				ablob2->blobx=ablob->blobx;
				ablob2->bloby=ablob->bloby;
				for(;;)
				{
					x2=(rand()&511)-256;
					y2=(rand()&511)-256;
					vel=x2*x2+y2*y2;
					if(vel>0x3000 && vel<0x10000L) break;
				}
				ablob2->blobdx=ablob->blobdx+x2;
				ablob2->blobdy=ablob->blobdy+y2;
				ablob2->bloblife=16+(rand()&31);
				ablob2->blobsize=SMALLSIZE;
				ablob2->blobnext=activeblobs;
				activeblobs=ablob2;
				ablob->bloblife=1;
			}			
		}
		x=ablob->blobx>>BLOBFRAC;
		y=ablob->bloby>>BLOBFRAC;
		size=ablob->blobsize;
		if(size==BIGSIZE && ablob->blobdy>0 && ablob->blobdy<200)
			size=sizes[ablob->bloblife&7];
		if(x>10 && x<XSIZE-10 && y>10 && y<YSIZE-10)
			disk(x,YSIZE-1-y,size);
		temp=ablob;
		ablob=ablob->blobnext;
		temp->blobnext=activeblobs;
		activeblobs=temp;
	}
}

void Blob::normal(char *colormap)
{
    int i,j;
	for(i=0;i<8192;i++)
	{
		j=i/9;
		colormap[i]=j<256 ? (j>=RATE ? j-RATE : 0) : 255;
	}
}
void Blob::bright(char *colormap)
{
	for(int i=0;i<8192;i++) 
	    colormap[i]=i>>3<255 ? (i>>3) : 255;
}

void Blob::updatemap(void)
{
	SDL_SetColors(explosion_surface, themap, 0, 256);
	
}

void Blob::loadcolor(int n,int r,int g,int b)
{
	themap[n].r=r<<2;
	themap[n].g=g<<2;
	themap[n].b=b<<2;
}

void Blob::loadcolors(Uint8 which)
{
int i,j;
int r,g,b;

	which%=11;
	for(i=0;i<256;i++)
	{
		switch(which)
		{
		case 0:
			if(i<64) loadcolor(i,0,0,0);
			else if(i<128)	loadcolor(i,i-64,0,0);
			else if(i<192) loadcolor(i,63,i-128,0);
			else loadcolor(i,63,63,i-192);
			break;
		case 1:
			if(i<64) loadcolor(i,0,0,0);
			else if(i<128)	loadcolor(i,0,0,i-64);
			else loadcolor(i,(i-128)>>1,(i-128)>>1,63);
			break;
		case 2:
			loadcolor(i,i>>2,i>>2,i>>2);
			break;
		case 3:
			r=rand()&0x3f;
			g=rand()&0x3f;
			b=rand()&0x3f;
			loadcolor(i,r*i>>8,g*i>>8,b*i>>8);
			break;
		case 4:
			loadcolor(i,i>>2,0,0);
			break;
		case 5:
			loadcolor(i,0,i>>2,0);
			break;
		case 6:
			loadcolor(i,0,0,i>>2);
			break;
		case 7:
			j=i&15;
			if(i&16) j=15-j;
			j=(i>>2)*j/16;
			loadcolor(i,j,j,j);
			break;
		case 8:
			j=0;
			if(i>8 && i<128) j=63;
			loadcolor(i,j,j,j);
			break;
		case 9:
			j=31-(i&31)<<1;
			r=i&32 ? j : 0;
			g=i&64 ? j : 0;
			b=i&128 ? j : 0;
			loadcolor(i,r,g,b);
			break;
		case 10:
			j=(i&15)<<2;
			if(i&16) j=63-j;
			r=i&32 ? j : 0;
			g=i&64 ? j : 0;
			b=i&128 ? j : 0;
			loadcolor(i,r,g,b);
			break;
		}
	}
	updatemap();
}


void Blob::eventBlit(SDL_Surface* surface, const PG_Rect& scr, const PG_Rect& dst){

    PG_ThemeWidget::eventBlit(explosion_surface, scr, dst);
    
    if ( vmem1 != (unsigned char *)explosion_surface->pixels )
	{
		p1= vmem1=(unsigned char *)explosion_surface->pixels;
		for (int i=0;i<YSIZE;i++)
		{
			mul640[i]=i*explosion_surface->pitch+vmem1;
			memset(p1,0,XSIZE);
			p1+=explosion_surface->pitch;
		}
	}
	
	now++;
	if(!flash)
	{
		if(explodenum>96 && explodenum<160 && !(rand()&511))
			flash=60;
	}
	else 
	    --flash;
		
	explodenum=(now>>4)+1;
	if(explodenum==320) 
	    now=0;
	if(explodenum>256) 
	    explodenum=256;
	

	if(!(rand()&31))
		addblob();
	
	moveblobs();
	putblobs();
	
	p1=vmem1;
	p2=vmem2;
	int k=explosion_surface->pitch;
	for(int i=0;i<YSIZE;i++)
	{
		memcpy(p2,p1,XSIZE);
		p2+=XSIZE;
		p1+=k;
	}
	fire(vmem2,vmem1,k,flash ? remap2 :remap);
   
 	
}


Uint32 Blob::eventTimer(PG_TimerObject::ID id, Uint32 interval){
    Update();
    PG_TimerObject::eventTimer(id, interval);
    return interval;
}
