#ifndef TEXTAMOVE_H
#define TEXTAMOVE_H

typedef struct {
    int health;
    int maxHealth;
    int gold;
    int combatBonus;

    int row;
    int col;
    char event;
} character;

typedef struct {
    int row;
    int col;
    char** floor; //pointer to array of pointers to arrays of chars, first * is to a row and second * is to a column 
} map;

void printDirections(int row, int col, map* floorStruct);
character moveCharacter(char direction, map* floorMap, character player);




#endif