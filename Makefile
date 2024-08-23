CC = gcc
LIBS = 
CFLAGS = -g -Wall
TARGET = CBinaryToTCConverter
OBJECTS = main.o

all: $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $^ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^ $(LIBS)