guitest:
	cc -o guitest widgets.c wtext.c graphsys.c guitest.c -lm `sdl2-config --cflags --libs` -D USE_SDL
