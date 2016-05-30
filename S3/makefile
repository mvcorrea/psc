CC = gcc
CFLAGS = -g -O1 -m32 -Wall -O1
LFLAGS = -g -O1 -m32 -lcurl -ljansson -L.
#TARGET = $(input)
TARGET = s3_1

## lib jansson build for OSX

all: $(TARGET)

helper.o: helper.c
	$(CC) $(CFLAGS) -c helper.c

$(TARGET): $(TARGET).o helper.o
	$(CC) $(LFLAGS) -o $(TARGET) $(TARGET).o helper.o  

$(TARGET).o: $(TARGET).c
	$(CC) $(CFLAGS) -c $(TARGET).c

clean:
	@ rm ./$(TARGET) *.o 2> /dev/null | true
