
// COS30008, Tutorial 2, 2024

#include "Polygon.h"

#include <iostream>
#include <fstream>
#include <cmath>

int main( int argc, char* argv[] )
{
    if ( argc < 2 )
    {
        std::cerr << "Arguments missing." << std::endl;
        std::cerr << "Usage: VectorOperations <filename>" << std::endl;
        
        // return failure, not enough arguments
        return 1;
    }

    // create text input stream connected to file named in argv[1]
    std::ifstream lInput( argv[1], std::ifstream::in );

	// operation can fail
	if ( !lInput.good() )
	{
		std::cerr << "Cannot open input file: " << argv[1] << std::endl;
		
		return 2;	// program failed (cannot open input)
	}

    Polygon lPolygon;
    
    lPolygon.readData( lInput );
    
    // close input file
    lInput.close();

    std::cout << "Data read:" << std::endl;
    
    for ( size_t i = 0; i < lPolygon.getNumberOfVertices(); i++ )
    {
        std::cout << "Vertex #" << i << ": " << lPolygon.getVertex( i ) << std::endl;
    }

    std::cout << "The perimeter of lPolygon is " << lPolygon.getPerimeter() << std::endl;
        
    std::cout << "Scale polygon by 3.2:" << std::endl;
    
    Polygon lScaled = lPolygon.scale( 3.2f );

    std::cout << "The perimeter of lScaled is " << lScaled.getPerimeter() << std::endl;

    float lFactor = std::roundf( lScaled.getPerimeter() * 100.0f / lPolygon.getPerimeter() ) / 100.0f;
    
    std::cout << "Scale factor: " << lFactor << std::endl;
    
    // return success
	return 0;
}
