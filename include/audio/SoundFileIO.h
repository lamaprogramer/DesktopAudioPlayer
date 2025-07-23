#pragma once

#include "AudioFileDescriptor.h"
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

      size_t read(std::queue<AudioChunk>& buffer);
      void seek(size_t frames, int whence);

      AudioFileDescriptor* getAudioData();
      double getSampleRateRatio();

      void close();

    private:
      std::filesystem::path path;
      SNDFILE* file;
      SRC_STATE* srcState; // Samplerate Converter state
      SRC_DATA srcData; // Samplerate Converter data

      AudioFileDescriptor data;
      std::vector<float> readBuffer;

      int error = 0;
      int readSize = 0;
      int deviceSampleRate = 0;
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