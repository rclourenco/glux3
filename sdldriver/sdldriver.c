#include "graphlib.c"
#include "../graphsys.h"

void sdldriver_refresh()
{
	graph_refresh();
}

char scancode_map[256] = {
/*         0      1      2      3      4      5      6      7      8      9      A      B     C       D      E      F */
/*0*/	0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,
/*1*/	0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,
/*2*/	0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,
/*3*/	0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,
/*4*/	0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0x4D,
/*5*/	0x4B,  0x50,  0x48,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,
/*6*/	0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,
/*7*/	0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,
/*8*/	0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,
/*9*/	0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,
/*A*/	0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,
/*B*/	0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,
/*C*/	0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,
/*D*/	0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,
/*E*/	0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,
/*F*/	0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF
};

void sdldriver_pollevents(GxEvent *gxe)
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		gxe->type=gxev_quit;
		break;
	case SDL_KEYDOWN:
		gxe->type=gxev_key;
		gxe->e.key = event.key.keysym.sym;
		if (gxe->e.key>=256) {
			gxe->e.key = 0x1000 | scancode_map[event.key.keysym.scancode&0xFF];
		}
		break;
	case SDL_WINDOWEVENT:
		switch (event.window.event) {
		case SDL_WINDOWEVENT_SIZE_CHANGED:
			if (event.window.windowID == GraphSystem.windowID) {
				GraphSystem.wratio = (float)SCREEN_W/event.window.data1;
                		GraphSystem.hratio = (float)SCREEN_H/event.window.data2;
				gx->refresh();
			}
		}
		break;
	}
}

void sdldriver_delay(unsigned int delay)
{
	SDL_Delay(delay);
}

void sdldriver_mouse_show()
{
//	SDL_ShowCursor(SDL_ENABLE);
}

void sdldriver_mouse_hide()
{
//	SDL_ShowCursor(SDL_DISABLE);
}

void sdldriver_mouse_get(int *x, int *y, int *b)
{
 *b=SDL_GetMouseState(x,y);
 *x = (float)(*x)*GraphSystem.wratio;
 *y = (float)(*y)*GraphSystem.hratio; 
}

void sdldriver_line(int x1, int y1, int x2, int y2)
{
	DrawLine(x1, y1, x2, y2);
}

void sdldriver_rectangle(int x1, int y1, int x2, int y2)
{
	DrawRect(x1, y1, x2, y2, LINE);
}

void sdldriver_putpixel(int x, int y, int c)
{
	PLOT(x, y, c);
}

void sdldriver_arc(int x, int y, int stangle, int endangle, int radius)
{
	DrawArc(x, y, stangle, endangle, radius);
}

void sdldriver_bar(int left, int top, int right, int bottom)
{
	
	FillArea(left, top, right, bottom, FillColor);
}

void sdldriver_bar3d(int left, int top, int right, int bottom, int depth, int topflag)
{
//	bar3d(left, top, right, bottom, depth, topflag);
}

void sdldriver_cleardevice(void)
{
	fillscreen(0);
}

void sdldriver_closegraph(void)
{
	modo3h();
}

void sdldriver_outtextxy(int x, int y, char *textstring)
{
	TextBackGround=255;
	writest(x,y,textstring);
}

void sdldriver_setbkcolor(int color)
{
	TextBackGround=color;
//	FillColor=color;
}

void sdldriver_setcolor(int color)
{
	TextColor=color;
	Color=color;
}

void sdldriver_setfillpattern(char *upattern, int color)
{
//	setfillpattern(upattern, color);
}

void sdldriver_setfillstyle(int pattern, int color)
{
	FillColor=color;
	TextBackGround=color;
//	setfillstyle(pattern, color);
}

void sdldriver_setlinestyle(int linestyle, unsigned upattern, int thickness)
{
	if (thickness==THICK_WIDTH)
		line_width=3;
	else
		line_width=0;

	switch(linestyle) {
	case DOTTED_LINE:
		line_pattern=0x5555;
		break;
	case 4: line_pattern=upattern;
		break;
	default:
		line_pattern=0;
	}
}

void sdldriver_settextstyle(int font, int direction, int charsize)
{
//	settextstyle(font, direction, charsize);
}

void sdldriver_setwritemode(int mode)
{
	switch(mode) {
	case COPY_PUT:
		DRAW=COPY_D;
	break;
	case XOR_PUT:
		DRAW=XOR_D;
	break;
	}
}

int sdldriver_textheight(char *str)
{
	return 8;
}

int sdldriver_textwidth(char *str)
{
	return 8*strlen(str);
}

GDriver sdldriver = {
                sdldriver_pollevents,
		sdldriver_delay,
		sdldriver_refresh,
		sdldriver_mouse_show,
		sdldriver_mouse_hide,
		sdldriver_mouse_get,

		sdldriver_line,
		sdldriver_rectangle,
		sdldriver_putpixel,
		sdldriver_arc,
		sdldriver_bar,
		sdldriver_cleardevice,
		sdldriver_closegraph,
		sdldriver_outtextxy,
		sdldriver_setbkcolor,
		sdldriver_setcolor,
		sdldriver_setfillpattern,
		sdldriver_setfillstyle,
		sdldriver_setlinestyle,
		sdldriver_settextstyle,
		sdldriver_setwritemode,
		sdldriver_textheight,
		sdldriver_textwidth
};


