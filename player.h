#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "room.h"
#include "item.h"

typedef struct __player {
  char name[256];
  int maxHp;
  int hp;
  int minAtk;
  int maxAtk;
  Dagger *dagger;
  Room* cuurRoom;
  Storage* storage;
} Player;

extern Player player;

void initPlayer();
void move();

#endif
