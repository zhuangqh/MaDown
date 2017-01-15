#pragma once

#include "AST.h"

namespace md {
#define VISITOR_VISIT_DECL(class_name)         \
    virtual string visit(class_name *) = 0;

  struct Visitor {
    virtual ~Visitor() {}

    VISITOR_VISIT_DECL(Text);

    VISITOR_VISIT_DECL(Header);

    VISITOR_VISIT_DECL(ListItem);

    VISITOR_VISIT_DECL(List);

    VISITOR_VISIT_DECL(Link);

    VISITOR_VISIT_DECL(Image);

    VISITOR_VISIT_DECL(TopText);
  };

} // namespace md
