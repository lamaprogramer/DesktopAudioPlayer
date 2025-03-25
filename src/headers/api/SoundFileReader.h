#pragma once

#include <filesystem>
#include <sndfile.h>

#include "Buffer.h"

using namespace iamaprogrammer;

namespace SoundFileReader {
  void read(std::filesystem::path path, Buffer<float>* buffer);
}