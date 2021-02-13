#ifndef VEC3D_H_
#define VEC3D_H_

#include <float.h>

class vec3d {
  //a 3d vector class, for position and possibly velocity later on
public:
  vec3d() : x(0), y(0), z(0) { }
  vec3d(float xin, float yin, float zin) : x(xin), y(yin), z(zin) { }
  vec3d(const vec3d &v) : x(v[0]), y(v[1]), z(v[2]) { }
  vec3d &operator=(const vec3d &v) {
    if(this != &v) {
      x = v[0];
      y = v[1];
      z = v[2];
    }
    return *this;
  }

  //array notation values
  float &operator[](int i);
  float operator [](int i) const;


  //modify vector with other vector
  vec3d operator+=(const vec3d&) const;

  float magnitude() const;
  float magnitudeSquared() const;
  vec3d normalize() const; //does not normalize beyond .001, returns this instead

private:
  float x;
  float y;
  float z;
  float max = FLT_MAX;
  float PI = 3.141592653589793238462643383279502884;
};

#endif
