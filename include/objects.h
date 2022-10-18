#ifndef OBJECTS_H_
#define OBJECTS_H_

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
        
    sf::Color color_;
    float spec_coeff_;

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
  
    Vector pos_;
    sf::Color color_;
};

#endif
