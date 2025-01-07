makefile:
CC = gcc
CFLAGS = -g -Wall -Wextra -pthread
OBJS = main.o manager.o resource.o system.o event.o

Target = spacesim

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(CFLAGS)

main.o: main.c defs.h 
	$(CC) $(CFLAGS) -c main.c

manager.o: manager.c defs.h
	$(CC) $(CFLAGS) -c manager.c

resource.o: resource.c defs.h
	$(CC) $(CFLAGS) -c resource.c

system.o: system.c defs.h
	$(CC) $(CFLAGS) -c system.c

event.o: event.c defs.h
	$(CC) $(CFLAGS) -c event.c

clean: 
	rm -f $(OBJS) $(TARGET)
	
