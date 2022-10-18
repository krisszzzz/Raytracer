#ifndef RAYCASTER_H_
#define RAYCASTER_H_

#include "vector.h"
#include <SFML/Graphics.hpp>

void vec_reflect( Vector* reflect,     // OUT: reflected vector
                  const Vector& dir,   // IN: direction vector
                  const Vector& norm); // IN: normalized vector of normal

float max( float first, float second);

 #endif
