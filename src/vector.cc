#include "vector.h"
#include <math.h>

#define WIDTH 1920
#define HEIGHT 1200

Vector&
Vector::operator+=( const Vector& rhs)
{
    set_x( get_x() + rhs.get_x());
    set_y( get_y() + rhs.get_y());
    set_z( get_z() + rhs.get_z());
    
    return *this;
}


Vector&
Vector::operator-=( const Vector& rhs)
{
    set_x( get_x() - rhs.get_x());
    set_y( get_y() - rhs.get_y());
    set_z( get_z() - rhs.get_z());
    
    return *this;
}

Vector&
Vector::operator*=( const float rhs)
{
    set_x( get_x() * rhs);
    set_y( get_y() * rhs);
    set_z( get_z() * rhs);
    
    return *this;
}


Vector
Vector::operator+( const Vector& add) const
{
    Vector tmp = *this;
    tmp += add;
    return tmp;
} /* Vector::operator+ */

Vector
Vector::operator-( const Vector& sub) const
{
    Vector tmp = *this;
    tmp -= sub;
    return tmp;
} /* Vector::operator- */

Vector
Vector::operator*( const float value) const
{
    Vector tmp = *this;
    tmp *= value;
    return tmp;
} /* Vector::operator* */

Vector
Vector::operator-() const
{
    Vector un_minus { -this->get_x(),
                      -this->get_y(),
                      -this->get_z()
                    };
    return un_minus;
} /* Vector::operator- */


static void
find_arrow( sf::Vertex line[2],
            sf::Vertex arrow[3])
{
    const float X = line[1].position.x - line[0].position.x;
    const float Y = line[1].position.y - line[0].position.y;

    constexpr float pi = 3.14f;
    constexpr float angle = pi / 60;
    constexpr float scale = 1.05f;

    arrow[0] = line[1]; // copy end of vector

    // rotate vector for pi / 60
    arrow[1].position.x = X * cos( angle) / scale - Y * sin( angle) / scale;
    arrow[1].position.y = X * sin( angle) / scale + Y * cos( angle) / scale;

    // move point
    arrow[1].position += line[0].position;

    arrow[2].position.x =  X * cos( angle) / scale + Y * sin( angle) / scale;
    arrow[2].position.y = -X * sin( angle) / scale + Y * cos (angle) / scale;

    arrow[2].position += line[0].position;
}
    
void
Vector::draw2D( sf::RenderWindow& window,
                const sf::Vector2f& start_point)
{
    sf::Vertex line[]
    {
        sf::Vertex { start_point },
        sf::Vertex { start_point + sf::Vector2f { get_x(), get_y() } }
    };

    sf::Vertex arrow[3] = {};

    find_arrow( line, arrow);

    window.draw( line, 2, sf::Lines);
    window.draw( arrow, 3, sf::Triangles);
}

void
Vector::rotate2D( const float angle)
{
    const float tmp_x = get_x();

    set_x( tmp_x * cos( angle) - get_y() * sin( angle));
    set_y( tmp_x * sin( angle) + get_y() * cos( angle));
}
