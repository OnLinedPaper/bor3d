#include "engine.h"
#include "viewport/viewport.h"
#include "timeframe/timeframe.h"

#include <ncurses.h>
#include <unistd.h>

#include <vector>
#include <iostream>

void engine::run() {

  //run a constant loop here:
  //check for input, then draw


  bool quit = false;
  while(!quit) {
   
    if(t_frame::get().incr_f()) {
      viewport::get().draw_blinky();
      viewport::get().draw_border();

      viewport::get().refresh();
    }

    next_tick();
  }
  return;
}

void engine::next_tick() {
  //game is set to 8 ticks per second
  
  float t_delay = t_frame::get().get_t_delay();
  float elapsed = t_frame::get().get_elapsed_ms();

  //delay some time - check to see how long computing took
  //and subtract that from the delay time for consistent delays
  if(t_delay - elapsed > 0) {
    if(t_delay - elapsed <= t_delay) {
      usleep((t_delay - elapsed) * 1000);
    }
    else {
      usleep(t_delay * 1000);
    }
  }

  t_frame::get().incr_t();
}

void engine::init() {
  //init viewport
  viewport::get();
  t_frame::get();

  t_frame::get().set_f_delay(20);
  t_frame::get().set_t_delay(125);
}

engine::engine() {
  init();
}

engine::~engine() {
  endwin();
}
