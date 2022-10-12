#ifndef RAYCASTER_H_
#define RAYCASTER_H_

#include "vector.h"
#include <SFML/Graphics.hpp>

class Sphere
{
public:
    Sphere() : color_(), spec_coeff_(0), centre_pos_(), radius_(0) {};

    Sphere( const Vector& centre_pos,
            const float radius,
            const sf::Color& color = sf::Color::White,
            const float spec_coeff = 10) :
        color_(color),
        spec_coeff_(spec_coeff),
        centre_pos_(centre_pos),
        radius_(radius) {};
        
    ~Sphere() {};

    sf::Color color_;
    float spec_coeff_;

    Vector centre_pos_;
    float radius_;
};

void vec_reflect( Vector* reflect,     // OUT: reflected vector
                  const Vector& dir,   // IN: direction vector
                  const Vector& norm); // IN: normalized vector of normal

float max( float first, float second);

void sphere_raycast( sf::RenderWindow& window,
                     const Sphere& sphere,
                     const Vector& light,
                     const sf::Color& light_color,
                     const Vector& view,
                     const sf::Color ambient);
 #endif
