/**
 * @file battle.h
 * @author C0117230
 */

#ifndef _BATTLE_H_
#define _BATTLE_H_

#include "creature.h"

typedef enum { Lose = -1, Winp, MidBoss, Boss, EnemyTypeLength } EnemyType;

typedef struct {
  Creature base;
  EnemyType type;
} Enemy;

Enemy* initEnemies();

EnemyType battle();

#endif
