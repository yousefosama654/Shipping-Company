#pragma once
#include "PriNode.h"
#pragma once
template <typename T>
class PriQ
{
private:
	PriNode<T>* frontptr;
	PriNode<T>* backptr;
public:
	PriQ();
	bool isEmpty();
	bool enqueue(T& entry, int pri);
	bool dequeue(T& frnt);
	bool peek(T& frnt);
	~PriQ();

	PriQ(PriQ<T>& copy);
};

template<typename T>
PriQ<T> ::PriQ()
{
	frontptr = nullptr;
	backptr = nullptr;
}

template <typename T>
bool PriQ<T> ::isEmpty()
{
	return (frontptr == nullptr);
}

template <typename T>
bool PriQ<T> ::enqueue(T& entry, int pri)
{
	PriNode<T>* newNode = new PriNode<T>(entry, pri);
	if (isEmpty())
	{
		frontptr = newNode;
		backptr = newNode;
		return false; 
	}
	else
	{
		PriNode<T>* traverse = frontptr;
		if (frontptr->getPriority() < newNode->getPriority())	//Highest Priority Case
		{
			newNode->setNext(frontptr);
			frontptr = newNode;
			return true;
		}
		if (backptr->getPriority() >= newNode->getPriority())	//Lowest Priority Case
		{
			backptr->setNext(newNode);
			backptr = newNode;
			return true;
		}
		while (traverse->getNext())	//Normal case
		{
			if (traverse->getNext()->getPriority() < newNode->getPriority())
			{
				newNode->setNext(traverse->getNext());
				traverse->setNext(newNode);
				return true;
			}
			traverse = traverse->getNext();
		}
	}
}

template <typename T>
bool PriQ<T> ::dequeue(T& frnt)
{
	if (isEmpty())
	{
		frnt = nullptr; 
		return false;
	}

	frnt = frontptr->getItem();
	PriNode<T>* toBeDeleted = frontptr;
	frontptr = frontptr->getNext();

	if (toBeDeleted == backptr)
		backptr = nullptr;

	delete toBeDeleted;
	return true;
}

template <typename T>
bool PriQ<T> ::peek(T& frnt)
{
	if (isEmpty())
	{
		frnt = nullptr; 
		return false;
	}

	frnt = frontptr->getItem();
	return true;
}

template <typename T>
PriQ<T>::~PriQ()
{
	T end;

	while (dequeue(end));
}

template <typename T>
PriQ<T>::PriQ(PriQ<T>& copy)
{
	PriNode<T>* ptr = copy.frontptr;

	if (!ptr)
	{
		frontptr = nullptr;
		backptr = nullptr;
		return;
	}

	PriNode<T>* tmpfirst = new PriNode<T>(ptr->getItem());
	frontptr = tmpfirst;
	backptr = tmpfirst;
	ptr = ptr->getNext();

	while (ptr)
	{
		PriNode<T>* tmp = new PriNode<T>(ptr->getItem());
		backptr->setNext(tmp);
		backptr = backptr->getNext();
		ptr = ptr->getNext();
	}
}
