#include "raytracer.h"

static int
is_equal( float lval,
          float rval)
{
    constexpr float ACCURACY = 1e-6f;
	return (fabs(lval - rval) < ACCURACY) ? 1 : 0;
} /* is_equal */


/*
 * solve linear equation b*x + c = 0
 */

static int
solve_linear( float b, 
              float c,
              float* x1,
              float* x2)
{
    if ( is_equal(b, 0) )
    {
        return ( is_equal(c, 0) ) ? INF_SOLUTION : NO_SOLUTION;
    }

    *x1 = *x2 = -c / b;

    return 1;

} /* solve_lineal */

int
solve_quadratic( float a,
                 float b,
                 float c,
                 float* x1,
                 float* x2)
{
    if ( is_equal(a, 0) )
    {
        return solve_linear( b, c, x1, x2);
    }

    float d = b * b - 4 * a * c;

    if ( is_equal(d, 0) )
    {
        *x1 = *x2 = -b / (2 * a);

        return ONE_SOLUTION;
    }

    if ( d > 0 )
    {
        float sqrt_d = sqrt(d);
        *x1 = (-b + sqrt_d) / (2 * a);
        *x2 = (-b - sqrt_d) / (2 * a);
        
        return TWO_SOLUTION;
    }
    
    return NO_SOLUTION;
    
}


static int
is_inter_against_ray( const Point3f& inter_point,
                      const Point3f& on_ray,
                      const Vector& ray_vec)
{
    Vector to_point = { inter_point.x_ - on_ray.x_,
                        inter_point.y_ - on_ray.y_,
                        inter_point.z_ - on_ray.z_ };

    return dot( to_point, ray_vec) < 0;

}

static void
find_nearest_inter( Point3f* nearest_inter, // the nearest inter will be placed in this var                 
                    const Point3f& point_ref,
                    const Point3f& on_ray)
{
    Vector first_point = { nearest_inter->x_ - on_ray.x_,
                           nearest_inter->y_ - on_ray.y_,
                           nearest_inter->z_ - on_ray.z_ };

    Vector second_point = { point_ref.x_ - on_ray.x_,
                            point_ref.y_ - on_ray.y_,
                            point_ref.z_ - on_ray.z_ };

    if ( second_point.count_len_sq() > first_point.count_len_sq() )
    {
        nearest_inter->x_ = point_ref.x_;
        nearest_inter->y_ = point_ref.y_;
        nearest_inter->z_ = point_ref.z_;
    }
        

}

static int 
is_intersect( Vector& dir, // vector of ray
              const Vector& orig,
              const Sphere& sphere)
{
    Vector to_center = sphere.centre_pos_ - orig;
    float dir_center_dot = dot( dir, to_center) /
                           sqrt( dir.count_len_sq());

    float distance_2 = to_center.count_len_sq() -
                       dir_center_dot * dir_center_dot;

    //printf( "distance_2 = %f\n", distance_2);

    if ( distance_2 > sphere.radius_ * sphere.radius_ )
    {
        return 0;
    }

    return 1;
}

void
raytracer( sf::RenderWindow& window,
           int x_size,
           int y_size,
           Sphere objects[],
           const Vector& view)
{

    // Point3f inter_points[2] = {};
    // Sphere sphere { sf::Color::Green, Vector { 960, 600, 0 }, 200 };

    // if (find_intersection( inter_points, Vector { 961 - 960, -600, -1500 }, Point3f { 960, 600, 1500 }, sphere) )
    // {
    //     printf("WTF\n");
    // }

    // printf( "Intersections: (%f; %f; %f) (%f; %f; %f)\n",
    //         inter_points[0].x_, inter_points[0].y_, inter_points[0].z_,
    //         inter_points[1].x_, inter_points[1].y_, inter_points[1].z_);
    
    sf::VertexArray point_map { sf::Points, x_size * y_size };
    
    for ( int y = 0; y < y_size; y++ )
    {
        for ( int x = 0; x < x_size; x++ )
        {
            int point_pos = x + y * x_size;
            
            Vector ray_vec { (float)x - view.x_,
                             (float)y - view.y_,
                              0       - view.z_ };

            if ( is_intersect( ray_vec, view, objects[0]) )
            {
                // if ( y <= 10 )
                // {
                //     printf( "x = %d, y = %d\n", x, y);
                // }
                
                // printf( "Ray vec: (%f, %f, %f), intersection: (%f; %f; %f), (%f; %f; %f)\n",
                //         ray_vec.x_, ray_vec.y_, ray_vec.z_,
                //         inter_points[0].x_, inter_points[0].y_, inter_points[0].z_,
                //         inter_points[1].x_, inter_points[1].y_, inter_points[1].z_);
                
                point_map[point_pos].position.x = (float)x;
                point_map[point_pos].position.y = (float)y;
                point_map[point_pos].color = objects[0].color_;
                
            }

        }
    }

    window.draw( point_map);
    
}




