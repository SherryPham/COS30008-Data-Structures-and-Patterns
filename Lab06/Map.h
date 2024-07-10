
// COS30008, tutorial 6, 2024

#pragma once

#include <istream>
#include <ostream>

template<typename Key, typename Value>
class Map
{
private:
    Key fKey;
    Value fValue;
    
public:
    Map( const Key& aKey = Key{}, const Value& aValue = Value{}) noexcept:
        fKey(aKey),
        fValue(aValue)
    {}

    const Key& key() const noexcept
    {
        return fKey;
    }
    
    const Value& value() const noexcept
    {
        return fValue;
    }
    
    template<typename U>
    operator U() const noexcept
    {
        return static_cast<U>(fValue);
    }
    
    friend std::istream& operator>>( std::istream& aIStream, Map& aMap )
    {
        return aIStream >> aMap.fKey >> aMap.fValue;
    }

    friend std::ostream& operator<<( std::ostream& aOStream, const Map& aMap )
    {
        return aOStream << "{" << aMap.fKey << ", " << aMap.fValue << "}";
    }
};
