#include <stdio.h>
#include "dungeon.h"
#include "player.h"

int main(int argc, char const* argv[]) {
  initDungeon();
  initPlayer();
  printRule();
  printDungeonInfo();
  // ! おためし
  Enemy* e = initEnemy();
  EnemyType et = battle(e);
  printf("EnemyType: %d\n", et);
}
