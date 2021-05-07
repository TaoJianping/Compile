//
// Created by tao on 2021/5/6.
//

#include "gtest/gtest.h"
#include "glog/logging.h"
#include "../Scanner.h"
#include "../PrattParser.h"
#include "../Expression.h"

using Lexer::Scanner;
using Parser::PrattParser;

TEST(testPartt, test1) {
	auto s = Scanner("(1 + 7)");
	auto v = s.scanTokens();
	for (auto t : v)
	{
		LOG(INFO) << t->lexeme;
	}

	auto p = PrattParser(v);
	auto res = p.parse();
	auto d = dynamic_cast<Parser::Binary*>(res);
	LOG(INFO) << "test";
}
