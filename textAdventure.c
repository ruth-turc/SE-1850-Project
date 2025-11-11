#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* PROTOTYPES */
void printDirections(int row, int col, int floorLevel);
int isValidDirection(int row, int col);

int playerCombatNumber(character player);
int monsterCombatNumber(int floorLevel);
int goldPickUp(int floorLevel);


//comment from Jane

/* structure to represent player */
typedef struct {
    int health;
    int gold;
    char[10] inventory;
    int row;
    int col;
} character;

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
    character player;
    player.health = 100;

    //initialize player location on floor1
    player.row = 0;
    player.col = 0;

    int floorLevel = 1;
    char choice[50];
    
    printf("You awaken in a dark cave...\n");

    while (player.health > 0){
        printDirections(player.row, player.col, floorLevel);
        scanf("%s", choice);
        //add move character
        if (isValidDirection(player.row, player.col)){
            printf("You run into a wall");
            continue;
        } 

        /* I think we need to figure out something else for the maps...like make their own function???*/
        switch (floor[player.row][player.column]){
            case 'u':
                printf("You find a set of stairs going up.\n");
                printf("You've been here before.\n");
                break;
            case 'd':
                printf("You find a set of stairs going down.\n");
                printf("Would you like to decsend?\n");
                printf("[y]es or [n]o --> ");
                scanf("%s", &choice);

                if (/* yes*/){
                    floorLevel++;
                }
                break;
            case 'g':
                printf("You found gold! Pick it up?\n");
                printf("[y]es or [n]o --> ");
                scanf("%s", &choice);

                if (/* yes*/){
                    goldPickUp(floorLevel);
                }
                break;
            case 'm':
                /* do we want a monster function that returns a different description
                    of a monster based on floor level?? This function could also take
                    care of combat.*/

            case 'i':
                /* make its own function?*/
            case 'v':
                /* same here? */
        };
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
        printf("go north[w] ");
    }
    if (col != max_row){
        printf("go east[d] ");
    }
    if (row != max_col){
        printf("go south[s] ");
    }
    if (col != 0){
        printf("go west[a]");
    }
}

int isValidDirection(int row, int col){
    printf("FIXME: write function");
    return 1;
}