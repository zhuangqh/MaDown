#pragma once

#include <string>
#include <vector>
#include <memory>

using std::string;
using std::vector;
using std::unique_ptr;

namespace md {
#define STNODE_ACCEPT_VISITOR_DECL() \
  virtual string accept(Visitor *)

  struct Visitor;

  enum Style {
    NORMAL, BOLD, ITALIC, QUOTE
  };

  struct STNode {
    virtual ~STNode() {}
    virtual void toHTML() {}
    virtual string accept(Visitor *) = 0;
  };

  struct Text : public STNode {
    Style style;
    string text;

    Text(Style s, const string &str) : style(s), text(str) {}

    STNODE_ACCEPT_VISITOR_DECL();
  };

  struct Header : public STNode {
    int headerLevel;
    vector<unique_ptr<Text>> text;
  
    Header(int hh) : headerLevel(hh) {}

    STNODE_ACCEPT_VISITOR_DECL();
  };

  struct ListItem : public STNode {
    vector<unique_ptr<Text>> text;
  
    ListItem() {}

    ListItem(vector<unique_ptr<Text>> ele) : text(std::move(ele)) {}

    STNODE_ACCEPT_VISITOR_DECL();
  };

  struct List : public STNode {
    bool isOrdered;
    vector<unique_ptr<ListItem>> elements;
  
    List(bool o, vector<unique_ptr<ListItem>> ele)
        : isOrdered(o), elements(std::move(ele)) {}

    STNODE_ACCEPT_VISITOR_DECL();
  };

  struct Link : public STNode {
    string link;
    string text;
  
    Link(const string &l, const string &t) : link(l), text(t) {}

    STNODE_ACCEPT_VISITOR_DECL();
  };

  struct Image : public STNode {
    string link;
    string text;
  
    Image(const string &l, const string &t) : link(l), text(t) {}

    STNODE_ACCEPT_VISITOR_DECL();
  };

  struct TopText : public STNode {
    vector<unique_ptr<Text>> elements;

    TopText(vector<unique_ptr<Text>> ele) : elements(std::move(ele)) {}

    STNODE_ACCEPT_VISITOR_DECL();
  };

} // namespace md
