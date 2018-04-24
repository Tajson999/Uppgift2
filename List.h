#ifndef LIST_H
#define LIST_H
#include <iostream>
#include "Node.h"
using namespace std;

template<typename T>
class List {
private:
	Node<T> *front;
public:
	List();
	virtual ~List();

	void insertAt(int pos, const T& element) throw(...);
	List(const List& other);
	List<T>& operator=(const List<T>& other);
	void removeAt(int pos) throw(...);
	bool removeElement(const T& element);
	bool findElement(const T& toFind) const;
	int length() const;
	T getAt(int pos) const throw(...);
	void getAll(T arr[], int cap) throw(...);

};


template<typename T>
List<T>::List() {
	this->front = nullptr;
}

template<typename T>
List<T>::~List() {
	Node<T> *oneBackPtr = front;
	Node<T> *currentPtr = front;
	while (currentPtr != nullptr) {
		oneBackPtr = currentPtr;
		currentPtr = currentPtr->getNext();
		delete oneBackPtr;
	}
}

template<typename T>
void List<T>::insertAt(int pos, const T & element) throw(...) {
	if (pos < 0) {
		throw "out of bounds";
	}
	if (pos == 0) {
		front = new Node<T>(element, front);
	}
	else {
		int currentPos = 1;
		Node<T> *oneBack = front;
		Node<T> *current = front->getNext();
		while (currentPos <= pos) {
			if (currentPos == pos) {
				oneBack->setNext(new Node<T>(element, current));
				currentPos++;
			}
			else {
				currentPos++;
				oneBack = current;
				if (current != nullptr) {
					current = current->getNext();
				}
				else {
					throw "out of bounds";
				}
			}
		}
	}
	
	
}
template<typename T>
List<T>::List(const List & other) {
	Node<T> *otherPtr = other.front;
	Node<T> *thisPtr = other.front;
	if (other.front != nullptr) {
		otherPtr = other.front->getNext();
		this->front = new Node<T>(other.front->getPayload(), other.front->getNext());
	}
	else {
		this->front = nullptr;
	}
	while (otherPtr != nullptr) {
		thisPtr->setNext(new Node<T>(otherPtr->getPayload(), otherPtr->getNext()));
		thisPtr = thisPtr->getNext();
		otherPtr = otherPtr->getNext();
	}
}

template<typename T>
List<T>& List<T>::operator=(const List<T>& other) {
	if (&other != this) {
		Node<T> *oneBackPtr = front;
		Node<T> *currentPtr = front;
		while (currentPtr != nullptr) {
			oneBackPtr = currentPtr;
			currentPtr = currentPtr->getNext();
			delete oneBackPtr;
		}

		if (other.front == nullptr) {
			this->front = nullptr;
		}
		else {
			Node<T> *otherPtr = other.front;
			Node<T> *thisPtr = other.front;
			if (other.front != nullptr) {
				otherPtr = other.front->getNext();
				this->front = new Node<T>(other.front->getPayload(), other.front->getNext());
			}
			while (otherPtr != nullptr) {
				thisPtr->setNext(new Node<T>(otherPtr->getPayload(), otherPtr->getNext()));
				thisPtr = thisPtr->getNext();
				otherPtr = otherPtr->getNext();
			}
		}
		

		
	}
	return *this;
}

template<typename T>
void List<T>::removeAt(int pos) throw(...) {
	if (pos < 0) {
		throw "out of bounds";
	}
	int currentPos = 0;
	Node<T> *oneBackPtr = front;
	Node<T> *currentPtr = front;
	while (currentPos <= pos) {
		if (currentPos == pos) {
			if (currentPtr == front) {
				front = currentPtr->getNext();
			}
			else {
				oneBackPtr->setNext(currentPtr->getNext());
			}
			delete currentPtr;
			currentPos++;
		}
		else {
			currentPos++;
			oneBackPtr = currentPtr;
			if (currentPtr->getNext() != nullptr) {
				currentPtr = currentPtr->getNext();
				
			}
			else {
				throw "out of bounds";
			}
		}
	}
}

template<typename T>
bool List<T>::removeElement(const T & element) {
	bool removed = false;
	Node<T> *oneBackPtr = front;
	Node<T> *currentPtr = front;
	while (removed == false && currentPtr != nullptr) {
		if (currentPtr->getPayload() == element) {
			if (currentPtr == front) {
				front = currentPtr->getNext();
			}
			else {
				oneBackPtr->setNext(currentPtr->getNext());
			}
			delete currentPtr;
			removed = true;
		}
		else {
			oneBackPtr = currentPtr;
			currentPtr = currentPtr->getNext();
		}
		

	}
	return removed;
}

template<typename T>
bool List<T>::findElement(const T & toFind) const {
	int currentPos = 0;
	bool found = false;
	Node<T> *Ptr = front;
	while (Ptr != nullptr) {
		if (Ptr->getPayload() == toFind) {
			found = true;
		}
		Ptr = Ptr->getNext();
		currentPos++;

	}
	return found;
}

template<typename T>
int List<T>::length() const {
	int length = 0;
	Node<T> *Ptr = front;
	while (Ptr != nullptr) {
		length++;
		Ptr = Ptr->getNext();
	}
	return length;
}

template<typename T>
T List<T>::getAt(int pos) const throw(...) {
	if (pos < 0) {
		throw "out of bounds";
	}
	int currentPos = 0;
	Node<T> *Ptr = front;
	while (currentPos <= pos) {
		if (currentPos == pos) {
			return Ptr->getPayload();
		}
		else {
			currentPos++;
			if (Ptr->getNext() != nullptr) {
				Ptr = Ptr->getNext();
			}
			else {
				throw "out of bounds";
			}
		}
	}
}

template<typename T>
void List<T>::getAll(T arr[], int cap) throw(...) {
	if (cap < this->length()) {
		throw "to small container";
	}
	int currentPos = 0;
	Node<T> *Ptr = front;
	while (currentPos < cap && Ptr != nullptr) {
		arr[currentPos] = Ptr->getPayload();
		Ptr = Ptr->getNext();
		currentPos++;
	}
}

#endif // !LIST_H