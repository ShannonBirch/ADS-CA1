#include "Trees.h"
#include "Node.h"
#include <map>
#include <queue>
#include <functional>
#include <queue>
#include <vector>
#include <iostream>
#include <climits>
#include <algorithm>
#include <string>
#include <fstream>
#include <cstdint>
#include <bitset>

using namespace std;


Trees::Trees(map<char, int> in) {
	freq = in;


	for (i = freq.begin(); i != freq.end(); i++) {
		q.push(new Node<char>(i->first, i->second)); //Makes a set of nodes from the map

	}

	Node<char>* left, *right, *branchNode;

	while (q.size() > 1) {
		priority_queue<Node<char>*, vector<Node<char>*>, node_cmp>cpy;//Sorts the nodes with the smallest on the top


		right = q.top(); //Right Node should be the smallest node 
		q.pop(); // Takes the right node out of the queue
		left = q.top(); //The next smallest node is the left node
		q.pop();

		branchNode = new Node<char>(NULL, right->getFreq() + left->getFreq());
		branchNode->setLeft(left);
		branchNode->setRight(right);
		q.push(branchNode); //Puts the branch node back into the queue

	}

	rootPtr = q.top(); //The Root node of the tree is the only node left


}



void Trees::preOrder(Node<char>* in, string code) {

	//checks the tree traversal until it reaches the leaf nodes
	//if it is the leaf node, then the character and the code associated with it
	//get preOrder passed into the encoded map

	if (in->getChar() == NULL) {	//Branch nodes have their characters set to NULL
		preOrder(in->getLeft(), code + "0");		//for each left traveral adds 0 to the code
		preOrder(in->getRight(), code + "1");		//for each right traveral adds 1 to the code
	}
	
	else {	// otherwise its a leaf node
		encoded[in->getChar()] = code;	
		cout <<" HER " <<  in->getChar() << code << endl;
	}
}


string Trees::encode(string in) {

	string s = "";
	for (char& c : in) {

		for (ci = encoded.begin(); ci != encoded.end(); ci++) {

			if (c == ci->first) {
				ci = encoded.find(c);
				s = s + ci->second;
			}
		}
	}

	ofstream myfile;
	myfile.open("encoded.txt");
	myfile << s;
	myfile.close();

	return s;
}


void Trees::decode(string in) {


	Node<char>* search = rootPtr;
	string output = "";



	for (unsigned i = 0; i < in.length(); i++) {

		if (in.at(i) == '0') {
			search = search->getLeft(); //0 is left
		}
		else if (in.at(i) == '1') {
			search = search->getRight(); //1 is right
		}

		if (!search->getLeft() || !search->getRight()) { //If Leaf node
			output = output + search->getChar();
			search = rootPtr;
		}


	}

	ofstream myfile;
	myfile.open("decoded.txt");
	myfile << output;
	myfile.close();

}




void Trees::compress(string in) {
	string output;

	bitset<8> charbits;
	int j = 0;
	int remainder = 0;
	remainder = in.length() % 8;

	int counter = 0;

	for (int i = 0; i < in.length(); i++) {
		if (in.at(i) == '0') {
			charbits[j] = 0;
		}
		else if (in.at(i) == '1') {
			charbits[j] = 1;
		}
		if (j < 7) {
			j++;
		}
		else {
			j = 0;
			unsigned long lon = charbits.to_ulong();
			unsigned char c = static_cast<unsigned char>(lon);
			output += c;
			counter++;
		}

	}
	
	for (int i = in.length() - (remainder); i < in.length(); i++) {
		output += in.at(i);
	}
	

	//cout << "COUNTER->"<< counter  << endl;


	//cout << output << endl;
	ofstream myfile;
	myfile.open("encoded.txt");

	myfile << counter  << " " << output;

	myfile.close();
	//cout << "->>>>>>>>"<< remainder << endl;
}


string Trees::uncompress() {

	ifstream file("encoded.txt", ios::binary);
	string encodedString((std::istreambuf_iterator<char>(file)),
		(std::istreambuf_iterator<char>()));

	cout << endl << endl;
	int start = 0;
	string convert = "";
	for (int i = 0; i < encodedString.length(); i++) {
		if (encodedString.at(i) == ' ') {

			start = i + 1;
			i = encodedString.length();
		}
		else {
			convert += encodedString.at(i);
		}
	}

	int numChars = stoi(convert);


	//cout << encodedString << endl;

	cout << endl << endl;
	string output;
	//cout << encodedString << endl;
	for (int i = start; i <= numChars+1; i++) {
		
		bitset<8>charbits = encodedString.at(i);
		//cout << encodedString.at(i);
		for (int j = 0; j < 8; j++) {
			if (charbits[j] == 0) {
				output += "0";
			}
			else if (charbits[j] == 1) {
				output += "1";
			}
		}

	}
	
	for (int i = (encodedString.length() - (numChars + start)); i < encodedString.length(); i++) {
		output += encodedString.at(i);
	}
	
	//cout <<"START->"<< start <<  "NUMCHARS->" << numChars;

	//cout << endl << endl << endl;
	//cout << output << endl;



	return output;
}