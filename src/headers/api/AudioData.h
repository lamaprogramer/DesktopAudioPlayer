#pragma once

#include <vector>

namespace iamaprogrammer {
  struct AudioData {
    size_t frames;
    int sampleRate;
    int channels;
  };
}