#include "src/engine.h"
#include "src/viewport/viewport.h"
#include "src/timeframe/timeframe.h"
#include "src/message/message.h"
#include "src/message/message_handler.h"
#include "src/object/box.h"
#include "src/camera/camera.h"
#include "src/environment/environment.h"

#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>

#include <vector>

void engine::run() {

  //run a constant loop here:
  //check for input, then draw

  int ch;
  bool quit = false;
  //TODO: add this to all objects once we can see the boundary
  box_3d *b = new box_3d(45, 45, 45, 46, 55, 55);
  environment::get().add_obj(b);
  camera c(50, 50, 15);

  while(!quit) {

    std::string campos;
    campos.append(std::to_string(c.get_pos()[0]) + ", ");
    campos.append(std::to_string(c.get_pos()[1]) + ", ");
    campos.append(std::to_string(c.get_pos()[2]));
    m_handler::get().add_msg(campos, 1);

    ch = getch();
    //check for ESC
    if(ch == 27) { quit = true; }

    if(ch != ERR) {
      std::string s;
      s += std::to_string(ch);
      s += " ";
      s += (char)ch;
      m_handler::get().add_msg(s, 1);

      switch(ch) {
        case 'w':
          c.move_relative(0, -1, 0); break;
        case 's':
          c.move_relative(0, 1, 0); break;
        case 'a':
          c.move_relative(-1, 0, 0); break;
        case 'd':
          c.move_relative(1, 0, 0); break;
        case 'q':
          c.move_relative(0, 0, -1); break;
        case 'e':
          c.move_relative(0, 0, 1); break;
        default:
          break;
      }
    }  

    if(t_frame::get().incr_f()) {
      viewport::get().clear();
      viewport::get().draw_snapshot(c);
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
  curs_set(1);
  endwin();
}
