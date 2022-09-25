#include <SFML/Graphics.hpp>
#include <math.h>


class Point2f
{
public:
    Point2f() : x_(0), y_(0) {};
    Point2f( float x, float y) : x_(x), y_(y) {};
    ~Point2f() {};

    float x_;
    float y_;
};

class Point3f
{
public:
    Point3f() : x_(0), y_(0), z_(0) {};
    Point3f( float x, float y, float z) : x_(x), y_(y), z_(z) {};
    ~Point3f() {};

    float x_;
    float y_;
    float z_;
};


class Vector
{
public:
    Vector() : x_(0), y_(0), z_(0), len_sq_(NAN) {};
    Vector( float x, float y) : x_(x), y_(y), z_(0), len_sq_(NAN) {};
    Vector( float x, float y, float z) : x_(x), y_(y), z_(z), len_sq_(NAN) {};
    ~Vector() {};
    
    void operator+=( const Vector& add);
    void operator-=( const Vector& sub);
   
    float count_len_sq()
    {
        len_sq_ = x_ * x_ + y_ * y_ + z_ * z_;
        return len_sq_;
    }

    void draw2D( sf::RenderWindow& window,
                 const sf::Vector2f& start_point);
    void rotate2D( const float angle);

    float x_;
    float y_;
    float z_;
    float len_sq_;
};


Vector operator+( const Vector& v1, const Vector& v2);
Vector operator-( const Vector& v1, const Vector& v2);

inline float dot( const Vector& vec1, const Vector& vec2)
{
    return vec1.x_ * vec2.x_ + vec1.y_ + vec2.y_ + vec1.z_ * vec2.z_;
};
