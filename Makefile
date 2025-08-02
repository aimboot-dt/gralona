CC=gcc
CFLAGS=-Wall -O2 -I src/inc
TARGET=build/gralona
SRC:= $(wildcard src/*.c)
OBJ:= $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET)
	rm -f src/*.o
install: 
	cp $(TARGET) /usr/local/bin/
