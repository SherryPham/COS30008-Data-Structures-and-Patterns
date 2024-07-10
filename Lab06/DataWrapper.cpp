
// COS30008, Tutorial 6, 2024

#include "DataWrapper.h"

#include <fstream>
#include <cassert>

DataWrapper::DataWrapper() :
    fSize(0),
    fData(nullptr)
{}

DataWrapper::~DataWrapper()
{
    delete [] fData;
}
        
bool DataWrapper::load( const std::string& aFileName )
{
    bool Result = false;
    std::ifstream lInput( aFileName, std::ifstream::in );
    
    if ( lInput )
    {
        if ( lInput >> fSize )
        {
            fData = new DataMap[fSize];
            
            for ( size_t i = 0; i < fSize; i++ )
            {
                lInput >> fData[i];
            }
            
            Result = true;
        }

        lInput.close();
    }
    
    return Result;
}

size_t DataWrapper::size() const noexcept
{
    return fSize;
}
    
const DataMap& DataWrapper::operator[]( size_t aIndex ) const
{
    assert( aIndex < fSize );
           
    return fData[aIndex];
}
