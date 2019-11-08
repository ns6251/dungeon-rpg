#ifndef _BATTLE_H_
#define _BATTLE_H_

typedef enum {
  winp,
  MidBoss,
  Boss,
  EnemyTypeLength
} EnemyType;

typedef struct 
{
  EnemyType type;
  char name[256];
  int hp;
  int minAtk;
  int maxAtk;
} Enemy;

#endif
