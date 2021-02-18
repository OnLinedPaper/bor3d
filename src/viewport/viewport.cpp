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

void viewport::draw_snapshot(const camera &c) {
  //make some memory - this needs to be resized
  //any time the window changes
  static uint8_t last_lines = -1;
  static uint8_t last_cols = -1;
  static char *draw_vals = NULL;

  if(LINES != last_lines || COLS != last_cols) {
    free(draw_vals);
    draw_vals = (char *)malloc(sizeof(char) * LINES * COLS);
    if(draw_vals == NULL) { 
      std::cerr << "malloc failed! S-H-I-T!" << std::endl;
      exit(1); 
    }
    last_lines = LINES;
    last_cols = COLS;
  }

  //fill with data
  c.take_snapshot(LINES, COLS, &draw_vals);
  
  for(int i=0; i<COLS; i++) {
    for(int j=0; j<LINES; j++) {
      mvwaddch(win, j, i, draw_vals[j*sizeof(char)*COLS+i]);
    }
  }
}

//draw the messages in the message queue
void viewport::draw_messages() const {

  //add 1 so we can draw in the corner of the box
  uint8_t b_width = BOX_WIDTH + 1;
  uint8_t b_height = BOX_HEIGHT + 1;

  uint8_t ONE_BORDER = 1;
  uint8_t TWO_BORDER = 2;
  uint8_t THREE_BORDER = 3;

  //offset is where we start printing
  int box_x_offset = (COLS > b_width + ONE_BORDER ? COLS - b_width : TWO_BORDER);
  int box_y_offset = (LINES > b_height + ONE_BORDER ? LINES - b_height : TWO_BORDER);

  //size is how much we print
  int box_x_size = (COLS > b_width ? b_width - ONE_BORDER : COLS - THREE_BORDER);
  int box_y_size = (LINES > b_height ? b_height - ONE_BORDER : LINES - THREE_BORDER);

  std::vector<std::string> returned_msgs = 
    m_handler::get().get_messages(box_x_size, box_y_size);
  
  for(int i=box_y_offset; i<LINES - ONE_BORDER; i++) {
    for(int j=box_x_offset; j<COLS - ONE_BORDER; j++) {
      mvwaddch(win, i, j, ' ');
    }
  }

  for(int i=0; (size_t)i<returned_msgs.size(); i++) {
    mvwprintw(win, box_y_offset + i, box_x_offset, returned_msgs[i].c_str());
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
