#include <stdio.h>
#include "textAMove.h"

void printDirections(int row, int col, map* floorStruct){
    //find the max row and column index for a specific floor level
    int max_row, max_col;


    max_row = floorStruct->row - 1;
    max_col = floorStruct->col -1;
    // printf("max row: %d\n",max_row);
    // printf("max col: %d\n", max_col);

    //print possible directions
    printf("what would you like to do?\n");

    if (row > 0){
        printf("go north[w] ");
    }

    if (col < max_col){
        printf("go east[d] ");
    }
    
    if (row < max_row){
        printf("go south[s] ");
    }
    if (col > 0){
        printf("go west[a]");
    }
    if (row < 0 || row > max_row || col < 0 || col > max_col){
        printf("OUT OF BOUNDS\n");
    }
}

//moves the player in the chosen direction
character moveCharacter(char direction, map* floorStructPtr, character player){
    int maxRow = floorStructPtr->row - 1;
    int maxCol = floorStructPtr->col - 1;
    char tile;

    if(floorStructPtr->floor[player.row][player.col] == '\0'){
        printf("ERROR, NULL\n");
        return player;
    }
    
    switch (direction)
    {
    case 'w':
        while(player.row > 0){
            player.row--;
            tile = floorStructPtr->floor[player.row][player.col];
            if(tile == ' '){
                continue;
            }
            else if(tile == 'g' || tile == 'i' || tile == 'm' || tile == 'd' || tile == 'u' || tile == 'v'){
                player.event = tile;
                break;
            }
            else{
                printf("Oh Oh - unknown event");
            }
        }
        break;

    case 'a':
        while(player.col > 0){
            player.col--;
            tile = floorStructPtr->floor[player.row][player.col];
            if(tile == ' '){
                continue;
            }
            else if(tile == 'g' || tile == 'i' || tile == 'm' || tile == 'd' || tile == 'u' || tile == 'v'){
                player.event = tile;
                break;
            }
            else{
                printf("Oh Oh - unknown event");
            }
        }
        break;

    case 's':
        while(player.row < maxRow){
            player.row++;
            tile = floorStructPtr->floor[player.row][player.col];
            if(tile == ' '){
                continue;
            }
            else if(tile == 'g' || tile == 'i' || tile == 'm' || tile == 'd' || tile == 'u' || tile == 'v'){
                player.event = tile;
                break;
            }
            else{
                printf("Oh Oh - unknown event");
            }
        }
        break;

    case 'd':
        while(player.col < maxCol){
            player.col++;
            tile = floorStructPtr->floor[player.row][player.col];
            if(tile == ' '){
                continue;
            }
            else if(tile == 'g' || tile == 'i' || tile == 'm' || tile == 'd' || tile == 'u' || tile == 'v'){
                player.event = tile;
                break;
            }
            else{
                printf("Oh Oh - unknown event");
            }
        }
        break;

    
    default:
        printf("Wrong Input!\n");
        break;
    }
    if(floorStructPtr->floor[player.row][player.col]== ' '){
        player.event = ' ';
    }
    return player;
}