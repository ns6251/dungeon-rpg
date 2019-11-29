/**
 * @file item.h
 * @author C0117230
 */

#ifndef _ITEM_H_
#define _ITEM_H_

typedef enum { Potion, SJewel, MJewel, LJewel, ItemTypeLen } ItemType;

typedef struct __item {
  ItemType type;
  char name[256];
  int score;
} Item;

typedef struct __dagger {
  char name[256];
  double criticalOdds;  //クリティカル率
  int rate;             // 武器倍率
} Dagger;

Item* initItems();
Dagger* initDagger();

#endif
