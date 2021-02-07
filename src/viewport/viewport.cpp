#include "viewport.h"
#include <ncurses.h>
#include "src/timeframe/timeframe.h"

#include <iostream>

viewport::viewport() {
  //init the viewport
  initscr();
  cbreak();
  noecho();

  //init the window
  //TODO: handle resizing gracefully
  win = newwin(LINES, COLS, 0, 0);
  keypad(win, TRUE);
  timeout(1);
  curs_set(0);
}

viewport::~viewport() {
  delwin(win);
  endwin();
}

//post a message in the little message box, which persists for
//however many ticks the program wants it to
//remember: wrap after 80 characters!
void post_message(std::string &text, int tick_lifespan) {

}

void viewport::draw_border() {

  //draw full borders
  for(int i=0; i<COLS; i++) {
    mvwaddch(win, 0,       i, '=' | A_REVERSE);
    mvwaddch(win, LINES-1, i, '=' | A_REVERSE);
  }

  for(int i=0; i<LINES; i++) {
    mvwaddch(win, i, 0,      'I' | A_REVERSE);
    mvwaddch(win, i, COLS-1, 'I' | A_REVERSE);
  }

  //overwrite the corners
  mvwaddch(win, 0,       0,      '#' | A_REVERSE);
  mvwaddch(win, 0,       COLS-1, '#' | A_REVERSE);
  mvwaddch(win, LINES-1, 0,      '#' | A_REVERSE);
  mvwaddch(win, LINES-1, COLS-1, '#' | A_REVERSE);

  //-   -   -   -   -   -   -   -   -   -   -   -   -   -      

  //add a little message box at the bottom right
  //box is at most 80 chars wide and 4 chars tall
  int box_x_size = (COLS > 82 ? COLS-82 : 0);
  int box_y_size = (LINES > 6 ? LINES-6 : 0);
  for(int i=box_x_size; i<COLS-1; i++) {
    mvwaddch(win, LINES-6, i, '-' | A_REVERSE);
  }
  for(int i=box_y_size; i<LINES-1; i++) {
    mvwaddch(win, i, COLS-82, '|' | A_REVERSE);
  }
}

void viewport::draw_blinky() {
  char c = 'x';
  switch(((int) (t_frame::get().get_t())) % 4) {
    case 0:
      c = 'q'; break;
    case 1:
      c = 'd'; break;
    case 2:
      c = 'b'; break;
    case 3:
      c = 'p'; break;
    default:
      c = 'x'; break;
  }

  mvwaddch(win, LINES-2, 1, c);

  return;
}

void viewport::refresh() {
  wrefresh(win);

}
