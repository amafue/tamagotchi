#define _XOPEN_SOURCE_EXTENDED 1
#include <ncurses.h>
#include <locale.h>

#define MENU_COUNT 3
#define ACTION_COUNT 3
#define STATE_MENU 0
#define STATE_GAME 1

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
    int choice = -1;

    const char *choices[] = {   //array of pointer addresses OJO
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
                    mvprintw(3+i, 4, "> %s <", choices[i]);
                    attroff(A_REVERSE); //clears inverted color, return to normal text styling
                }else
                {
                    mvprintw(3+i, 6, "%s", choices[i]);
                }
            }

            mvprintw(8, 2, "UP/DOWN arrows to move, ENTER to select");
            refresh();

            input = getch();

            switch (input)
            {
            case KEY_UP:
                menu_selected--;    //go to back one index
                if (menu_selected < 0)  //if index goes from 0 to -1
                {
                    menu_selected = MENU_COUNT - 1; //go to last index (2 in this case)
                }
                break;

            case KEY_DOWN:
                menu_selected++;
                if (menu_selected >= MENU_COUNT)
                {
                    menu_selected = 0;
                }
                break;

            case 10:
            case KEY_ENTER:
                choice = menu_selected;

                if (choice == 2)
                {
                    endwin();
                    return 0;
                }else if (choice == 1)
                {
                    state = STATE_GAME;

                } else if (choice == 0)
                {
                    /* code */
                }
                 
                mvprintw(9,2,"You selected: %s\n", choices[choice]);
                refresh();  //updates the terminal
                getch();    //waits for user to press a key
                endwin();
            default:    
                break;
            }

        } else if (state == STATE_GAME)
        {
            mvprintw(1,2,"Your pet:\n\n\n");
            for(int i = 0; i<3; i++){
                printw("%s\n",selected_cat[i]);
            };
        }
        
        refresh();
        input = getch();
    }
    
    
    refresh();  //push changes to the visible screen

    // getch();    //wait for user input

    endwin();    //leave ncurses mode
    return 0;

}