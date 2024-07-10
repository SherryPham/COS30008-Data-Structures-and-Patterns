//Created by Tran Anh Thu Pham
//ofstream12.cpp

#include "ofstream12.h"

#include <fstream>
#include <iostream>
#include <cstring>
#include <cstddef> 
#include <cassert>


void ofstream12::reset()		        // reset buffer
{
	for (size_t i = 0; i < fBufferSize; i++)
	{
		fBuffer[i] &= std::byte{0};
	}
	fByteIndex = 0;
	fBitIndex = 7;
}

void ofstream12::completeWriteBit() // complete write
{
	fBitIndex--;

	if (fBitIndex < 0)
	{
		fByteIndex++;
		fBitIndex = 7;

		if (fByteIndex == fBufferSize)
		{
			flush();
			reset();
		}
	}
	
}
void ofstream12::writeBit0()           // write 0
{
	completeWriteBit();
}
void ofstream12::writeBit1()          // write 1
{
	fBuffer[fByteIndex] |= std::byte{1} << fBitIndex;
	completeWriteBit();
}

ofstream12::ofstream12(const char* aFileName, size_t aBufferSize) :
	fBuffer(new std::byte[aBufferSize]),
	fBufferSize(aBufferSize),
	fBitIndex(7),
	fByteIndex(0)

{
	reset(); // init buffer with a sensible value
	open(aFileName); // open associate output file, if specified
}


ofstream12::~ofstream12()
{
	close();	// close the underlying file

	delete[] fBuffer;	// free the buffer memory
}

void ofstream12::open(const char* aFileName)
{
	assert(!isOpen());

	if (aFileName)
	{
		fOStream.open(aFileName, std::ofstream::binary);
	}
}

void ofstream12::close()
{
	flush();
	fOStream.close();
}


bool ofstream12::good() const
{
	return fOStream.good();
}

bool ofstream12::isOpen() const
{
	return fOStream.is_open();
}

void ofstream12::flush()
{
	// flush pending output, last byte maybe filled 50%
	fOStream.write(reinterpret_cast <char*>(fBuffer), fByteIndex + (fBitIndex % 7 == 0 ? 0 : 1));

}

ofstream12& ofstream12::operator<<(size_t aValue)
{
	for (size_t i = 0; i < 12; i++) // write 12 Bits
	{
		if ((aValue & 0x01) > 0)	// The current lowest bit is set
		{
			writeBit1();
		}
		else 
		{
			writeBit0();
		}
		aValue >>= 1;	//aValue := aValue / 2
	}
	return *this;		//return updated output stream
}
