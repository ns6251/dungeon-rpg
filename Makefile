PROGRAM = main.out
OBJS = battle.o item.o main.o player.o room.o turn.o dungeon.o

CC = gcc
CFLAGS = -std=c11 -Wpedantic -W -Wall

.SUFFIXES: .c .o

$(PROGRAM): $(OBJS)
	$(CC) -o $(PROGRAM) $^

.c.o:
	$(CC) $(CFLAGS) -c $<

.PHONY: clean
clean:
	$(RM) $(PROGRAM) $(OBJS)

# TODO: 依存するheaderファイルを記述
battle.o: battle.h
item.o : item.h
main.o:
player.o: player.h room.h item.h
room.o: room.h
turn.o: 
dungeon.o: dungeon.h
