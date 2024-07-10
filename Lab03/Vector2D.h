
// COS30008, tutorial 3, 2024

#pragma once

#include <iostream>

class Vector2D
{
private:

    float fX;
    float fY;
    
public:
    
    Vector2D( float aX = 1.0f, float aY = 0.0f ) noexcept;
    Vector2D( std::istream& aIStream ) : Vector2D() { aIStream >> *this; }
	
    float x() const noexcept { return fX; }
    float y() const noexcept { return fY; }

    Vector2D operator+( const Vector2D& aOther ) const noexcept;
    Vector2D operator-( const Vector2D& aOther ) const noexcept;

    Vector2D operator*( const float aScalar ) const noexcept;
    float dot( const Vector2D& aOther ) const noexcept;
    float cross( const Vector2D& aOther ) const noexcept;

    float length() const noexcept;
    Vector2D normalize() const noexcept;

    float direction() const noexcept;
    Vector2D align( float aAngleInDegrees ) const noexcept;

    friend std::istream& operator>>( std::istream& aIStream, Vector2D& aVector );
    friend std::ostream& operator<<( std::ostream& aOStream, const Vector2D& aVector );
};

Vector2D operator*( const float aScalar, const Vector2D& aVector ) noexcept;
