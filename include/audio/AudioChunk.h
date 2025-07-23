#pragma once
#include <vector>

namespace iamaprogrammer {
  class AudioChunk {
  public:
    AudioChunk();
    AudioChunk(long size);

    std::vector<float>* data();

  private:
    long size = 0;
    std::vector<float> buffer;
  };
};