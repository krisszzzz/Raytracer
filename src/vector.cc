#include "vector.h"
#include <math.h>

#define WIDTH 1920
#define HEIGHT 1200

inline void
Vector::operator+=( const Vector& add)
{
    x_ += add.x_;
    y_ += add.y_;
    z_ += add.z_;
};

inline void
Vector::operator-=( const Vector& sub)
{
    x_ -= sub.x_;
    y_ -= sub.y_;
    z_ -= sub.z_;
}

Vector
operator+( const Vector& v1, const Vector& v2)
{
    Vector tmp = v1;
    tmp += v2;
    return tmp;
}

Vector
operator-( const Vector& v1, const Vector& v2)
{
    Vector tmp = v1;
    tmp -= v2;
    return tmp;
}

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

void
sphere_raycast( sf::RenderWindow& window,
                const Point2f centre,
                Point3f light_pos,
                const float radius)
{
    int i_radius = (int)radius;

    // recount light position in centre system
    //light_pos.x_ = -centre.x_;
    //light_pos.y_ = centre.y_;

    sf::VertexArray point_map { sf::Points, i_radius * i_radius * 4 };

    float r_2 = (float) ( radius * radius);

    for ( int x = 0; x < 2 * i_radius; x++ )
    {
        float x_pos = (float)x - radius;
        
        for ( int y = 0; y < 2 * i_radius; y++ )
        {
            int point_pos = x + y * 2 * i_radius;
            
            point_map[point_pos].position.x = (float)x + centre.x_ - radius;
            point_map[point_pos].position.y = (float)y + centre.y_ - radius;
            point_map[point_pos].color      = sf::Color::Black;
            
            float y_pos = (float)-y + radius;
            float x_y_sqr = x_pos * x_pos + y_pos * y_pos;

            if ( x_y_sqr < r_2 )
            {
                float z_pos = sqrt( r_2 - x_y_sqr);
                
                Vector norm { x_pos, y_pos, z_pos };

                Vector light_vec  {
                                light_pos.x_ - norm.x_,
                                light_pos.y_ - norm.y_,
                                light_pos.z_ - norm.z_
                };               

                float normalize = sqrt( norm.count_len_sq()) *
                                  sqrt( light_vec.count_len_sq());
                
                float intens = dot( norm, light_vec) / normalize;
                
                if ( intens < 0 )
                    intens = 0;

                int color = (int)(intens * 256);
                
                point_map[point_pos].color.b = (sf::Uint8)color;
            }

        }
        
    }

    window.draw( point_map);

}
