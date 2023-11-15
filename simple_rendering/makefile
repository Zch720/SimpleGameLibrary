.PHONY: all debug build_lib dirs libdir clean

# g++ flags
CFLAGS = -std=c++11 -Wfatal-errors -Wall

# ext libraries
GLFW_INCLUDE = ../ext/glfw/include
GLFW_LIB = ../ext/glfw/lib

GLAD_INCLUDE = ../ext/glad/include
GLAD_SRCS = ../ext/glad/src/gl.c

GLM_INCLUDE = ../ext/glm/include

STB_INCLUDE = ../ext/stb/include
STB_OBJECTS = ../ext/glad/obj/glad.o

INCLUDES = -I $(GLFW_INCLUDE) -I $(GLAD_INCLUDE) -I $(GLM_INCLUDE) -I $(STB_INCLUDE)

ALL_LIBS = -L $(GLFW_LIB) -lgtest -lpthread -lglfw3

# simple rendering
SIMPLE_RENDERING_INCLUDE = -I ./include

# tests
TEST_ALL = ./test/ut_all.cpp
TEST_HEADERS = ./test/window_test.h

all: dirs bin/ut_all

debug: dirs bin/debug_ut_all

build_lib: dirs libdir lib/libsrendering.a

lib/libsrendering.a: obj/window.o
	ar rcs $@ $^

bin/ut_all: $(TEST_ALL) $(TEST_HEADERS) obj/window.o
	g++ $(CFLAGS) $(INCLUDES) ${STB_OBJECTS} -o $@ $^ $(ALL_LIBS)

bin/debug_ut_all: $(TEST_ALL) $(TEST_HEADERS) obj/window.o
	g++ $(CFLAGS) -g $(INCLUDES) ${STB_OBJECTS} -o $@ $^ $(ALL_LIBS)

obj/window.o: include/window.h src/window.cpp
	g++ $(CFLAGS) $(INCLUDES) $(SIMPLE_RENDERING_INCLUDE) -c src/window.cpp -o $@

dirs:
	mkdir -p bin obj ../ext/glad/obj

libdir:
	mkdir -p lib

clean:
	rm -rf bin obj lib