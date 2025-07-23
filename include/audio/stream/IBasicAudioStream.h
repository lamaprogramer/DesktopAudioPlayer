#pragma once

#include <string>
#include "../reader/IAudioReader.h"
#include "../resampler/IAudioResampler.h"

namespace iamaprogrammer {
  typedef std::queue<iamaprogrammer::AudioChunk> AudioBuffer;

  struct AudioStreamData {
    iamaprogrammer::AudioFileDescriptor* data;
    AudioBuffer* buffer;

    bool seeking = false;
    long seekOffset = 0;
    long start = 0;
  };

  class IBasicAudioStream {
  public:
    virtual void openStream(IAudioReader* reader, IAudioResampler* resampler, int chunkSize) = 0;
    virtual void closeStream() = 0;

    virtual void startStream() = 0;
    virtual void seekStream(int frames) = 0;
    virtual void stopStream() = 0;

    virtual bool isStreamStopped() = 0;
    virtual bool isStreamActive() = 0;

    //virtual double getSampleRate() = 0;
    virtual int getChannelCount() = 0;
    virtual AudioBuffer* getAudioBuffer() = 0;

    virtual std::string getError() = 0;
    virtual bool hasError() = 0;
  protected:
    AudioBuffer audioBuffer;
  };
}