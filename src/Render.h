#pragma once
#include "Visitor.h"

namespace md {
#define RENDER_VISIT_DECL(class_name)         \
    virtual string visit(class_name *);

  class Render : public Visitor {
  private:
  public:
    RENDER_VISIT_DECL(Text);

    RENDER_VISIT_DECL(Header);

    RENDER_VISIT_DECL(ListItem);

    RENDER_VISIT_DECL(List);

    RENDER_VISIT_DECL(Link);

    RENDER_VISIT_DECL(Image);

    RENDER_VISIT_DECL(Code);

    RENDER_VISIT_DECL(TopText);
  };

} // namespace md
