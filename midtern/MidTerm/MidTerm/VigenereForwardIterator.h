
// COS30008, Midterm 2024

#pragma once

#include <string>

#include "KeyProvider.h"

constexpr size_t CHARACTERS = 26;

enum class EVigenereMode
{
    Encode,
    Decode
};

class VigenereForwardIterator
{
private:
    EVigenereMode fMode;
    char fMappingTable[CHARACTERS][CHARACTERS];
    KeyProvider fKeys;
    std::string fSource;
    size_t fIndex;
    char fCurrentChar;

    // Initialize the mapping table
    // Row 1:   B - A
    // Row 26:  A - Z
    void initializeTable();

    void encodeCurrentChar() noexcept;
    void decodeCurrentChar() noexcept;

public:

    VigenereForwardIterator(
        const std::string& aKeyword,
        const std::string& aSource,
        EVigenereMode aMode = EVigenereMode::Encode) noexcept;

    char operator*() const noexcept;

    VigenereForwardIterator& operator++() noexcept;
    VigenereForwardIterator operator++(int) noexcept;

    bool operator==(const VigenereForwardIterator& aOther) const noexcept;
    bool operator!=(const VigenereForwardIterator& aOther) const noexcept;

    VigenereForwardIterator begin() const noexcept;
    VigenereForwardIterator end() const noexcept;
};
