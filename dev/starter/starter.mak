SRC:=$(wildcard dev/starter/*.c)
CFLAGS:=-Iext/glfw/include -Lext/glfw/src
LDFLAGS:=-lglfw3 -framework Cocoa -framework IOKit -framework OpenGL

all:
	cc $(SRC) $(CFLAGS) $(LDFLAGS) -o app