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


Item* initItems(void);

#endif
