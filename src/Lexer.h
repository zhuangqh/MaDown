#pragma once

#include "util.h"
#include <functional>
#include <string>

namespace md {

  enum Token {
    TOK_H1 = 0, TOK_H2, TOK_H3, TOK_H4, TOK_H5, TOK_H6,
    TOK_EMPHASIS, TOK_IMAGE, TOK_LINK, TOK_TEXT, TOK_LIST,
    TOK_PAREN_MID, TOK_PAREN_END, TOK_EOF, TOK_EOL
  };

  class Lexer {
  public:
    Lexer(const Lexer&) = delete;
    void operator = (const Lexer&) = delete;

    explicit Lexer(CharStream cs) : CharInStream(cs) {
      nextChar = CharInStream();
    }

    char curChar;
    char nextChar;
    std::string strBuffer;

    int get_token();

  private:
    CharStream CharInStream;
  };

} // namespace md
