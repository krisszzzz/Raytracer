#ifndef RAY_TRACER_H_
#define RAY_TRACER_H_

#include "raycaster.h"

enum SOLUTIONS
{
    INF_SOLUTION = -1,
    NO_SOLUTION = 0,
    ONE_SOLUTION = 1,
    TWO_SOLUTION = 2
};


class Point3f
{
 public:

    Point3f() : x_(0), y_(0), z_(0) {};
    Point3f(float x, float y, float z) : x_(x), y_(y), z_(z) {};
    
    float x_;
    float y_;
    float z_;
};

void
raytracer( sf::RenderWindow& window,
           int x_size,
           int y_size,
           Sphere objects[],
           int object_count,
           const Vector& view,
           const Vector& light_pos);

#endif



