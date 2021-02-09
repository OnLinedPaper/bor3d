#ifndef OBJECT_H_
#define OBJECT_H_

//a drawable 3d object that can be placed in an environment
//note that this class is virtual, specific objects must be created
class obj_3d {

  obj_3d();
  virtual ~obj_3d() = default; 

  //TODO: virtual bool collides(); 
};

#endif
