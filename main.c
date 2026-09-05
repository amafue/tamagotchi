#define _XOPEN_SOURCE_EXTENDED 1
#include <ncurses.h>
#include <locale.h>

#define MENU_COUNT 3
#define ACTION_COUNT 3
#define STATE_MENU 0
#define STATE_GAME 0

int main(int argc, char **argv)
{

    setlocale(LC_ALL, "");  //enables c to process nnon standard char

    initscr();  //enter ncurses mode
    cbreak();   //characters are saved in a buffer intil press enter
    noecho();   //disables automatic printing of keys
    curs_set(0);    //hide blinking cursor
    keypad(stdscr, TRUE);   //enables capture special keys input, like arrow keys

    int state = STATE_MENU; //remembers which is screen is active (menu/game)
    int menu_selected = 0;  //tracks which menu option is currently highlighted
    int game_selected = 0;
    int input = 0;  //stores key int code returned by getch()

    const char *main_menu[MENU_COUNT] = {   //array of pointer addresses OJO
        "New Game",
        "Continue",
        "Quit"
    };

    bool is_happy = false;
    bool is_hungry = false;
    bool is_sleep = false;
    bool is_stress = false;

    char default_cat[][50] = {
        "       /\\______/\\",
        "     >| ˶ • ᴛ • ˶|< ",
        "      /    𝇌♡𝇋   \\",
    };

    char hungry_cat[][50] = {
        "       /\\______/\\",
        "     >| ˶ o ᴛ o ˶|< ",
        "      /    𝇌♡𝇋   \\",
    };

    char happy_cat[][50] = {
        "       /\\______/\\",
        "     >| ˶ > ᴛ < ˶|< ",
        "      /    𝇌♡𝇋   \\",
    };

    char sleep_cat[][50] = {
        "       /\\______/\\",
        "     >|  〰 ᴛ 〰 |< ",
        "      /    𝇌♡𝇋   \\",
    };

    char stress_cat[][50] = {
        "       /\\______/\\",
        "     >| ˶ @ ᴛ @ ˶|< ",
        "      /    𝇌♡𝇋   \\",
    };


    while (1)
    {
        clear();

        if (state== STATE_MENU)
        {
            mvprintw(1,2,"Virtual Pet Menu");
            for (int i = 0; i < MENU_COUNT; i++)
            {
                if (i == menu_selected)
                {
                    attron(A_REVERSE);  //inverts foreground and background text colors
                    mvprintw(3+i, 4, "> %s <", main_menu);
                    attroff(A_REVERSE); //clears inverted color, return to normal text styling
                }else
                {
                    mvprintw(3+i, 6, "%s", main_menu[i]);
                }
            }

            mvprintw(8, 2, "UP/DOWN arrows to move, ENTER to select");
            refresh();

            input = getch();

            
        }
        
    }
    


    char (*selected_cat)[50] = default_cat;   //pointer to the array

    if (is_happy)
    {
        selected_cat = happy_cat;
    } else if (is_hungry)
    {
        selected_cat = hungry_cat;
    } else if (is_sleep)
    {
        selected_cat = sleep_cat;
    } else if (is_stress)
    {
        selected_cat = stress_cat;
    } else
    {
        selected_cat = default_cat;
    }

    for(int i = 0; i<3; i++){
            printw("%s\n",selected_cat[i]);
        };
    
    refresh();  //push changes to the visible screen

    // getch();    //wait for user input

    endwin();    //leave ncurses mode

}