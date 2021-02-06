 "bored.h"

#include <ncurses.h>

#include <iostream>

int main(void) {

  initscr();
  cbreak();
  noecho();

  WINDOW * win = newwin(LINES, COLS, 0, 0);
  keypad(win, TRUE);
  nodelay(win, TRUE);


  wrefresh(win);

  delwin(win);
  
  endwin();

  return 0;
}
