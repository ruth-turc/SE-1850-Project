#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* PROTOTYPES */
int calculatePlayerBonus(const char inventory[]);
int playerCombatNumber(int playerBonus);
int monsterCombatNumber(int floorLevel);
int goldPickUp(int floorLevel);

/* structure to represent player */
struct character {
    int health;
    char name[50];
    char inventory[10];
};

/* Maps!
        Key: 'u' = stairs up, 'd' = stairs down,'g' = gold, 
            'm' = monster, 'i' = item, 'v' = vender/merchant
    We might eventually want to make a function that will return
    the maps instead of declaring them here?
*/
char floor1[][3] = {{' ','m','g'},
                  {' ',' ','d'}};

char floor2[][3] = {{' ','i','d'},
                  {'u','m',' '},
                  {' ',' ','g'}};

int main(){
    //create character structure called player and assign health
    struct character player;
    player.health = 100;
    char choice[50];
    
    //ask player for name
    printf("~~~~ Welcome Adventurer! ~~~~\n");
    printf("Please Enter your name ---> ");
    scanf("%s",&player.name);

    printf("%s, are you ready to start exploring?\n ",player.name);
    printf("[yes] or [no] ---> ");
    scanf("%s", &choice);

    if (strcmp(choice,"no" == 0)){
        printf("Well, that's too bad...you don't have a choice.");
    }

    return 0;
}

