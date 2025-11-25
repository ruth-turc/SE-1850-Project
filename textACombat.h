#ifndef textACombat
#define textACombat
#include "textAMove.h"


typedef struct {
    int health;
    int combatBonus;
} monster;

monster generateMonster(monster badGuy, int floorLevel);
character printCombat(monster badGuy, character player);
int combatNumber(int combatBonus);

#endif