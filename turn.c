/**
 * @file turn.c
 * @author C0117230
 */

static int turn;

void addTurn(void) {
  turn++;
}

int getTurn(void) {
  return turn;
}
