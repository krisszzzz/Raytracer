#ifndef VECTOR_H_
#define VECTOR_H_

#include <SFML/Graphics.hpp>
#include <cmath>



class Vector
{
public:
    Vector() : kernel() {}
    Vector( float x, float y, float z) : kernel(x, y, z) {}
    
    // prevent copying len of vector
    // Will be problem here: vec = vec1 - vec2;
    
          
    Vector& operator+=( const Vector& rhs);
    Vector& operator-=( const Vector& rhs);
    Vector& operator*=( const float rhs);
    Vector operator*( const float value) const;
    Vector operator+( const Vector& add) const;
    Vector operator-( const Vector& sub) const;
    Vector operator-() const;

    float
    get_x() const
    {
        return kernel.x_;
    }

    float
    get_y() const
    {
        return kernel.y_;
    }

    float
    get_z() const
    {
        return kernel.z_;
    }

    float
    get_len_sq() const
    {
        return kernel.len_sq_;
    }

    void
    set_x( float x)
    {
        kernel.x_ = x;
    }

    void
    set_y( float y)
    {
        kernel.y_ = y;
    }

    void
    set_z( float z)
    {
        kernel.z_ = z;
    }

    void
    set_len_sq( float len_sq)
    {
        kernel.len_sq_ = len_sq;
    }

    void
    set_len_sq()
    {
        if ( std::isnan( get_len_sq()) )
        {
            count_len_sq();
        }
    }

    void
    count_len_sq()
    {
        kernel.len_sq_ = get_x() * get_x() + get_y() * get_y() + get_z() * get_z();
    }

    void
    norm()
    {
        set_len_sq(); // count current len

        if ( get_len_sq() > 0 )
        {
            *this *= 1 / sqrtf( get_len_sq());
            set_len_sq(1.f); // set len to 1.f
        }
    }

    void
    print() const
    {
        printf( "%p: (%f, %f, %f), len = %f\n",
                this, this->get_x(), this->get_y(), this->get_z(), this->get_len_sq());
    }

    void draw2D( sf::RenderWindow& window,
                 const sf::Vector2f& start_point);
    void rotate2D( const float angle);

private:

    // Place in inner class the kernel to avoid
    // hardening Vector

    class VectorKern
    {
    public:
        VectorKern() : x_(0), y_(0), z_(0), len_sq_(NAN) {};
        VectorKern( float x, float y, float z) : x_(x), y_(y), z_(z), len_sq_(NAN) {};
        VectorKern( const VectorKern& vec) : x_(vec.x_), y_(vec.y_), z_(vec.z_), len_sq_(NAN) {};

        VectorKern& operator=( const VectorKern& vec)
        {
            x_ = vec.x_;
            y_ = vec.y_;
            z_ = vec.z_;
            len_sq_ = NAN;

            return *this;
        }
        
        ~VectorKern() = default;
        // prevent copying vector len
        // Will be problem here vec = vec1 + vec2; 

        float x_;
        float y_;
        float z_;
        float len_sq_;

    } kernel;

};

inline float
dot( const Vector& vec1, const Vector& vec2)
{
    return vec1.get_x() * vec2.get_x() +
           vec1.get_y() * vec2.get_y() +
           vec1.get_z() * vec2.get_z();
}

inline float
cosv( Vector* const lhs, Vector* const rhs)
{
    lhs->set_len_sq();
    rhs->set_len_sq();

    float normalize = sqrtf( rhs->get_len_sq()) * sqrtf( lhs->get_len_sq());
    return dot( *lhs, *rhs) / normalize; 
}

#endif
