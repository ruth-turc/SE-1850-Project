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
    fillFloor(levels,0,3,2,temp1);
    printMap(levels[0]);

    levels[1] = createFloor(3,3);
    char temp2[3][3] = {{' ','i','d'},
                       {' ','m','u'},
                       {' ',' ','g'}};

    fillFloor(levels,1,3,3,temp2);
    printMap(levels[1]);

    levels[2] = createFloor(5,4);
    char temp3[5][4] = {{' ','v','u','g'},
                       {'m',' ',' ',' '},
                       {' ','m','i',' '},
                       {' ',' ',' ','m'},
                       {'g',' ','d',' '}};
    fillFloor(levels,2,4,5,temp3);
    printMap(levels[2]);
}

//fills the floor with attributes of given 2D array
void fillFloor(map* levels[], int floorNum,int col, int row, char temp[][col]){
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

void printMap(map* map){
    for(int i = 0; i < map->row; i++){
        for(int j = 0; j < map->col; j++){
            printf("[%c] ",map->floor[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
