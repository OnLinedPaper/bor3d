#include "camera.h"

camera::camera() :
  position({0, 0, 0}),
  angle({0, 0, 0,}),
  fov(90)
{ }

camera::camera(float x, float y, float z) :
  position({x, y, z}),
  angle({0, 0, 0}),
  fov(90)
{ }

camera::camera(float x, float y, float z, float pitch, float yaw, float roll) :
  position({x, y, z}),
  angle({pitch, yaw, roll}),
  fov(90)
{ }

camera::camera(const camera &c) :
  position({c.get_pos()[0], c.get_pos()[1], c.get_pos()[2]}),
  angle({c.get_angle()[0], c.get_angle()[1], c.get_angle()[2]}),
  fov(c.get_fov())
{ }

camera & camera::operator=(const camera &c) {
  if(this != &c) {
    this->move_absolute(c.get_pos()[0], c.get_pos()[1], c.get_pos()[2]);
    this->look_absolute(c.get_angle()[0], c.get_angle()[1], c.get_angle()[2]);
    this->set_fov(c.get_fov());
  }
  return *this; 
}

camera::~camera() { }

//-   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -

void camera::move_relative(float x, float y, float z) {
  position[0] += x; position[1] += y; position[2] += z;
}

void camera::move_absolute(float x, float y, float z) {
  position[0] = x; position[1] = y; position[2] = z;
}

void camera::look_relative(float pitch, float yaw, float roll) {
  angle[0] += pitch; angle[1] += yaw; angle[2] += roll;
}

void camera::look_absolute(float pitch, float yaw, float roll) { 
  angle[0] = pitch; angle[1] = yaw; angle[2] = roll;
}

//-   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -

//this will allocate space for a char array of width * height
//it will then create a set of ray data at each "corner" of a char, which
//is to say, each terminal box (a "pixel") will check at its 4 corners.
//(this occupies an array of width+1 * height+1.)
//if all corners agree on what they hit, it's a solid collision with an object.
//if they don't agree, it's a boundary of some sort.
void camera::take_snapshot(int width, int height, char ***retval) const {
  **retval = 0;
}
