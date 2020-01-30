CC = gcc

CFLAGS = -g -Wall

TARGET = main.out

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

run:
	./$(TARGET)

clean:
	$(RM) $(TARGET)
