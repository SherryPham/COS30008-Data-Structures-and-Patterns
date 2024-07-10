
//Created by Tran Anh Thu Pham on 24th April, 2024
//Midterm Assessment - COS30008
//VigenereForwardIterator.cpp

#pragma once

#include "VigenereForwardIterator.h"

#include <cassert>
#include <cctype>
#include <string>

//Encode current character
void VigenereForwardIterator::encodeCurrentChar() noexcept
{
	char currentChar = fSource[fIndex];
	if (std::isalpha(currentChar))
	{
		char keywordChar = *fKeys++;

		size_t row = std::toupper(keywordChar) - 'A';
		size_t column = std::toupper(currentChar) - 'A';

		fCurrentChar = fMappingTable[row][column];

		if (std::islower(currentChar))
		{
			fCurrentChar = std::tolower(fCurrentChar);
		}
	}
	else
	{
		fCurrentChar = currentChar; //No ecoding for non-alphabetic character
	}
	
}

//Decode current character
void VigenereForwardIterator::decodeCurrentChar() noexcept
{
	char currentChar = fSource[fIndex];
	if (std::isalpha(currentChar))
	{
		char keywordChar = *fKeys++;

		size_t row = std::toupper(keywordChar) - 'A';
		
		//Find the collumn corresponding to the current character
		for (size_t i = 0; i < CHARACTERS; ++i)
		{
			if (fMappingTable[row][i] == std::toupper(currentChar))
			{
				fCurrentChar = 'A' + i;   //decoded character

				if (std::islower(currentChar))
				{
					fCurrentChar = std::tolower(fCurrentChar);
				}
				break;
			}
		}
	}
	else {
		fCurrentChar = currentChar; //No decoding for non-alphabetic character
	}
}


//Constructor
VigenereForwardIterator::VigenereForwardIterator(const std::string& aKeyword,const std::string& aSource,EVigenereMode aMode) noexcept :

	fMode(aMode),
	fKeys(aKeyword, aSource),
	fSource(aSource),
	fIndex(0),
	fCurrentChar('\0')
{
	initializeTable(); 
	if (!fSource.empty())
	{
		if (fMode == EVigenereMode::Encode)
		{
			encodeCurrentChar();
		}
		else if (fMode == EVigenereMode::Decode)
		{
			decodeCurrentChar();
		}
	}
}

//Dereference operator returns the character the iterator is posotioned on
char VigenereForwardIterator::operator*() const noexcept
{
	return fCurrentChar;
}

//Prefix operator advances the iterator and returns the updated iterator
VigenereForwardIterator& VigenereForwardIterator::operator++() noexcept
{
	fIndex++;
	if (fIndex < fSource.size())
	{
		if (fMode == EVigenereMode::Encode)
		{
			encodeCurrentChar();
		}
		else if (fMode == EVigenereMode::Decode)
		{
			decodeCurrentChar();
		}
	}
	return *this;
}

//Postfix operator advances the interator and returns the old iterator
VigenereForwardIterator VigenereForwardIterator::operator++(int) noexcept
{
	VigenereForwardIterator old = *this;
	++(*this);
	return old;
}

//Return true if this iterator and aOther are equal
bool VigenereForwardIterator::operator==(const VigenereForwardIterator& aOther) const noexcept
{
	return (fSource == aOther.fSource) && (fIndex == aOther.fIndex);
}

//Return true if this iterator and aOther are not equal
bool VigenereForwardIterator::operator!=(const VigenereForwardIterator& aOther) const noexcept
{
	return !(*this == aOther);
}

//Return a copy of "this" iterator positioned at the first keyword character
VigenereForwardIterator VigenereForwardIterator::begin() const noexcept
{
	VigenereForwardIterator iter = *this; 
	iter.fIndex = 0;
	return iter;

}

//Return a copy of "this" iterator positioned at the last keyword character
VigenereForwardIterator VigenereForwardIterator::end() const noexcept
{
	VigenereForwardIterator old = *this;
	old.fIndex = fSource.size();
	return old;
}