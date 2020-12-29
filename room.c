/**
 * @file room.c
 */

#include "room.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "battle.h"
#include "creature.h"
#include "item.h"
#include "player.h"

static Item* items_g;

static GameState noEvent(void) {
  printf("この部屋には何もないようだ……\n");
  return Still;
}

static GameState findItem(void) {
  Item* item = player.curRoom->item;
  printf("%sを拾った！\n", item->name);
  player.storage[item->type]++;
  return Still;
}

static GameState findDagger(void) {
  printf("%sを見つけた！\n", player.curRoom->dagger->name);
  player.dagger = player.curRoom->dagger;
  printf("%sは%sを装備した( ･´ｰ･｀)ﾄﾞﾔｰ\n", player.base.name,
         player.dagger->name);
  return Still;
}

static bool isDrop(double odds) {
  return (odds >= ((double)rand() / RAND_MAX));
}

static void dropItem(ItemType it, double odds) {
  if (!isDrop(odds)) {
    printf("アイテムをドロップしなかった……(´・ω・｀)ｼｮﾎﾞｰﾝ\n");
    return;
  }
  printf("%sがドロップした!(⌒∇⌒)ﾔｯﾀｰ\n", items_g[it].name);
  player.storage[it]++;
}

static GameState encountEnemy(void) {
  Enemy* enemy = player.curRoom->enemy;
  printf("%sが現れた！\n", enemy->base.name);
  EnemyType et = battle(enemy);
  switch (et) {
    case Winp:
      // printf("宝（小）がドロップ\n");
      dropItem(SJewel, 0.5);
      return Still;
    case MidBoss:
      // printf("宝（中）がドロップ\n");
      dropItem(MJewel, 1.0);
      return Still;
    case Boss:
      // printf("宝（大）がドロップ\n");
      dropItem(LJewel, 1.0);
      return GameClear;
    case Lose:
      return GameOver;
    default:
      break;
  }
  exit(EXIT_FAILURE);
}

static GameState spring(void) {
  const int s = 25;
  printf("%sは泉を発見した！\n", player.base.name);
  player.base.maxHp += s;
  player.base.hp += s;
  printf("%sは泉を浴びて、体力と体力の最大値が%d上昇した！\n", player.base.name,
         s);
  return Still;
}

static GameState trap(void) {
  const int dmg = 10;
  printf("イタイ！\n");
  printf("%sは、トラップに引っかかってしまった。\n", player.base.name);
  printf("%dのダメージ！\n", dmg);
  player.base.hp -= dmg;
  if (player.base.hp <= 0) {
    return GameOver;
  } else {
    return Still;
  }
}

/**
 * @brief Roomの隣接関係を作成する
 * @author
 */
static void connectRoom(Room* rooms) {
  // 1に隣接する部屋
  rooms[0].neighbors = (Room**)calloc(2, sizeof(Room*));
  rooms[0].neighbors[0] = &rooms[1];

  // 2に隣接する部屋
  rooms[1].neighbors = (Room**)calloc(4, sizeof(Room*));
  rooms[1].neighbors[0] = &rooms[0];
  rooms[1].neighbors[1] = &rooms[2];
  rooms[1].neighbors[2] = &rooms[4];

  // 3に隣接する部屋
  rooms[2].neighbors = (Room**)calloc(3, sizeof(Room*));
  rooms[2].neighbors[0] = &rooms[1];
  rooms[2].neighbors[1] = &rooms[3];

  // 4に隣接する部屋
  rooms[3].neighbors = (Room**)calloc(3, sizeof(Room*));
  rooms[3].neighbors[0] = &rooms[2];
  rooms[3].neighbors[1] = &rooms[6];

  // 5に隣接する部屋
  rooms[4].neighbors = (Room**)calloc(3, sizeof(Room*));
  rooms[4].neighbors[0] = &rooms[1];
  rooms[4].neighbors[1] = &rooms[5];

  // 6に隣接する部屋
  rooms[5].neighbors = (Room**)calloc(4, sizeof(Room*));
  rooms[5].neighbors[0] = &rooms[4];
  rooms[5].neighbors[1] = &rooms[7];
  rooms[5].neighbors[2] = &rooms[11];

  // 7に隣接する部屋
  rooms[6].neighbors = (Room**)calloc(3, sizeof(Room*));
  rooms[6].neighbors[0] = &rooms[3];
  rooms[6].neighbors[1] = &rooms[8];

  // 8に隣接する部屋
  rooms[7].neighbors = (Room**)calloc(2, sizeof(Room*));
  rooms[7].neighbors[0] = &rooms[5];

  // 9に隣接する部屋
  rooms[8].neighbors = (Room**)calloc(4, sizeof(Room*));
  rooms[8].neighbors[0] = &rooms[6];
  rooms[8].neighbors[1] = &rooms[10];
  rooms[8].neighbors[2] = &rooms[12];

  // 10に隣接する部屋
  rooms[9].neighbors = (Room**)calloc(2, sizeof(Room*));
  rooms[9].neighbors[0] = &rooms[11];

  // 11に隣接する部屋
  rooms[10].neighbors = (Room**)calloc(2, sizeof(Room*));
  rooms[10].neighbors[0] = &rooms[8];

  // 12に隣接する部屋
  rooms[11].neighbors = (Room**)calloc(4, sizeof(Room*));
  rooms[11].neighbors[0] = &rooms[5];
  rooms[11].neighbors[1] = &rooms[9];
  rooms[11].neighbors[2] = &rooms[12];

  // 13に隣接する部屋
  rooms[12].neighbors = (Room**)calloc(4, sizeof(Room*));
  rooms[12].neighbors[0] = &rooms[8];
  rooms[12].neighbors[1] = &rooms[11];
  rooms[12].neighbors[2] = &rooms[13];

  // 14に隣接する部屋
  rooms[13].neighbors = (Room**)calloc(3, sizeof(Room*));
  rooms[13].neighbors[0] = &rooms[12];
  rooms[13].neighbors[1] = &rooms[18];

  // 15に隣接する部屋
  rooms[14].neighbors = (Room**)calloc(3, sizeof(Room*));
  rooms[14].neighbors[0] = &rooms[16];
  rooms[14].neighbors[1] = &rooms[19];

  // 16に隣接する部屋
  rooms[15].neighbors = (Room**)calloc(4, sizeof(Room*));
  rooms[15].neighbors[0] = &rooms[17];
  rooms[15].neighbors[1] = &rooms[18];
  rooms[15].neighbors[2] = &rooms[20];

  // 17に隣接する部屋
  rooms[16].neighbors = (Room**)calloc(3, sizeof(Room*));
  rooms[16].neighbors[0] = &rooms[18];
  rooms[16].neighbors[1] = &rooms[14];

  // 18に隣接する部屋
  rooms[17].neighbors = (Room**)calloc(2, sizeof(Room*));
  rooms[17].neighbors[0] = &rooms[15];

  // 19に隣接する部屋
  rooms[18].neighbors = (Room**)calloc(4, sizeof(Room*));
  rooms[18].neighbors[0] = &rooms[13];
  rooms[18].neighbors[1] = &rooms[15];
  rooms[18].neighbors[2] = &rooms[16];

  // 20に隣接する部屋
  rooms[19].neighbors = (Room**)calloc(3, sizeof(Room*));
  rooms[19].neighbors[0] = &rooms[14];
  rooms[19].neighbors[1] = &rooms[23];

  // 21に隣接する部屋
  rooms[20].neighbors = (Room**)calloc(3, sizeof(Room*));
  rooms[20].neighbors[0] = &rooms[15];
  rooms[20].neighbors[1] = &rooms[22];

  // 22に隣接する部屋
  rooms[21].neighbors = (Room**)calloc(2, sizeof(Room*));
  rooms[21].neighbors[0] = &rooms[23];

  // 23に隣接する部屋
  rooms[22].neighbors = (Room**)calloc(3, sizeof(Room*));
  rooms[22].neighbors[0] = &rooms[20];
  rooms[22].neighbors[1] = &rooms[23];

  // 24に隣接する部屋
  rooms[23].neighbors = (Room**)calloc(5, sizeof(Room*));
  rooms[23].neighbors[0] = &rooms[19];
  rooms[23].neighbors[1] = &rooms[21];
  rooms[23].neighbors[2] = &rooms[22];
  rooms[23].neighbors[3] = &rooms[24];

  // 25に隣接する部屋
  rooms[24].neighbors = (Room**)calloc(2, sizeof(Room*));
  rooms[24].neighbors[0] = &rooms[23];
}

static void setEvent(Room* rooms) {
  for (int i = 0; i < ROOM_NUM; i++) {
    rooms[i].event = noEvent;
  }
  rooms[2].event = encountEnemy;
  rooms[3].event = findItem;
  rooms[5].event = encountEnemy;
  rooms[6].event = trap;
  rooms[7].event = findItem;
  rooms[9].event = findDagger;
  rooms[10].event = findItem;
  rooms[13].event = encountEnemy;
  rooms[14].event = findItem;
  rooms[15].event = encountEnemy;
  rooms[16].event = encountEnemy;
  rooms[17].event = findItem;
  rooms[18].event = findItem;
  rooms[19].event = trap;
  rooms[20].event = findItem;
  rooms[21].event = findItem;

  rooms[22].event = spring;
  rooms[23].event = encountEnemy;

  rooms[24].event = encountEnemy;
}

/**
 * @brief Roomを作成する
 * @author
 */
Room* initRoom() {
  Room* rooms = (Room*)calloc(ROOM_NUM, sizeof(Room));
  char* namelist[ROOM_NUM] = {"Room A", "Room B", "Room C", "Room D", "Room E",
                              "Room F", "Room G", "Room H", "Room I", "Room J",
                              "Room K", "Room L", "Room M", "Room N", "Room O",
                              "Room P", "Room Q", "Room R", "Room S", "Room T",
                              "Room U", "Room V", "Room W", "Room X", "Room Y"};
  for (int i = 0; i < ROOM_NUM; i++) {
    strcpy(rooms[i].name, namelist[i]);
    rooms[i].isVisited = false;
  }
  connectRoom(rooms);
  setEvent(rooms);
  return rooms;
}

void setItems(Room* rooms, Item* items) {
  items_g = items;
  rooms[3].item = &items[SJewel];
  rooms[7].item = &items[SJewel];
  rooms[14].item = &items[SJewel];
  rooms[20].item = &items[SJewel];
  rooms[17].item = &items[MJewel];
  rooms[10].item = &items[Potion];
  rooms[18].item = &items[Potion];
  rooms[21].item = &items[Potion];
}

void setDagger(Room* rooms, Dagger* dagger) {
  rooms[9].dagger = dagger;
}

void setEnemy(Room* rooms, Enemy* enemy) {
  //雑魚
  rooms[2].enemy = &enemy[0];
  rooms[5].enemy = &enemy[1];
  //強い雑魚
  rooms[15].enemy = &enemy[2];
  rooms[16].enemy = &enemy[3];
  rooms[23].enemy = &enemy[4];
  // 中ボス
  rooms[13].enemy = &enemy[5];
  // ボス
  rooms[24].enemy = &enemy[6];
}
