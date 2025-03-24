SRC:=test/test_renderer.c src/glad.c src/r_mesh.c src/r_shader.c src/r_render.c
CFLAGS:=-Isrc -Iext/glfw/include -Lext/glfw/src
LDFLAGS:=-lglfw3 -framework Cocoa -framework IOKit -framework OpenGL

all:
	cc $(SRC) $(CFLAGS) $(LDFLAGS) -o test_renderer