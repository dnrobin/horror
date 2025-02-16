SOURCES += src/mem.c
SOURCES += src/math.c
SOURCES += src/glad.c
SOURCES += src/parson.c
SOURCES += src/timing.c
SOURCES += src/trigger.c
SOURCES += src/bitmap.c
SOURCES += src/shaders.c
SOURCES += src/res.c
SOURCES += src/map.c
SOURCES += src/camera.c
SOURCES += src/controls.c
SOURCES += src/collision.c
SOURCES += src/graphics.c
SOURCES += src/render.c
SOURCES += src/sound.c
SOURCES += src/input.c
SOURCES += src/game.c
SOURCES += src/main.c

all:
	cc -g -Wall -O3 $(SOURCES) -Iext/glfw/include -Lext/glfw/src -lglfw3 \
													\
		-framework GLUT 							\
		-framework OpenGL 							\
		-framework OpenAL 							\
		-framework CoreAudio 						\
		-framework Cocoa							\
		-framework IOKit							\
													\
		-o maze
