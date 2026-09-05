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

    char (*selected_cat)[50];

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

    getch();    //wait for user input

    endwin();    //leave ncurses mode

}