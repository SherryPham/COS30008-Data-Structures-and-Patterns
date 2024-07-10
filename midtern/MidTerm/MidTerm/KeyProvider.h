
// COS30008, Midterm 2024

#pragma once

#include <string>

class KeyProvider
{
private:
    std::string fKeys;
    size_t fIndex;

    std::string preprocessString(const std::string& aString) noexcept;

public:

    KeyProvider(const std::string& aKeyword, const std::string& aSource) noexcept;

    char operator*() const noexcept;

    KeyProvider& operator++() noexcept;
    KeyProvider operator++(int) noexcept;

    bool operator==(const KeyProvider& aOther) const noexcept;
    bool operator!=(const KeyProvider& aOther) const noexcept;

    KeyProvider begin() const noexcept;
    KeyProvider end() const noexcept;
};
