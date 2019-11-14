#ifndef _ROOM_H_
#define _ROOM_H_

#include <stdbool.h>
#include "item.h"
#include "battle.h"

#define ROOM_NUM (25)

typedef struct __room Room;

struct __room {
  char name[256];
  bool isVisited;
  Enemy* enemy;
  Item* item;
  Room* neighbors;
};

extern Room rooms[ROOM_NUM];

void initRoom();

#endif
