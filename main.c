/**
 * @file main.c
 * @author C0117230
 */

#include <stdbool.h>
#include <stdio.h>
#include "dungeon.h"
#include "player.h"
#include "turn.h"

int main(void) {
  GameState gamestate = initDungeon();
  initPlayer();
  printRule();

  while (gamestate == Still) {
    printDungeonInfo();
    printf("now: \"%s\"\n", player.curRoom->name);
    move();
    gamestate = player.curRoom->event();
    addTurn();
  }
  switch (gamestate) {
    case GameOver:
      printf("Game Over!\n");
      break;
    case GameClear:
      printf("Game Clear!\n");
      break;
  }
  printScore();
}
