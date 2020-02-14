#include <strings.h>
#include <stdlib.h>
#include "graphsys.h"

#ifdef USE_SDL
#include "sdldriver/sdldriver.c"
#endif

GDriver *gx=NULL;

int initgraphics(char *mode, char *opt)
{
	#ifdef USE_SDL
	if(!strcmp(mode, "DEFAULT")) {
		int r = init_sdldriver(640,480);
		if (r) {
			gx=&sdldriver;
		}
		return r;
	}
	#endif

	return 0;
}

int haskey = -1;
int gxGetch() 
{
	if (haskey==-1) {
		GxEvent gxev;
		do {
			gx->pollevent(&gxev);
			if (gxev.type != gxev_key)
				gx->delay(1);
		} while(gxev.type!=gxev_key);
		haskey = gxev.e.key;
	}
	if (haskey>=256) {
		haskey = haskey & 0xFF;
		printf("KEY: %d\n", haskey);
		return 0;
	}
	int t = haskey;
	haskey=-1;
	return t;
}

int gxKbhit() 
{
	if (haskey==-1) {
		GxEvent gxev;
		gx->pollevent(&gxev);
		if (gxev.type == gxev_key)
			haskey = gxev.e.key;
		else
			gx->delay(1);
	}

	return haskey != -1;
}

