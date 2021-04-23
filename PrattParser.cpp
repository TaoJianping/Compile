//
// Created by tao on 2021/4/21.
//

#include "PrattParser.h"

#include <utility>

using Parser::Precedence;

Parser::PrattParser::PrattParser(vector<Token*> tokens): tokens(std::move(tokens))
{

}

Expression* Parser::PrattParser::parse()
{
	return this->parsePrecedence(Precedence::PREC_NONE)
}

Expression* Parser::PrattParser::parsePrecedence(Precedence precedence)
{

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
