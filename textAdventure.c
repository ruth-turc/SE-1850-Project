#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* PROTOTYPES */
int calculatePlayerBonus(const char inventory[]);
int playerCombatNumber(int playerBonus);
int monsterCombatNumber(int floorLevel);
int goldPickUp(int floorLevel);

/* global variables */
int playerHP;

/* Maps!
        Key: 'u' = stairs up, 'd' = stairs down,'g' = gold, 
            'm' = monster, 'i' = item, 'v' = vender/merchant
*/
char floor1[2][3] = {{' ','m','g'},
                  {' ',' ','d'}};

char floor2[3][3] = {{' ','i','d'},
                  {'u','m',' '},
                  {' ',' ','g'}};

char floor3[3][2] = {{'g','v'},
                     {'g','u'},
                     {'d','g'}};
int main(){
    char inventory[10];
    int playerHP = 100;
    return 0;
}

