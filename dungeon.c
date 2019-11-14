#include <stdio.h>
#include "room.h"
#include "battle.h"

extern Room rooms[ROOM_NUM];

void initDungeon() {
  initEnemy();
  initRoom();
}

void printRule() {
  printf("printRule\n");
}

void printScore() {
  printf("printScore\n");
}

void printDungeonInfo() {
  printf("printDungeonInfo\n");
}
