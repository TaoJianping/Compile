//
// Created by tao on 2021/4/23.
//

#include "Expression.h"

Parser::Literal::Literal(Token* token): value(token)
{

}

Parser::Grouping::Grouping(Parser::Expression* expr): expression(expr)
{

}
