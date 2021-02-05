#ifndef VIEWPORT_H_
#define VIEWPORT_H_

#include <ncurses.h>

//this singleton class will handle drawing to the screen

class viewport {

public:
  ~viewport();

  static viewport &get() {
    static viewport instance;
    return instance;
  }

  void draw_border();
  void refresh();

private:
  viewport();
  viewport(const viewport &) = delete;
  viewport &operator=(const viewport &) = delete;

  WINDOW *win;
};

#endif
