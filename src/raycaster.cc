#include "raycaster.h"
#include <SFML/Config.hpp>


static void
transfer_coord( Vector* new_vec,
                const Vector& vec,
                const Vector& coord_sys)
{
    new_vec->set_x( vec.get_x() - coord_sys.get_x());
    new_vec->set_y( coord_sys.get_y() - vec.get_y());
    new_vec->set_z( vec.get_z() - coord_sys.get_z());
} /* transfer_coord */


float
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
} /* vec_reflect */


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
            
            point_map[point_pos].position.x = (float)x + sphere.centre_pos_.get_x() -
                                               sphere.radius_;
            point_map[point_pos].position.y = (float)y + sphere.centre_pos_.get_y() -
                                               sphere.radius_;
            
            point_map[point_pos].color = sf::Color::Transparent; // default color
            
            float x_pos = (float)x - sphere.radius_;
            float x_y_sqr = x_pos * x_pos + y_pos * y_pos;

            if ( x_y_sqr < r_2 )
            {
                float z_pos = sqrtf( r_2 - x_y_sqr);

                Vector norm_vec   { x_pos, y_pos, z_pos };
                Vector view_vec   { view_pos - norm_vec };
                Vector light_vec  { light_pos - norm_vec };

                float diffusion = max( cosv( &norm_vec, &light_vec), 0.f);
                Vector reflect_vec {};
                
                norm_vec.norm();
                vec_reflect( &reflect_vec, light_vec, norm_vec);

                // notice that reflect_vec look to different direction, because of light_vec
                // so we should use "-"
                float specular = powf( max( -cosv( &view_vec, &reflect_vec), 0.f), sphere.spec_coeff_);

                constexpr int cvt_to_int = 255;

                sf::Uint8 i_diff = (sf::Uint8)(diffusion * cvt_to_int);
                sf::Uint8 i_spec = (sf::Uint8)(specular * cvt_to_int);

                sf::Color diff_color { i_diff, i_diff, i_diff };
                sf::Color spec_color { i_spec, i_spec, i_spec };

                point_map[point_pos].color = ambient +
                                             diff_color * sphere.color_ +
                                             spec_color * light_color; 

            }

        }
        
    }

    window.draw( point_map);

} /* sphere_raycast */


