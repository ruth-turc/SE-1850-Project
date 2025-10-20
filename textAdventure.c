#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* PROTOTYPES */
int calculatePlayerBonus(const char inventory[]);
int playerCombatNumber(int playerBonus);
int monsterCombatNumber(int floor level);
int goldPickUp(int floor level);

/* global variables */
int playerHP;

/* Maps!
        Key: 'u' = stairs up, 'd' = stairs down,'g' = gold, 
            'm' = monster, 'i' = item, 'v' = vender/merchant

    We might want to eventually move these to their own file 
    and use a pointer?
*/
char floor1[][] = {' ','m','g'}
                  {' ',' ','d'};

char floor2[][] = {' ','i','d'}
                  {'u','m',' '}
                  {' ',' ','g'};
int main(){
    char inventory[10];
    int playerHP = 100;
    return 0;
}

