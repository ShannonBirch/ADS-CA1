#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <cctype>
#include <iomanip>
#include <queue>
#include <vector>
#include <algorithm>
#include "Trees.h"
#include "Node.h"
using namespace std;


int main(){

	map <char, int> freq;			//map for frequency of characters
	map <char, int>::iterator i;	//iterator for the frequency map

	
	ifstream file("text.txt");		//reads the file containing the text to be encrypted


	//reads all characters from the into the string
	string initialText((std::istreambuf_iterator<char>(file)),	
		(std::istreambuf_iterator<char>()));					



	//assigns a character as key and its frequency as value
	for (unsigned int i = 0; i < initialText.size(); ++i) {
		++freq[initialText[i]];			
										
	}
	

	//passes in the above map into the trees contructor
	Trees t1 = Trees(freq);


	//traverses the tree in post order, and assigns 8 bit code to each end
	t1.preOrder(t1.getRoot(),"");



	t1.compress(t1.encode(initialText));

	t1.decode(t1.uncompress());


	cout << initialText;



	system("pause");
	return 0;
}