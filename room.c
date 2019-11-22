/**
 * @file room.c
 */

#include "room.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "battle.h"
#include "item.h"
#include "player.h"

Room* rooms;

static GameState noEvent(void) {
  printf("この部屋には何もないようだ……\n");
  return Still;
}

static GameState findItem(void) {
  Item* item = player.curRoom->item;
  printf("%sを拾った！", item->name);
  player.storage[item->type]++;
  return Still;
}

static GameState findDagger(void) {
  printf("%sを見つけた！\n", player.curRoom->dagger->name);
  player.dagger = player.curRoom->dagger;
  printf("%sは%sを装備した\n", player.name, player.dagger->name);
  return Still;
}

static GameState encountEnemy(void) {
  Enemy* enemy = player.curRoom->enemy;
  printf("%sが現れた！\n", enemy->name);
  EnemyType et = battle(enemy);
  switch (et) {
    case Winp:
      printf("宝（小）が確率でドロップ（予定）");
      return Still;
    case MidBoss:
      printf("宝（中）がドロップ（予定）");
      return Still;
    case Boss:
      printf("宝（大）がドロップ（予定）");
      return GameClear;
    case Lose:
      return GameOver;
    default:
      break;
  }
  exit(EXIT_FAILURE);
}

/**
 * @brief Roomの隣接関係を作成する
 * @author
 */
static void connectRoom() {
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
  rooms[7].neighbors[0] = &rooms[3];

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
  rooms[12].neighbors[0] = &rooms[6];
  rooms[12].neighbors[1] = &rooms[10];
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
  rooms[16].neighbors = (Room**)calloc(4, sizeof(Room*));
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

static void setEvent() {
  for (int i = 0; i < ROOM_NUM; i++) {
    rooms[i].event = noEvent;
  }
  // * test
  rooms[1].event = findDagger;
  rooms[24].event = encountEnemy;
}

/**
 * @brief Roomを作成する
 * @author
 */
void initRoom() {
  rooms = (Room*)calloc(ROOM_NUM, sizeof(Room));
  char* namelist[ROOM_NUM] = {"Room1",  "Room2",  "Room3",  "Room4",  "Room5",
                              "Room6",  "Room7",  "Room8",  "Room9",  "Room10",
                              "Room11", "Room12", "Room13", "Room14", "Room15",
                              "Room16", "Room17", "Room18", "Room19", "Room20",
                              "Room21", "Room22", "Room23", "Room24", "Room25"};

  for (int i = 0; i < ROOM_NUM; i++) {
    strcpy(rooms[i].name, namelist[i]);
  }
  connectRoom();
  setEvent();
  // 雑魚
  // rooms[2].enemy = &enemy;
  // rooms[5].enemy = &enemy;
  // rooms[15].enemy = &enemy;
  // rooms[16].enemy = &enemy;
  // 中ボス
  // rooms[13].enemy = &enemy;
  // rooms[24].enemy = &enemy;
  // ボス
  // rooms[25].enemy = &enemy;

  // rooms[3].item = &items[SJewel];
  // rooms[7].item = &items[SJewel];
  // rooms[16].item = &items[SJewel];
  // rooms[20].item = &items[SJewel];

  // rooms[17].item = &items[MJewel];
  // * test
  static Dagger d = {"Dagger", 1 / 3, 2};
  rooms[1].dagger = &d;
  static Enemy e = {Boss, "ラスボス", 50, 50, 3, 5};
  rooms[24].enemy = &e;

  // rooms[10].item = &items[Potion];
  // rooms[18].item = &items[Potion];
  // rooms[21].item = &items[Potion];
}
