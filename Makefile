CC=gcc
CFLAGS=-Wall -g -O2 -I src/inc -lcurl -lz
TARGET=build/gralona
SRC:= $(wildcard src/*.c)
OBJ:= $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC)  $(OBJ) $(CFLAGS) -o $(TARGET)

src/%.o: src/%.c
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(TARGET)
	rm -f src/*.o
install: 
	cp $(TARGET) /usr/local/bin/
