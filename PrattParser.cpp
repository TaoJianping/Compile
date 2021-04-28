//
// Created by tao on 2021/4/21.
//

#include "PrattParser.h"

#include <utility>

using Parser::Precedence;

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
	auto left = rule.prefix();

	while (static_cast<int32_t>(precedence) < )
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

	auto binaryFunction = [this]()
	{ return this->readBinary(); };

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

Expression* Parser::PrattParser::readBinary()
{


	return new Binary();
}

Expression* Parser::PrattParser::readGroup()
{
	return new Grouping(this->expression());
}

Expression* Parser::PrattParser::expression()
{
	return this->parsePrecedence(Precedence::PREC_NONE);
}

Expression* Parser::PrattParser::readUnary()
{
	auto prefix = this->previous();
	auto num = this->current();
	this->next();

	num->lexeme = "-" + num->lexeme;
	return new Literal(num);
}
