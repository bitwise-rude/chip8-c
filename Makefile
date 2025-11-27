CC = gcc

SRC = main.c memory/memory.c processor/cpu.c graphics/graphics.c

SDL_CFLAGS = $(shell sdl2-config --cflags)
SDL_LDFLAGS = $(shell sdl2-config --libs)

CFLAGS = -g $(SDL_CFLAGS)
LDFLAGS = $(SDL_LDFLAGS)

OBJ = $(SRC:.c=.o)

TARGET = chip8

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
