#include "Lexer.h"
#include <map>
#include <iostream>

namespace md {

  const std::string keyChars = "-*#![]()` ";

  std::map<std::string, Token> tokenTable {
      {"# ", TOK_H1},
      {"## ", TOK_H2},
      {"### ", TOK_H3},
      {"#### ", TOK_H4},
      {"##### ", TOK_H5},
      {"###### ", TOK_H6},
      {"**", TOK_EMPHASIS},
      {"![", TOK_IMAGE},
      {"[", TOK_LINK},
      {"](", TOK_PAREN_MID},
      {")", TOK_PAREN_END},
      {"- ", TOK_LIST},
      {"`", TOK_QUOTE},
      {"*", TOK_ITALIC},
      {"```", TOK_CODE}
  };

  bool is_key_char(char c) {
    return keyChars.find(c) != std::string::npos;
  }

  int Lexer::get_token() {
    auto next = [&](){
      curChar = nextChar;
      nextChar = CharInStream();
    };

    next();
    strBuffer.clear();
    if (curChar == EOF) return TOK_EOF;
    if (curChar == '\n') return TOK_EOL;
    //if (isblank(curChar)) return get_token();

    while (is_key_char(curChar) && is_key_char(nextChar)) {
      strBuffer += curChar;
      next();
    }

    strBuffer += curChar;

    if (is_key_char(curChar) && tokenTable.find(strBuffer) != tokenTable.end()) {
      return tokenTable[strBuffer];
    }

    if (tokenTable.find(strBuffer) != tokenTable.end()) {
      return tokenTable[strBuffer];
    }

    while (nextChar != '\n' && !is_key_char(nextChar)) {
      next();
      strBuffer += curChar;
    }

    return TOK_TEXT;
  }

} // namespace md
