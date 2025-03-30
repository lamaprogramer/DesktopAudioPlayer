#pragma once

#include <vector>

namespace iamaprogrammer {
  struct AudioData {
    std::vector<float> buffer;
    long long frames;
    int sampleRate;
    int channels;
  };
}