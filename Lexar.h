#pragma once
#ifndef LEXAR_H
#define LEXAR_H

#include "Token.h"
#include <vector>
#include <string>
#include <fstream>

enum class LexarState {NORMAL, IN_COMMENT, IN_BLOCK_COMMENT, IN_QUOTE};


class Lexar {
public:

	Lexar(std::string fileName);
	~Lexar();

	std::vector<Token>tokenize();

private:
	LexarState lstate;
	int lineNumber;
	std::string fileName;
	
};

#endif