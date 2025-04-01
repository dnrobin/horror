TARGET = maze

CFLAGS =-std=c99 -Iext/glfw/include -Iext/libdae/include
CFLAGS+=-W -Wall -w
CFLAGS+=-MMD
CFLAGS+=-O0 -g

LDFLAGS=-framework OpenGL -framework OpenAL -framework IOKit -framework CoreAudio -framework Cocoa
LDLIBS =-Lext/glfw/lib -lglfw3 -Lext/libdae/lib -ldae

SRCS = $(wildcard src/*.c)
OBJS = $(SRCS:src/%.c=build/%.o)
DEPS = $(SRCS:src/%.c=build/%.d)


all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS) $(LDLIBS)

build/%.o: src/%.c
	mkdir -p build
	$(CC) -c -o $@ $< $(CFLAGS)

-include $(DEPS)

clean:
	rm -f $(TARGET)
	rm -f $(DEPS) $(OBJS)

.PHONY: all clean