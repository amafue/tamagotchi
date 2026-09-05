#define _XOPEN_SOURCE_EXTENDED 1
#include <ncurses.h>
#include <locale.h>

int main(int argc, char **argv)
{

    setlocale(LC_ALL, "");  //enables c to process nnon standard char

    initscr();  //enter ncurses mode
    cbreak();   //characters are saved in a buffer intil press enter
    noecho();   //disables automatic printing of keys

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

    if (is_happy)
    {
        for(int i = 0; i<3; i++){
            printw("%s\n",happy_cat[i]);
        };
    } else if (is_hungry)
    {
        for(int i = 0; i<3; i++){
            printw("%s\n",hungry_cat[i]);
        };
    } else if (is_sleep)
    {
        for(int i = 0; i<3; i++){
            printw("%s\n",sleep_cat[i]);
        };
    } else if (is_stress)
    {
        for(int i = 0; i<3; i++){
            printw("%s\n",stress_cat[i]);
        };
    } else
    {
        for(int i = 0; i<3; i++){
            printw("%s\n",default_cat[i]);
        };
    }
    
    
    
    
    

    refresh();  //push changes to the visible screen

    getch();    //wait for user input

    endwin();    //leave ncurses mode

}