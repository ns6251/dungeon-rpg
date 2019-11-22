/**
 * @file dungeon.h
 * @author C0117230
 */

#ifndef _DUNGEON_H_
#define _DUNGEON_H_

typedef enum { Still, GameOver, GameClear } GameState;

GameState initDungeon();

void printRule();

void printScore();

void printDungeonInfo();

#endif
