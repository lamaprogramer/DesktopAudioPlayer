#pragma once
#include "IBasicAudioStream.h"  

#include <queue>
#include <stdexcept>
#include <portaudio.h>
#include "../AudioChunk.h"
#include "../AudioFileDescriptor.h"

namespace iamaprogrammer {
  class PortAudioStream : public IBasicAudioStream {
  public:
    PortAudioStream();

    void openStream(IAudioReader* reader, IAudioResampler* resampler, int chunkSize) override;
    void closeStream() override;

    void startStream() override;
    void seekStream(int frames) override;
    void stopStream() override;

    bool isStreamStopped() override;
    bool isStreamActive() override;

    //double getSampleRate() override;
    int getChannelCount() override;
    AudioBuffer* getAudioBuffer() override;

    std::string getError() override;
    bool hasError() override;
  private:
    PaStream* stream;
    PaError error;

    AudioStreamData audioStreamData;

    static int getDeviceIndex();
    static const PaDeviceInfo* getDeviceInfo();

    static int paCallback(
      const void* inputBuffer, void* outputBuffer,
      unsigned long framesPerBuffer,
      const PaStreamCallbackTimeInfo* timeInfo,
      PaStreamCallbackFlags statusFlags,
      void* userData
    ) {
      float* out = static_cast<float*>(outputBuffer);
      AudioStreamData* streamData = static_cast<AudioStreamData*>(userData);

      AudioChunk chunk = streamData->buffer->front();
      streamData->buffer->pop();

      if (streamData->seeking) {
        streamData->start += streamData->seekOffset * streamData->data->channels;
        streamData->seeking = false;
      }

      long pos = 0;
      for (unsigned long i = 0; i < framesPerBuffer; i++) {
        for (int channelOffset = 0; channelOffset < streamData->data->channels; channelOffset++) {
          *out++ = chunk.data()->at(pos + channelOffset);
        }

        pos += streamData->data->channels;
        streamData->start += streamData->data->channels;
      }

      return paContinue;
    }
  };
}