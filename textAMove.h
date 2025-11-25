#ifndef TEXTAMOVE_H
#define TEXTAMOVE_H
#include "textAMaps.h"

typedef struct {
    int health;
    int maxHealth;
    int gold;
    int combatBonus;

    int row;
    int col;
    char event;
} character;



void printDirections(int row, int col, map* floorStruct);
character moveCharacter(char direction, map* floorMap, character player);




#endif