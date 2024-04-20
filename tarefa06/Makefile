CFLAGS = -std=c99 -Wall -Werror -Werror=vla -g
LDFLAGS = -lm

.PHONY: all clean

all: otimizar

selecionar: otimizar.c
	gcc $(CFLAGS) otimizar.c -o otimizar $(LDFLAGS)

clean:
	rm -f otimizar
