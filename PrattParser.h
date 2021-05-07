//
// Created by tao on 2021/4/21.
//

#ifndef COMPILE_PRATTPARSER_H
#define COMPILE_PRATTPARSER_H

#include <vector>
#include <stack>
#include <functional>

#include "Scanner.h"
#include "Expression.h"


using std::vector;
using Lexer::Token;
using Lexer::TokenType;
using Parser::Expression;
using std::stack;

namespace Parser
{
	class ParseException : std::exception {
	};

	enum class Precedence : int32_t
	{
		PREC_NONE,
		PREC_ASSIGNMENT,  // =
		PREC_TERM,        // + -
		PREC_FACTOR,      // * /
		PREC_UNARY,       // ! -
	};

	struct ParseRule
	{
		std::function<Expression*()> prefix;
		std::function<Expression*(Expression* left)> infix;
		Precedence precedence;
	};

	class PrattParser
	{
	private:
		stack<Expression*> _stack;
		vector<Token*> tokens;
		Expression* parsePrecedence(Precedence precedence);
		size_t index = 0;
		Token* next();
		Token* current();
		Token* previous();

		bool check(TokenType type);
		bool isAtEnd();
		Token* peek();
		Token* advance();
		Token* consume(TokenType, const std::string &);

		ParseRule getRule(Token* token);
		Expression* expression();
		Expression* readNumber();
		Expression* readBinary(Expression* left);
		Expression* readGroup();
		Expression* readUnary();



	public:
		explicit PrattParser(vector<Token*> tokens);
		Expression* parse();
	};

}


#endif //COMPILE_PRATTPARSER_H
