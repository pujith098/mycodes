CC = gcc
CFLAGS = -Wall -Wextra -O2
TARGET = test_palindrome
SRC = palindrome.c test_palindrome.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

