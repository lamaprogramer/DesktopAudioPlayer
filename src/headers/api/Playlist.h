#pragma once
#include <filesystem>
#include <string>
#include <vector>

namespace iamaprogrammer {
  class Playlist {
  public:
    Playlist();
    Playlist(std::string name);

    void add(std::string name);
    void remove(std::string name);

    void writeTo(std::filesystem::path filePath);
    static Playlist loadFrom(std::filesystem::path filePath);
  private:
    std::string name;
    std::vector<std::string> audio;
  };
}