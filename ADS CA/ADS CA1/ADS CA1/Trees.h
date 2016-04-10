#pragma once
#include <iostream>
#include "Node.h"
#include <map>
#include <queue>

using namespace std;

class Trees
{
private:
	Node<char>* rootPtr = NULL;

	map<char, int> freq;
	map <char, int>::iterator i;

	priority_queue<Node<char>*, vector<Node<char>*>, node_cmp>q;

	map<char, string> encoded;
	map<char, string>::iterator ci;

	map<char, string> codeMap;
	map<char, string>::iterator codeI;



public:
	Trees(map<char, int>);

	Node<char>* getRoot() { return rootPtr; }
	void preOrder(Node<char>* in, string);

	string encode(string);
	void decode(string);


	void compress(string);
	string uncompress();
};