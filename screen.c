#define _XOPEN_SOURCE_EXTENDED 1
#include <ncurses.h>
#include <locale.h>
#include <stdio.h>

#include "save.h"
#include "pet.h"

#define MENU_COUNT 3
#define STATE_MENU 0
#define STATE_GAME 1
#define GAME_BTNS 4
#define STATE_QUIT 2

extern char pet_name[50];
extern int hunger;
extern int happiness;
extern int stress;

int draw_menu(void){

    keypad(stdscr, TRUE);
    cbreak();   
    noecho();  
    curs_set(0); 

    static int menu_selected = 0;  //tracks which menu option is currently highlighted
    int input = 0;  //stores key int code returned by getch()
    int choice = -1;

    const char *choices[] = {   //array of pointer addresses
        "New Game",
        "Continue",
        "Quit"
    };

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
            return STATE_QUIT;    
        }else if (choice == 1)
        {
            load_game();
            return STATE_GAME;

        } else if (choice == 0)
        {
            new_game();
            return STATE_GAME;
        }
    default:    
        break;
    }
    return STATE_MENU;
}

// char naming_pet(){
    
// }

int draw_game(void){

    keypad(stdscr, TRUE);
    cbreak();   
    noecho();  
    curs_set(0);   

    static int btn_selected = 0;
    int choice = -1;
    int input = 0;

    const char *choices[] = {
        "Feed",
        "Mini Game",
        "Sleep",
        "Quit"
    };

    static bool is_sleep = false;
    bool is_happy = (happiness>75);
    bool is_hungry = (hunger<30);
    bool is_stress = (stress<70);

    render_pet(is_happy,is_hungry,is_sleep, is_stress);

    mvprintw(1,0,"Name: %s", pet_name);
    mvprintw(1,20,"Hunger: %d", hunger);
    mvprintw(1,40,"Happiness: %d", happiness);
    mvprintw(1,60,"Energi: %d", stress);

    for (int i = 0; i < GAME_BTNS; i++)
    {
        if (i == btn_selected)
        {
            attron(A_REVERSE);  //inverts foreground and background text colors
            mvprintw(8, i*20, "> %s <", choices[i]);
            attroff(A_REVERSE); //clears inverted color, return to normal text styling
        }else
        {
            mvprintw(8, i*20, "%s", choices[i]);
        }
    }

    refresh();

    nodelay(stdscr, TRUE);

    input =getch();

    switch (input)
    {
        case KEY_LEFT:
            btn_selected--;    //go to back one index
            if (btn_selected < 0)  //if index goes from 0 to -1
            {
                btn_selected = GAME_BTNS - 1; //go to last index (2 in this case)
            }
            break;

        case KEY_RIGHT:
            btn_selected++;    //go to back one index
            if (btn_selected >= GAME_BTNS)  //if index goes from 0 to -1
            {
                btn_selected = 0; //go to last index (2 in this case)
            }
            break;
        
        case 10:
            case KEY_ENTER:
                choice = btn_selected;

                if (choice == 3)
                {
                    return STATE_MENU;

                } else if (choice == 0)
                {
                    hunger=100;
                    is_sleep=false;
                }else if (choice == 1)
                {
                    //minigame
                    happiness=100;
                    is_sleep=false;
                }else if (choice == 2)
                {
                    is_sleep = true;
                    stress = 100;
                }
                
                mvprintw(10,0,"You selected: %s\n", choices[btn_selected]);
                refresh();
                break;

        default:
            break;
    }

    return STATE_GAME;
}