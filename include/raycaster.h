#ifndef RAYCASTER_H_
#define RAYCASTER_H_

#include "vector.h"
#include <SFML/Graphics.hpp>

class Sphere
{
public:
    Sphere() : color_(), centre_pos_(), radius_(0) {};
    Sphere( sf::Color color, const Vector& centre_pos, float radius) :
            color_(color), centre_pos_(centre_pos), radius_(radius) {};
        
    ~Sphere() {};

    sf::Color color_;

    Vector centre_pos_;
    float radius_;
};

void vec_reflect( Vector* reflect,     // OUT: reflected vector
                  const Vector& dir,   // IN: direction vector
                  const Vector& norm); // IN: normalized vector of normal

void sphere_raycast( sf::RenderWindow& window,
                     const Sphere& sphere,
                     const Vector& light,
                     const sf::Color& light_color,
                     const Vector& view,
                     const sf::Color ambient);
 #endif
