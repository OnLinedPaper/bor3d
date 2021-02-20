#include <cmath>
#include <cstdint>
#include <iostream>

#include "camera.h"
#include "src/environment/environment.h"

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
void camera::take_snapshot(int lines, int cols, char **retval) const {
  //this will hold raytrace data for the 4 corners
  static uint8_t last_lines = -1;
  static uint8_t last_cols = -1;
  static char *trace_vals = NULL;

  if(lines != last_lines || cols != last_cols) {
    free(trace_vals);
    trace_vals = (char *)malloc(sizeof(char) * (lines+1) * (cols+1));
    if(trace_vals == NULL) {
      std::cerr << "malloc failed! S-H-I-T!" <<std::endl;
      exit(1);
    }
    last_lines = lines;
    last_cols = cols;
  }

/*
  static std::random_device r;
  static std::default_random_engine re(r());
  static std::uniform_int_distribution<int> uniform_dist(1, 4);

   switch (uniform_dist(re)) {
     case 1: return '.';
     case 2: return ',';
     case 3: return '\'';
     case 4: return '`';
     default: return '?';
  }

*/  

  //set array to empty space
  for(int j=0; j<lines; j++) {
    for(int i=0; i<cols; i++) {
      (*retval)[j * sizeof(char) * cols + i] = '?';
    }
  }

  //TODO: raytrace here
  //given FOV, width, and height, we can determine focal length
  //however... we need to first convert screen pixels to world units
  //frankie's fullscreen terminal rests at about 200 cols to 50 lines, and the world is 100 units wide
  //probably going to set it at 1:10 for the world:view units but ic an adjust this as i see fit
  //also need to set it to a 4:1 ratio (about) for the width and height

  //TODO: these "mixels" are taller than they are wide oops
  //don't account for fisheye of any sort yet - just snap a grid and adjust 
  float unit_convert = .2;
  for(int j=0; j<lines+1; j++) {
    for(int i=0; i<cols+1; i++) {
      (trace_vals)[j * sizeof(char) * (cols+1) + i] = environment::get()
          .trace_ray(
          {
              position[0], 
              position[1], 
              position[2]
          }, 
          {
              position[0] + (i - (cols+1)/2) * unit_convert, 
              position[1] + (j - (lines+1)/2) * unit_convert * 2, 
              position[2] + 50
          });
    }
  }

  //take data in trace_vals and compare it to get retval's data
  for(int j=0; j<lines; j++) {
    for(int i=0; i<cols; i++) {
      int ret_index = j * sizeof(char) * cols + i;
      int trace_index = ret_index + j;

      if(
        (trace_vals)[trace_index] == (trace_vals)[trace_index + 1] && 
        (trace_vals)[trace_index] == (trace_vals)[trace_index + cols + 1] &&
        (trace_vals)[trace_index] == (trace_vals)[trace_index + 1 + cols + 1] 
      ) { (*retval)[ret_index] = (trace_vals)[trace_index]; }
      else { (*retval)[ret_index] = 'x'; }
    }
  }

  return;
}

vec3d camera::get_end_vec(float ray_len) const {
  //use the angle vec to compute a normalized vector via atan
  //take that vector and multiply it by the length to get an endpoint
  //add that to the position vector to get the endpoint

  //a value of 0,0,0 in the angle vector means we're looking straight ahead
  //that is to say: no angle correlates to a vector of 0,0,1
  //TODO: ignoring roll (z) for now, will add that in later

  return {0, 0, 0};
}
