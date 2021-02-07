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

  void post_message(std::string &, int);

  WINDOW *get_win() { return win; }
  void clear() { werase(win); }
  void draw_border();
  void draw_blinky();
  void refresh();

private:
  viewport();
  viewport(const viewport &) = delete;
  viewport &operator=(const viewport &) = delete;

  WINDOW *win;
};

#endif
