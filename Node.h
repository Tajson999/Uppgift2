#ifndef NODE_H
#define NODE_H

template<typename T>
class Node {
private:
	Node<T> *next;
	T payload;
public:
	Node(T payload, Node<T> *next);
	Node(T payload);
	Node();
	~Node();

	void setNext(Node *ptr);
	Node<T>* getNext();
	T getPayload();

};

template<typename T>
Node<T>::Node(T payload, Node<T>* next) {
	this->payload = payload;
	this->next = next;
}

template<typename T>
Node<T>::Node(T payload) {
	this->payload = payload;
	this->next = nullptr;
}

template<typename T>
Node<T>::Node() {
	this->next = nullptr;
}

template<typename T>
Node<T>::~Node() {
	
}

template<typename T>
void Node<T>::setNext(Node<T> * ptr) {
	this->next = ptr;
}

template<typename T>
Node<T>* Node<T>::getNext() {
	return this->next;
}

template<typename T>
T Node<T>::getPayload() {
	return this->payload;
}

#endif // !NODE_H