# Makefile
CC = gcc
CFLAGS = -Wall -g
TARGET = score
OBJ = main.o input.o calc.o output.o

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

main.o: main.c student.h
	$(CC) $(CFLAGS) -c main.c

input.o: input.c student.h
	$(CC) $(CFLAGS) -c input.c

calc.o: calc.c student.h
	$(CC) $(CFLAGS) -c calc.c

output.o: output.c student.h
	$(CC) $(CFLAGS) -c output.c

clean:
	rm -f $(TARGET) $(OBJ)
