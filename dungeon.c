/**
 * @file dungeon.c
 */

#include "dungeon.h"
#include <stdbool.h>
#include <stdio.h>
#include "battle.h"
#include "room.h"
#include "turn.h"

static Enemy* enemies;
static Dagger* dagger;
static Item* items;

/**
 * @author C0117230
 */
GameState initDungeon() {
  enemies = initEnemies();
  dagger = initDagger();
  items = initItems();
  initRoom();
  return Still;
}

/**
 * @author C0117109
 */
void printRule() {
  printf(
      "主人公はトレジャーハンターであり、ダンジョン内の財宝を求めてやってきた！"
      "\n"
      "ダンジョン内の各部屋は行き来が自由となっている。\n"
      "部屋に落ちている宝を集めながら、最深部の部屋を目指そう！\n"
      "雑魚敵を倒すと、50％の確率でお宝(小)をドロップするぞ！\n"
      "回復ポーションがいくつかの部屋に落ちているのでその場で使うか、保持したま"
      "ま移動もできるぞ！ただし戦闘中には使用できないので注意が必要だ！\n"
      "回復ポーションを使うとHPが全回復する。回復ポーションは後述するスコアにポ"
      "イントとして加算されるものでもあるのでよく考えて使おう！\n"
      "いくつかの部屋に武器も落ちている。手に入れると戦闘を優位に進めることがで"
      "きる。\n"
      "与えることのできるダメージが2倍になり、33％に確率でクリティカルヒット攻"
      "撃ができるぞ！\n"
      "またある部屋には様々なトラップやギミックが仕掛けられているぞ！HPを回復し"
      "てくれるギミックもあるが、ダメージを与えてくるトラップもあるので気を付け"
      "よう！\n"
      "ターン制でゲームは進んでいき、部屋を移動するとき、又は戦闘にて主人公→敵"
      "の行動で1ターンのカウントとする。\n"
      "ダンジョン内には中ボスとボスがいて、これらに位置は主人公から認識できるよ"
      "うになっているよ。\n"
      "ボスを倒すと最終的なスコアとして獲得したお宝や、ポーションの合計からかか"
      "ったターン数×10Pを引いて最終スコアを算出するぞ！\n"
      "主人公のHPが0になったとき、獲得したお宝は入手できずにスタート地点からや"
      "り直しになるぞ！\n");
  printf("主人公\tHP 30 与えられるダメージ 1~3\n");
  printf("雑魚\tHP 10 与えられるダメージ 1~3\n");
  printf("中ボス\tHP 25 与えられるダメージ 1~6\n");
  printf("ボス\tHP 50 与えられるダメージ 3~5\n");
  printf("お宝ポイントの振り分け\n");
  printf("お宝(小):\t100P\n");
  printf("お宝(中)\t500P\n");
  printf("お宝(大)\t1000P\n");
  printf("ポーション\t500P\n");
}

void printScore() {
  // TODO
  printf("printScore\n");
}

void printDungeonInfo() {
  // TODO
  printf("%dターン目\n", getTurn());
}
