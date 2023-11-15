.PHONY: all ext_test dirs clean clean-all

# g++ flags
CFLAGS = -std=c++11 -Wfatal-errors -Wall

# ext libraries
GLFW_INCLUDE = ./ext/glfw/include
GLFW_LIB = ./ext/glfw/lib

GLAD_INCLUDE = ./ext/glad/include
GLAD_SRCS = ./ext/glad/src/gl.c

GLM_INCLUDE = ./ext/glm/include

STB_INCLUDE = ./ext/stb/include
STB_OBJECTS = ./ext/glad/obj/glad.o

EXT_INCLUDES = -I $(GLFW_INCLUDE) -I $(GLAD_INCLUDE) -I $(GLM_INCLUDE) -I $(STB_INCLUDE)

EXT_LIBS = -L $(GLFW_LIB)
EXT_LINK_LIBS = -lgtest -lpthread -lglfw3
EXT_ALL_LIBS = $(EXT_LIBS) $(EXT_LINK_LIBS)

# simple rendering
SIMPLE_RENDERING_INCLUDE = ./simple_rendering/include
SIMPLE_RENDERING_LIB = ./simple_rendering/lib

# all includes and libs
INCLUDES = $(EXT_INCLUDES) -I $(SIMPLE_RENDERING_INCLUDE)

LIBS = $(EXT_LIBS) -L $(SIMPLE_RENDERING_LIB)
LINK_LIBS = $(EXT_LINK_LIBS) -lsrendering
ALL_LIBS = $(LIBS) $(LINK_LIBS)

# ext tests
EXT_TEST_ALL = ./ext_tests/ut_all.cpp
EXT_TEST_HEADERS = ./ext_tests/glfw_breath.h ./ext_tests/glm_breath.h

# tests
TEST_ALL = ./test/ut_all.cpp
TEST_HEADERS = ./test/simple_rendering_breath.h

all: dirs bin/ut_all

ext_test: dirs bin/ext_ut_all

bin/ut_all: $(TEST_ALL) $(TEST_HEADERS) simple_rendering/lib/libsrendering.a
	g++ $(CFLAGS) $(INCLUDES) ${STB_OBJECTS} -o $@ $^ $(ALL_LIBS)

bin/ext_ut_all: $(EXT_TEST_ALL) $(EXT_TEST_HEADERS)
	g++ $(CFLAGS) $(EXT_INCLUDES) ${STB_OBJECTS} -o $@ $^ $(EXT_ALL_LIBS)

simple_rendering/lib/libsrendering.a:
	make -C simple_rendering build_lib

dirs:
	mkdir -p bin ext/glad/obj

clean:
	rm -rf bin

clean-all:
	$(MAKE) clean
	make -C simple_rendering clean