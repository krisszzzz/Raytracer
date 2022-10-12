#include "raycaster.h"
#include <SFML/Config.hpp>


static void
transfer_coord( Vector* new_vec,
                const Vector& vec,
                const Vector& coord_sys)
{
    new_vec->x_ = vec.x_ - coord_sys.x_;
    new_vec->y_ = coord_sys.y_ - vec.y_;
    new_vec->z_ = vec.z_ - coord_sys.z_;
} /* transfer_coord */


static float
max( float first, float second)
{
    return ( first > second ) ? first : second;
} /* max */


void
vec_reflect( Vector* reflect,    // OUT: reflected vector
             const Vector& dir,  // IN: direction vector
             const Vector& norm) // IN: normalized vector of normal
{
    *reflect = dir - norm * 2.f * dot( dir, norm);
}


void
sphere_raycast( sf::RenderWindow& window,
                const Sphere& sphere,
                const Vector& light,
                const sf::Color& light_color,
                const Vector& view,
                const sf::Color ambient)
{
    int i_radius = (int)sphere.radius_;

    // recount light position in centre system

    Vector light_pos = {};
    Vector view_pos = {};

    transfer_coord( &light_pos, light, sphere.centre_pos_);
    transfer_coord( &view_pos, view, sphere.centre_pos_);

    sf::VertexArray point_map { sf::Points, i_radius * i_radius * 4 };

    float r_2 = (float) ( sphere.radius_ * sphere.radius_);

    for ( int y = 0; y < 2 * i_radius; y++ )
    {
        float y_pos = (float)-y + sphere.radius_;
        
        for ( int x = 0; x < 2 * i_radius; x++ )
        {
            int point_pos = x + y * 2 * i_radius;
            
            point_map[point_pos].position.x = (float)x + sphere.centre_pos_.x_ -
                                               sphere.radius_;
            point_map[point_pos].position.y = (float)y + sphere.centre_pos_.y_ -
                                               sphere.radius_;
            point_map[point_pos].color = sf::Color::Black; // default color
            
            float x_pos = (float)x - sphere.radius_;
            float x_y_sqr = x_pos * x_pos + y_pos * y_pos;

            if ( x_y_sqr < r_2 )
            {
                float z_pos = sqrt( r_2 - x_y_sqr);

                Vector norm_vec   { x_pos, y_pos, z_pos };
                Vector view_vec   { view_pos - norm_vec };
                Vector light_vec  { light_pos - norm_vec };

                float diffusion = max( cosv( norm_vec, light_vec), 0.f);
                Vector reflect_vec {};
                
                norm_vec.norm();
               
                vec_reflect( &reflect_vec, light_vec, norm_vec);

                float specular = pow( max( -cosv( view_vec, reflect_vec), 0.f), 25.f);

                sf::Uint8 i_diff = (sf::Uint8)(diffusion * 255);
                sf::Uint8 i_spec = (sf::Uint8)(specular * 255);

                sf::Color diff_color { i_diff, i_diff, i_diff };
                sf::Color spec_color { i_spec, i_spec, i_spec };

                point_map[point_pos].color = ambient +  diff_color * sphere.color_ + spec_color ; 

            }

        }
        
    }

    window.draw( point_map);

} /* sphere_raycast */


