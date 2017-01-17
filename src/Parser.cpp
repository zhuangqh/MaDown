#include "Parser.hpp"

namespace md {

  void Parser::next_token() {
    curToken = nextToken;
    strBuffer = lexer.strBuffer;
    nextToken = lexer.get_token();
  }

  void Parser::parse() {
    while (true) {
      next_token();

      unique_ptr<STNode> block;
      switch (curToken) {
        case TOK_EOF:
          return;
        case TOK_H1: case TOK_H2: case TOK_H3:
        case TOK_H4: case TOK_H5: case TOK_H6:
          block = parse_header();
          break;
        case TOK_LIST:
          block = parse_list();
          break;
        case TOK_LINK:
          block = parse_link();
          break;
        case TOK_IMAGE:
          block = parse_image();
          break;
        case TOK_CODE:
          block = parse_code_block();
          break;
        default:
          block = make_unique<TopText>(parse_line());
      }

      article.push_back(std::move(block));
    }
  }

  vector<unique_ptr<Text>> Parser::parse_line() {
    vector<unique_ptr<Text>> lineText;
    unique_ptr<Text> textPtr = nullptr;
    string textStr;
    bool isEnd = false;

    while (nextToken != TOK_EOF) {
      switch (curToken) {
        case TOK_EOL:
          isEnd = true;
          break;
        case TOK_EMPHASIS:
          textPtr = parse_formatted_text(TOK_EMPHASIS, Style::BOLD);
          break;
        case TOK_QUOTE:
          textPtr = parse_formatted_text(TOK_QUOTE, Style::QUOTE);
          break;
        case TOK_ITALIC:
          textPtr = parse_formatted_text(TOK_ITALIC, Style::ITALIC);
          break;
        default:
          textPtr = make_unique<Text>(Style::NORMAL, strBuffer);
      }

      if (textPtr != nullptr) {
        lineText.push_back(std::move(textPtr));
        textPtr = nullptr;
      }

      if (isEnd) break;

      next_token();
    }

    return lineText;
  }

  unique_ptr<Header> Parser::parse_header() {
    auto header = make_unique<Header>(curToken);
    next_token();
    header->text = parse_line();

    return header;
  }

  unique_ptr<List> Parser::parse_list() {
    vector<unique_ptr<ListItem>> elements;

    next_token();
    elements.push_back(make_unique<ListItem>(parse_line()));

    unique_ptr<ListItem> listItem = nullptr;
    while (nextToken == TOK_LIST) {
      next_token(); // eat '-'
      next_token(); // to text
      elements.push_back(make_unique<ListItem>(parse_line()));
    }

    return make_unique<List>(false, std::move(elements));
  }

  unique_ptr<STNode> Parser::parse_link() {
    string text, link;

    string strBuf = strBuffer;

    auto step = [&]() {
      next_token();
      strBuf += strBuffer;
    };

    step();
    if (curToken != TOK_TEXT) {
      return make_unique<Text>(Style::NORMAL, strBuf);
    } else {
      text = strBuffer;
    }

    step();
    if (curToken != TOK_PAREN_MID) {
      return make_unique<Text>(Style::NORMAL, strBuf);
    }

    step();
    if (curToken != TOK_TEXT) {
      return make_unique<Text>(Style::NORMAL, strBuf);
    } else {
      link = strBuffer;
    }

    step();
    if (curToken != TOK_PAREN_END) {
      return make_unique<Text>(Style::NORMAL, strBuf);
    } else {
      return make_unique<Link>(link, text);
    }
  }

  unique_ptr<Text> Parser::parse_formatted_text(int token, Style textStyle) {
    string strBuf;

    next_token();
    while (curToken != token && nextToken != TOK_EOF && nextToken != TOK_EOL) {
      strBuf += strBuffer;
      next_token();
    }

    if (curToken == token) {
      return make_unique<Text>(textStyle, strBuf);
    } else {
      return make_unique<Text>(Style::NORMAL, strBuf);
    }
  }

  unique_ptr<STNode> Parser::parse_image() {
    string text, link;

    string strBuf = strBuffer;

    auto step = [&]() {
      next_token();
      strBuf += strBuffer;
    };

    step();
    if (curToken != TOK_TEXT) {
      return make_unique<Text>(Style::NORMAL, strBuf);
    } else {
      text = strBuffer;
    }

    step();
    if (curToken != TOK_PAREN_MID) {
      return make_unique<Text>(Style::NORMAL, strBuf);
    }

    step();
    if (curToken != TOK_TEXT) {
      return make_unique<Text>(Style::NORMAL, strBuf);
    } else {
      link = strBuffer;
    }

    step();
    if (curToken != TOK_PAREN_END) {
      return make_unique<Text>(Style::NORMAL, strBuf);
    } else {
      return make_unique<Image>(link, text);
    }
  }

  unique_ptr<Code> Parser::parse_code_block() {
    next_token(); // eat '```'

    vector<string> elements;
    string strBuf;

    while (nextToken != TOK_EOF) {
      if (curToken == TOK_CODE) {
        break;
      } else if (curToken == TOK_EOL) {
        elements.push_back(strBuf);
        strBuf.clear();
      } else {
        strBuf += strBuffer;
      }
      next_token();
    }

    return make_unique<Code>(elements);
  }

} // namespace md
