/**
 * @file battle.c
 * @author C0117230
 */

#include "battle.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "modules.h"
#include "player.h"
#include "turn.h"

static const double CRITICAL_RATE = 2.0;  // 共通クリティカル倍率

Enemy* initEnemies() {
  const int e_num = 7;
  Enemy* e = (Enemy*)calloc(e_num, sizeof(Enemy));

  Enemy zako = {Winp, "ゾンビ", 10, 10, 1, 3};
  Enemy strong_Zako = {Winp, "アリゲーター", 15, 15, 2, 4};
  Enemy mid = {MidBoss, "ケルベロス", 30, 30, 1, 5};
  Enemy boss = {Boss, "ウロボロス", 50, 50, 2, 6};

  e[0] = zako;
  e[1] = zako;
  e[2] = strong_Zako;
  e[3] = strong_Zako;
  e[4] = strong_Zako;
  e[5] = mid;
  e[6] = boss;
  return e;
}

static int basicDamage(int min, int max) {
  int dmg = min + (int)(rand() * (max - min + 1.0) / (1.0 + RAND_MAX));
  return dmg;
}

static bool isCritical(double odds) {
  return (odds >= ((double)rand() / RAND_MAX));
}

static int daggerRate(Dagger* d) {
  int rate = 1;
  if (d == NULL) {
    return rate;
  }
  rate = d->rate;
  if (isCritical(d->criticalOdds)) {
    char* serif[17] = {
        "〇ねぇぇぇぇぇぇぇぇぇぇぇぇぇぇ！！！！！！！！！！！！！！！",
        "神の力思い知れ！ゴッドブロオオォ！ゴッドブローとは女神の怒りと悲しみを"
        "乗せた必殺の拳！相手は死ぬ！",
        "黒より黒く闇より暗き漆黒に我が深紅の混淆を望みたもう。覚醒のとき来たれ"
        "り。無謬の境界に落ちし理。無行の歪みとなりて現出せよ！踊れ踊れ踊れ、我"
        "が力の奔流に望むは崩壊なり。並ぶ者なき崩壊なり。万象等しく灰塵に帰し、"
        "深淵より来たれ！これが人類最大の威力の攻撃手段、これこそが究極の攻撃魔"
        "法、エクスプロージョン！(物理)",
        "マジでショックです！でも、幸せならOKですb",
        "弱く見えるぞ",
        "君かわいいね（笑）どこ住み？会える？何歳？今暇？会わない？てかLINEやっ"
        "てる？（笑）",
        "逝け！モンスターボール！！！！！！！！！！",
        "あったかいふとんでぐっすりねる！こんな楽しいことがほかにあるか。",
        "フタエノキワミ、アッー!",
        "逝くのデス！",
        "今日は風が騒がしいな………",
        "N〇Kをぶっ壊す！！",
        "愛…………愛に……愛に愛に愛に愛に愛に愛に愛に…！！！！！！！！！！",
        "それー( ´·ω·)つ──✨💗💗💗ω・)/",
        "アベ政権を許すな",
        "響け､集え!全てを滅する刃と化せ！！ロスト･フォン･ドライブ！！",
        "(۳˚Д˚)۳= ▁▂▃▅▆▇█▓▒"};
    printf("%s\n", serif[rand() % 17]);
    printf("----------クリティカルヒット！----------\n");
    rate *= CRITICAL_RATE;
  }
  return rate;
}

EnemyType battle(Enemy* e) {
  while (true) {
    enter2continue();
    addTurn();
    printf("%s: %d/%d\t%s: %d/%d\n", player.name, player.hp, player.maxHp,
           e->name, e->hp, e->maxHp);
    // プレイヤーの攻撃
    int dmg = (int)basicDamage(player.minAtk, player.maxAtk);
    dmg *= daggerRate(player.dagger);
    e->hp -= dmg;
    printf("%sの攻撃！%sに%dのダメージ！\n", player.name, e->name, dmg);
    if (e->hp <= 0) {
      printf("battle win\n");
      return e->type;
    }

    // エネミーの攻撃
    dmg = basicDamage(e->minAtk, e->maxAtk);
    player.hp -= dmg;
    printf("%sの攻撃！%sに%dのダメージ！\n", e->name, player.name, dmg);
    if (player.hp <= 0) {
      printf("battle lose\n");
      return Lose;
    }
  }
}
