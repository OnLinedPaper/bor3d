#ifndef MESSAGE_H_
#define MESSAGE_H_

#include <string>
#include <vector>

//the "message" entity holds a string and an int
//the string is the message, while the int is the "lifespan" in ticks

class box_msg {

public:
  box_msg(std::string msg, int lifespan);

  //slice a message up into a vector of chunks of given length
  //if message is shorter than length, return vector of size 1
  std::vector<std::string> slice(int length) const;

  std::string get_msg() const { return msg; }
  void set_msg(std::string &m) { msg = m; }
  int get_life() const { return lifespan; }
  void set_life(int l) { lifespan = l; }
  int get_len() const { return msg.length(); }

  bool is_alive() const { return lifespan > 0; }

  void update();
private:
  std::string msg;
  int lifespan;

};

#endif
