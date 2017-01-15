#include "AST.h"
#include "Visitor.h"

namespace md {

#define STNODE_ACCEPT_VISITOR_IMPL(class_name)  \
  string class_name::accept(Visitor *v) {       \
  return v->visit(this);                        \
}

  STNODE_ACCEPT_VISITOR_IMPL(Text);

  STNODE_ACCEPT_VISITOR_IMPL(Header);

  STNODE_ACCEPT_VISITOR_IMPL(ListItem);

  STNODE_ACCEPT_VISITOR_IMPL(List);

  STNODE_ACCEPT_VISITOR_IMPL(Link);

  STNODE_ACCEPT_VISITOR_IMPL(Image);

  STNODE_ACCEPT_VISITOR_IMPL(TopText);

}