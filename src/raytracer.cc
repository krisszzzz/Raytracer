#include "raytracer.h"
#include <float.h>
#include <SFML/Config.hpp>
#include <SFML/Graphics/Color.hpp>


Raytracer::Raytracer( const std::vector<Sphere>& objects,
                      const std::vector<Light>& lighting,
                      const std::size_t x_res,
                      const std::size_t y_res,
                      const Vector& camera) :
    LightRenderer( objects,
                   lighting,
                   x_res,
                   y_res,
                   camera),
    render_object_(NOT_AN_OBJECT)
{
} /* Raytracer() */

Raytracer::Raytracer( const std::size_t x_res,
                      const std::size_t y_res,
                      const Vector& camera) :
    LightRenderer( x_res,
                   y_res,
                   camera),
    render_object_(NOT_AN_OBJECT)
{
} /* Raytracer() */


static int
find_intersection( Ray* const ray,
                   const Sphere& object,
                   float* const intersection)
{
    Vector to_center = object.get_centre() - ray->get_orig();
    ray->get_dir().norm();

    float dir_center_dot = dot( ray->get_dir(), to_center);
    to_center.count_len_sq();

    float distance_2 = to_center.get_len_sq() -
                       dir_center_dot * dir_center_dot;

    if ( distance_2 > object.get_radius() * object.get_radius() )
    {
        return 0;
    }

    float dist_to_inter_center = sqrtf( object.get_radius() * object.get_radius() - distance_2);

    *intersection = dir_center_dot - dist_to_inter_center;
    float second_scale = dir_center_dot + dist_to_inter_center;

    if ( *intersection < 0 )
    {
        *intersection = second_scale;
    }
    
    if ( *intersection < 0 ) // both intersection against the ray direction
    {
        return 0;
    }

    return 1;
 
} /* find_intersection */

#define NO_HIT -1

int
Raytracer::hittable( Ray* const ray,
                     Vector* nearest)
{
    int nearest_obj = NO_HIT;
    float f_nearest = FLT_MAX;
    
    for ( std::size_t i = 0; i < objects_.size(); i++ )
    {
        if ( i == render_object_ )
        {
            continue; // skip render_object
        }

        float intersection = 0;

        if ( find_intersection( ray,
                                get_object( i),
                                &intersection) )
        {
            if ( intersection < f_nearest )
            {
                f_nearest = intersection;
                nearest_obj = (int)i;
            }
            
        }
    }
    
    if ( nearest != nullptr )
    {
        *nearest = ray->get_orig() + ray->get_dir() * f_nearest;
    }

    return nearest_obj;
    
}

static float
max( float first, float second)
{
    return ( first > second ) ? first : second;
} /* max */


#define UINT_8( coeff) (sf::Uint8)(coeff * 255)


static sf::Color operator*( sf::Color color, float value)
{
    if ( value > 1 )
    {
        value = 1;
    }

    sf::Color value_color { UINT_8( value), UINT_8( value), UINT_8( value) };

    return color * value_color;
}

sf::Color
Raytracer::get_phong( const Vector& orig)
{
    std::size_t no_light = 0;
    sf::Color color = sf::Color::Black;

    Vector norm_vec = orig - get_render_object().get_centre();
    Vector to_camera = get_camera() - orig;
    norm_vec.norm();
    
    for ( std::size_t light_count = 0; light_count < get_n_light(); light_count++ )
    {
        Ray light_ray { orig, get_light( light_count).get_pos() - orig };

        if ( hittable( &light_ray) != NO_HIT )
        {
            no_light++;
            continue;
        }

        float diffusion = max( cosv( &light_ray.get_dir(), &norm_vec), 0.f);
        
        light_ray.reflect( norm_vec);
        float specular = powf( max( -cosv( &light_ray.get_dir(), &to_camera), 0.f),
                               get_render_object().get_specular());

        sf::Color material = get_render_object().get_color();
        sf::Color light = get_light( light_count).get_color();

        color += material * light * ( diffusion + specular );
    }

    return color;
}


#define MAX_DEPTH 10

sf::Color
Raytracer::trace_ray( Ray* const ray, int max_depth)
{
    Vector hit_vec {};

    int nearest = hittable( ray, &hit_vec);

    if ( nearest == NO_HIT )
    {
        return sf::Color::Transparent;
    }

    set_render_object( nearest);

    sf::Color local_color = get_phong( hit_vec);

    Vector norm_vec = hit_vec - get_object( nearest).get_centre();
    norm_vec.norm();

    ray->reflect( norm_vec);
    ray->set_orig( hit_vec);

    max_depth--;

    if ( max_depth == 0 || !get_object( nearest).is_reflective() ) 
    {
        return local_color;
    }

    sf::Color reflected_color = trace_ray( ray, max_depth);

    // no intersection with another object
    if ( reflected_color == sf::Color::Transparent )
    {
        return local_color;
    }

    return local_color * ( 1 - get_object( nearest).get_reflective() )  + 
           reflected_color * get_object( nearest).get_reflective();
}


void
Raytracer::render()
{
    for ( std::size_t y = 0; y < y_res_; y++ )
    {
        for ( std::size_t x = 0; x < x_res_; x++ )
        {
            Vector on_flat { (float)x, (float)y, 0 };

            Ray ray { get_camera(), on_flat - get_camera() };
            
            set_render_object( NOT_AN_OBJECT);
            // the ray yet is not reached any object, so the render object
            // doesn't exist
            sf::Color color = trace_ray( &ray, MAX_DEPTH);

            set_point( x, y, color);
        }
    }
}

