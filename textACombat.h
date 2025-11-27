#ifndef textACombat
#define textACombat
#include "textAMove.h"
#include "textAEvents.h"


typedef struct {
    int health;
    int combatBonus;
} monster;

monster generateMonster(monster badGuy, int floorLevel);
character printCombat(monster badGuy, character player, int floorLevel);
int combatNumber(int combatBonus);
character finalBoss(character player);

#endif