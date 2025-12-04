#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "textACombat.h"


/* generates stats of the monster based on floorLevel */
monster generateMonster(monster badGuy, int floorLevel){
    badGuy.health = floorLevel*3;
    badGuy.combatBonus = floorLevel;

    return badGuy;
}

/* determines wether or not the player can run away.
    base percent of 75% plus player combat bonus*/
int runAway(character player){
    srand(time(NULL));
    int runAway = (rand() % 100) + 1; // random Number between 1 - 100
    runAway += player.combatBonus;

    if (runAway >= 25){
        return 0;
    } else {
        return 1;
    }
}

//print and execute combat
character printCombat(monster badGuy, character player,int floorLevel){
    printf("The monster snarls its sharp teeth at you...\n\n");
    int playerDamage;
    int monsterDamage;
    char attack;
    char choice;

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
        printf("loot the monster?\n");
        printf("[y]es or [n]o --> ");
        scanf(" %c", &choice);

        while(choice != 'y' && choice != 'n'){
            printf("not one of the options!\n");
            printf("[y]es or [n]o --> ");
            scanf(" %c", &choice);
        }
        if (choice == 'y'){
            player = monsterDrops(player,floorLevel);
        } else {
            printf("You leave the monster.\n");
            printf("It looked too gross to touch anyway.\n");
        }
    }   

    return player;
}

/* generates a random number for combat */
int combatNumber(int combatBonus){
    srand(time(NULL));
    int combatNumber = (rand() % 6) + 1; //random number between 1-6
    combatNumber += combatBonus;

    return combatNumber;
}

/* prints and executes combat of the final boss, a dragon! */
character finalBoss(character player){
    monster dragon = generateMonster(dragon, 4);
    int playerDamage;
    int monsterDamage;
    char attack;

    printf("\n\nAfter stumbling through the dark dungeon, you finally reach the end...\n");
    printf("Or so you thought...\n\n");
    printf("Something stands in your way of freedom...\n");
    printf("A dragon.\n\n");

    printf("Press any key to attack --> ");
    scanf(" %c",&attack);

    //player attacks
    playerDamage = combatNumber(player.combatBonus);
    dragon.health = dragon.health -  playerDamage;
    printf("You delt %d damage!\n", playerDamage);
    printf("\n");

    while (dragon.health >= 0){

        //dragon attacks
        printf("The dragon swings at you...\n");
        monsterDamage = combatNumber(dragon.combatBonus);
        player.health -= monsterDamage;
        printf("The dragon hit you for %d damage!\n",monsterDamage);
        printf("\n");

        if (player.health < 1){
            break; 
        }

        //prompt player to attack
        printf("Enter any key to attack --> ");
        scanf(" %c",&attack);

        //player attacks
        playerDamage = combatNumber(player.combatBonus);
        dragon.health -= playerDamage;
        printf("You delt %d damage!\n", playerDamage);
        printf("\n");
    }
    
    if (dragon.health < 1){
        printf("\n~~~~~~ VICTORY! ~~~~~~\n");
        printf("You have defeated the dragon!\n\n");
    }   else if (player.health < 1){
        printf("\n~~~~~~ DEATH ~~~~~~\n");
        printf("You were so close...\n");
        printf("Better luck next time :)\n");
    }

}