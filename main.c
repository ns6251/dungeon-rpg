/**
 * @file main.c
 * @author C0117230
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "dungeon.h"
#include "modules.h"
#include "player.h"
#include "turn.h"

static void askAction() {
  while (true) {
    printf("\nSelect next action.\n");
    printf("部屋を移動する: [1]\tポーションを使う: [2]\tヘルプ: [3]\t>");
    char input[4] = "";

    scanf("%4[^\n]%*[^\n]", input);
    scanf("%*c");
    int n = atoi(input);

    if (n > 3 || n <= 0) {
      printf("正しい値を入力してね！\n");
      continue;
    }
    if (n == 1) {
      move();
      break;
    }
    if (n == 2) {
      usePotion();
      continue;
    }
    if (n == 3) {
      printRule();
      continue;
    }
  }
}

int main(void) {
  initPlayer();
  GameState gamestate = initDungeon();
  printRule();

  while (gamestate == Still) {
    printDungeonInfo();
    askAction();
    if (player.curRoom->isVisited == false) {
      gamestate = player.curRoom->event();
      enter2continue();
      player.curRoom->isVisited = true;
    }
    addTurn();
  }
  switch (gamestate) {
    case GameOver:
      printf("%sは死んでしまった…\n\n", player.base.name);
      break;
    case GameClear:
      printf("Game Clear!\n");
      break;
    default:
      fprintf(stderr, "このメッセージが表示されるのはおかしい\n");
      exit(EXIT_FAILURE);
      break;
  }
  printScore(gamestate);
}
