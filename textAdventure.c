#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "textAMaps.h"

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




/* PROTOTYPES */
void printDirections(int row, int col, map* floorStruct);

monster generateMonster(monster badGuy, int floorLevel);
void printCombat(monster badGuy, character player);
int combatNumber(int combatBonus);

int goldPickUp(int floorLevel);
character moveCharacter(char direction, map* floorMap, character player);







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
        printf("\ncurrent position: %d %d\n",player.row,player.col);
        printDirections(player.row, player.col,levels[floorLevel-1]);
        scanf(" %c", &choice);
        player = moveCharacter(choice,levels[floorLevel-1],player);
        

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
                scanf(" %c", &choice);

                if (choice == 'y'){
                    floorLevel--;
                }
                break;
            case 'g':
                printf("You found gold! Pick it up?\n");
                printf("[y]es or [n]o --> ");
                scanf(" %c", &choice);

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
                scanf(" %c", &choice);

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
            default:
                printf("nothing here\n");
                continue;
        }

        if (player.health < 1){
            printf("~~~~~~ DEATH ~~~~~~\n");
            printf("Game over, loser.\n");
            break;
        }
    }

    
    return 0;
}

/* FUNCTIONS!!!*/

void printDirections(int row, int col, map* floorStruct){
    //find the max row and column index for a specific floor level
    int max_row, max_col;
    max_row = floorStruct->row - 1;
    max_col = floorStruct->col -1;
    printf("max row: %d\n",max_row);
    printf("max col: %d\n", max_col);

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

    if(floorStructPtr->floor[player.row][player.col] == '\0'){
        printf("ERROR, NULL\n");
        return player;
    }
    
    switch (direction)
    {
    case 'w':
        while(player.row > 0){
            player.row--;
            switch(floorStructPtr->floor[player.row][player.col]){
                case ' ':
                    continue;
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
                    printf("Oh oh - w - '%c'\n",floorStructPtr->floor[player.row][player.col]);
            }
        }
        break;
    case 'a':
        while(player.col > 0){
            player.col--;
            switch(floorStructPtr->floor[player.row][player.col]){
                case ' ':
                    continue;
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
                    printf("Oh oh - a - '%c'\n",floorStructPtr->floor[player.row][player.col]);
            }
        }
        break;

    case 's':
        while(player.row < maxRow){
            player.row++;
            switch(floorStructPtr->floor[player.row][player.col]){
                case ' ':
                    continue;
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
                    printf("Oh oh - s - '%c'\n",floorStructPtr->floor[player.row][player.col]);
            }
        }
        break;

    case 'd':
        while(player.col < maxCol){
            player.col++;
            switch(floorStructPtr->floor[player.row][player.col]){
                case ' ':
                    continue;
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
                    printf("Oh oh - d - '%c'\n",floorStructPtr->floor[player.row][player.col]);
            }
        }
        break;

    
    default:
        printf("Wrong Input!\n");
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
    int playerDamage;
    int monsterDamage;
    char attack;

    //prompt user to attack
    printf("The monster snarls its sharp teeth at you...\n");
    printf("Enter any key to attack --> \n");
    scanf(" %c",&attack);

    //Player attacks
    playerDamage = combatNumber(player.combatBonus);
    badGuy.health -= playerDamage;
    printf("You delt %d damage!\n", playerDamage);

    //while the player is still alive and the monster is still alive
    while ((badGuy.health >= 1)||(player.health >= 1)){
        //moster attacks
        printf("The monster swings at you...\n");
        monsterDamage = combatNumber(badGuy.combatBonus);
        player.health -= monsterDamage;
        printf("The monster hit you for %d damage!\n",monsterDamage);

        //prompt player to attack
        printf("Enter any key to attack --> \n");
        scanf(" %c",&attack);

        //player attacks
        playerDamage = combatNumber(player.combatBonus);
        badGuy.health -= playerDamage;
        printf("You delt %d damage!\n", playerDamage);
        
    }
    
    if (badGuy.health < 1){
        printf("~~~~~~ VICTORY! ~~~~~~\n");
    }   
}

int combatNumber(int combatBonus){
    srand(time(NULL));
    int combatNumber = (rand() % 6) + 1; //random number between 1-6
    combatNumber += combatBonus;

    return combatNumber;
}

