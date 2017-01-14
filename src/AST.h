#pragma once

#include <string>
#include <vector>
#include <memory>

using std::string;
using std::vector;
using std::unique_ptr;

namespace md {

  enum Style {
    NORMAL, BOLD, ITALIC
  };

  struct STNode {
    virtual ~STNode() {}
    virtual void toHTML() {}
  };

  struct Text : public STNode {
    Style style;
    string text;

    Text(Style s, const string &str) : style(s), text(str) {}
  };

  struct Header : public STNode {
    int headerLevel;
    vector<unique_ptr<Text>> text;
  
    Header(int hh) : headerLevel(hh) {}
  };

  struct ListItem : public STNode {
    vector<unique_ptr<Text>> text;
  
    ListItem() {}
  };

  struct List : public STNode {
    bool isOrdered;
    vector<unique_ptr<ListItem>> elements;
  
    List(bool o, vector<unique_ptr<ListItem>> ele)
        : isOrdered(o), elements(std::move(ele)) {}
  };

  struct Link : public STNode {
    string link;
    vector<unique_ptr<Text>> text;
  
    Link(const string &l, const string &t) : link(l) {}
  };

  struct Image : public STNode {
    string link;
    vector<unique_ptr<Text>> text;
  
    Image(const string &l, const string &t) : link(l) {}
  };

} // namespace md
