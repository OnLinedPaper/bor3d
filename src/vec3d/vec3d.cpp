#include "vec3d.h"

#define _USE_MATH_DEFINES
#include <math.h>

float &vec3d::operator [](int i) {
  //return reference
  switch(i) {
    case 0:
      return x; break;
    case 1:
      return y; break;
    case 2:
      return z; break;
    default:
      return max; break;
  }
}

float vec3d::operator [](int i) const {
  //return reference
  switch(i) {
    case 0:
      return x; break;
    case 1:
      return y; break;
    case 2:
      return z; break;
    default:
      return max; break;
  }
}

float vec3d::magnitude() const {
  return sqrt((x * x) + (y * y) + (z * z));
}

float vec3d::magnitudeSquared() const {
  return ((x * x) + (y * y) + (z * z));
}

vec3d vec3d::normalize() const {
  //does not normalize past .001, returns this
  float m = this->magnitude();
  if(m < .001 && m > -.001) {
    return *this;
  }
  return vec3d(x/m, y/m, z/m);
}
