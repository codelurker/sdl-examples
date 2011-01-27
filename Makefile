LDLIBS=$(shell sdl-config --libs --cflags)

programs=01_initialize 02_setwindowmode 03_eventloop 04_loadbmp 05_draw 06_setcolorkey 07_fillrect 08_moving 09_drag_n_drop 10_drag_n_drop_pixelperfect

all: $(programs)

clean:
	rm -rf $(programs)
