/**
 * @file room.h
 * @author C0117230
 */

#ifndef _ROOM_H_
#define _ROOM_H_

#include <stdbool.h>
#include "battle.h"
#include "dungeon.h"
#include "item.h"

#define ROOM_NUM (25)

typedef struct __room Room;

struct __room {
  char name[256];
  bool isVisited;
  Enemy* enemy;
  Item* item;
  Dagger* dagger;
  Room** neighbors;
  GameState (*event)(void);
};

Room* initRoom();
void setItems(Room*, Item*);
void setDagger(Room*, Dagger*);
void setEnemy(Room*, Enemy*);
#endif
