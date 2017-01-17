#pragma once

#include "./Lexer.h"
#include "./AST.h"
#include <functional>

namespace md {

  class Parser {
    unique_ptr<Header> parse_header();

    unique_ptr<List> parse_list();

    unique_ptr<STNode> parse_link();

    unique_ptr<Text> parse_formatted_text(int token, Style textStyle);

    unique_ptr<STNode> parse_image();

    unique_ptr<Code> parse_code_block();

    vector<unique_ptr<Text>> parse_line();

    void next_token();

    Lexer lexer;

    int curToken;

    int nextToken;

    string strBuffer;
  public:
    Parser(const Parser&) = delete;
    void operator = (const Parser&) = delete;
    explicit Parser(CharStream cs) : lexer(cs) {
      nextToken = lexer.get_token();
    }

    void parse();

    std::vector<unique_ptr<STNode>> article;
  };

} // namespace md
