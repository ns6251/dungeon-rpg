/**
 * @file player.h
 * @author C0117230
 */

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "item.h"
#include "room.h"

typedef struct __player {
  char name[256];
  int hp;
  int maxHp;
  int minAtk;
  int maxAtk;
  int storage[ItemTypeLen];
  Dagger* dagger;
  Room* curRoom;
} Player;

extern Player player;

void initPlayer();
void move();

#endif
