#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "textAEvents.h"

/*returns the amount of gold the player picks up
    based on floorLevel*/
int goldPickUp(int floorLevel){
    int gold = 2*floorLevel;
    return gold;
}

/* pick up a randomized item */
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
            break;

        default:
            printf("You reach to grab it...but theres nothing there.\n");
            printf("Your eyes must have decieved you.\n");
            break;
    }

    return player;
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
        printf("[y]es please! or [n]o, I'm broke. --> ");
        scanf(" %c", &choice);
        if (choice == 'n'){
            keepShoping = 0;
        }
    }
    return player;
}

character monsterDrops(character player, int monsterHealth){
    srand(time(NULL));
    int lootFound = (rand() % 4) + 1;

    int goldAmount = monsterHealth;
    int amountHealed = player.maxHealth - player.health;
    
    switch (lootFound){
        case 1:
            printf("You find a healing potion!\n");
            printf("It must have been left by a previous explorer\n");
            printf("+%d health",amountHealed);
            player.health = player.maxHealth;
            break;
        case 2:
            printf("You find the weapon the monster was using.\n");
            printf("It looks pretty beat up, but it is sharper than your sword.\n");
            printf("+1 combat bonus!\n");
            player.combatBonus += 1;
            break;
        case 3:
            printf("The monster was wearing a bit of armor.\n");
            printf("You could get better use out of it...the monsters can't use it if its dead.\n");
            printf("+1 max health");
            player.maxHealth += 1;
            break;
        default:
            printf("You find gold!\n");
            player.gold += goldAmount;
            printf("+%d gold.\n",goldAmount);
            break;

    }
    
    return player;
}