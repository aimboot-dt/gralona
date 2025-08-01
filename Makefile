CC=gcc
CFLAGS=-Wall -O2 -I src/inc
TARGET=build/gralona
OBJ=src/main.o src/refresh.o src/repos.o src/package_parser.o

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
