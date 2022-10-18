#ifndef SCENE_H_
#define SCENE_H_

#include "vector.h"
#include "objects.h"

#include <SFML/Graphics.hpp>
#include <cstddef>
#include <vector>

#define RESOLUTION_DEFAULT 0 

#define NON_COPYABLE( Type)         \
        Type( const Type&) = delete; \
        Type& operator=( const Type&) = delete

// Special class for raycasting and raytracing
class Scene
{
public:

    Scene() : kernel() {};
    
    Scene( sf::RenderWindow* window,
           const Vector& camera,
           std::size_t obj_size = 0,
           std::size_t light_size = 0,
           const sf::Color& ambient = sf::Color::Black) :
        kernel(window,
               camera,
               obj_size,
               light_size,
               ambient)
    {};

    Sphere&
    get_obj( std::size_t size)
    {
        return kernel.objects_.at( size);
    }
    
    const Sphere&
    get_obj( std::size_t size) const
    {
        return kernel.objects_.at( size);
    }

    std::size_t
    get_obj_size() const
    {
        return kernel.objects_.size();
    }

    void
    set_obj( std::size_t size,
             const Sphere& obj)
    {
        kernel.objects_.at( size) = obj;
    }

    Light&
    get_light( std::size_t size)
    {
        return kernel.lighting_.at( size);
    }

    const Light&
    get_light( std::size_t size) const
    {
        return kernel.lighting_.at( size);
    }

    void
    set_light( std::size_t size,
               const Light& light)
    {
        kernel.lighting_.at( size) = light;
    }
    

    std::size_t
    get_light_size() const
    {
        return kernel.lighting_.size();
    }

    Vector&
    get_camera()
    {
        return kernel.camera_;
    }

    const Vector&
    get_camera() const
    {
        return kernel.camera_;
    }
    
    void
    set_camera( const Vector& camera)
    {
        kernel.camera_ = camera;
    }

    void
    add_light( const Vector& light_pos,
               const sf::Color& color)
    {
        Light tmp_light { light_pos, color };
        kernel.lighting_.push_back( tmp_light);
    }

    void
    add_light( const Light& light)
    {
        kernel.lighting_.push_back( light);
    }

    void
    add_obj( const Sphere& obj)
    {
        kernel.objects_.push_back( obj);
    }

    sf::RenderWindow*
    get_window()
    {
        return kernel.window_;
    }

    void
    attach( sf::RenderWindow* window)
    {
        kernel.window_ = window;
    }

    void
    detach()
    {
        kernel.window_ = nullptr;
    }

    std::vector<Light>&
    get_lighting()
    {
        return kernel.lighting_;
    }

    std::vector<Sphere>&
    get_objects()
    {
        return kernel.objects_;
    }

    struct Phong
    {
        float diffusion;
        float specular;
    }; 
    
    int get_phong( Phong* phong,
                   const Vector& orig,
                   const std::size_t curr_obj);

    void raycast( const std::size_t obj_num = 0);
    void raytrace( std::size_t width = RESOLUTION_DEFAULT,
                   std::size_t height = RESOLUTION_DEFAULT);
    
private:
  
    class SceneKern
    {
    public:
        SceneKern() :
            window_(nullptr),
            objects_(0),
            lighting_(0),
            camera_(),
            ambient_() {}; 

        SceneKern( sf::RenderWindow* window,
                   const Vector& camera,
                   std::size_t obj_count,
                   std::size_t light_count,
                   const sf::Color& ambient
                   ) :
            window_(window),
            objects_(obj_count),
            lighting_(light_count),
            camera_(camera),
            ambient_(ambient)
        {};

        NON_COPYABLE( SceneKern);
           
        sf::RenderWindow* window_;
        std::vector<Sphere> objects_;
        std::vector<Light> lighting_;
        Vector camera_;
        sf::Color ambient_;
    } kernel;
    
};
    

#endif
