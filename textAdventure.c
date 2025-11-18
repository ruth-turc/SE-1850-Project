#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#define NUM_FLOORS 2


/* structure to represent player */
typedef struct {
    int health;
    int gold;
    int combatBonus;
    int row;
    int col;
    char event;
} character;

typedef struct {
    int health;
    int combatBonus;
} monster;

typedef struct {
    int row;
    int col;
    char** floor; //pointer to array of pointers to arrays of chars, first * is to a row and second * is to a column 
} map;



/* PROTOTYPES */
void printDirections(int row, int col, int floorLevel);
int isValidDirection(int row, int col);

monster generateMonster(monster badGuy, int floorLevel);
void printCombat(monster badGuy, character player);

int goldPickUp(int floorLevel);
character moveCharacter(char direction, map* floorMap, character player);

map* createFloor(int row, int col);
void initFloors(map* levels[]);
void fillFloor(map* levels[], int floorNum,int col, char temp[][col]);
void freeFloor(map* map);






/* Maps!
        Key: 'u' = stairs up, 'd' = stairs down,'g' = gold, 
            'm' = monster, 'i' = item, 'v' = vender/merchant
    We might eventually want to make a function that will return
    the maps instead of declaring them here?
*/


int main(){
    /*create character structure called player, assign health, 
        and start with combat bonus of 1 */
    character player;
    player.health = 100;
    player.combatBonus = 1;

    //definition of array of pointers to sctructs for each floor
    map* levels[NUM_FLOORS];

    initFloors(levels);
    

    //initialize player location on floor1
    player.row = 0;
    player.col = 0;

    monster badGuy;

    int floorLevel = 1;
    char choice;
    
    printf("You awaken in a dark cave...\n");



    while (player.health > 0){
        printDirections(player.row, player.col, floorLevel);
        scanf("%c", choice);
        player = moveCharacter(choice,levels[floorLevel],player);
        if (!isValidDirection(player.row, player.col)){
            printf("You run into a wall\n");
            continue;
        } 

        /* I think we need to figure out something else for the maps...like make their own function???*/ 
        switch (player.event){
            case 'u':
                printf("You find a set of stairs going up.\n");
                printf("You've been here before.\n");
                floorLevel++;
                break;
            case 'd':
                printf("You find a set of stairs going down.\n");
                printf("Would you like to decsend?\n");
                printf("[y]es or [n]o --> ");
                scanf("%c", &choice);

                if (choice == 'y'){
                    floorLevel--;
                }
                break;
            case 'g':
                printf("You found gold! Pick it up?\n");
                printf("[y]es or [n]o --> ");
                scanf("%c", &choice);

                if (choice == 'y'){
                    player.gold += goldPickUp(floorLevel);
                    printf("+%d gold\n",goldPickUp(floorLevel));
                } else if (choice == 'n'){
                    printf("You leave the gold.\n");
                }
                break;
            case 'm':
                printf("You run into a monster!\n");
                printf("[f]ight or [r]un?");
                scanf("%c", choice);

                if (choice =='f'){
                    generateMonster(badGuy, floorLevel);
                    printCombat(badGuy, player);
                } else if (choice =='r'){
                    printf("coward.\n");
                }
                break;
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

//moves the player in the chosen direction
character moveCharacter(char direction, map* floorStructPtr, character player){
    int maxRow = floorStructPtr->row;
    int maxCol = floorStructPtr->col;
    
    switch (direction)
    {
    case 'w':
        while(player.row >= 0){
            switch(floorStructPtr->floor[player.row][player.col]){
                case ' ':
                    player.row--;
                    break;
                case 'g':
                    player.event = 'g';
                    return player;
                    break; 
                case 'i':
                    player.event = 'i';
                    return player;
                    break;
                case 'm':
                    player.event = 'm';
                    return player;
                    break;
                case 'd':
                    player.event = 'd';
                    return player;
                    break;
                case 'u':
                    player.event = 'u';
                    return player;
                    break;
                default:
                    printf("Oh oh");
            }
        }
        break;
    case 'a':
        while(player.col >= 0){
            switch(floorStructPtr->floor[player.row][player.col]){
                case ' ':
                    player.col--;
                    break;
                case 'g':
                    player.event = 'g';
                    return player;
                    break; 
                case 'i':
                    player.event = 'i';
                    return player;
                    break;
                case 'm':
                    player.event = 'm';
                    return player;
                    break;
                case 'd':
                    player.event = 'd';
                    return player;
                    break;
                case 'u':
                    player.event = 'u';
                    return player;
                    break;
                default:
                    printf("Oh oh");
            }
        }

    case 's':
        while(player.row < maxRow){
            switch(floorStructPtr->floor[player.row][player.col]){
                case ' ':
                    player.row++;
                    break;
                case 'g':
                    player.event = 'g';
                    return player;
                    break; 
                case 'i':
                    player.event = 'i';
                    return player;
                    break;
                case 'm':
                    player.event = 'm';
                    return player;
                    break;
                case 'd':
                    player.event = 'd';
                    return player;
                    break;
                case 'u':
                    player.event = 'u';
                    return player;
                    break;
                default:
                    printf("Oh oh");
            }
        }

    case 'd':
        while(player.col < maxCol){
            switch(floorStructPtr->floor[player.row][player.col]){
                case ' ':
                    player.col++;
                    break;
                case 'g':
                    player.event = 'g';
                    return player;
                    break; 
                case 'i':
                    player.event = 'i';
                    return player;
                    break;
                case 'm':
                    player.event = 'm';
                    return player;
                    break;
                case 'd':
                    player.event = 'd';
                    return player;
                    break;
                case 'u':
                    player.event = 'u';
                    return player;
                    break;
                default:
                    printf("Oh oh");
            }
        }

    
    default:
        printf("Oh oh x2\n");
        break;
    }
    return player;
}

/*returns the amount of gold the player picks up
    based on floorLevel*/
int goldPickUp(int floorLevel){
    int gold = 2*floorLevel;
    return gold;
}

/* generates stats of the monster based on floorLevel */
monster generateMonster(monster badGuy, int floorLevel){
    badGuy.health = floorLevel * 5;
    badGuy.combatBonus = floorLevel;

    return badGuy;
}

void printCombat(monster badGuy, character player){
    printf("The monster snarls its sharp teeth at you...\n");   
}


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

