LDLIBS=$(shell sdl-config --libs --cflags)

programs=01_initialize 02_setwindowmode 03_eventloop 04_loadbmp 05_draw 06_setcolorkey 07_fillrect 08_moving

all: $(programs)

clean:
	rm -rf $(programs)
