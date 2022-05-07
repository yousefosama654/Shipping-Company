#pragma once
template<class ItemType>
class ListADT
{
public:
	virtual bool isEmpty() const = 0;
	virtual bool insert(int newPosition, const ItemType& newEntry) = 0;
	virtual bool remove(int position) = 0;
	virtual void clear() = 0;
	virtual ItemType getEntry(int position) const = 0;
};
