//
// Created by pabluxfirpux on 12/20/25.
//

#include "screen.h"

#include <ncurses.h>
#include <string.h>
#include <stdbool.h>

void turnHighlightMode(bool on) {
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    if (on) {
        attron(COLOR_PAIR(1));
    } else {
        attroff(COLOR_PAIR(1));
    }
}


void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string)
{	int length, x, y;
    float temp;

    if(win == NULL)
        win = stdscr;
    getyx(win, y, x);
    if(startx != 0)
        x = startx;
    if(starty != 0)
        y = starty;
    if(width == 0)
        width = 80;

    length = strlen(string);
    temp = (width - length)/ 2;
    x = startx + (int)temp;
    mvwprintw(win, y, x, "%s", string);
    refresh();
}

void test_Colors() {
    initscr();			/* Start curses mode 		*/
    if(has_colors() == FALSE)
    {	endwin();
        printf("Your terminal does not support color\n");
        endwin();
        return;
    }
    start_color();			/* Start color 			*/
    turnHighlightMode(true);
    print_in_middle(stdscr, LINES / 2, 0, 0, "Viola !!! In color ...");
    turnHighlightMode(false);
    getch();
    endwin();
}