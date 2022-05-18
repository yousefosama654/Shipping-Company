#ifndef _LINKEDLIST
#define _LINKEDLIST
#include "ListADT.h"
#include "Node.h"
#include <iostream>
using namespace std;

template <typename T>
class LinkedList : public ListADT<T>
{
private:
	Node<T>* Head;	//Pointer to the head of the list
	int itemCount;
	Node<T>* getNodeAt(int position) const
	{
		if ((position >= 1) && (position <= itemCount))
		{
			Node<T>* curPtr = Head;
			for (int skip = 1; skip < position; skip++)
				curPtr = curPtr->getNext();
			return curPtr;
		}
		else
			return NULL;
	}
public:
	LinkedList() : itemCount(0)
	{
		Head = nullptr;
	}

	LinkedList(const LinkedList<T>& L)
	{
		int i = 1;
		T x;
		while (x = L.getEntry(i))
		{
			insert(i, x);
			i++;
		}
	}

	T getEntry(int position) const
	{
		bool ableToGet = (position >= 1) && (position <= itemCount);
		if (ableToGet)
		{
			Node<T>* nodePtr = getNodeAt(position);
			return nodePtr->getItem();
		}
		return 0;
	}

	bool isEmpty() const
	{
		if (itemCount == 0)
			return true;
		return false;
	}

	bool insert(int newPosition, const T& newEntry)
	{
		bool ableToInsert = (newPosition >= 1) && (newPosition <= itemCount + 1);
		if (ableToInsert)
		{
			Node<T>* newNodePtr = new Node<T>(newEntry);
			if (newPosition == 1)
			{
				newNodePtr->setNext(Head);
				Head = newNodePtr;
			}
			else
			{
				Node<T>* prevPtr = getNodeAt(newPosition - 1);
				newNodePtr->setNext(prevPtr->getNext());
				prevPtr->setNext(newNodePtr);
			}
			itemCount++;
		}
		return ableToInsert;
	}

	bool remove(int position)
	{
		bool ableToRemove = (position >= 1) && (position <= itemCount);
		if (ableToRemove)
		{
			Node<T>* curPtr = nullptr;
			if (position == 1)
			{
				curPtr = Head;
				Head = Head->getNext();
			}
			else
			{
				Node<T>* prevPtr = getNodeAt(position - 1);
				curPtr = prevPtr->getNext();
				prevPtr->setNext(curPtr->getNext());
			}
			curPtr->setNext(nullptr);
			delete curPtr;
			curPtr = nullptr;
			itemCount--;
		}
		return ableToRemove;
	}

	void clear()
	{
		while (!isEmpty())
			remove(1);
	}

	~LinkedList()
	{
		clear();
	}
};
#endif
/*
*/