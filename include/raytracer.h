#include "renderer.h"
#include "ray.h"

#define NOT_AN_OBJECT (std::size_t)-1

class Raytracer : public LightRenderer
{
public:
    NON_COPYABLE( Raytracer);

    Raytracer( const std::vector<Sphere>& objects,
               const std::vector<Light>& lighting,
               const std::size_t x_res,
               const std::size_t y_res,
               const Vector& camera = Vector { 0, 0, 0 });

    Raytracer( const std::size_t x_res,
               const std::size_t y_res,
               const Vector& camera = Vector { 0, 0, 0 });

    Raytracer() : LightRenderer(), render_object_(NOT_AN_OBJECT) {};
    
    void render();
    
private:

    void set_render_object( std::size_t new_object)
    {
        render_object_ = new_object;
    }

    const Sphere&
    get_render_object() const
    {
        return objects_.at( render_object_);
    }
    
    sf::Color get_phong( const Vector& orig); 
    sf::Color trace_ray( Ray* const ray, int max_depth); 
    int hittable( Ray* const ray,
                  Vector* nearest = nullptr);
    
    std::size_t render_object_; // current Sphere that is rendered
};

