SRC:=src/glad.c
CFLAGS:=-Isrc -Iext/glfw/include -Lext/glfw/src
LDFLAGS:=-lglfw3 -framework Cocoa -framework IOKit -framework OpenGL

all:
	cc dev/gltf3.c $(SRC) $(CFLAGS) $(LDFLAGS) -o gltf3