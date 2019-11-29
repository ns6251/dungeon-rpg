/**
 * @file item.c
 */

#include "item.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief 登場する複数のItemを作成する
 * @return Item* 各アイテムの情報を含んだ配列の先頭ポインタ
 * @author
 */
Item* initItems() {
  Item* items = (Item*)calloc(ItemTypeLen, sizeof(Item));

  items[Potion].type = Potion;
  strcpy(items[Potion].name, "ポーション");
  items[Potion].score = 500;

  items[SJewel].type = SJewel;
  strcpy(items[SJewel].name, "宝(小)");
  items[SJewel].score = 100;

  items[MJewel].type = MJewel;
  strcpy(items[MJewel].name, "宝(中)");
  items[MJewel].score = 500;

  items[LJewel].type = LJewel;
  strcpy(items[LJewel].name, "宝(大)");
  items[LJewel].score = 1000;

  return items;
}

/**
 * @brief Daggerを作成する
 * @return 作成したDaggerのポインタ
 * @author C0117230
 */
Dagger* initDagger() {
  Dagger* dagger = (Dagger*)calloc(1, sizeof(Dagger));
  strcpy(dagger->name, "ダガー");
  dagger->criticalOdds = 1 / 3;
  dagger->rate = 2;
  return dagger;
}
