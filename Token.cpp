
#include "Token.h"


Token::Token(){
	readString = "";
	lineNumber = -1;
	tokenType = TokenType::UNDEFINED;
}

Token::Token(std::string readString, int lineNumber, TokenType tokenType){
	this->readString = readString;
	this->lineNumber = lineNumber;
	this->tokenType = tokenType;
}

Token::Token(char readChar, int lineNumber, TokenType tokenType){
	readString = "";
	readString += readChar;
	this->lineNumber = lineNumber;
	this->tokenType = tokenType;
}

std::string Token::getReadString(){
	return readString;
}

int Token::getLineNumber(){
	return lineNumber;
}

TokenType Token::getTokenType(){
	return tokenType;
}

void Token::setReadString(std::string readString){
	this->readString = readString;
}

void Token::setLineNumber(int lineNumber){
	this->lineNumber = lineNumber;
}

void Token::setTokenType(TokenType tokenType) {
	this->tokenType = tokenType;
}

std::string Token::toString(){
	std::string str = "(";
	
	switch (tokenType) {
		case TokenType::COMMA :			str += "COMMA"; break;
		case TokenType::PERIOD :		str += "PERIOD"; break;
		case TokenType::Q_MARK :		str += "Q_MARK"; break;
		case TokenType::LEFT_PAREN :	str += "LEFT_PAREN"; break;
		case TokenType::RIGHT_PAREN :	str += "RIGHT_PAREN"; break;
		case TokenType::COLON :			str += "COLON"; break;
		case TokenType::COLON_DASH :	str += "COLON_DASH"; break;
		case TokenType::MULTIPLY :		str += "MULTIPLY"; break;
		case TokenType::ADD :			str += "ADD"; break;
		case TokenType::SCHEMES :		str += "SCHEMES"; break;
		case TokenType::FACTS :			str += "FACTS"; break;
		case TokenType::RULES :			str += "RULES"; break;
		case TokenType::QUERIES :		str += "QUERIES"; break;
		case TokenType::ID :			str += "ID"; break;
		case TokenType::STRING :		str += "STRING"; break;
		case TokenType::COMMENT :		str += "COMMENT"; break;
		case TokenType::UNDEFINED :		str += "UNDEFINED"; break;
		case TokenType::EOF_TYPE :		str += "EOF"; break;
	}

	str += ",\"" + readString + "\",";
	str += std::to_string(lineNumber);
	str += ")";
	
	return str;
}
