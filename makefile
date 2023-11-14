.PHONY: all clean dirs

CFLAGS = -std=c++11 -Wfatal-errors -Wall

GLFW_INCLUDE = ./ext/glfw/include
GLFW_LIB = ./ext/glfw/lib

GLAD_INCLUDE = ./ext/glad/include
GLAD_SRCS = ./ext/glad/src/gl.c

GLM_INCLUDE = ./ext/glm/include

STB_INCLUDE = ./ext/stb/include

INCLUDES = -I$(GLFW_INCLUDE) -I$(GLAD_INCLUDE) -I$(GLM_INCLUDE) -I$(STB_INCLUDE)

LIBS = -L$(GLFW_LIB) -lgtest -lpthread -lglfw3

EXT_TEST_ALL = ./ext_tests/ut_all.cpp

EXT_TEST_HEADERS = ./ext_tests/glfw_breath.h ./ext_tests/glm_breath.h

all: dirs bin/ut_all

ext/glad/obj/glad.o: $(GLAD_HEADERS) $(GLAD_SRCS)
	gcc -I$(GLAD_INCLUDE) -c$(GLAD_SRCS) -o $@

bin/ut_all: $(EXT_TEST_ALL) $(EXT_TEST_HEADERS) ext/glad/obj/glad.o
	g++ $(CFLAGS) $(INCLUDES) -o $@ $^ $(LIBS)

dirs:
	mkdir -p bin ext/glad/obj

clean:
	rm -rf bin