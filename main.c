/**
 * @file main.c
 * @author C0117230
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "dungeon.h"
#include "player.h"
#include "turn.h"

int main(void) {
  GameState gamestate = initDungeon();
  initPlayer();
  printRule();

  while (gamestate == Still) {
    usePotion();
    printDungeonInfo();
    move();
    if (player.curRoom->isVisited == false) {
      gamestate = player.curRoom->event();
      player.curRoom->isVisited = true;
    }
    addTurn();
  }
  switch (gamestate) {
    case GameOver:
      printf("%sは死んでしまった…\n\nGame Over!\n", player.name);
      break;
    case GameClear:
      printf("Game Clear!\n");
      printScore();
      break;
    default:
      fprintf(stderr, "このメッセージが表示されるのはおかしい\n");
      exit(EXIT_FAILURE);
      break;
  }
}
