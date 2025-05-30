#pragma once
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

namespace iamaprogrammer {
  class Playlist {
  public:
    Playlist();
    Playlist(std::string name);

    void add(std::string name);
    void remove(const std::string &name);

    static Playlist load(std::filesystem::path filePath);
  private:
    std::string name;
    std::vector<std::string> audio;

    Playlist(std::vector<std::string> audio, std::string name);
  };
}