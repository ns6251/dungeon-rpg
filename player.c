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
  strcpy(player.name, "Taro");
  player.hp = player.maxHp = 30;
  player.minAtk = 1;
  player.maxAtk = 3;
  player.curRoom = &rooms[0];
  player.curRoom->isVisited = true;
}

/**
 * @brief グローバル変数playerを別の部屋に移動させる
 * @auther: C0117230
 */
void move() {
  while (true) {
    // 質問
    printf("次どっちいく？ ");
    int maxindex = -1;
    for (int i = 0; player.curRoom->neighbors[i] != NULL; i++) {
      printf("[%d] \"%s\"\t ", i + 1, player.curRoom->neighbors[i]->name);
      maxindex++;
    }
    printf("> ");
    // 入力の受付及び入力チェック
    char input[4];
    scanf("%4s%*[^\n]%*c", input);
    int index = atoi(input) - 1;
    if (index < 0 || maxindex < index) {
      printf("正しい値を入力してね!\n");
      continue;
    }
    // playerの居る部屋を更新
    player.curRoom = player.curRoom->neighbors[index];
    break;
  }
}
