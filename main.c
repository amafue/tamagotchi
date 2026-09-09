#define _XOPEN_SOURCE_EXTENDED 1
#include <ncurses.h>
#include <locale.h>
#include <stdio.h>
#include "save.h"
#include "screen.h"
#include "pet.h"
#include <time.h>
#include <unistd.h>

#define STATE_MENU 0
#define STATE_GAME 1
#define STATE_QUIT 2

char pet_name[50];
int hunger;
int happiness;
int stress;

int main(int argc, char **argv)
{
    int draw_game();
    setlocale(LC_ALL, "");  //enables c to process nnon standard char

    initscr();  //enter ncurses mode
    cbreak();   //characters are saved in a buffer intil press enter
    noecho();   //disables automatic printing of keys
    curs_set(0);    //hide blinking cursor
    keypad(stdscr, TRUE);   //enables capture special keys input, like arrow keys
 
    int state = STATE_MENU; //remembers which is screen is active (menu/game)
    time_t last_hun_update = time(NULL);
    time_t last_strs_update=time(NULL);
    time_t last_happ_update=time(NULL);

    while (state != STATE_QUIT)
    {

        if (state == STATE_GAME)
        {
            time_t now = time(NULL);
            if (now - last_hun_update >= 20)
            {
                hunger-=5;
                last_hun_update = now;
            }
            if (now - last_strs_update >= 25)
            {
                stress-=5;
                last_strs_update = now;
            }
            if(now - last_happ_update >= 15)
            {
                happiness-=5;
                last_happ_update = now;
            }
        }

        clear();

        if (state== STATE_MENU)
        {
            nodelay(stdscr, FALSE);
            state = draw_menu();

        } else if (state == STATE_GAME)
        {
            nodelay(stdscr, TRUE);
            state = draw_game();
        }
        
        refresh();
        napms(100);   //pause for 100 mls
    }

    endwin();    //leave ncurses mode
    return 0;

}