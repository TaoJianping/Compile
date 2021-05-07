//
// Created by tao on 2021/4/23.
//

#ifndef COMPILE_EXPRESSION_H
#define COMPILE_EXPRESSION_H

#include "Scanner.h"



using Lexer::Token;

namespace Parser
{
	class Expression
	{
	public:
		virtual  ~Expression() = default;
	};

	class Binary : public Expression
	{
	public:
		Expression* left;
		Token* _operator;
		Expression* right;
	};

	class Grouping : public Expression
	{
	public:
		explicit Grouping(Expression* expr);
		Expression* expression;
	};

	class Unary : public Expression
	{
	public:
		Token* _operator;
		Expression* right;
	};

	class Literal : public Expression
	{
	public:
		explicit Literal(Token* token);
		Token* value;
	};
}


#endif //COMPILE_EXPRESSION_H
