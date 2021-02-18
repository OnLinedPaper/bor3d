#include "box.h"
#include "src/rect2d/rect2d.h"
#include "src/rect2d/hitbox/hitline.h"

box_3d::box_3d(float tlc_x, float tlc_y, float tlc_z, float brc_x, float brc_y, float brc_z) :
    tlc(tlc_x, tlc_y, tlc_z),
    brc(brc_x, brc_y, brc_z)
{  }

box_3d::box_3d(const vec3d tlc_in, float x_size, float y_size, float z_size) :
    tlc(tlc_in),
    brc(tlc_in[0] + x_size, tlc_in[1] + y_size, tlc_in[2] + z_size)
{  }

box_3d::~box_3d() { }

bool box_3d::collides(const vec3d &start, const vec3d &end) const {
  //TODO: look up raytracing algos
  //i think - THINK - i can just offload this to 3 checks of line and rect2d
  //given how few resources this program will consume it's likely i can get away with this
  //gotta check around and be sure though
  bool front_hit = rect2d(tlc[0], tlc[1], brc[0]-tlc[0], brc[1]-tlc[1])
      .overlap(hitline({start[0], start[1]}, {end[0], end[1]}));

  bool top_hit = rect2d(tlc[0], tlc[2], brc[0]-tlc[0], brc[2]-tlc[2])
      .overlap(hitline({start[0], start[2]}, {end[0], end[2]}));

  bool side_hit = rect2d(tlc[1],tlc[2], brc[1]-tlc[1], brc[2]-tlc[2])
      .overlap(hitline({start[1], start[2]}, {end[1], end[2]}));

  return front_hit && top_hit && side_hit;
}
