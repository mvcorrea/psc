CC = gcc
CFLAGS = -g -O1 -m32 -Wall -O1
LFLAGS = -g -O1 -m32 -lcurl -ljansson -L.
CTAGS  = ctags -R . 
#TARGET = $(input)
TARGET = s3_4

## lib jansson build for OSX

.PHONY: open run clean cls tags

all: cls $(TARGET)

helper.o: helper.c
	$(CC) $(CFLAGS) -c helper.c

$(TARGET): $(TARGET).o helper.o
	$(CC) $(LFLAGS) -o $(TARGET) $(TARGET).o helper.o  

$(TARGET).o: $(TARGET).c
	$(CC) $(CFLAGS) -c $(TARGET).c

open:
	open -a "Google Chrome" forecast.json

run:
	./$(TARGET)

clean:
	@ rm ./$(TARGET) *.o 2> /dev/null | true

cls:
	clear

tags: 
	$(CTAGS)

