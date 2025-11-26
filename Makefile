CC = gcc 
CFLAGS = -Wall -Werror -std=c99
SRC = main.c memory/memory.c processor/cpu.c

OBJ = $(SRC:.c=.o)

TARGET = chip8

all :  $(TARGET)

$(TARGET) :  $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

%.o : %.c
	$(CC) -c $< -o $@
 

clean:
	rm -f $(OBJ) $(TARGET)
