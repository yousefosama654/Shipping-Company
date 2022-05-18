#pragma once
#include "Node.h"
using namespace std;

template <typename T>
class Queue
{
private:

	Node<T>* backPtr;
	Node<T>* frontPtr;
	int count; 
public:
	Queue();
	bool isEmpty() const;
	bool enqueue(const T& newEntry);
	bool dequeue(T& frntEntry);
	int getCount(); 
	bool peek(T& frntEntry)  const;
	~Queue();
	Queue(const Queue<T>& LQ);
};

template <typename T>
Queue<T>::Queue()
{
	backPtr = nullptr;
	frontPtr = nullptr;
	count = 0; 
}
template <typename T>
int Queue<T>::getCount()
{
	return count; 
}
template <typename T>
bool Queue<T>::isEmpty() const
{
	return (frontPtr == nullptr);
}


template <typename T>
bool Queue<T>::enqueue(const T& newEntry)
{
	if (!newEntry)
		return false; 
	count++; 
	Node<T>* newNodePtr = new Node<T>(newEntry);
	if (isEmpty())
		frontPtr = newNodePtr;
	else
		backPtr->setNext(newNodePtr);

	backPtr = newNodePtr;
	return true;
}

template <typename T>
bool Queue<T>::dequeue(T& frntEntry)
{
	if (isEmpty())
		return false;
	count--; 
	Node<T>* nodeToDeletePtr = frontPtr;
	frntEntry = frontPtr->getItem();
	frontPtr = frontPtr->getNext();
	if (nodeToDeletePtr == backPtr)
		backPtr = nullptr;

	delete nodeToDeletePtr;

	return true;

}


template <typename T>
bool Queue<T>::peek(T& frntEntry) const
{
	if (isEmpty())
	{
		frntEntry = nullptr;
		return false;
	}

	frntEntry = frontPtr->getItem();
	return true;

}


template <typename T>
Queue<T>::~Queue()
{
	T temp;

	while (dequeue(temp));
}


template <typename T>
Queue<T>::Queue(const Queue<T>& LQ)
{
	Node<T>* NodePtr = LQ.frontPtr;
	if (!NodePtr)
	{
		frontPtr = backPtr = nullptr;
		count = 0; 
		return;
	}
	this->count = LQ.count;

	Node<T>* ptr = new Node<T>(NodePtr->getItem());
	frontPtr = backPtr = ptr;
	NodePtr = NodePtr->getNext();
	while (NodePtr)
	{
		Node<T>* ptr = new Node<T>(NodePtr->getItem());
		backPtr->setNext(ptr);
		backPtr = ptr;
		NodePtr = NodePtr->getNext();
	}
}


