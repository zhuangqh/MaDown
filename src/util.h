#pragma once
#include <functional>
#include <memory>
#include "AST.h"

namespace md {

  using CharStream = std::function<int()>;

  template<typename T, typename... Args>
  std::unique_ptr<T> make_unique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
  }

  template<typename Derived, typename Base>
  std::unique_ptr<Derived>
  static_unique_ptr_cast( std::unique_ptr<Base>&& p ) {
    auto d = static_cast<Derived *>(p.release());
    return std::unique_ptr<Derived>(d, std::move(p.get_deleter()));
  }

} // namespace std
