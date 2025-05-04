#pragma once

#include "AudioData.h"
#include <filesystem>
#include <sndfile.h>
#include <vector>
#include <queue>
#include <string>

#include "AudioChunk.h"

namespace iamaprogrammer {

  class AudioReader {
    public:
      AudioReader();
      AudioReader(std::filesystem::path filePath);

      long long read(std::queue<AudioChunk>& buffer, long bufferSize);
      void seek(long offset);

      AudioData* getAudioData();

      AudioData close();

    private:
      std::filesystem::path path;
      SNDFILE* file;
      AudioData data;
  };

  class AudioWriter {
    public:
      AudioWriter(std::filesystem::path filePath);
  };

  static std::string toString(float* buf, int size) {
    if (buf == nullptr || size == 0) {
      return "[]";
    }
  
    std::string str = "[";
    for (int i = 0; i < size; i++) {
      str += std::to_string(buf[i]);
      if (i < size - 1) str += ", ";
    }
    str += "]";
    return str;
  };
}