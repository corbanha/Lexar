#include "Token.h"
#include "Lexar.h"
#include <vector>
#include <iostream>

using namespace std;

int main(int argc, char **argv){

    string fileName;
    
	if (argc <= 1) {
	    cout << "You didn't include a file in the command args, which file do you want to read?:" << endl;
	    cin >> fileName;
	}else{
	    fileName = argv[1];
	}
	cout << "Reading from file: " << fileName << endl;

	Lexar lex(fileName);

	vector<Token> toks = lex.tokenize();
	
	int j = toks.size();
	for (int i = 0; i < j; i++) {
		cout << toks.at(i).toString() << endl;
	}

	cout << "Total Tokens = " << toks.size() << endl;

    return 0;
}