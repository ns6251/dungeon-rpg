/**
 * @file player.h
 * @author C0117230
 */

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "creature.h"
#include "item.h"
#include "room.h"

typedef struct player {
  Creature base;
  int storage[ItemTypeLen];
  Dagger* dagger;
  Room* curRoom;
} Player;

extern Player player;

void initPlayer();
void move();
void usePotion();
void setPlayer(Room*);

#endif
