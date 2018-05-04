CFLAGS   = -Wall -Wextra -mtune=native `sdl2-config --cflags`
LDFLAGS  = `sdl2-config --libs` -lSDL2_image -lm

.SUFFIXES:
.SUFFIXES: .c .o

srcdir	 =src/
TARGETS	 = texturecolormod timed

.PHONY: all
all: $(TARGETS)

texturecolormod: $(srcdir)helper.c $(srcdir)main.c
	$(CC) $(CFLAGS) -o $@ $+ $(LDFLAGS)

timed: $(srcdir)helper.c $(srcdir)timed.c
	$(CC) $(CFLAGS) -o $@ $+ $(LDFLAGS) -lrt

.PHONY: clean
clean:
	@rm $(TARGETS) 2>/dev/null || true

