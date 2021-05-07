//
// Created by tao on 2021/4/21.
//

#include "PrattParser.h"

#include <utility>
#include <iostream>
#include "glog/logging.h"

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
	auto p = this->previous()->lexeme;
	auto rule = this->getRule(this->previous());

	if (rule.prefix == nullptr)
	{
		LOG(ERROR) << "Prefix Lost";
		return nullptr;
	}
	auto left = rule.prefix();

	while (precedence <= (this->getRule(this->current()).precedence))
	{
		this->next();
		auto prevToken = this->previous()->lexeme;
		auto r = this->getRule(this->previous());
		left = r.infix(left);
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
		return ParseRule{ nullptr, binaryFunction, Precedence::PREC_TERM };
	}
	else if (token->type == Lexer::TokenType::TOKEN_MINUS)
	{
		return ParseRule{ unaryFunction, nullptr, Precedence::PREC_TERM };
	}
	else if (token->type == Lexer::TokenType::TOKEN_LEFT_PAREN)
	{
		return ParseRule{ groupFunction, nullptr, Precedence::PREC_NONE };
	}
	else if (token->type == Lexer::TokenType::TOKEN_EOF)
	{
		return ParseRule{ nullptr, nullptr, Precedence::PREC_NONE };
	}
	else if (token->type == Lexer::TokenType::TOKEN_RIGHT_PAREN)
	{
		return ParseRule{ nullptr, nullptr, Precedence::PREC_NONE };
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

	auto rule = this->getRule(be->_operator);
	be->right = this->parsePrecedence(rule.precedence);

	return be;
}

Expression* Parser::PrattParser::readGroup()
{
	auto g = new Grouping(this->expression());
	this->consume(Lexer::TokenType::TOKEN_RIGHT_PAREN, "Expect ')' after value.");
	return g;
}

Expression* Parser::PrattParser::expression()
{
	return this->parsePrecedence(Precedence::PREC_ASSIGNMENT);
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

bool Parser::PrattParser::check(TokenType type)
{
	if (isAtEnd())
		return false;
	return peek()->type == type;
}

bool Parser::PrattParser::isAtEnd()
{
	return this->peek()->type == TokenType::TOKEN_EOF;
}

Token* Parser::PrattParser::peek()
{
	return this->tokens.at(this->index);
}

Token* Parser::PrattParser::consume(TokenType type, const std::string& msg)
{
	if (this->check(type))
	{
		return this->advance();
	}
//	throw error(peek(), msg);
	LOG(ERROR) << msg;
	throw ParseException();
}

Token* Parser::PrattParser::advance()
{
	if (!isAtEnd()) this->index++;
	return previous();
}
