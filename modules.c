#include "modules.h"
#include <stdio.h>

void enter2continue(void) {
  printf("Press enter to continue...");
  while (getchar() != '\n')
    ;
  printf("\n");
}
