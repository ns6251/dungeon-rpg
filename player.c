/**
 * @file player.c
 * @author C0117230
 */

#include "player.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Player player;

/**
 * @brief グローバル変数playerの初期化を行う。
 * @author C0117230
 */
void initPlayer() {
  char name[512] = "";
  printf("Your name? >");
  scanf("%511[^\n]%*[^\n]", name);
  scanf("%*c");
  if (strlen(name) != 0) {
    strcpy(player.base.name, name);
  } else {
    strcpy(player.base.name, "Gucci gang");
  }
  player.base.hp = player.base.maxHp = 30;
  player.base.minAtk = 1;
  player.base.maxAtk = 3;
}

void setPlayer(Room* r) {
  player.curRoom = r;
  player.curRoom->isVisited = true;
}

/**
 * @brief グローバル変数playerを別の部屋に移動させる
 * @auther: C0117230
 */
void move() {
  while (true) {
    // 質問
    printf("次どっちいく？ []の数字をいれてね\n");
    int maxindex = -1;
    for (int i = 0; player.curRoom->neighbors[i] != NULL; i++) {
      printf("\t\"%s\" [%d] ", player.curRoom->neighbors[i]->name, i + 1);
      maxindex++;
    }
    printf("> ");
    // 入力の受付及び入力チェック
    char input[4];
    scanf("%4[^\n]%*[^\n]", input);
    scanf("%*c");
    int index = atoi(input) - 1;
    if (index < 0 || maxindex < index) {
      printf("正しい値を入力してね\n");
      continue;
    }
    Room* next = player.curRoom->neighbors[index];
    if (next->enemy != NULL && next->isVisited == false &&
        (next->enemy->type == MidBoss || next->enemy->type == Boss)) {
      printf("本当に%sに挑みますか？ [y/n] > ", next->enemy->base.name);
      scanf("%4[^\n]%*[^\n]", input);
      scanf("%*c");
      if (strcmp(input, "n") == 0) {
        continue;
      } else if (strcmp(input, "y") != 0) {
        printf("正しい値を入力してね\n");
        continue;
      }
    }
    // playerの居る部屋を更新
    player.curRoom = next;
    break;
  }
}

void usePotion() {
  if (player.storage[Potion] <= 0) {
    printf("ポーションを持っていない！\n");
    return;
  }
  if (player.base.hp == player.base.maxHp) {
    printf("体力は満タンだ\n");
    return;
  }

  char input[4];
  while (true) {
    printf("ポーションを使用しますか？[y/n]: ");
    scanf("%4[^\n]%*[^\n]", input);
    scanf("%*c");
    if (strcmp((input), "y") == 0) {
      player.base.hp = player.base.maxHp;
      player.storage[Potion]--;
      printf("%sはポーションを使ってHPは全快した！\n", player.base.name);
      break;
    } else if (strcmp(input, "n") == 0) {
      printf("%sはポーションを温存することにした。\n", player.base.name);
      break;
    } else {
      printf("正しい値を入力してね\n");
    }
  }
}
