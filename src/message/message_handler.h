#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H

#include "src/message/message.h"


//a singleton to handle messages that want to be printed
class m_handler {

public:
  ~m_handler();

  static m_handler &get() {
    static m_handler instance;
    return instance;
  }

  void add_msg(std::string msg, int life);

  //get mesages for printing - slice them automatically, and only return as
  //many as there are lines to print, i.e. if there's lots of messages
  //only return a couple
  //note that this returns NEWEST MESSAGES FIRST
  std::vector<std::string> get_messages(int slice, size_t lines);

  void update();
private:
  m_handler();
  m_handler(const m_handler &) = delete;
  m_handler &operator=(const m_handler &) = delete;

  std::vector<box_msg> message_queue;
};


#endif
