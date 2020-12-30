#include "creature.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void basic_attack(Creature* a, Creature* b) {
  int damage = a->minAtk +
               (int)(rand() * (a->maxAtk - a->minAtk + 1.0) / (1.0 + RAND_MAX));
  b->hp -= damage;
  printf("%sの攻撃！%sに%dのダメージ！\n", a->name, b->name, damage);
}

static struct attacker basic_attacker = {.attack = basic_attack};

void Creature_init(Creature* self,
                   char* name,
                   int hp,
                   int maxHp,
                   int minAtk,
                   int maxAtk) {
  strncpy(self->name, name, sizeof(self->name));
  self->hp = hp;
  self->maxHp = maxHp;
  self->minAtk = minAtk;
  self->maxAtk = maxAtk;
  self->attack = &basic_attacker;
}

void Creature_attack(Creature* a, Creature* b) {
  a->attack->attack(a, b);
}
