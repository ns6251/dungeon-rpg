PROGRAM = main.out
OBJS = $(patsubst %.c,%.o,$(wildcard *.c))
HEADER = $(wildcard *.h)

.SUFFIXES: .c .o

CC = gcc
CFLAGS = -std=c11 -Wpedantic -W -Wall

$(PROGRAM): $(OBJS)
	$(CC) -o $(PROGRAM) $^

.c.o:
	$(CC) $(CFLAGS) -c $<

.PHONY: clean
clean:
	$(RM) $(PROGRAM) $(OBJS)

$(OBJS): $(HEADER)