CC = gcc

CFLAGS = -Wall -Wextra -std=gnu11 -D_XOPEN_SOURCE=700 -I.

SRC = main.c \
      fire/fire.c \
      struct/struct.c \
      screens/screens.c

OBJ = $(SRC:.c=.o)

TARGET = app


$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: clean
