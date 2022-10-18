
#include "ray.h"

#define NO_CROSS -1

int
Ray::find_cross_scale( const Sphere& object,
                       float* cross_scale)
{
    Vector to_center = object.centre_pos_ - get_orig();
    get_ray().norm();

    float dir_center_dot = dot( get_ray(), to_center);
    to_center.count_len_sq();

    float distance_2 = to_center.get_len_sq() -
                       dir_center_dot * dir_center_dot;


    if ( distance_2 > object.radius_* object.radius_ )
    {
        return 0;
    }

    float dist_to_inter_center = sqrtf( object.radius_ * object.radius_ - distance_2);

    float first_scale = dir_center_dot - dist_to_inter_center;
    float second_scale = dir_center_dot + dist_to_inter_center;

    if ( first_scale < 0 )
    {
        first_scale = second_scale;
    }
    
    if ( first_scale < 0 ) // both intersection against the ray direction
    {
        return 0;
    }

    if ( cross_scale != nullptr )
    {
        *cross_scale = first_scale;
    }

    return 1;
    
}

int
Ray::find_cross( const Sphere& object,
                 Vector* cross)
{
    float cross_scale = 0;
    
    if ( find_cross_scale( object, &cross_scale) )
    {
        if ( cross != nullptr )
        {
            *cross = get_orig() + get_ray() * cross_scale;
        }

        return 1;
    }

    return 0;
}

int
Ray::nearest_cross( const std::vector<Sphere>& objects,
                    Vector* cross)
{
    int nearest_obj = NO_CROSS;
    int inter_count = 0;
    float nearest = 0;

    for ( std::size_t obj_count = 0; obj_count < objects.size(); obj_count++ )
    {
        float tmp_cross = 0;

        if ( find_cross_scale( objects.at( obj_count), &tmp_cross) )
        {
            inter_count++;
            
            if ( inter_count == 1 )
            {
                nearest = tmp_cross;
                nearest_obj = obj_count;
            }

            if ( tmp_cross < nearest )
            {
                nearest = tmp_cross;
                nearest_obj = obj_count;
            }

        }
    }

    if ( cross != nullptr )
    {
        *cross = get_orig() + get_ray() * nearest;
    }

    return nearest_obj;
}

int
Ray::is_cross( const std::vector<Sphere>& objects)
{
    for ( std::size_t obj_count = 0; obj_count < objects.size(); obj_count++ )
    {
        if ( find_cross_scale( objects.at( obj_count)) )
        {
            return 1;
        }
    }

    return 0;
}

int
Ray::is_cross( const std::vector<Sphere>& objects,
               const std::size_t obj_orig)
{

  for ( std::size_t obj_count = 0; obj_count < objects.size(); obj_count++ )
    {
        if ( obj_count == obj_orig )
        {
            continue;
        }
        
        if ( find_cross_scale( objects.at( obj_count)) )
        {
            return 1;
        }
    }

    return 0;
}
