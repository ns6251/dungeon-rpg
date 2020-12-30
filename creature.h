#pragma once

typedef struct creature Creature;
typedef void (*attack_t)(Creature* a, Creature* b);

struct attacker {
  attack_t attack;
};

struct creature {
  char name[256];
  int hp;
  int maxHp;
  int minAtk;
  int maxAtk;
  struct attacker* attack;
};

void Creature_init(Creature* self,
                   char* name,
                   int hp,
                   int maxHp,
                   int minAtk,
                   int maxAtk);

void Creature_attack(Creature* a, Creature* b);
