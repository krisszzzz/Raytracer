#ifndef RAYCASTER_H_
#define RAYCASTER_H_

#include "vector.h"
#include <SFML/Graphics.hpp>

class Sphere
{
public:
    Sphere() : color_(), centre_pos_(), radius_(0) {};
    Sphere( sf::Color color, Point2f centre_pos, float radius) :
            color_(color), centre_pos_(centre_pos), radius_(radius) {};
        
    ~Sphere();

    sf::Color color_;
    Point2f centre_pos_;
    float radius_;
};

void sphere_raycast( sf::RenderWindow& window,
                     const Point2f centre,
                     Point3f light_pos,
                     const float radius,
                     const sf::Color color);
 #endif
