#ifndef VIEWPORT_H_
#define VIEWPORT_H_

#include <ncurses.h>
#include <string>

//this singleton class will handle drawing to the screen

class viewport {

public:
  ~viewport();

  static viewport &get() {
    static viewport instance;
    return instance;
  }

  void draw_messages() const;

  WINDOW *get_win() { return win; }
  void clear() { werase(win); }
  void draw_border() const;
  void draw_blinky() const;
  void refresh();

private:
  viewport();
  viewport(const viewport &) = delete;
  viewport &operator=(const viewport &) = delete;

  void draw_msg_box() const;

  WINDOW *win;
  uint8_t BOX_WIDTH;
  uint8_t BOX_HEIGHT;
};

#endif
