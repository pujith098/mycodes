CC = gcc
CFLAGS = -Wall -Wextra -O2
TARGET = test_median
SRC = median.c test_median.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

