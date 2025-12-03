CC = gcc
CFLAGS = -Wall -Wextra -O2

TARGET = test_fabinoci
SRC = fabinoci.c test_fabinoci.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

