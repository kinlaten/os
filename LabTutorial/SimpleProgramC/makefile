#### Beginner version
#
#hw: hw.o helper.o
#	gcc -o hw hw.o helper.o -lm
#
#hw.o: hw.c
#	gcc -c hw.c
#
#helper.o: helper.c
#	gcc -c helper.c
#
#clean: 
#	rm -f *.o hw


#### Advanced version
#SRC = hw.c helper.c
SRC = $(wildcard *.c)
TARGET = hw
CC = gcc
OPT = -Wall -O
LIB = -lm

# Create .o file with names as from .c file
OBJ = $(SRC:.c=.o)

#If none file change, do nothing 
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $(TARGET) $(OBJ) $(LIB)

%.o: %c
	$(CC) $(OPT) -c $< -o $@

clean: 
	rm -f $(OBJ) $(TARGET)
