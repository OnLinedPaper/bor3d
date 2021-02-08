#include "viewport.h"
#include <ncurses.h>
#include "src/timeframe/timeframe.h"
#include "src/message/message_handler.h"

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

  BOX_WIDTH = 80;
  BOX_HEIGHT = 6;
}

viewport::~viewport() {
  delwin(win);
  endwin();
}

//draw the messages in the message queue
void viewport::draw_messages() const {

  //add 1 so we can draw in the corner of the box
  uint8_t b_width = BOX_WIDTH + 1;
  uint8_t b_height = BOX_HEIGHT + 1;

  //the +1 and the +2 are so we don't step on the borders of the
  //textbox and window during resizing events
  int box_x_size = (COLS > b_width + 1 ? COLS - b_width : 2);
  int box_y_size = (LINES > b_height + 1 ? LINES - b_height : 2);

  std::vector<std::string> returned_msgs = 
    m_handler::get().get_messages(box_x_size, box_y_size);
  
  for(int i=0; (size_t)i<returned_msgs.size(); i++) {
    mvwprintw(win, box_y_size + i, box_x_size, "hello, world!");
  }
}

void viewport::draw_border() const {

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

  draw_msg_box();
}

void viewport::draw_msg_box() const {
  //add 2 to the size to accommodate the left and right borders
  uint8_t b_width = BOX_WIDTH + 2;
  uint8_t b_height = BOX_HEIGHT + 2;

  //add a little message box at the bottom right
  //box is at most 80 chars wide and 4 chars tall
  int box_x_size = (COLS > b_width ? COLS - b_width : 1);
  int box_y_size = (LINES > b_height ? LINES - b_height : 1);
  for(int i=box_x_size; i<COLS-1; i++) {
    mvwaddch(win, box_y_size, i, '-' | A_REVERSE);
  }
  for(int i=box_y_size; i<LINES-1; i++) {
    mvwaddch(win, i, box_x_size, '|' | A_REVERSE);
  }

}

void viewport::draw_blinky() const {
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

  mvwaddch(win, LINES-1, 0, c | A_REVERSE);

  return;
}

void viewport::refresh() {
  wrefresh(win);

}
