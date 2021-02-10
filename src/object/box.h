#ifndef BOX_H_
#define BOX_H_

#include "src/object/object.h"
#include "src/vec3d/vec3d.h"

class box_3d : public obj_3d {

public:
  box_3d(float, float, float, float, float, float);
  box_3d(const vec3d, float, float, float);
  ~box_3d();

  virtual bool collides(const vec3d &start, const vec3d &end) const override;

private:

  box_3d() = delete;
  box_3d(const box_3d &) = delete;
  box_3d &operator=(const box_3d &) = delete;
  vec3d tlc;
  vec3d brc;

};

#endif
