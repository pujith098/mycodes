CC = gcc
CFLAGS = -Wall -Wextra -O2

TARGET = palindrome
SRC = string_palindrome.c test_string_palindrome.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

