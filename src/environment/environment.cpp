#include <random>

#include "environment.h"
#include "src/object/object.h"
#include "src/object/box.h"
#include "src/message/message_handler.h"

/*
  0 y 0
    y
    |
    |      
    |   0 0 z
    |    z
    |   /
    |  /
    | /
    |/
    o----------------x
  0 0 0            x 0 0 
*/

//configure these at 100, 100 until i decide to add xml parsing
environment::environment() :
    x_size(100),
    y_size(100),
    z_size(100)
{ 
  //add 6 rectangles for the "boundaries" of the world, i'm allowed to be lazy if i want
  //each projects 1 unit past the boundary to give it volume
 
  //front, we spawn facing this one
  this->add_obj(new box_3d(0, y_size, z_size, x_size, 0, z_size + 1));

  //back, we spawn with this behind us
  this->add_obj(new box_3d(0, y_size, 0, x_size, 0, -1));

  //left, we spawn with this to our left
  this->add_obj(new box_3d(-1, y_size, z_size, 0, 0, 0));

  //right, we spawn with this to our right
  this->add_obj(new box_3d(x_size, y_size, z_size, x_size + 1, 0, 0));

  //top, we spawn with this above us
  this->add_obj(new box_3d(0, y_size + 1, z_size, x_size, y_size, 0));

  //bottom, we spawn with this below us
  this->add_obj(new box_3d(0, 0, z_size, x_size, -1, 0));
}

environment::~environment() { 
  for(std::vector<obj_3d *>::iterator it = objs.begin(); it != objs.end(); it++) {
    delete *it;
  }
}

void environment::add_obj(obj_3d *o) {
  objs.push_back(o);
}

char environment::trace_ray(const vec3d start, const vec3d end) const {
  for(obj_3d *o : objs) {
    if(o && o->collides(start, end)) {
      return '+';
    }
  }
  return '\0';

}
