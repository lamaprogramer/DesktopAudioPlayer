#pragma once
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

#include "md5.h"

namespace iamaprogrammer {
  class Playlist {
  public:
    Playlist();
    Playlist(std::string name);

    void add(md5_hash fileHash);
    void remove(const md5_hash fileHash);

    static Playlist load(std::filesystem::path filePath);
  private:
    std::string name;
    std::vector<md5_hash> audio;

    Playlist(std::vector<md5_hash> audio, std::string name);
  };
}