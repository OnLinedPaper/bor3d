#include "environment.h"
#include "src/object/object.h"

//configure these at 100, 100 until i decide to add xml parsing
environment::environment() :
    x_size(100),
    y_size(100)
  { }

environment::~environment() { }

void environment::add_obj(obj_3d *o) {
  objs.push_back(o);
}
