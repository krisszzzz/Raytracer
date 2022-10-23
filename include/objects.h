#ifndef OBJECTS_H_
#define OBJECTS_H_

#include "vector.h"


class Material
{
public:
    
    Material( const sf::Color color,
              float spec_coeff,
              float reflective) :
        color_(color),
        spec_coeff_(spec_coeff),
        reflective_(reflective) 
    {};

    Material() : color_(0), spec_coeff_(0), reflective_(0) {};

    float get_specular() const 
    {
        return spec_coeff_;
    }

    float get_reflective() const
    {
        return reflective_;
    }

    int is_reflective() const
    {
        constexpr float min_refl = 1e-3f;
        return reflective_ > min_refl;
    }

    sf::Color get_color() const
    {
        return color_;
    }

private:
    sf::Color color_;
    float spec_coeff_;
    float reflective_;
}; /* class for containing material properties */

class Sphere : public Material
{
public:
    Sphere() : Material(), centre_pos_(), radius_(0) {};

    Sphere( const Vector& centre_pos,
            const float radius,
            const sf::Color& color = sf::Color::White,
            const float spec_coeff = 10,
            const float reflective = 0) :
        Material( color, spec_coeff, reflective),
        centre_pos_(centre_pos),
        radius_(radius) {};

    Vector get_centre() const
    {
        return centre_pos_;
    }

    float get_radius() const
    {
        return radius_;
    }

private:
    Vector centre_pos_;
    float radius_;
};

class Light
{
public:
    Light( const Vector& pos,
           const sf::Color& color) :
        pos_(pos), color_(color) {};

    Light() : pos_(), color_() {};

    Vector get_pos() const 
    {
        return pos_;
    }

    sf::Color get_color() const
    {
        return color_;
    }

private:
    Vector pos_;
    sf::Color color_;
};

#endif
