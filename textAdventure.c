#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* PROTOTYPES */
void printDirections(int row, int col, int floorLevel);
int isValidDirection(int row, int col);

int calculatePlayerBonus(const char inventory[]);
int playerCombatNumber(int playerBonus);
int monsterCombatNumber(int floorLevel);
int goldPickUp(int floorLevel);

//comment from Jane

/* structure to represent player */
struct character {
    int health;
    char name[50];
    char inventory[10];
    int row;
    int col;
};

/* Maps!
        Key: 'u' = stairs up, 'd' = stairs down,'g' = gold, 
            'm' = monster, 'i' = item, 'v' = vender/merchant
    We might eventually want to make a function that will return
    the maps instead of declaring them here?
*/
char floor1[2][3] = {{' ','m','g'},
                  {' ',' ','d'}};

char floor2[3][3] = {{' ','i','d'},
                  {'u','m',' '},
                  {' ',' ','g'}};

int main(){
    //create character structure called player and assign health
    struct character player;
    player.health = 100;

    //initialize player location on floor1
    player.row = 0;
    player.col = 0;

    int floorLevel = 1;
    char choice[50];
    
    printf("You awaken in a dark cave...\n");

    while (1){
        printDirections(player.row, player.col, floorLevel);
        scanf("%s", choice);
        if (isValidDirection(player.row, player.col)){
            //continue with the loop
        } else {
            printf("You run into a wall");
        }
    }

    
    return 0;
}

/* FUNCTIONS!!!*/

void printDirections(int row, int col, int floorLevel){
    //find the max row and column index for a specific floor level
    int max_row, max_col;
    switch (floorLevel){
        case 1:
            max_row = 2;
            max_col = 1;
            break;
        case 2:
            max_row = 2;
            max_col = 2;
            break;
    };

    //print possible directions
    printf("what would you like to do?\n");
    if (row != 0){
        printf("[go north]");
    }
    if (col != max_row){
        printf("[go east]");
    }
    if (row != max_col){
        printf("[go south]");
    }
    if (col != 0){
        printf("[go west]");
    }
}

int isValidDirection(int row, int col){
    printf("FIXME: write function");
    return 1;
}