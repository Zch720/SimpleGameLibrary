.PHONY: all dirs clean

CFLAGS = -std=c99 -Wfatal-errors -Wall

all: dirs glad/obj/glad.o

glad/obj/glad.o: glad/src/gl.c
	gcc $(CFLAGS) -I glad/include -c glad/src/gl.c -o $@

dirs:
	mkdir -p glad/obj

clean:
	rm -rf glad/obj