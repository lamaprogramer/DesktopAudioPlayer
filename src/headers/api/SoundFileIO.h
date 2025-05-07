#pragma once

#include "AudioData.h"
#include <filesystem>
#include <vector>
#include <queue>
#include <string>

#include <samplerate.h>
#include <sndfile.h>

#include "AudioChunk.h"

namespace iamaprogrammer {

  class AudioReader {
    public:
      AudioReader();
      AudioReader(std::filesystem::path filePath, int deviceSampleRate, int readSize);

      long long read(std::queue<AudioChunk>& buffer);
      void seek(long long frames, int whence);

      AudioData* getAudioData();
      double getSampleRateRatio();

      AudioData close();

    private:
      std::filesystem::path path;
      SNDFILE* file;
      SRC_STATE* srcState; // Samplerate Converter state
      SRC_DATA srcData; // Samplerate Converter data
      AudioData data;

      std::vector<float> readBuffer;

      int error = 0;

      int readSize = 0;
      int deviceSampleRate = 0;
      double sampleRateRatio = 1.0;
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