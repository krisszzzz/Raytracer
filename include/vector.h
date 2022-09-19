#include <SFML/Graphics.hpp>
#include <math.h>

class Vector
{
public:
    Vector() : x_(0), y_(0), len_(NAN) {};
    Vector(float x, float y) : x_(x), y_(y), len_(NAN) {};
    ~Vector() {};
    
    void operator+=( Vector& add);
    void operator-=( Vector& sub);

    Vector operator+( Vector& add);
    Vector operator-( Vector& sub);

    void draw( sf::RenderWindow& window,
               const sf::Vector2f& start_point);
    void rotate( const float angle);
    void count_len();

    float x_;
    float y_;
    float len_;
};

