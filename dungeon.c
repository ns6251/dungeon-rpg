/**
 * @file dungeon.c
 */

#include "dungeon.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "battle.h"
#include "modules.h"
#include "player.h"
#include "room.h"
#include "turn.h"

static Enemy* enemies;
static Dagger* dagger;
static Item* items;
static Room* rooms;

/**
 * @author C0117230
 */
GameState initDungeon() {
  srand((unsigned)time(NULL));
  enemies = initEnemies();
  dagger = initDagger();
  items = initItems();
  rooms = initRoom();
  setItems(rooms, items);
  setDagger(rooms, dagger);
  setEnemy(rooms, enemies);
  setPlayer(rooms);
  return Still;
}

static void printMap() {
  printf(
      "      ---Dungeon Map---     \n\n"
      "            K                 \n"
      "            ║                 \n"
      "S     C═D═G═I    Q═O═T V     G\n"
      "T     ║     ║    ║   ║ ║     O\n"
      "A   A═B     M═N^═S   ╚═X═Y*  A\n"
      "R     ║     ║    ║     ║     L\n"
      "T     E═F═L═╝    P═U═W═╝     ‼\n"
      "        ║ ║      ║            \n"
      "        H J      R            \n"
      "^ : Kerberos\t* : Ouroboros \n\n");
}

/**
 * @author C0117109
 */
void printRule() {
  printf(
      "----------物語のあらすじ----------"
      "\n\n"
      " 主人公はダンジョン内の財宝を求めてやってきたトレジャーハンター"
      "\n"
      " 部屋に落ちている宝を集めながら、最深部の部屋を目指してボスを倒し、お宝"
      "を持ち帰ろう！\n\n");
  enter2continue();
  printf(
      "----------攻略するうえでの説明とヒント----------\n\n"
      " ☆ ダンジョン内の各部屋は行き来が自由となっている。\n"
      "\n"
      " ☆ 雑魚敵を倒すと、50％の確率でお宝(小)をドロップするぞ！\n"
      "\n"
      " ☆ "
      "ダンジョン内にある武器を手に入れると戦闘を優位に進めることができるぞ！\n"
      "\n"
      " ☆ "
      "武器を手に入れると、『与えることのできるダメージが2倍』になり、さらに『3"
      "3％の確率でクリティカルヒット攻撃』ができるぞ！\n"
      "\n"
      " ☆ ダンジョン内には様々なトラップやギミックが仕掛けられているぞ！\n"
      "    "
      "HPを回復してくれるギミックもあるが、ダメージを与えてくるトラップもあるの"
      "で気を付けよう！\n"
      "\n"
      " ☆ "
      "回復ポーションを見つけたら、その場で使うか、保持したまま移動もできるぞ！"
      "\n"
      "   ただし『戦闘中には使用できない』ので注意が必要だ！\n"
      "\n"
      " ☆ 回復ポーションを使うとHPが全回復する。\n"
      "   "
      "回復ポーションは,クリア後にポイントに換算されるのでよく考えて使おう！\n"
      "\n"
      " ☆ "
      "ターン制でゲームは進んでいき、『部屋を移動するとき』、又は『戦闘にて主人"
      "公→敵の行動』で1ターンのカウントとする。\n"
      "\n"
      " ☆ "
      "ダンジョン内には中ボスとボスがいて、これらの位置は常にマップに表示されて"
      "いるよ。\n"
      "\n"
      " ☆ "
      "ボスを倒すと最終的なスコアとして獲得したお宝や、ポーションの合計からかか"
      "ったターン数×10Pを引いて最終スコアを算出するぞ！\n\n");
  enter2continue();
  printf("----------各キャラのステータス----------\n\n");
  printf("主人公\tHP 30 与えられるダメージ 1~3\n");
  printf("ゾンビ\tHP 10 与えられるダメージ 1~3\n");
  printf("アリゲーター\tHP 15 与えられるダメージ 2~4\n");
  printf("ケルベロス\tHP 30 与えられるダメージ 1~5\n");
  printf("ウロボロス\tHP 50 与えられるダメージ 2~6\n");
  printf("\n----------お宝ポイントの振り分け----------\n\n");
  printf("お宝(小)\t100P\n");
  printf("お宝(中)\t500P\n");
  printf("お宝(大)\t1000P\n");
  printf("ポーション\t500P\n\n");
  printf(
      "------------------------------------------------------------------------"
      "\n\n");
  enter2continue();
}

void printScore(GameState gs) {
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
  if (gs == GameOver) {
    printf("You died:\t\t\t%d\n", -result);
    result = 0;
  }
  printf("最終スコア:\t\t%d\n", result);
}

void printDungeonInfo() {
  printf(
      "------------------------------------------------------------------------"
      "\n\n");
  printMap();
  printf("%dターン目\t", getTurn());
  printf("HP: %d/%d\t", player.hp, player.maxHp);
  printf("ポーション所持数: %d\n", player.storage[Potion]);
  printf("現在位置: \"%s\"\n\n", player.curRoom->name);
}
