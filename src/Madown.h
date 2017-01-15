#pragma once

#include <string>
#include <iostream>
#include <functional>
#include "TextStream.h"
#include "Parser.hpp"
#include "Render.h"

using namespace std;

namespace md {

  string HTMLPrefix =
      string("<html>\n") +
      "  <head>\n" +
      "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n" +
      "    <meta charset=\"utf-8\">\n" +
      "  </head>\n" +
      "  <body>\n";

  string HTMLPostfix =
      string("  </body>\n") +
      "</html>";

  template<typename Stream>
  string render(Stream &s) {
    Parser parser([&s]() -> int {return s.get_char();});
    Render *render = new Render();

    parser.parse();

    string HTMLBody;
    for (auto &&STNode : parser.article) {
      HTMLBody += STNode->accept(render) + "\n";
    }

    return HTMLPrefix + HTMLBody + HTMLPostfix;
  }

} // namespace md
