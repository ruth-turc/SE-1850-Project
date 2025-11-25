#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "textAMaps.h"

#define NUM_FLOORS 2

/* structure to represent player */
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
    int health;
    int combatBonus;
} monster;

/* PROTOTYPES */
void printDirections(int row, int col, map* floorStruct);

monster generateMonster(monster badGuy, int floorLevel);
character printCombat(monster badGuy, character player);
int combatNumber(int combatBonus);

int goldPickUp(int floorLevel);
character itemPickUp(character player);
character shop(character player, int floorLevel);

character moveCharacter(char direction, map* floorMap, character player);

map* createFloor(int row, int col);
void initFloors(map* levels[]);
void fillFloor(map* levels[], int floorNum,int col, char temp[][col]);
void freeFloor(map* map);

int main(){
    /*create character structure called player, assign health, 
        and start with combat bonus of 1 */
    character player;
    player.health = 10;
    player.maxHealth = 10;
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


    //game loop!
    while (player.health > 0){




        printf("\ncurrent position: %d %d\n",player.row,player.col);
        printDirections(player.row, player.col,levels[floorLevel-1]);
        scanf(" %c", &choice);
        player = moveCharacter(choice,levels[floorLevel-1],player);
        printf("\n");

        switch (player.event){
            case 'u': //stairs going up
                printf("You find a set of stairs going up.\n");
                printf("You've been here before.\n");
                printf("Would you like to ascend?\n");
                printf("[y]es or [n]o? --> ");
                scanf(" %c",&choice);

                if (choice == 'y'){
                    floorLevel--;
                }
                break;
            case 'd': //stairs going down
                printf("You find a set of stairs going down.\n");
                printf("Would you like to decsend?\n");
                printf("[y]es or [n]o --> ");
                scanf(" %c", &choice);

                if (choice == 'y'){
                    floorLevel++;
                }
                break;
            case 'g': //GOLD!
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
            case 'm': //monster
                printf("You run into a monster!\n");
                printf("[f]ight or [r]un? --> ");
                scanf(" %c", &choice);

                if (choice =='f'){
                    badGuy = generateMonster(badGuy, floorLevel);
                    player = printCombat(badGuy, player);
                } else if (choice =='r'){
                    printf("coward.\n\n");
                }
                break;
            case 'i': //item
                printf("It may be dark, but you think you see something on the ground...\n");
                printf("Pick it up?\n");
                printf("[y]es or [n]o? --> ");
                scanf(" %c", &choice);

                if (choice == 'y'){
                    player = itemPickUp(player);
                } else if (choice == 'n'){
                    printf("You leave the item\n");
                }
                break;
            case 'v': //vender or merchant
                printf("You run into a traveling merchant!\n");
                printf("would you like to shop?\n");
                printf("[y]es or [n]o --> \n");
                scanf(" %c", &choice);

                if (choice == 'y'){
                    player = shop(player,floorLevel);
                } else if (choice == 'n'){
                    printf("You walk away.\n");
                }
                printf("\n");
                break;
            default:
                continue;
        }

        //if player is dead, exit loop, and print death statement
        if (player.health < 1){
            printf("~~~~~~ DEATH ~~~~~~\n");
            printf("Game over, loser.\n");
            break;
        }
    }

    
    return 0;
}

/* FUNCTIONS!!!*/



/*returns the amount of gold the player picks up
    based on floorLevel*/
int goldPickUp(int floorLevel){
    int gold = 2*floorLevel;
    return gold;
}

//pick up a randomized item
character itemPickUp(character player){
    srand(time(NULL));
    int itemChoice = (rand() % 4) + 1; //random number between 1-4

    switch (itemChoice){
        case 1: //new weapon
            printf("Its a shiny new sword!!\n");
            printf("Combat Bonus +1\n");
            player.combatBonus += 1;
            break;

        case 2: //new armor
            printf("Its a new peice of amor!\n");
            printf("Max health +5\n");
            player.maxHealth += 5;
            break;

        case 3: //healing potion
            printf("Its a healing potion!\n");
            printf("+%d health",player.maxHealth);
            player.health = player.maxHealth;

        default:
            printf("You reach to grab it...but theres nothing there.\n");
            printf("Your eyes must have decieved you.\n");
    }
}

/* generates a merchant selling items
    prices are based off of floor level */
character shop(character player, int floorLevel){
    int healPrice = floorLevel*2;
    int armorPrice = floorLevel + 5;
    int weaponPrice = floorLevel + 1;
    int keepShoping = 1;
    char choice;

    printf("\t~~~SHOP~~~\n");
    printf("Items Available: \n");
    printf("Healing Potion (heal up to max HP): %d gold", healPrice);
    printf("Armor Upgrade (increase max HP): %d gold", armorPrice);
    printf("Weapon Upgrade (increase combat bonus): %d gold", weaponPrice);

    while (keepShoping){
        printf("What would you like to buy? \n");
        printf("[h]ealing potion, [a]rmor upgrade, [w]eapon upgrade --> ");
        scanf(" %c", &choice);

        switch (choice){
            case 'h':
                if (player.gold >= healPrice){
                    player.gold -= healPrice;
                    printf("-%d gold\n", healPrice);
                    printf("+%d HP\n", player.maxHealth);
                    player.health = player.maxHealth;
                } else {
                    printf("Not Enough Funds.\n");
                }
            case 'a':
                if (player.gold >= armorPrice){
                    player.gold -= armorPrice;
                    printf("-%d gold\n", armorPrice);
                    printf("+2 max HP\n");
                    player.maxHealth += 2;
                } else {
                    printf("Not Enough Funds.\n");
                }
            case 'w':
                if (player.gold >= weaponPrice){
                    player.gold -= weaponPrice;
                    printf("-%d gold\n", weaponPrice);
                    printf("+2 combat bonus HP\n");
                    player.combatBonus += 2;
                } else {
                    printf("Not Enough Funds.\n");
                }
            default:
                printf("Item not recognized. Try again.\n");
                continue;
        }

        printf("Would you like to keep shoping?");
        printf("[y]es please! or [n]o, I'm broke :( --> ");
        scanf(" %c", &choice);
        if (choice == 'n'){
            keepShoping = 0;
        }
    }
    return player;
}

/* generates stats of the monster based on floorLevel */
monster generateMonster(monster badGuy, int floorLevel){
    badGuy.health = floorLevel*3;
    badGuy.combatBonus = floorLevel;

    return badGuy;
}

//print and execute combat
character printCombat(monster badGuy, character player){
    printf("The monster snarls its sharp teeth at you...\n\n");
    int playerDamage;
    int monsterDamage;
    char attack;

    //prompt user to attack
    printf("Enter any key to attack --> ");
    scanf(" %c",&attack);

    //Player attacks
    playerDamage = combatNumber(player.combatBonus);
    badGuy.health = badGuy.health -  playerDamage;
    printf("You delt %d damage!\n", playerDamage);
    printf("\n");

    //while the player is still alive and the monster is still alive
    while (badGuy.health >= 0){

        //moster attacks
        printf("The monster swings at you...\n");
        monsterDamage = combatNumber(badGuy.combatBonus);
        player.health -= monsterDamage;
        printf("The monster hit you for %d damage!\n",monsterDamage);
        printf("\n");

        if (player.health < 1){
            break; 
        }

        //prompt player to attack
        printf("Enter any key to attack --> ");
        scanf(" %c",&attack);

        //player attacks
        playerDamage = combatNumber(player.combatBonus);
        badGuy.health -= playerDamage;
        printf("You delt %d damage!\n", playerDamage);
        printf("\n");
    }
    
    if (badGuy.health < 1){
        printf("\n~~~~~~ VICTORY! ~~~~~~\n\n");
    }   

    return player;
}

int combatNumber(int combatBonus){
    srand(time(NULL));
    int combatNumber = (rand() % 6) + 1; //random number between 1-6
    combatNumber += combatBonus;

    return combatNumber;
}