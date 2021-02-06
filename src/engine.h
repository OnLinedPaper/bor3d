#ifndef ENGINE_H_
#define ENGINE_H_

class engine {

public:
  engine();
  ~engine();

  void run();

private:

  void init();
  void next_tick();


};

#endif
