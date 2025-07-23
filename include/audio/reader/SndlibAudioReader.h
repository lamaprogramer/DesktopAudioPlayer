#pragma once
#include "IAudioReader.h"
#include <sndfile.h>
#include <queue>
#include <filesystem>
#include <iostream>

namespace iamaprogrammer {
  class SndlibAudioReader: public IAudioReader {
  public:
    SndlibAudioReader();
    SndlibAudioReader(std::filesystem::path filePath, int readSize);

    size_t read(IAudioResampler* resampler, std::queue<AudioChunk>& buffer) override;
    void seek(size_t frames, int whence) override;
    void* getReadBuffer() override;

    AudioFileDescriptor* getAudioFileDescriptor() override;
    void close() override;
  private:
    std::filesystem::path path;
    SNDFILE* file;

    AudioFileDescriptor audioFileDescriptor;
    std::vector<float> readBuffer;

    int readSize = 0;
  };
}