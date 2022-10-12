#include "raytracer.h"

static int 
find_intersect( float* const scaling_coeff, // get scanling coefficent to find the intersection point
                const Vector& dir,    // normalized vector of ray
                const Vector& orig,   // point on the dir vector
                const Sphere& sphere) // sphere
{
    
    Vector to_center = sphere.centre_pos_ - orig;
    float dir_center_dot = dot( dir, to_center);
    to_center.set_len_sq();

    float distance_2 = to_center.get_len_sq() -
                       dir_center_dot * dir_center_dot;

    if ( distance_2 > sphere.radius_ * sphere.radius_ )
    {
        return 0;
    }

    float dist_to_inter_center = sqrtf( sphere.radius_ * sphere.radius_ - distance_2);

    *scaling_coeff = dir_center_dot - dist_to_inter_center;
    float second_inter = dir_center_dot + dist_to_inter_center;

    // TODO: not work for inner intersection
    
    if ( *scaling_coeff < 0 && second_inter < 0) // both intersection against the ray direction
    {
        return 0;
    }

    return 1;
}

static int
find_nearest_inter( float* const scaling_coeff,
                    const Vector& dir,
                    const Vector& orig,
                    Sphere objects[],
                    int object_count)
{
    int obj_count = 0;
    int inter_count = 0;
    int nearest_obj = -1;

    for (; obj_count < object_count; obj_count++ )
    {
        float curr_inter = 0;
        
        if ( find_intersect( &curr_inter, dir, orig, objects[obj_count]) )
        {
            inter_count++;

            if ( inter_count == 1 )
            {
                *scaling_coeff = curr_inter;
                nearest_obj = obj_count;
            }

            if ( curr_inter < *scaling_coeff )
            {
                *scaling_coeff = curr_inter;
                nearest_obj = obj_count;
            }

        }
    }

    return nearest_obj;

}

void
raytracer( sf::RenderWindow& window,
           int x_size,
           int y_size,
           Sphere objects[],
           int object_count,
           const Vector& view,
           const Vector& light_pos)
{
    Vector view_vec = view;

    sf::VertexArray point_map { sf::Points, x_size * y_size };
    
    for ( int y = 0; y < y_size; y++ )
    {
        for ( int x = 0; x < x_size; x++ )
        {
            int point_pos = x + y * x_size;
            
            point_map[point_pos].position.x = (float)x;
            point_map[point_pos].position.y = (float)y;
 
            Vector ray_vec { (float)x - view_vec.get_x(),
                             (float)y - view_vec.get_y(),
                             0        - view_vec.get_z() };
            ray_vec.norm();
            
            float scale_to_inter = 0;

            int nearest = find_nearest_inter( &scale_to_inter,
                                              ray_vec,
                                              view_vec,
                                              objects,
                                              object_count);

            if ( nearest != -1 )
            {
                Vector inter_pos = view + ray_vec * scale_to_inter;
                Vector norm_vec = inter_pos - objects[nearest].centre_pos_;
                norm_vec.norm();

                Vector reflect_vec {};
                
                vec_reflect( &reflect_vec, inter_pos, norm_vec);

                Vector light_vec = light_pos - inter_pos;
                light_vec.norm();

                float light_inter = 0;
                int inter = find_nearest_inter( &light_inter, -light_vec, light_pos, objects, object_count);

                if ( inter != nearest && inter != -1 )
                {
                    point_map[point_pos].color = sf::Color::Black;
                    continue;
                }
                
                
                Vector light_refl_vec {};
                vec_reflect( &light_refl_vec, light_vec, norm_vec);
                
                float diffusion = max( cosv( &light_vec, &norm_vec), 0.f);
                float specular  = powf( max( -cosv( &light_refl_vec, &view_vec), 0.f),
                                       objects[nearest].spec_coeff_);
                // use "-" because the light_vec in against direction
                
                constexpr int cvt_to_int = 255;
                
                sf::Uint8 i_diff = (sf::Uint8)(diffusion * cvt_to_int);
                sf::Color diff_color { i_diff, i_diff, i_diff };
                sf::Uint8 i_spec = (sf::Uint8)(specular * cvt_to_int);
                sf::Color spec_color { i_spec, i_spec, i_spec };
                
                point_map[point_pos].color = objects[nearest].color_ * diff_color + spec_color;
                
            }

        }
    }

    window.draw( point_map);
    
}




