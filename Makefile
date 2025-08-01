CC=gcc
CFLAGS=-Wall -O2
TARGET=build/gralona
OBJ= src/main.o src/repos.o

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET)
install: 
	cp $(TARGET) /usr/local/bin/
