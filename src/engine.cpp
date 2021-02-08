#include "engine.h"
#include "viewport/viewport.h"
#include "timeframe/timeframe.h"
#include "message/message.h"
#include "message/message_handler.h"

#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>

#include <vector>

void engine::run() {

  //run a constant loop here:
  //check for input, then draw

  //int ch;
  bool quit = false;

  while(!quit) {

    //ch = getch();
  
    if(t_frame::get().incr_f()) {
      viewport::get().clear();
      viewport::get().draw_border();
      viewport::get().draw_messages();
      viewport::get().draw_blinky();

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

  if(t_frame::get().incr_t()) {
    m_handler::get().update();
     if((int)(t_frame::get().get_t()) % 12 == 0) {
      //make a message of 8 ticks and have viewport show it
      
m_handler::get().add_msg("hell AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", 9);
    } 
  }
}

void engine::init() {
  //init singletons
  viewport::get();
  t_frame::get();
  m_handler::get();

  t_frame::get().set_f_delay(20);
  t_frame::get().set_t_delay(125);
}

engine::engine() {
  init();
}

engine::~engine() {
  endwin();
}
