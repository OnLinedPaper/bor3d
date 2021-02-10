#ifndef OBJECT_H_
#define OBJECT_H_

#include "src/vec3d/vec3d.h"

//a drawable 3d object that can be placed in an environment
//note that this class is virtual, specific objects must be created
class obj_3d {

public:
  obj_3d();
  virtual ~obj_3d() = default; 

  virtual bool collides(const vec3d &, const vec3d &) const = 0; 

private:

};

#endif
