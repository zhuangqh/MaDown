#pragma once

#include <string>
#include <iostream>
#include <functional>
#include <regex>
#include "TextStream.h"
#include "Parser.hpp"
#include "Render.h"

using namespace std;

namespace md {

  class Madown {
  public:
    string theme;

    Madown(const string &t) : theme(t) {}

    Madown() : theme("base") {}

    template<typename Stream>
    string render(Stream &s) {
      string CSS;
      if (!IO::read_str_from_file("../static/" + theme +  ".css", CSS)) {
        std::cout << "fail to load css\n";
        return "";
      }

      string HTML;
      if (!IO::read_str_from_file("../static/base.html", HTML)) {
        std::cout << "fail to load HTML\n";
        return "";
      }

      Parser parser([&s]() -> int {return s.get_char();});
      Render *render = new Render();

      parser.parse();

      string HTMLBody;
      for (auto &&STNode : parser.article) {
        HTMLBody += STNode->accept(render) + "\n";
      }

      std::regex CSSLabel("\\{%style%\\}");
      std::regex BodyLabel("\\{%body%\\}");

      HTML = std::regex_replace(HTML, CSSLabel, CSS); // insert CSS stylesheet
      HTML = std::regex_replace(HTML, BodyLabel, HTMLBody); // insert HTML of markdown

      return HTML;
    }
  };

} // namespace md
