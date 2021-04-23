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
		Token* value;
	};
}


#endif //COMPILE_EXPRESSION_H
