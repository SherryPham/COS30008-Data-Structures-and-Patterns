
// COS30008: Tutorial 10, 2024

#pragma once

#include <optional>
#include <cassert>

template<typename T>
class Stack
{
private:
    T* fElements;
    size_t fStackPointer;
    size_t fCurrentSize;

    void resize(size_t aNewSize)
    {
        assert(fStackPointer <= aNewSize);

        T* lNewElements = new T[aNewSize];

        for (size_t i = 0; i < fStackPointer; i++)
        {
            lNewElements[i] = std::move(fElements[i]);
        }

        delete[] fElements;

        fElements = lNewElements;
        fCurrentSize = aNewSize;
    }

    void ensure_capacity()
    {
        // Is load factor 1?
        if (fStackPointer == fCurrentSize)
        {
            resize(fCurrentSize * 2);
        }
    }

    void adjust_capacity()
    {
        // Is load factor 1/4?
        if (fStackPointer <= fCurrentSize / 4)
        {
            resize(fCurrentSize / 2);
        }
    }

public:

    Stack() :
        fElements(new T[1]),
        fStackPointer(0),
        fCurrentSize(1)
    {}

    ~Stack()
    {
        delete[] fElements;
    }

    // copy semantics
    Stack(const Stack& aOther) :
        fElements(new T[aOther.fCurrentSize]),
        fStackPointer(aOther.fStackPointer),
        fCurrentSize(aOther.fCurrentSize)
    {
        assert(fStackPointer <= fCurrentSize);

        // we only need to copy contents up to stack pointer
        for (size_t i = 0; i < fStackPointer; i++)
        {
            fElements[i] = aOther.fElements[i];
        }
    }

    Stack operator=(const Stack<T>& aOther)
    {
        if (this != &aOther)           // self-assignment check
        {
            this->~Stack();              // free this stack

            new (this) Stack(aOther);  // in-place new copy constructor
        }

        return *this;
    }

    // move semantics
    Stack(Stack<T>&& aOther) noexcept :
        Stack()
    {
        swap(aOther); // swap idiom
    }

    Stack operator=(Stack<T>&& aOther) noexcept
    {
        if (this != &aOther)
        {
            swap(aOther); // swap idiom
        }

        return *this;
    }

    void swap(Stack& aOther) noexcept
    {
        std::swap(fElements, aOther.fElements);
        std::swap(fStackPointer, aOther.fStackPointer);
        std::swap(fCurrentSize, aOther.fCurrentSize);
    }

    size_t size() const noexcept
    {
        return fStackPointer;
    }

    std::optional<T> top() noexcept
    {
        if (fStackPointer > 0)
        {
            return std::optional<T>(fElements[fStackPointer - 1]);
        }
        else
        {
            return std::optional<T>();
        }
    }

    void push(const T& aValue)
    {
        ensure_capacity();

        fElements[fStackPointer++] = aValue;
    }

    template<typename... Args>
    void emplace(Args&&... args)  // uses type deduction
    {
        ensure_capacity();

        // free old entry
        fElements[fStackPointer].~T();

        // placement new (matching constructor)
        new (&fElements[fStackPointer++]) T(std::forward<Args>(args)...);
    }

    void pop()
    {
        assert(fStackPointer > 0);

        fStackPointer--;

        adjust_capacity();
    }
};
