#include "textAMaps.h"
#include <stdio.h>
#include <stdlib.h>


//creates space in memory needed for each floor depending on num of rows and colms and returns a pointer to it
map* createFloor(int row, int col){
    map* map1 = (map*)malloc(sizeof(map));
    map1 -> row = row;
    map1 -> col = col;

    map1->floor = malloc(row*sizeof(char*));
    for(int i = 0; i < row; i++){
        map1->floor[i] = malloc(col * sizeof(char));
    }
    return map1;
}

//initialization of floors
void initFloors(map* levels[]){
    levels[0] = createFloor(2,3);
    char temp1[2][3] = {{' ','m','g'},
                       {' ',' ','d'}};
    fillFloor(levels,0,3,temp1);

    levels[1] = createFloor(3,3);
    char temp2[3][3] = {{' ','i','d'},
                  {'u','m',' '},
                  {' ',' ','g'}};

    fillFloor(levels,1,3,temp2);
}

//fills the floor with attributes of given 2D array
void fillFloor(map* levels[], int floorNum,int col, char temp[][col]){
    for (int r = 0; r < levels[floorNum]->row; r++){
        for(int c = 0; c < levels[floorNum]->col; c++){
            levels[floorNum]->floor[r][c] = temp[r][c];
        }
    }
}
//frees the memory in one floor
void freeFloor(map* map){
    for(int i = 0; i < map->row; i++){
        free(map->floor[i]);
    }
    free(map->floor);
    free(map);
}
