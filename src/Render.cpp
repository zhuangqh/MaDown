#include "Render.h"

namespace md {

  string Render::visit(Text *p) {
    if (p->style == Style::BOLD) {
      return "<b>" + p->text + "</b>";
    } else if (p->style == Style::QUOTE) {
      return "<code>" + p->text + "</code>";
    } else if (p->style == Style::ITALIC) {
      return "<em>" + p->text + "</em>";
    } else {
      return p->text;
    }
  }

  string Render::visit(Header *p) {
    string header = "h1";
    header[1] = static_cast<char>(p->headerLevel + '1');

    string text;
    for (auto &&textPtr : p->text) {
      text += textPtr->accept(this);
    }

    return "<" + header + ">" + text + "</" + header + ">";
  }

  string Render::visit(ListItem *p) {
    string text;
    for (auto &&textPtr : p->text) {
      text += textPtr->accept(this);
    }

    return "<li>" + text + "</li>";
  }

  string Render::visit(List *p) {
    string listItems;

    for (auto &&itemPtr : p->elements) {
      listItems += itemPtr->accept(this);
    }

    if (p->isOrdered) {
      return "<ol>" + listItems + "</ol>";
    } else {
      return "<ul>" + listItems + "</ul>";
    }
  }

  string Render::visit(Link *p) {
    return "<a href=\"" + p->link + "\">" + p->text + "</a>";
  }

  string Render::visit(Image *p) {
    return "<div><img src=\"" + p->link + "\"><p>" + p->text + "</p></div>";
  }

  string Render::visit(Code *p) {
    bool isFirst = true;
    string codeType;
    string text;

    for (auto &item : p->elements) {
      if (isFirst) {
        codeType = item;
        isFirst = false;
      } else {
        text += item + "\n";
      }
    }

    return "<pre class=\"" + codeType + "\">" + text + "</pre>";
  }

  string Render::visit(TopText *p) {
    string content;

    for (auto &&textPtr : p->elements) {
      content += textPtr->accept(this);
    }

    return "<p>" + content + "</p>";
  }

} // namespace md
