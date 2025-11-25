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