// COS30008, Final Exam, 2024

#include "PalindromeStringIterator.h"

void PalindromeStringIterator::moveToNextIndex()
{
	// 3a) Move the index forward until an uppercase alphabetic character is found
	fIndex++;
	while (fIndex < static_cast<int>(fString.length()) && !std::isalpha(fString[fIndex])) 
	{
		fIndex++;
	}
}

void PalindromeStringIterator::moveToPreviousIndex()
{
	// 3b) Move the index backward until an uppercase alphabetic character is found
	fIndex--;
	while (fIndex >= 0 && !std::isalpha(fString[fIndex])) 
	{
		fIndex--;
	}
}

//3c)
PalindromeStringIterator::PalindromeStringIterator(const std::string& aString) : fString(aString), fIndex(-1)
{}

char PalindromeStringIterator::operator*() const noexcept
{ 
	// 3d) Return the uppercase alphabetic character at the current index
	return std::toupper(fString[fIndex]);
}

PalindromeStringIterator& PalindromeStringIterator::operator++() noexcept
{
	// 3e) Move to the next uppercase alphabetic character
	moveToNextIndex();
	return *this;
}

PalindromeStringIterator PalindromeStringIterator::operator++(int) noexcept
{
	PalindromeStringIterator old = *this;

	++(*this);

	return old;
}

PalindromeStringIterator& PalindromeStringIterator::operator--() noexcept
{
	// 3f) Move to the previous uppercase alphabetic character
	moveToPreviousIndex();
	return *this;
}

PalindromeStringIterator PalindromeStringIterator::operator--(int) noexcept
{
	PalindromeStringIterator old = *this;

	--(*this);

	return old;
}

bool PalindromeStringIterator::operator==(const PalindromeStringIterator& aOther) const noexcept
{
	// 3g) Check if the iterators point to the same position in the string
	return fIndex == aOther.fIndex;
}

bool PalindromeStringIterator::operator!=(const PalindromeStringIterator& aOther) const noexcept
{
	return !(*this == aOther);
}

PalindromeStringIterator PalindromeStringIterator::begin() const noexcept
{
	// 3h) Create a new iterator pointing to the first uppercase alphabetic character
	PalindromeStringIterator iter = *this;
	iter.fIndex = 0;
	if (!std::isalpha(iter.fString[iter.fIndex])) 
	{
		iter.moveToNextIndex();
	}
	return iter;
}

PalindromeStringIterator PalindromeStringIterator::end() const noexcept
{
	// 3i) Create a new iterator pointing to the position after the last uppercase alphabetic character
	PalindromeStringIterator iter = *this;
	iter.fIndex = static_cast<int>(iter.fString.length());
	return iter;
}

PalindromeStringIterator PalindromeStringIterator::rbegin() const noexcept
{
	// 3j) Create a new iterator pointing to the last uppercase alphabetic character
	PalindromeStringIterator iter = *this;
	iter.fIndex = static_cast<int>(iter.fString.length()) - 1;
	if (!std::isalpha(iter.fString[iter.fIndex])) 
	{
		iter.moveToPreviousIndex();
	}
	return iter;
}

PalindromeStringIterator PalindromeStringIterator::rend() const noexcept
{
	// 3k)
	PalindromeStringIterator iter = *this;
	iter.fIndex = -1;
	return iter;
}