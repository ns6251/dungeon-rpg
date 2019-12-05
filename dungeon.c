/**
 * @file dungeon.c
 */

#include "dungeon.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "battle.h"
#include "player.h"
#include "room.h"
#include <time.h>
#include "turn.h"

static Enemy* enemies;
static Dagger* dagger;
static Item* items;
static Room* rooms;

/**
 * @author C0117230
 */
GameState initDungeon() {
  srand(time(NULL));
  enemies = initEnemies();
  dagger = initDagger();
  items = initItems();
  rooms = initRoom();
  setItems(rooms, items);
  setDagger(rooms, dagger);
  setEnemy(rooms, enemies);
  return Still;
}

static void printMap() {
  printf(
      "---Dungeon Map---      \n\n"
      "    Start                \n"
      "      A           #      \n"
      "      ║           ║      \n"
      "   E══B══C     ╔══S══╗   \n"
      "   ║     ║     ║     ║   \n"
      "H══F     D  R══P     Q   \n"
      "   ║     ║     ║     ║   \n"
      "J══L     G     U     O   \n"
      "   ║     ║     ║     ║   \n"
      "   ╚══M══I══K  W     T   \n"
      "      ║        ║     ║   \n"
      "      N^       ╚══X══╩══V\n"
      "      ║           ║      \n"
      "      #           Y*     \n"
      "                 Goal  \n\n"
      "^ : midBoss\t* : Boss \n\n");
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
      "ダンジョン内には中ボスとボスがいて、これらの位置は主人公から認識できるよ"
      "うになっているよ。\n"
      "ボスを倒すと最終的なスコアとして獲得したお宝や、ポーションの合計からかか"
      "ったターン数×10Pを引いて最終スコアを算出するぞ！\n"
      "主人公のHPが0になったとき、獲得したお宝は入手できずにスタート地点からや"
      "り直しになるぞ！\n"

  );
  printf("主人公\tHP 30 与えられるダメージ 1~3\n");
  printf("弱雑魚\tHP 10 与えられるダメージ 1~3\n");
  printf("強雑魚\tHP 15 与えられるダメージ 2~4\n");
  printf("中ボス\tHP 30 与えられるダメージ 1~6\n");
  printf("ボス\tHP 50 与えられるダメージ 3~6\n");
  printf("お宝ポイントの振り分け\n");
  printf("お宝(小)\t100P\n");
  printf("お宝(中)\t500P\n");
  printf("お宝(大)\t1000P\n");
  printf("ポーション\t500P\n");
  printf(
      "------------------------------------------------------------------------"
      "-----\n\n");
}

void printScore() {
  //宝の合計｛宝（大）＋宝（中）＋宝（小）＋ポーションの数｝-(ターン×10)
  int result = 0;
  for (int i = 0; i < ItemTypeLen; i++) {
    int score = items[i].score * player.storage[i];
    printf("%sの所持数:\t%d\t+%d\n", items[i].name, player.storage[i], score);
    result += score;
  }
  int score = getTurn() * 10;
  printf("所要ターン数:\t%d\t-%d\n", getTurn(), score);
  result -= score;
  printf("最終スコア:\t\t%d\n", result);
}

void printDungeonInfo() {
  printf(
      "\n----------------------------------------------------------------------"
      "-------\n\n");
  printf("%dターン目\t", getTurn());
  printf("HP: %d/%d\t", player.hp, player.maxHp);
  printf("現在位置: \"%s\"\n", player.curRoom->name);
  printMap();
}
