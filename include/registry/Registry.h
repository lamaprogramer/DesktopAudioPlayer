#pragma once

#include <filesystem>
#include <functional>

namespace iamaprogrammer {
  template <typename T>
  class Registry {
  public:
    virtual void load(std::filesystem::path audioDirectory) = 0;

    virtual const std::vector<T> getSortedEntries(std::function<bool(const T&, const T&)> sorter) = 0;

  protected:
    std::vector<T> entries;
  };
}