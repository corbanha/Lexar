#include "Lexar.h"
#include "Token.h"
#include <vector>
#include <iostream>

using namespace std;

Lexar::Lexar(string fileName){
	this->fileName = fileName;
}

Lexar::~Lexar(){
}

vector<Token> Lexar::tokenize(){
	lstate = LexarState::NORMAL;
	lineNumber = 1;
	int topLineNumber = -1; //used for quotes and multiline since they want the line number on the top
	vector<Token> tokens;

	ifstream in;

	try {
		in.open(fileName);

		char c;
		string comstr;

		while (in.get(c)) {
			
			//////INSIDE A QUOTE///////
			if (lstate == LexarState::IN_QUOTE) {
				
				if (c == '\'') {
					if (in.peek() == '\'') {
						//it's an apostrophe here
						comstr += c;
						in.get(c);
					}
					else {
						//this is the end of the string
						comstr += c;

						Token token(comstr, topLineNumber, TokenType::STRING);
						tokens.push_back(token);

						comstr = "";

						lstate = LexarState::NORMAL;
					}
				}
				else {
					
					if (in.peek() == EOF) {
						//end of file but we haven't closed
						Token token(comstr, topLineNumber, TokenType::UNDEFINED);
						tokens.push_back(token);
					}

					comstr += c;
					if (c == '\n') {
						lineNumber++;
					}
				}
			}

			/////INSIDE A COMMENT//////
			else if (lstate == LexarState::IN_COMMENT) {
				if (c == '\n') {
					//end the comment
					Token token(comstr, topLineNumber, TokenType::COMMENT);
					tokens.push_back(token);
					lineNumber++;
					lstate = LexarState::NORMAL;
				}
				else {
					comstr += c;
				}
			}


			//////INSIDE A BLOCK COMMENT ///////
			else if (lstate == LexarState::IN_BLOCK_COMMENT) {
				if (c == '|' && in.peek() == '#') {
					//end of the block comment
					lstate = LexarState::NORMAL;
					comstr += "|#";
					in.get(c);//read in the next one too

					Token token(comstr, topLineNumber, TokenType::COMMENT);
					tokens.push_back(token);
				}
				else if (in.peek() == EOF) {
					//this multiline comment wasn't ended correctly
					comstr += c;
					Token token(comstr, topLineNumber, TokenType::UNDEFINED);
					tokens.push_back(token);
				}
				else {
					comstr += c;
					if (c == '\n') {
						lineNumber += 1;
					}
				}

				//////NOT INSIDE ANYTHING AT THE MOMENT//////
			}
			else {
				//checks if c is an alphabetic letter
				if (isalpha(c)) {

					//check for SCHEMES, FACTS, RULES, QUERIES
					string tempString = "";
					
					while (isalnum(in.peek())) {
						tempString += c;
						in.get(c);
					}

					if(in.peek() != EOF) tempString += c;

					Token token(tempString, lineNumber, TokenType::ID);

					if (tempString == "Schemes") {
						token.setTokenType(TokenType::SCHEMES);
					}
					else if (tempString == "Facts") {
						token.setTokenType(TokenType::FACTS);
					}
					else if (tempString == "Rules") {
						token.setTokenType(TokenType::RULES);
					}
					else if (tempString == "Queries") {
						token.setTokenType(TokenType::QUERIES);
					}
					tokens.push_back(token);
					
				}
				////WHITESPACE
				else if (isspace(c)) {
					//check if it is a new line
					if (c == '\n') {
						lineNumber++;
					}
				}
				////NUMBERS
				else if (isdigit(c)) {
					//add single digits as an undefined token
					Token token(c, lineNumber, TokenType::UNDEFINED);
					tokens.push_back(token);
				}
				else if (c =='\'') {
					//starting a quote
					topLineNumber = lineNumber;
					lstate = LexarState::IN_QUOTE;
					comstr = "'";
				}
				else if (c == '#') {
					topLineNumber = lineNumber;
					if (in.peek() == '|') {
						in.get(c);
						lstate = LexarState::IN_BLOCK_COMMENT;
						comstr = "#|";
					}
					else {
						lstate = LexarState::IN_COMMENT;
						comstr = "#";
					}
				}else {
					//check for our special characters:
					
					Token token(c, lineNumber, TokenType::UNDEFINED);

					switch (c) {
					case ',': token.setTokenType(TokenType::COMMA); break;
					case '.': token.setTokenType(TokenType::PERIOD); break;
					case '?': token.setTokenType(TokenType::Q_MARK); break;
					case '(': token.setTokenType(TokenType::LEFT_PAREN); break;
					case ')': token.setTokenType(TokenType::RIGHT_PAREN); break;
					case ':':
						if (in.peek() == '-') {
							token.setTokenType(TokenType::COLON_DASH);
							token.setReadString(":-");
							in.get(c);
						}
						else {
							token.setTokenType(TokenType::COLON);
						}
						break;
					case '*': token.setTokenType(TokenType::MULTIPLY); break;
					case '+': token.setTokenType(TokenType::ADD); break;
					}

					tokens.push_back(token);
						
				}
			}
		}

		Token token("", lineNumber, TokenType::EOF_TYPE);
		tokens.push_back(token);

		in.close();
	}
	catch (int e) {
		cout << "An error occured trying to tokenize " << fileName << " " << e << endl;
	}


	return tokens;
}
