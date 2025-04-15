SRC:=../src/glad.c
CFLAGS:=-I../src -I../ext/glfw/include -L../ext/glfw/src
LDFLAGS:=-lglfw3 -framework Cocoa -framework IOKit -framework OpenGL

all:
	cc gltf1.c $(SRC) $(CFLAGS) $(LDFLAGS) -o gltf1