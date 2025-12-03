CC = gcc
CFLAGS = -Wall -Wextra -O2
TARGET = test_prime

SRC = prime.c test_prime.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) -lm

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

