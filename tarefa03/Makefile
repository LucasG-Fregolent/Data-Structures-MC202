CFLAGS = -std=c99 -Wall -Werror -Werror=vla -g 
LDFLAGS = -lm

.PHONY: all clean

all: rainhas

rainhas: rainhas.c
	gcc $(CFLAGS) rainhas.c -o rainhas $(LDFLAGS)

clean: rm -f rainhas