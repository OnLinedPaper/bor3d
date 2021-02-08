#include "message.h"

box_msg::box_msg(std::string m, int life) : 
  msg(m),
  lifespan(life)
{ }

std::vector<std::string> box_msg::slice(int length) const {
  std::vector<std::string> retvec;

  for(unsigned int i=0; i<msg.length(); i+=length) {
    retvec.push_back(msg.substr(i, length));
  }

  return(retvec);
}

void box_msg::update() {
  lifespan--;
}
