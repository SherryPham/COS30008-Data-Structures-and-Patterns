

//Created by Tran Anh Thu Pham on 24th April, 2024
//Midterm Assessment - COS30008
//KeyProvider.cpp

#pragma once

#include "KeyProvider.h"

#include <cassert>
#include <cctype>
#include <string>


//Return uppercase string, make sure no non-alphabet character
std::string KeyProvider::preprocessString(const std::string& aString) noexcept
{
    std::string result;
    for (char c : aString)
    {
        if (isalpha(c)) //check if a character is a alphabet
        {
            result += toupper(c); //convert that character to uppercase 
        }
    }
    return result;
}


// Constructor to compute the keyword sequence
KeyProvider::KeyProvider(const std::string& aKeyword, const std::string& aSource) noexcept :
    fIndex(0)
{
    std::string processedSource = preprocessString(aSource); 
    std::string processedKeyword = preprocessString(aKeyword); 
    
    size_t sourceLength = processedSource.length(); //length of input message
    size_t keywordLength = processedKeyword.length(); //length of input keyword

    size_t repititions = sourceLength / keywordLength; //the number of times keyword repeated to match the source
    size_t remainingChars = sourceLength % keywordLength; //the remainder of keyword's chracters after matching the source

    fKeys.reserve(sourceLength);

    if (repititions > 0)
    {
        for (size_t i = 0; i < repititions; ++i)
        {
            fKeys += processedKeyword;
        }
   }
    
    if (remainingChars > 0)
    {
        fKeys += processedKeyword.substr(0, remainingChars);
    }

    size_t messageLength = preprocessString(aSource).length();
    assert(fKeys.length() == messageLength);
}


//Dereference operator returns the keyword character the iterator is positioned on
char KeyProvider::operator*() const noexcept
{
    return fKeys[fIndex];
}

//Prefix operator advances the interator and return the update iterator
KeyProvider& KeyProvider::operator++() noexcept
{
    fIndex++;
    return *this;
}

//Postfix operator advances the iterator and return the old iterator
KeyProvider KeyProvider::operator++(int) noexcept
{
    KeyProvider old = *this;
    ++(*this);
    return old;
}

//Return true if this iterator and aOther are equal
bool KeyProvider::operator==(const KeyProvider& aOther) const noexcept
{
    return (fKeys == aOther.fKeys && fIndex == aOther.fIndex);
}

//Return true if this iterator and aOther are not equal
bool KeyProvider::operator!=(const KeyProvider& aOther) const noexcept
{
    return !(*this == aOther);
}

//Return a copy of "this" iterator positioned at the first keyword character
KeyProvider KeyProvider::begin() const noexcept
{
    KeyProvider copy = *this;
    copy.fIndex = 0;
    return copy;
}

//Return a copy of "this" iterator positioned at the last keyword character
KeyProvider KeyProvider::end() const noexcept
{
    KeyProvider copy = *this;
    copy.fIndex = fKeys.length(); //Set index to the end of the keyword sequence
    return copy;
}

