#include "scene.h"

static void
transfer_coord( Vector* vec,
                const Vector& coord_sys)
{
    vec->set_x( vec->get_x() - coord_sys.get_x());
    vec->set_y( coord_sys.get_y() - vec->get_y());
    vec->set_z( vec->get_z() - coord_sys.get_z());
} /* transfer_coord */



void
Scene::raycast( const std::size_t obj_num)
{
    const Sphere sphere = get_obj( obj_num);
    const Vector coord_sys = sphere.centre_pos_;
    
    float radius = sphere.radius_;
    int i_radius = (float)radius;

    sf::VertexArray point_map { sf::Points, i_radius * i_radius * 4 };

    float r_2 = (float) (radius * radius);

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

                Vector norm_vec { x_pos, y_pos, z_pos };
                 // printf("Before:\n");
                // norm_vec.print();
                transfer_coord( &norm_vec, coord_sys);
                // norm_vec.print();
                Phong phong {};
                get_phong( &phong, norm_vec, obj_num);
                
                constexpr int cvt_to_int = 255;

                sf::Uint8 i_diff = (sf::Uint8)(phong.diffusion * cvt_to_int);
                sf::Uint8 i_spec = (sf::Uint8)(phong.specular * cvt_to_int);

                sf::Color diff_color { i_diff, i_diff, i_diff };
                sf::Color spec_color { i_spec, i_spec, i_spec };

                point_map[point_pos].color = 
                                             diff_color * sphere.color_ +
                                             spec_color; 

            }

        }
        
    }

    get_window()->draw( point_map);

} /* sphere_raycast */


