#pragma once

#include <filesystem>
#include <sndfile.h>

#include "Buffer.h"
#include <vector>

using namespace iamaprogrammer;

namespace SoundFileReader {

  struct AudioInfo {
    std::vector<float> buffer;
    SF_INFO info;
  };

  AudioInfo read(std::filesystem::path path);
  void write(std::filesystem::path path, SF_INFO& fileInfo, std::vector<float>* buffer);
}