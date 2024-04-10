.PHONY: all dirs clean

CFLAGS = -std=c99 -Wfatal-errors -Wall

all: dirs glad/lib/glad.o

glad/lib/glad.o: glad/src/gl.c
	gcc $(CFLAGS) -I glad/include -c glad/src/gl.c -o $@

dirs:
	mkdir -p glad/lib

clean:
	rm -rf glad/lib