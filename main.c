#define _XOPEN_SOURCE_EXTENDED 1
#include <ncurses.h>
#include <locale.h>
#include <stdio.h>

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

int draw_game(char pet_name[], int hunger, int happiness, int stress){

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
        mvprintw(i+3,28,"%s\n",selected_cat[i]);
    };

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

                }
                
                    
                mvprintw(10,0,"You selected: %s\n", choices[btn_selected]);
                refresh();
                break;

        default:
            break;
    }

    return STATE_GAME;
}

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
        return 0;
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