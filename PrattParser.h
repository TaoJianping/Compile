//
// Created by tao on 2021/4/21.
//

#ifndef COMPILE_PRATTPARSER_H
#define COMPILE_PRATTPARSER_H

#include <vector>
#include <functional>

#include "Scanner.h"
#include "Expression.h"


using std::vector;
using Lexer::Token;
using Parser::Expression;

namespace Parser
{

	enum class Precedence : int32_t
	{
		PREC_NONE,
		PREC_TERM,        // + -
		PREC_FACTOR,      // * /
		PREC_UNARY,       // ! -
	};

	struct ParseRule
	{
		std::function<void()> prefix;
		std::function<void()> infix;
		Precedence precedence;
	};

	class PrattParser
	{
	private:
		vector<Token*> tokens;
		Expression* parsePrecedence(Precedence precedence);
		size_t index = 0;
		Token* next();
		Token* current();
		Token* previous();
	public:
		explicit PrattParser(vector<Token*> tokens);
		Expression* parse();
	};

}


#endif //COMPILE_PRATTPARSER_H
