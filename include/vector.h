#ifndef VECTOR_H_
#define VECTOR_H_

#include <SFML/Graphics.hpp>
#include <math.h>



class Vector
{
public:
    Vector() : x_(), y_(), z_(), len_sq_(NAN) {};
    Vector( float x, float y, float z) : x_(x), y_(y), z_(z), len_sq_(NAN) {};
    
    void operator+=( const Vector& add)
    {
        x_ += add.x_;
        y_ += add.y_;
        z_ += add.z_;
    }
    
    void operator-=( const Vector& sub)
    {
         x_ -= sub.x_;
         y_ -= sub.y_;
         z_ -= sub.z_;
         
    };

    void operator*=( const float prod)
    {
        x_ *= prod;
        y_ *= prod;
        z_ *= prod;
    }

    Vector operator+( const Vector& add) const
    {
        Vector tmp = *this;
        tmp += add;
        return tmp;
    }

    Vector operator-( const Vector& sub) const
    {
        Vector tmp = *this;
        tmp -= sub;
        return tmp;
    }

    Vector operator*( const float value) const
    {
        Vector tmp = *this;
        tmp *= value;
        return tmp;
    }

    float count_len_sq()
    {
        len_sq_ = x_ * x_ + y_ * y_ + z_ * z_;
        return len_sq_;
    }

    void norm()
    {
        *this *= 1 / sqrt( count_len_sq());
    }

    void draw2D( sf::RenderWindow& window,
                 const sf::Vector2f& start_point);
    void rotate2D( const float angle);

    float x_;
    float y_;
    float z_;
    float len_sq_;
};

inline float dot( const Vector& vec1, const Vector& vec2)
{
    return vec1.x_ * vec2.x_ +
           vec1.y_ * vec2.y_ +
           vec1.z_ * vec2.z_;
}

inline float cosv( Vector& vec1, Vector& vec2)
{
    float normalize = sqrt(vec1.count_len_sq()) * sqrt(vec2.count_len_sq());
    return dot( vec1, vec2) / normalize; 
}


#endif
