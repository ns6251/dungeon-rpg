#ifndef _ITEM_H_
#define _ITEM_H_

typedef enum { Potion, SJewel, MJewel, LJewel, Dagger, ItemTypeLen } ItemType;

typedef struct __item {
  ItemType id;
  char name[256];
  int score;
} Item;

typedef struct __storage {
  int list[ItemTypeLen];
} Storage;

#endif
