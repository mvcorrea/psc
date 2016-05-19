CC = gcc
CFLAGS = -g -O1 -m32 -Wall -O1
LFLAGS = -g -O1 -m32 -lcurl -ljansson -L.
TARGET = s3

## lib jansson build for OSX

all: $(TARGET)

$(TARGET): $(TARGET).o
	$(CC) $(LFLAGS) -o $(TARGET) $(TARGET).o  

$(TARGET).o: $(TARGET).c
	$(CC) $(CFLAGS) -c $(TARGET).c

clean:
	@ rm ./$(TARGET) *.o 2> /dev/null | true
