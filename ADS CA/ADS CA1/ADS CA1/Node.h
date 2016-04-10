#pragma once
#include <iostream>
using namespace std;


template < class T> class Node
{
private:
	int freq;
	T character;
	Node<T>* left = NULL;
	Node<T>* right = NULL;
	
public:
	Node(T, int);
	Node();
	T getChar();
	int getFreq();

	void setLeft(Node<T>*);
	void setRight(Node<T>*);

	Node<T>* getLeft();
	Node<T>* getRight();
};

template <class T>
Node<T>::Node(T c, int f) {
	character = c;
	freq = f;
}

template <class T>
Node<T>::Node() {}

template <class T>
T Node<T>::getChar(){
	return character;
}

template <class T>
int Node<T>::getFreq()  {
	return freq;
}

template <class T>
void Node<T>::setLeft(Node<T>* l) {
	left = l;
}

template <class T>
void Node<T>::setRight(Node<T>* r) {
	right = r;
}

template <class T>
Node<T>* Node<T>::getLeft() {
	return left;
}

template <class T>
Node<T>* Node<T>::getRight() {
	return right;
}

struct node_cmp { //Custom comparator for a priority queue using the node

	bool operator()( Node<char> *lside,  Node<char>* rside) const
	{
	
		if (lside->getFreq() > rside->getFreq())	return true;//If leftside is bigger it gets less priority
		
		if (rside->getFreq() > lside->getFreq())	return false;//If rightside is bigger it gets less priority
		
		 //Branch nodes (Character == Null) get less priority than a leaf node with the same frequency
		if (rside->getChar() == NULL && lside->getChar() != NULL)	return true;
		
		return false;

	}
};