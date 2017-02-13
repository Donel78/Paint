## Simple SDL mini code
 
CC=gcc
 
CPPFLAGS= `pkg-config --cflags --libs sdl gtk+-3.0 gmodule-2.0`
CFLAGS= -Wall -Wextra -std=c99 -O3
LDFLAGS=
LDLIBS= `pkg-config --libs sdl gtk+-3.0 gmodule-2.0` -lSDL_image
 
SRC= main.c paint_function.c signal_function.c
OBJ= ${SRC:.c=.o}
 
all: main
 
main: ${OBJ}
 
clean:
	rm -f *~ *.o
	rm -f main
 
# END
