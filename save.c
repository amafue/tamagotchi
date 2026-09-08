#define _XOPEN_SOURCE_EXTENDED 1
#include <ncurses.h>
#include <locale.h>
#include <stdio.h>

char pet_name[50];
int hunger;
int happiness;
int stress;

void load_game(void){
    FILE *file = fopen("gameplay.txt", "r");

    if (file == NULL) return;
    {
        /* code */
    }
    

    char text[150];
    
    fgets(text, 150, file);

    fclose(file);


}

void save_game(void){

    FILE *file = fopen("gameplay.txt", "w");

    fprintf(file, "%s\n", pet_name);
    fprintf(file, "%d\n", hunger);
    fprintf(file, "%d\n", happiness);
    fprintf(file, "%d\n", stress);

    fclose(file);
}

void new_game(void){
    hunger = 100;
    happiness = 100;
    stress = 100;
}

