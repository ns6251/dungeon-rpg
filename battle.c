/**
 * @file battle.c
 * @author C0117230
 */

#include "battle.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "player.h"

static const double CRITICAL_RATE = 2.0;  // 共通クリティカル倍率

Enemy* initEnemies() {
  const int e_num = 7;
  Enemy* e = (Enemy*)calloc(e_num, sizeof(Enemy));

  Enemy zako = {Winp, "zako", 10, 10, 1, 3};
  Enemy strong_Zako = {Winp, "s-zako", 15, 15, 2, 4};
  Enemy mid = {MidBoss, "mid", 30, 30, 1, 6};
  Enemy boss = {Boss, "Boss", 50, 50, 3, 6};

  e[0] = zako;
  e[1] = zako;
  e[2] = strong_Zako;
  e[3] = strong_Zako;
  e[4] = strong_Zako;
  e[5] = mid;
  e[6] = boss;
  return e;
}

static int basicDamage(int min, int max) {
  int dmg = min + (int)(rand() * (max - min + 1.0) / (1.0 + RAND_MAX));
  return dmg;
}

static bool isCritical(double odds) {
  return (odds >= ((double)rand() / RAND_MAX));
}

static int daggerRate(Dagger* d) {
  int rate = 1;
  if (d == NULL) {
    return rate;
  }
  rate = d->rate;
  if (isCritical(d->criticalOdds)) {
    rate *= CRITICAL_RATE;
  }
  return rate;
}

EnemyType battle(Enemy* e) {
#ifndef _srand_
#define _srand_
  srand(time(NULL));
#endif
  while (true) {
    printf("%s: %d/%d\t%s: %d/%d\n", player.name, player.hp, player.maxHp,
           e->name, e->hp, e->maxHp);
    // プレイヤーの攻撃
    int dmg = (int)basicDamage(player.minAtk, player.maxAtk);
    dmg *= daggerRate(player.dagger);
    e->hp -= dmg;
    printf("%sの攻撃！%sに%dのダメージ！\n", player.name, e->name, dmg);
    if (e->hp <= 0) {
      printf("battle win\n");
      return e->type;
    }

    // エネミーの攻撃
    dmg = basicDamage(e->minAtk, e->maxAtk);
    player.hp -= dmg;
    printf("%sの攻撃！%sに%dのダメージ！\n", e->name, player.name, dmg);
    if (player.hp <= 0) {
      printf("battle lose\n");
      return Lose;
    }
  }
}
