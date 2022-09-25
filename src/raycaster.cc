#include "raycaster.h"


void
sphere_raycast( sf::RenderWindow& window,
                const Point2f centre,
                Point3f light_pos,
                const float radius,
                const sf::Color color)
{
    int i_radius = (int)radius;

    // recount light position in centre system
    light_pos.x_ -= centre.x_;
    light_pos.y_ =  centre.y_ - light_pos.y_;

    sf::VertexArray point_map { sf::Points, i_radius * i_radius * 4 };

    float r_2 = (float) ( radius * radius);

    for ( int y = 0; y < 2 * i_radius; y++ )
    {
        float y_pos = (float)-y + radius;
        
        for ( int x = 0; x < 2 * i_radius; x++ )
        {
            int point_pos = x + y * 2 * i_radius;
            
            point_map[point_pos].position.x = (float)x + centre.x_ - radius;
            point_map[point_pos].position.y = (float)y + centre.y_ - radius;
            point_map[point_pos].color = sf::Color::Black; // default color
            
            float x_pos = (float)x - radius;
            float x_y_sqr = x_pos * x_pos + y_pos * y_pos;

            if ( x_y_sqr < r_2 )
            {
                float z_pos = sqrt( r_2 - x_y_sqr);
                
                Vector norm_vec { x_pos, y_pos, z_pos };
                Vector light_vec  {
                                light_pos.x_ - norm_vec.x_,
                                light_pos.y_ - norm_vec.y_,
                                light_pos.z_ - norm_vec.z_
                };               

                float normalize = radius * sqrt( light_vec.count_len_sq());
                
                float col_intens = dot( norm_vec, light_vec) / normalize;
                
                if ( col_intens < 0 )
                    col_intens = 0;

                // int dif_color = (int)(intens * 255);

                point_map[point_pos].color      = color;

                // point_map[point_pos].color.b = (sf::Uint8)dif_color;
            }

        }
        
    }

    window.draw( point_map);

}


