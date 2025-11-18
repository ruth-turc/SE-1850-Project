#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>


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
void printDirections(int row, int col, int floorLevel);
int isValidDirection(int row, int col);

monster generateMonster(monster badGuy, int floorLevel);
void printCombat(monster badGuy, character player);
int combatNumber(int combatBonus);

int goldPickUp(int floorLevel);
character moveCharacter(char direction, char floorMap[][], character player);




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
    /*create character structure called player, assign health, 
        and start with combat bonus of 1 */
    character player;
    player.health = 100;
    player.combatBonus = 1;

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
        //add move character
        if (!isValidDirection(player.row, player.col)){
            printf("You run into a wall");
            continue;
        } 

        /* I think we need to figure out something else for the maps...like make their own function???*/
        switch (player.event){
            case 'u':
                printf("You find a set of stairs going up.\n");
                printf("You've been here before.\n");
                break;
            case 'd':
                printf("You find a set of stairs going down.\n");
                printf("Would you like to decsend?\n");
                printf("[y]es or [n]o --> ");
                scanf("%c", &choice);

                if (choice == 'y'){
                    floorLevel++;
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

        if (player.health < 1){
            printf("~~~~~~ DEATH ~~~~~~\n");
            printf("Game over, loser.\n");
            break;
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

character moveCharacter(char direction, char floorMap[][3], character player){
    int maxRow = sizeof(floorMap) / sizeof(floorMap[0]);
    int maxCol = sizeof(floorMap[0]) / sizeof(floorMap[0][0]);
    switch (direction)
    {
    case 'w':
        while(player.row >= 0){
            switch(floorMap[player.row][player.col]){
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
            switch(floorMap[player.row][player.col]){
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
            switch(floorMap[player.row][player.col]){
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
            switch(floorMap[player.row][player.col]){
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
    int playerDamage;
    int monsterDamage;
    char attack;

    //prompt user to attack
    printf("The monster snarls its sharp teeth at you...\n");
    printf("Enter any key to attack --> \n");
    scanf("%c",attack);

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
        scanf("%c",attack);

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