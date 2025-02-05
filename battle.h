/**
 * @file battle.h
 * @author C0117230
 */

#ifndef _BATTLE_H_
#define _BATTLE_H_

typedef enum { Lose = -1, Winp, MidBoss, Boss, EnemyTypeLength } EnemyType;

typedef struct {
  EnemyType type;
  char name[256];
  int hp;
  int maxHp;
  int minAtk;
  int maxAtk;
} Enemy;

Enemy* initEnemies();

EnemyType battle();

#endif
