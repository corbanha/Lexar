#pragma once
#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum class TokenType {COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON,
    COLON_DASH, MULTIPLY, ADD, SCHEMES, FACTS, RULES, QUERIES, ID, STRING,
    COMMENT, UNDEFINED, EOF_TYPE};

class Token {
public:
	Token();
	Token(std::string readstring, int lineNumber, TokenType tokenType);
	Token(char readChar, int lineNumber, TokenType tokenType);

	std::string getReadString();
	int getLineNumber();
	TokenType getTokenType();

	void setReadString(std::string readString);
	void setLineNumber(int lineNumber);
	void setTokenType(TokenType tokenType);

	std::string toString();

private:
	std::string readString;
	int lineNumber;
	TokenType tokenType;

};

#endif