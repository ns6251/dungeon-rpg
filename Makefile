PROGRAM = main.out
SOURCES = $(wildcard *.c)
HEADERS = $(wildcard *.h)
OBJS = $(patsubst %.c,%.o,$(SOURCES))
CC = gcc
CFLAGS = -std=c11 -Wpedantic -W -Wall
FORMATER = clang-format

.SUFFIXES: .c .o


$(PROGRAM): $(OBJS)
	$(CC) $(CFLAGS) -o $(PROGRAM) $^

.c.o:
	$(CC) $(CFLAGS) -c $<

.PHONY: clean
clean:
	$(RM) $(PROGRAM) $(OBJS)

.PHONY: format
format:
	$(FORMATER) -i -style=file $(SOURCES) $(HEADERS)

$(OBJS): $(HEADERS)
