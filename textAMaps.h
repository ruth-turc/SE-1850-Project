#ifndef TEXTAMAPS_H
#define TEXTAMAPS_H

typedef struct {
    int row;
    int col;
    char** floor; //pointer to array of pointers to arrays of chars, first * is to a row and second * is to a column 
} map;

map* createFloor(int row, int col);
void initFloors(map* levels[]);
void fillFloor(map* levels[], int floorNum,int col, int row, char temp[][col]);
void freeFloor(map* map);
void printMap(map* map);

#endif 