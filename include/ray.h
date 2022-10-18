#ifndef RAY_H_
#define RAY_H_

#include "vector.h"
#include "objects.h"

class Ray
{
public:
    Ray( const Vector& ray,
         const Vector& orig) :
        ray_(ray),
        orig_(orig),
        color_(sf::Color::Transparent) {};

    // Vector&
    // operator[]( std::size_t elem)
    // {
    //     return cross_.at( elem);
    // }

    void
    mix_color( const sf::Color& color)
    {
        color_ *= color;
    }

    void
    set_color( const sf::Color& color)
    {
        color_ = color;
    }

    void
    set_ray( const Vector& ray)
    {
        ray_ = ray;
    }

    Vector&
    get_ray()
    {
        return ray_;
    }

    Vector&
    get_orig()
    {
        return orig_;
    }

    void
    reflect( const Vector& norm)
    {
        ray_ = ray_ - norm * 2.f * dot( ray_, norm);
        ray_.norm();
    }

    int find_cross( const Sphere& object,
                    Vector* cross = nullptr);
    int find_cross_scale( const Sphere& object,
                          float* cross_scale = nullptr);
    int is_cross( const std::vector<Sphere>& objects);
    int is_cross( const std::vector<Sphere>& objects,
                  const std::size_t obj_orig);
    int nearest_cross( const std::vector<Sphere>& objects,
                       Vector* cross);

private:
    Vector ray_;
    Vector orig_;
    sf::Color color_;
};

#endif
