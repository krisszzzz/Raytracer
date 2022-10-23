#include "renderer.h"

LightRenderer::LightRenderer( const std::vector<Sphere>& objects,
                              const std::vector<Light>& lighting,
                              const std::size_t x_res,
                              const std::size_t y_res,
                              const Vector& camera) :
    x_res_(x_res),
    y_res_(y_res),
    point_map_(sf::Points, x_res * y_res),
    camera_(camera),
    objects_(objects),
    lighting_(lighting)
{
} /* LightRenderer::LightRenderer */

LightRenderer::LightRenderer( const std::size_t x_res,
                              const std::size_t y_res,
                              const Vector& camera) :
    x_res_(x_res),
    y_res_(y_res),
    point_map_(sf::Points, x_res * y_res),
    camera_(camera),
    objects_(),
    lighting_()
{
} /* LighRenderer::LightRenderer */


LightRenderer::LightRenderer() :
    x_res_(0),
    y_res_(0),
    point_map_(),
    camera_(),
    objects_(),
    lighting_()
{
} /* LighRenderer::LightRenderer */

void
LightRenderer::set_point( std::size_t x,
                          std::size_t y,
                          sf::Color color)
{
    point_map_[x + y * x_res_].position.x = (float)x; 
    point_map_[x + y * x_res_].position.y = (float)y; 
    point_map_[x + y * x_res_].color = color;
} /* LightRenderer::set_point */

void
LightRenderer::clear( sf::Color color)
{
    for ( std::size_t y = 0; y < y_res_; y++ )
    {
        for ( std::size_t x = 0; x < x_res_; x++ )
        {
            set_point( x, y, color);
        }
        
    }
} /* LightRenderer::clear */

       
