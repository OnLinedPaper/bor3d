#ifndef CAMERA_H_
#define CAMERA_H_

#include "src/vec3d/vec3d.h"

class camera {

public:
  camera();
  camera(float, float, float);
  camera(float, float, float, float, float, float);
  camera(const camera &);
  camera &operator=(const camera &);
  ~camera();

  void move_relative(float, float, float);
  void move_absolute(float, float, float);

  void look_relative(float, float, float);
  void look_absolute(float, float, float);

  //take a look through a viewport of specified width and height,
  //then fill a char array of what was seen
  void take_snapshot(int, int, char **) const;

  vec3d get_pos() const { return position; }
  vec3d get_angle() const { return angle; }

  float get_fov() const { return fov; }
  void set_fov(float f) { fov = f; }

private:
  vec3d position;
  vec3d angle;

  float fov;
};

#endif
