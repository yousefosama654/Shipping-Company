#pragma once
template <typename T>
class PriNode
{
private:
	T item;
	PriNode<T>* next;
	int priority;
public:
	PriNode()
	{
		next = nullptr;
		priority = 0;
	}

	PriNode(T newItem, int p = 0)
	{
		item = newItem;
		next = nullptr;
		priority = p;
	}

	void setItem(T newItem)
	{
		item = newItem;
	}

	void setNext(PriNode<T>* nextPtr)
	{
		next = nextPtr;
	}

	void setPriority(int p)
	{
		priority = p;
	}

	T getItem() const
	{
		return item;
	}

	PriNode<T>* getNext() const
	{
		return next;
	}

	int getPriority() const
	{
		return priority;
	}
};