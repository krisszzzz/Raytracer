#include "vector.h"
#include <math.h>

#define WIDTH 1920
#define HEIGHT 1200

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
        sf::Vertex { start_point + sf::Vector2f { x_, y_ } }
    };

    sf::Vertex arrow[3] = {};

    find_arrow( line, arrow);

    window.draw( line, 2, sf::Lines);
    window.draw( arrow, 3, sf::Triangles);
}

void
Vector::rotate2D( const float angle)
{
    const float tmp_x = x_;

    x_ = tmp_x * cos( angle) - y_ * sin( angle);
    y_ = tmp_x * sin( angle) + y_ * cos( angle);
}
