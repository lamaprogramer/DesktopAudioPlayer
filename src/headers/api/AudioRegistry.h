#pragma once
#include <filesystem>
#include <vector>
#include <string>

namespace iamaprogrammer {
  struct AudioEntry {
    unsigned char hash[16]; // md5
    std::string filename;
  };

  class AudioRegistry {
  public:
    static void write();
    static void load(std::filesystem::path audioDirectory);
    static void MDPrint(const unsigned char digest[16]);

  protected:
    static std::vector<AudioEntry> entries;
  };
}