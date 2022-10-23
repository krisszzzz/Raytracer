#ifndef RAY_H_
#define RAY_H_


#include "vector.h"

class Ray
{
public:
    Ray( const Vector& orig,
         const Vector& dir) :
        orig_(orig),
        dir_(dir)
    {};

    Ray() :
        orig_(),
        dir_()
    {};

    void
    set_orig( const Vector& orig)
    {
        orig_ = orig;
    }

    void
    set_dir( const Vector& dir)
    {
        dir_ = dir;
    }

    const Vector&
    get_orig() const
    {
        return orig_;
    }
    
    const Vector&
    get_dir() const
    {
        return dir_;
    }

    Vector&
    get_orig()
    {
        return orig_;
    }

    Vector&
    get_dir()
    {
        return dir_;
    }
    
    void reflect( const Vector& norm)
    {
        dir_ = dir_ - norm * 2.f * dot( dir_, norm);
    }

private:
    Vector orig_;
    Vector dir_;
};

#endif
