#include "viewport.h"
#include <ncurses.h>

viewport::viewport() {
  //init the viewport
  initscr();
  cbreak();
  noecho();

  //init the window
  //TODO: handle resizing gracefully
  win = newwin(LINES, COLS, 0, 0);
  keypad(win, TRUE);
  nodelay(win, TRUE);
}

viewport::~viewport() {
  delwin(win);
  endwin();
}

void viewport::draw_border() {

  //draw full borders
  for(int i=0; i<COLS; i++) {
    mvwaddch(win, 0,       i, '=' | A_REVERSE);
    mvwaddch(win, LINES-1, i, '=' | A_REVERSE);
  }

  for(int i=0; i<LINES; i++) {
    mvwaddch(win, i, 0,      '|' | A_REVERSE);
    mvwaddch(win, i, COLS-1, '|' | A_REVERSE);
  }

  //overwrite the corners
  mvwaddch(win, 0,       0,      '#' | A_REVERSE);
  mvwaddch(win, 0,       COLS-1, '#' | A_REVERSE);
  mvwaddch(win, LINES-1, 0,      '#' | A_REVERSE);
  mvwaddch(win, LINES-1, COLS-1, '#' | A_REVERSE);

}

void viewport::refresh() {
  wrefresh(win);
}
