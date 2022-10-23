#ifndef RENDERER_H_
#define RENDERER_H_

#include <SFML/Graphics/VertexArray.hpp>
#include <objects.h>
#include <vector>

#define NON_COPYABLE( Type)         \
        Type( const Type&) = delete; \
        Type& operator=( const Type&) = delete

class LightRenderer 
{
public:

    NON_COPYABLE( LightRenderer);
    
    LightRenderer( const std::vector<Sphere>& objects,
                   const std::vector<Light>& lighting,
                   const std::size_t x_res,
                   const std::size_t y_res,
                   const Vector& camera = Vector {0, 0, 0});

    LightRenderer( const std::size_t x_res,
                   const std::size_t y_res,
                   const Vector& camera = Vector {0, 0, 0});

    LightRenderer();

    Sphere&
    get_object( std::size_t size)
    {
        return objects_.at( size);
    }
    
    const Sphere&
    get_object( std::size_t size) const
    {
        return objects_.at( size);
    }

    std::size_t
    get_n_objects() const
    {
        return objects_.size();
    }

    void
    set_point( std::size_t x,
               std::size_t y,
               sf::Color color);
    
    void
    set_object( std::size_t size,
                const Sphere& obj)
    {
        objects_.at( size) = obj;
    }

    Light&
    get_light( std::size_t size)
    {
        return lighting_.at( size);
    }

    const Light&
    get_light( std::size_t size) const
    {
        return lighting_.at( size);
    }

    void
    set_light( std::size_t size,
               const Light& light)
    {
        lighting_.at( size) = light;
    }

    std::size_t
    get_n_light() const
    {
        return lighting_.size();
    }

    Vector&
    get_camera()
    {
        return camera_;
    }

    const Vector&
    get_camera() const
    {
        return camera_;
    }
    
    void
    set_camera( const Vector& camera)
    {
        camera_ = camera;
    }

    void
    add_light( const Vector& light_pos,
               const sf::Color& color)
    {
        Light tmp_light { light_pos, color };
        lighting_.push_back( tmp_light);
    }

    void
    add_light( const Light& light)
    {
        lighting_.push_back( light);
    }

    void
    add_object( const Sphere& obj)
    {
        objects_.push_back( obj);
    }

    std::vector<Light>&
    get_lighting()
    {
        return lighting_;
    }

    std::vector<Sphere>&
    get_objects()
    { 
        return objects_;
    }

    sf::VertexArray&
    get_point_map()
    {
        return point_map_;
    }

    virtual void render() = 0;
    virtual ~LightRenderer() = default;

    void clear( sf::Color color);
protected:
    
    std::size_t x_res_; // width 
    std::size_t y_res_; // heiight

    sf::VertexArray point_map_; //< vertex array object to store
                                //<  result of rendering
    Vector camera_; //< camera need to render image
    std::vector<Sphere> objects_; //< vector of Spheres
    std::vector<Light> lighting_; //< vector of lights
};

#endif
