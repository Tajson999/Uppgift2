#ifndef HEAP_H
#define HEAP_H

template<typename T>
class Heap {
private:
	T *arr;
	int nrOf;
	int cap;

	void resize();
	void percolateDown(int hole);
public:
	Heap(int cap = 5);
	~Heap();
	
	bool isEmpty();
	void insert(T item);
	T getMin() throw(...);
	//void printHeap();
};

template<typename T>
inline void Heap<T>::resize() {
	cap *= 2;
	T *newArr = new T[cap];
	for (int i = 0; i < nrOf; i++) {
		newArr[i+1] = arr[i+1];
	}
	delete[] arr;
	arr = newArr;
}

template<typename T>
inline void Heap<T>::percolateDown(int hole) {
	int minChild;
	bool done = false;
	T temp = arr[hole];
	for (; done == false && hole * 2 <= nrOf;) {
		minChild = hole * 2;
		if ((hole*2) + 1 <= nrOf && arr[(hole * 2) + 1] < arr[hole*2]){
			minChild = (hole * 2) + 1;
		}
		if (arr[minChild] < temp) {
			arr[hole] = arr[minChild];
			hole = minChild;
		}
		else {
			done = true;	
		}
	}
	arr[hole] = temp;
}

template<typename T>
inline Heap<T>::Heap(int cap) {
	this->nrOf = 0;
	this->cap = cap;
	arr = new T[cap];
}

template<typename T>
inline Heap<T>::~Heap() {
	delete[] arr;
}

template<typename T>
inline bool Heap<T>::isEmpty() {
	return nrOf == 0;
}

template<typename T>
inline void Heap<T>::insert(T item) {
	if (nrOf + 1 >= cap) {
		resize();
	}
	int hole = ++nrOf;
	T copy = item;
	arr[0] = item;
	for (; item < arr[hole / 2]; hole /= 2) {
		arr[hole] = arr[hole / 2];
	}
	arr[hole] = arr[0];	
}

template<typename T>
inline T Heap<T>::getMin() throw(...) {
	if (isEmpty()) {
		throw "Empty Array";
	}
	T min = arr[1];
	arr[1] = arr[nrOf--];
	percolateDown(1);
	return min;
}

//template<typename T>
//inline void Heap<T>::printHeap() {
//	int n = 0;
//	for (int i = 0; i < nrOf; i++) {
//		cout << " " << arr[i+1];
//		if (i == 0){
//			cout << endl;
//		}
//		if (i == 2) {
//			cout << endl;
//		}
//		if (i == 6) {
//			cout << endl;
//		}
//		if (i == 10) {
//			cout << endl;
//		}
//	}
//}


#endif // !HEAP_H
