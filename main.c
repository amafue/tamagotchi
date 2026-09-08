#define _XOPEN_SOURCE_EXTENDED 1
#include <ncurses.h>
#include <locale.h>
#include <stdio.h>
#include "save.h"
#include "screen.h"
#include "pet.h"

#define MENU_COUNT 3
#define ACTION_COUNT 3
#define STATE_MENU 0
#define STATE_GAME 1
#define GAME_BTNS 4
#define STATE_QUIT 2

char pet_name[50];
int hunger;
int happiness;
int stress;
int draw_menu(void);

int main(int argc, char **argv)
{
    void load_game(void);
    void update_game(void);
    void new_game(void);
    int draw_game(char pet_name[], int hunger, int happiness, int stress);
    

    setlocale(LC_ALL, "");  //enables c to process nnon standard char

    initscr();  //enter ncurses mode
    cbreak();   //characters are saved in a buffer intil press enter
    noecho();   //disables automatic printing of keys
    curs_set(0);    //hide blinking cursor
    keypad(stdscr, TRUE);   //enables capture special keys input, like arrow keys
 
    int state = STATE_MENU; //remembers which is screen is active (menu/game)
    int input = 0;  //stores key int code returned by getch()

    while (state != STATE_QUIT)
    {
        clear();

        if (state== STATE_MENU)
        {
            state = draw_menu();

        } else if (state == STATE_GAME)
        {
            state = draw_game(pet_name, hunger, happiness, stress);
        }
        
        refresh();
    }
    
    
    refresh();  //push changes to the visible screen

    // getch();    //wait for user input

    endwin();    //leave ncurses mode
    return 0;

}