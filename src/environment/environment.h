#ifndef ENVIRONMENT_H_
#define ENVIRONMENT_H_

#include <vector>
#include "src/object/object.h"

//handles the "world" within which 3d objects can be placed
class environment {

public:
  ~environment();

  static environment &get() {
    static environment instance;
    return instance;
  }

  void add_obj(obj_3d *o);

private:
  environment();
  environment(const environment &) = delete;
  environment &operator=(const environment &) = delete;

  double x_size;
  double y_size;
  double z_size;

  std::vector<obj_3d *> objs;
};

#endif
