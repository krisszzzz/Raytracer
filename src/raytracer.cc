#include "scene.h"
#include "ray.h"
#include <cstdio>
#include <unistd.h>

#define NO_CROSS -1

float
max( float first, float second)
{
    return ( first > second ) ? first : second;
} /* max */

void
vector_reflect( Vector* reflect,    // OUT: reflected vector
                const Vector& dir,  // IN: direction vector
                const Vector& norm) // IN: normalized vector of normal
{
    *reflect = dir - norm * 2.f * dot( dir, norm);
} /* vec_reflect */

int 
Scene::get_phong( Phong* phong,
                  const Vector& orig, 
                  const std::size_t curr_obj)
{
    std::size_t no_light = 0;
    
    for ( std::size_t light_count = 0; light_count < get_light_size(); light_count++ )
    {
        Vector norm_vec = orig - get_obj( curr_obj).centre_pos_;
        Vector to_camera = get_camera() - orig;
        norm_vec.norm();

        Ray light_ray { get_light( light_count).pos_ - orig,
                        orig };

        if ( light_ray.is_cross( get_objects(), curr_obj) )
        {
            no_light++;
            continue;
        }

        // light_ray.get_ray().print();
        // norm_vec.print();
        
        phong->diffusion += max( cosv( &light_ray.get_ray(), &norm_vec), 0.f);
        
        light_ray.reflect( norm_vec);
        
        phong->specular += powf( max( -cosv( &light_ray.get_ray(), &to_camera), 0.f),
                                 get_obj( curr_obj).spec_coeff_);

    }

    if ( phong->diffusion > 1 )
        phong->diffusion = 1;

    if ( phong->specular > 1 )
        phong->specular = 1;

    if ( no_light == get_obj_size() )
    {
        return NO_CROSS;
    }

    return 0;
}

// static int
// get_raytrace( Ray* const ray,
//               Scene* scene,
//               const int curr_obj,
//               const Vector& orig)
// {
//     ray->add_cross( orig);
//     Vector norm_vec = orig - scene->get_obj( curr_obj).centre_pos_;
//     norm_vec.norm();

//     ray->reflect( norm_vec);

//     for ( std::size_t i = 0; i < ray->get_max_depth(); i++ )
//     {
//         int inter_obj = 0;

//         if ( !check_intersect( scene, &inter_obj, curr_obj, ray->get_cross( i), ray->get_ray()) )
//         {
//             break;
//         }

        
//     }

//     return 0;
// }

void
Scene::raytrace( std::size_t width,
                 std::size_t height)
{
    if ( width == RESOLUTION_DEFAULT )
    {
        width = get_window()->getSize().x; 
    }

    if ( height == RESOLUTION_DEFAULT )
    {
        height = get_window()->getSize().y;
    }

    sf::VertexArray point_map { sf::Points, height * width };
    
    for ( std::size_t y = 0; y < height; y++ )
    {
        for ( std::size_t x = 0; x < width; x++ )
        {
            std::size_t point_pos = x + y * width;
            
            point_map[point_pos].position.x = (float)x;
            point_map[point_pos].position.y = (float)y;
 
            Vector on_flat { (float)x, (float)y, 0 };
            Vector cross {};
            
            Ray ray { on_flat - get_camera(), get_camera() };

            int nearest = ray.nearest_cross( get_objects(), &cross);
            
            if ( nearest != NO_CROSS )
            {
                Phong phong = {};

                int is_shadowed = get_phong( &phong,
                                             cross,
                                             nearest);

                if ( is_shadowed )
                {
                     point_map[point_pos].color *= sf::Color::Black;
                     continue;
                }

                constexpr int cvt_to_int = 255;
                
                sf::Uint8 i_diff = (sf::Uint8)(phong.diffusion * cvt_to_int);
                sf::Color diff_color { i_diff, i_diff, i_diff };
                sf::Uint8 i_spec = (sf::Uint8)(phong.specular * cvt_to_int);
                sf::Color spec_color { i_spec, i_spec, i_spec };
                
                point_map[point_pos].color = get_obj(nearest).color_ * diff_color + spec_color;
                
            }

        }
    }

    get_window()->draw( point_map);
    
}




