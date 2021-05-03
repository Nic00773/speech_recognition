#Makefile

CC=gcc 

CPPFLAGS = `pkg-config gtk+-3.0 --cflags sdl` -MMD
CFLAGS = -Wall -Wextra -std=c99 -g

#CFLAGS = -W -Wall -Wextra -Wunreachable-code -Wwrite-strings -Wstrict-prototypes -std=c99 -O2
LDFLAGS =
LDLIBS= `pkg-config gtk+-3.0 --libs sdl` -lSDL_image -lm

all: main

main: main.o

clean:
	${RM} main

# END
