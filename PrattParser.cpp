//
// Created by tao on 2021/4/21.
//

#include "PrattParser.h"

#include <utility>
#include <iostream>

using Parser::Precedence;
using std::cout;

Parser::PrattParser::PrattParser(vector<Token*> tokens) : tokens(std::move(tokens))
{

}

Expression* Parser::PrattParser::parse()
{
	return this->expression();
}

Expression* Parser::PrattParser::parsePrecedence(Precedence precedence)
{
	this->next();
	auto rule = this->getRule(this->previous());

	if (rule.prefix == nullptr)
	{
		std::cout << "Prefix Lost";
		return nullptr;
	}
	auto left = rule.prefix();

	while (precedence <= (this->getRule(this->current()).precedence))
	{
		this->next();
		auto rule = this->getRule(this->previous());
		left = rule.infix(left);
	}

	return left;
}

Token* Parser::PrattParser::next()
{
	this->index += 1;
	return this->tokens.at(this->index);
}

Token* Parser::PrattParser::current()
{
	return this->tokens.at(this->index);
}

Token* Parser::PrattParser::previous()
{
	return this->tokens.at(this->index - 1);
}

Parser::ParseRule Parser::PrattParser::getRule(Token* token)
{
	auto readNumberFunction = [this]()
	{ return this->readNumber(); };

	auto binaryFunction = [this](Expression* left)
	{ return this->readBinary(left); };

	auto unaryFunction = [this]()
	{ return this->readUnary(); };

	auto groupFunction = [this]()
	{ return this->readGroup(); };

	if (token->type == Lexer::TokenType::TOKEN_NUMBER)
	{
		return ParseRule{ readNumberFunction, nullptr, Precedence::PREC_NONE };
	}
	else if (token->type == Lexer::TokenType::TOKEN_PLUS)
	{
		return ParseRule{ nullptr, binaryFunction, Precedence::PREC_NONE };
	}
	else if (token->type == Lexer::TokenType::TOKEN_MINUS)
	{
		return ParseRule{ unaryFunction, nullptr, Precedence::PREC_NONE };
	}
	else if (token->type == Lexer::TokenType::TOKEN_LEFT_PAREN)
	{
		return ParseRule{ groupFunction, nullptr, Precedence::PREC_NONE };
	}

	throw Expression();
}

Expression* Parser::PrattParser::readNumber()
{
	return new Literal(this->previous());
}

Expression* Parser::PrattParser::readBinary(Expression* left)
{
	auto be = new Binary();

	be->left = left;
	be->_operator = this->previous();
	be->right = this->expression();

	return be;
}

Expression* Parser::PrattParser::readGroup()
{
	auto g = new Grouping(this->expression());
	this->next();
	return g;
}

Expression* Parser::PrattParser::expression()
{
	return this->parsePrecedence(Precedence::PREC_NONE);
}

Expression* Parser::PrattParser::readUnary()
{
	auto prefix = this->previous();
	auto exp = this->parsePrecedence(Precedence::PREC_UNARY);

	auto u = new Unary;
	u->right = exp;
	u->_operator = prefix;
	return u;
}
