#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <ctype.h>

using namespace std;

void caesarCipher(string);

int main() {

	ifstream file("text.txt");		//reads the file containing the text to be encrypted

	string initialText((std::istreambuf_iterator<char>(file)),
		(std::istreambuf_iterator<char>()));



	caesarCipher(initialText);




	system("pause");
	return 0;
}







void caesarCipher(string in) {

	string alp = "abcdefghijklmnopqrstuvwxyz";
	string cipher = "";

	cout << "Enter Key to cipher " << endl;
	int key = 0;
	cin >> key;



	for (int i = 0; i < in.size(); i++) {
		char temp = tolower(in.at(i));
		if (alp.find(temp) != string::npos) {
			temp = alp.at((alp.find(temp) + key) % 26);
			cipher += temp;
		}
		else {
			cipher += in.at(i);
		}
	}





	cout << cipher << endl;

}