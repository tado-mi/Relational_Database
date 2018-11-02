# the compiler
CC = gcc

# compiler flags
# -g	add debugging info to the executable
# -Wall	turn on (most) compiler warnings
CFLAGS = -g -Wall

TARGET = main

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

run:
	./$(TARGET)

clean:
	$(RM) $(TARGET)
