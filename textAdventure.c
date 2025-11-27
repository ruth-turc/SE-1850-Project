#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#include "textAMaps.h"
#include "textAMove.h"
#include "textACombat.h"
#include "textAEvents.h"

#define NUM_FLOORS 4

int main(){
    /*create character structure called player, assign health, 
        and start with combat bonus of 1 */
    character player;
    player.health = 10;
    player.maxHealth = 10;
    player.combatBonus = 1;
    player.gold = 0;

    //definition of array of pointers to sctructs for each floor
    map* levels[NUM_FLOORS];

    initFloors(levels); //initialize floors
    

    //initialize player location on floor1
    player.row = 0;
    player.col = 0;

    monster badGuy;

    int floorLevel = 1;
    char choice;

    printf("~~~ WELCOME TO TEXT ADVENTURE! ~~~\n\n");

    printf("Would you like a toutorial?\n");
    printf("[y]es or [n]o? --> ");
    scanf(" %c", &choice);

    while (choice != 'y' && choice != 'n'){
        printf("Not an option!\n\n");
        printf("[y]es or [n]o? --> ");
        scanf(" %c", &choice);
    }
    if (choice == 'y'){
        printf("\nText Adventure is a dungeon crawler type game.\n");
        printf("To play, you will be tasked with finding your way to the bottom of the dungeon.\n");
        printf("\nThe dungeon is littered with monsters, and they get stronger as the dungeon gets deeper.\n");
        printf("In order to survive, you will want to pick up any item or gold you see, and ");
        printf("loot any monster you have the chance.\n\n");

        printf("Ready to play?\n");
        printf("[y]es! --> ");
        scanf(" %c", &choice);

        printf("\n\n\n\n");
    } else {
        printf("\n\n\n\n");
    }
    
    printf("You awaken in a dark cave...\n");


    //game loop!
    while (player.health > 0){

        printf("\ncurrent position: %d %d\n",player.row,player.col);
        printf("current HP: %d\n", player.health);
        printf("current level: -%d\n\n",floorLevel);

        //if player has reached the final floor, start boss fight
        if (floorLevel == NUM_FLOORS){
            finalBoss(player);
            break;
        }
        
        printDirections(player.row, player.col,levels[floorLevel-1]);
        scanf(" %c", &choice);

        while(choice != 'w' && choice != 'a' && choice != 's' && choice != 'd'){
            printf("Wrong Input!\n\n");
            printDirections(player.row, player.col,levels[floorLevel-1]);
            scanf(" %c", &choice);
        }

        player = moveCharacter(choice,levels[floorLevel-1],player);
        printf("\n");

        switch (player.event){
            case 'u': //stairs going up
                printf("You find a set of stairs going up.\n");
                printf("You've been here before.\n");
                printf("Would you like to ascend?\n");
                printf("[y]es or [n]o? --> ");
                scanf(" %c",&choice);
                
                while(choice != 'y' && choice != 'n'){
                    printf("not one of the options!\n");
                    printf("Would you like to ascend?\n");
                    printf("[y]es or [n]o --> ");
                    scanf(" %c", &choice);
                }
                if (choice == 'y'){
                    floorLevel--;
                    player.event = 'd';
                }
                break;
            case 'd': //stairs going down
                printf("You find a set of stairs going down.\n");
                printf("Would you like to decsend?\n");
                printf("[y]es or [n]o --> ");
                scanf(" %c", &choice);

                while(choice != 'y' && choice != 'n'){
                    printf("not one of the options!\n");
                    printf("Would you like to decsend?\n");
                    printf("[y]es or [n]o --> ");
                    scanf(" %c", &choice);
                }
                if (choice == 'y'){
                    floorLevel++;
                    player.event = 'u';
                    }
                
                
                break;
            case 'g': //GOLD!
                printf("You found gold! Pick it up?\n");
                printf("[y]es or [n]o --> ");
                scanf(" %c", &choice);
                
                while(choice != 'y' && choice != 'n'){
                    printf("not one of the options!\n");
                    printf("[y]es or [n]o --> ");
                    scanf(" %c", &choice);
                }

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

                while(choice != 'f' && choice != 'r'){
                    printf("not one of the options!\n");
                    printf("[f]ight or [r]un? --> ");
                    scanf(" %c", &choice);
                }

                if (choice =='f'){
                    badGuy = generateMonster(badGuy, floorLevel);
                    player = printCombat(badGuy, player, floorLevel);
                } else if (choice =='r'){
                    printf("coward.\n\n");
                }
                break;
            case 'i': //item
                printf("It may be dark, but you think you see something on the ground...\n");
                printf("Pick it up?\n");
                printf("[y]es or [n]o? --> ");
                scanf(" %c", &choice);
                
                while(choice != 'y' && choice != 'n'){
                    printf("not one of the options!\n");
                    printf("[y]es or [n]o --> ");
                    scanf(" %c", &choice);
                }

                if (choice == 'y'){
                    player = itemPickUp(player);
                } else if (choice == 'n'){
                    printf("You leave the item\n");
                }
                break;
            case 'v': //vender or merchant
                printf("You run into a traveling merchant!\n");
                printf("would you like to shop?\n");
                printf("[y]es or [n]o --> ");
                scanf(" %c", &choice);

                while(choice != 'y' && choice != 'n'){
                    printf("not one of the options!\n");
                    printf("[y]es or [n]o --> ");
                    scanf(" %c", &choice);
                }

                if (choice == 'y'){
                    player = shop(player,floorLevel);
                } else if (choice == 'n'){
                    printf("You walk away.\n");
                }
                printf("\n");
                break;
            default:
                printf("just a wall\n");
                continue;
        }

        //if player is dead, exit loop, and print death statement
        if (player.health < 1){
            printf("~~~~~~ DEATH ~~~~~~\n");
            printf("Game over, loser.\n");
            break;
        }

    }

    for(int i = 0; i < NUM_FLOORS; i++){
        freeFloor(levels[i]);
    }

    
    return 0;
}