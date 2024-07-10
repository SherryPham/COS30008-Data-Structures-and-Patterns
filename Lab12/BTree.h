
// COS30008, Tutorial 12, 2024

#pragma once

#include <memory>
#include <cassert>
#include <iostream>

#include "Visitors.h"

template<typename T>
class BTree
{
public:
	using Node = std::unique_ptr<BTree>;

	BTree(const T& aKey = T{}) noexcept :
		fKey(aKey)
	{}

	BTree(T&& aKey) noexcept :
		fKey(std::move(aKey))
	{}

	~BTree()
	{
		std::cout << "Delete " << fKey << std::endl;
	}

	template<typename... Args>
	static Node makeNode(Args&&... args)
	{
		return std::make_unique<BTree>(std::forward<Args>(args)...);
	}

	BTree(const BTree& aOther) :
		fKey(aOther.fKey)
	{
		if (aOther.fLeft)
		{
			// copy non-empty subtree
			fLeft = std::move(makeNode(*aOther.fLeft));
		}

		if (aOther.fRight)
		{
			// copy non-empty subtree
			fRight = std::move(makeNode(*aOther.fRight));
		}
	}

	BTree& operator=(const BTree& aOther)
	{
		if (this != &aOther)
		{
			this->~BTree();

			new (this) BTree(aOther);
		}

		return *this;
	}

	BTree(BTree&& aOther) noexcept :
		BTree()
	{
		swap(aOther);
	}

	BTree& operator=(BTree&& aOther) noexcept
	{
		if (this != &aOther)
		{
			swap(aOther);
		}

		return *this;
	}

	void swap(BTree& aOther) noexcept
	{
		std::swap(fKey, aOther.fKey);
		std::swap(fLeft, aOther.fLeft);
		std::swap(fRight, aOther.fRight);
	}

	const T& operator*() const noexcept
	{
		return fKey;
	}

	bool hasLeft() const noexcept
	{
		return fLeft ? true : false;
	}

	BTree& left() const
	{
		// valid node
		assert(fLeft);

		return *fLeft;
	}

	bool hasRight() const noexcept
	{
		return fRight ? true : false;
	}

	BTree& right() const
	{
		// valid node
		assert(fRight);

		return *fRight;
	}

	void attachLeft(Node& aNode)
	{
		// transfers ownership from aNode to fLeft

		// valid free node
		assert(!fLeft);

		fLeft = std::move(aNode);
	}

	void attachRight(Node& aNode)
	{
		// transfers ownership from aNode to fRight

		// valid free node
		assert(!fRight);

		fRight = std::move(aNode);
	}

	Node detachLeft()
	{
		// transfers ownership from fLeft to result

		// valid index and node
		assert(fLeft);

		return std::move(fLeft);
	}

	Node detachRight()
	{
		// transfers ownership from fRight to result

		// valid index and node
		assert(fRight);

		return std::move(fRight);
	}

	bool leaf() const noexcept
	{
		return !fLeft && !fRight;
	}

	size_t height() const noexcept
	{
		size_t Result = 0;

		if (!leaf())
		{
			Result = std::max(fLeft ? fLeft->height() + 1 : 0,
				fRight ? fRight->height() + 1 : 0);
		}

		return Result;
	}

	const T& findMax() const noexcept
	{
		if (hasRight())
		{
			return right().findMax();
		}

		return **this;
	}

	const T& findMin() const noexcept
	{
		if (hasLeft())
		{
			return left().findMin();
		}

		return **this;
	}

	void doDepthFirstSearch(const TreeVisitor<T>& aVisitor) const noexcept
	{
		aVisitor.preVisit(**this);

		if (hasLeft())
		{
			left().doDepthFirstSearch(aVisitor);
		}

		aVisitor.inVisit(**this);

		if (hasRight())
		{
			right().doDepthFirstSearch(aVisitor);
		}

		aVisitor.postVisit(**this);
	}

private:
	T fKey;
	Node fLeft;
	Node fRight;
};
