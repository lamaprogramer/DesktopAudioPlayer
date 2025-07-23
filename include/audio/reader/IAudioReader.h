#pragma once
#include "../AudioFileDescriptor.h"
#include "../AudioChunk.h"
#include "../resampler/IAudioResampler.h"

#include <queue>

namespace iamaprogrammer {
  class IAudioReader {
  public:
    virtual size_t read(IAudioResampler* resampler, std::queue<AudioChunk>& buffer) = 0;
    virtual void seek(size_t frames, int whence) = 0;
    virtual void* getReadBuffer() = 0;

    virtual AudioFileDescriptor* getAudioFileDescriptor() = 0;

    virtual void close() = 0;
  };
}