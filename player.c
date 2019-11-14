#include <stdio.h>
#include <string.h>
#include "player.h"
#include "room.h"
#include "item.h"

Player player;

void initPlayer() {
  printf("initPlayer\n");
  strcpy(player.name, "Taro");
  player.hp = player.maxHp = 25;
  player.minAtk = 1;
  player.maxAtk = 3;
}

void move() {
  printf("move");
}
