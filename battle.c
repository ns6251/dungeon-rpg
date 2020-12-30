/**
 * @file battle.c
 * @author C0117230
 */

#include "battle.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "creature.h"
#include "modules.h"
#include "player.h"
#include "turn.h"

static void Enemy_init(Enemy* self,
                       char* name,
                       int hp,
                       int maxHp,
                       int minAtk,
                       int maxAtk,
                       EnemyType type) {
  Creature_init(&self->base, name, hp, maxHp, minAtk, maxAtk);
  self->type = type;
}

Enemy* initEnemies() {
  Enemy* e = (Enemy*)calloc(7, sizeof(Enemy));
  Enemy_init(&e[0], "ゾンビ1", 10, 10, 1, 3, Winp);
  Enemy_init(&e[1], "ゾンビ2", 10, 10, 1, 3, Winp);
  Enemy_init(&e[2], "アリゲーター1", 15, 15, 2, 4, Winp);
  Enemy_init(&e[3], "アリゲーター2", 15, 15, 2, 4, Winp);
  Enemy_init(&e[4], "アリゲーター3", 15, 15, 2, 4, Winp);
  Enemy_init(&e[5], "ケルベロス", 30, 30, 1, 5, MidBoss);
  Enemy_init(&e[6], "ウロボロス", 50, 50, 2, 6, Boss);
  return e;
}

EnemyType battle(Enemy* enemy) {
  Creature* p = (Creature*)&player;
  Creature* e = (Creature*)enemy;

  while (true) {
    enter2continue();
    addTurn();
    printf("%s: %d/%d\t%s: %d/%d\n", p->name, p->hp, p->maxHp, e->name, e->hp,
           e->maxHp);
    // プレイヤーの攻撃
    Creature_attack(p, e);
    if (e->hp <= 0) {
      printf("battle win\n");
      return enemy->type;
    }

    // エネミーの攻撃
    Creature_attack(e, p);
    if (p->hp <= 0) {
      printf("battle lose\n");
      return Lose;
    }
  }
}
