
// COS30008, 2024

#define _USE_MATH_DEFINES     // must be defined before any #include  
#include "Vector2D.h"

#include <cmath>

Vector2D::Vector2D( float aX, float aY ) noexcept :
    fX(aX),
    fY(aY)
{}

Vector2D Vector2D::operator+( const Vector2D& aOther ) const noexcept
{
    return Vector2D( x() + aOther.x(), y() + aOther.y() );
}

Vector2D Vector2D::operator-( const Vector2D& aOther ) const noexcept
{
    return Vector2D( x() - aOther.x(), y() - aOther.y() );
}

Vector2D Vector2D::operator*( const float aScalar ) const noexcept
{
    return Vector2D( x() * aScalar, y() * aScalar );
}

float Vector2D::dot( const Vector2D& aOther ) const noexcept
{
    return x() * aOther.x() + y() * aOther.y();
}

float Vector2D::cross( const Vector2D& aOther ) const noexcept
{
    return x() * aOther.y() - y() * aOther.x();
}

float Vector2D::length() const noexcept
{
    float val = std::sqrt( x() * x() + y() * y() );
    
    return std::round( val * 100.0f ) / 100.0f;
}

Vector2D Vector2D::normalize() const noexcept
{
    return *this * (1.0f/length());
}

float Vector2D::direction() const noexcept
{
    float val = std::atan2( y(), x() ) * 180.0f / static_cast<float>(M_PI);
    
    return std::round( val * 100.0f ) / 100.0f;
}

Vector2D Vector2D::align( float aAngleInDegrees ) const noexcept
{
    float lRadians = aAngleInDegrees * static_cast<float>(M_PI) / 180.0f;

    return length() * Vector2D(std::cos( lRadians ), std::sin( lRadians ));
}

std::istream& operator>>( std::istream& aIStream, Vector2D& aVector )
{
    return aIStream >> aVector.fX >> aVector.fY;
}

std::ostream& operator<<( std::ostream& aOStream, const Vector2D& aVector )
{
    return aOStream << "[" << round( aVector.fX ) << "," << round( aVector.fY ) << "]";
}

Vector2D operator*( const float aScalar, const Vector2D& aVector ) noexcept
{
    return aVector * aScalar;
}
