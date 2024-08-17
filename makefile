format:
	   @indent -kr -i8 library.h library.c

build:
	   @gcc -Wall -Wextra -Wpedantic -Werror -Wconversion -std=c18 -g *.c

run:
	   @clear && ./a.out

clean:
	   @rm a.out *~

all: format build run clean