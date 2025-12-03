CC = gcc
CFLAGS = -Wall -Wextra -O2
TARGET = test_atoi
SRC = atoi.c test_atoi.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

