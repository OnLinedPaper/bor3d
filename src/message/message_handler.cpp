#include "message_handler.h"

m_handler::m_handler() { }
m_handler::~m_handler() {
  
  std::vector<box_msg>::iterator it = message_queue.begin();
  while(it != message_queue.end()) {
    it = message_queue.erase(it);
  }
}

void m_handler::add_msg(std::string msg, int life) {
  message_queue.push_back( {msg, life} );
}

std::vector<std::string> m_handler::get_messages(int slice, size_t lines){
  //remember! newest messages FIRST! start at the back of the vector!
  std::vector<std::string> retvec;
  std::vector<std::string> in_val;

  //check to see if there's any values in here to parse
  if(message_queue.size() > 0) {

    //make an iterator to the last value in the vector
    std::vector<box_msg>::iterator it = message_queue.end();
    it--;

    while(true) {
      //get the slices of the current message
      in_val = it->slice(slice);

      for(std::string s : in_val) {
        if(retvec.size() < lines) {
          retvec.push_back(s);
        }
      }
    
      //check to see if the vec is full OR if we've gone through the whole
      //vector
      if(retvec.size() >= lines || it == message_queue.begin()) { break; }

      it--;
    }
  }

  return retvec;
}

void m_handler::update() {
  //iterate through the vector and remove the messages that are out of life

  std::vector<box_msg>::iterator it = message_queue.begin();
  while(it != message_queue.end()) {
    it->update();
    if(!it->is_alive()) { 
      //remove the iterator from the vector
      it = message_queue.erase(it); 
    }
    else { 
      it++; 
    }
  }
}
