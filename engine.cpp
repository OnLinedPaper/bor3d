#include "engine.h"
#include "viewport.h"

#include <ncurses.h>
#include <unistd.h>

#include <vector>
#include <iostream>

void engine::run() {

  //run a constant loop here:
  //check for input, then draw


  while(true) {
   


    viewport::get().draw_border();

    viewport::get().refresh();

    usleep(50000);
  }
  return;
}

void engine::init() {
  //init viewport
  viewport::get();
}

engine::engine() {
}

engine::~engine() {
  endwin();
}
