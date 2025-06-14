#pragma once

#include <iostream>
#include <portaudio.h>
#include <filesystem>
#include <vector>
#include <queue>
#include <mutex>
#include <thread>

#include "AudioChunk.h"
#include "AudioData.h"
#include "SoundFileIO.h"

namespace iamaprogrammer {
  class AudioStream {
    public:
      enum StreamState {
        OPEN,
        CLOSED
      };
      
      enum PlayingState {
        PLAYING,
        SEEKING,
        STOPPED,
        BUFFERING
      };

      AudioStream();
      AudioStream(std::filesystem::path filePath);

      void setFile(std::filesystem::path filePath);

      void setup();

      void start();
      void seek(float seconds);
      void stop();

      void end();

      std::filesystem::path getFilePath();
      PlayingState getPlayingState();
      StreamState getStreamState();

    private:
      static int READ_SIZE;
      static int MAX_LOADED_CHUNKS;

      struct AudioStreamData {
        iamaprogrammer::AudioData* data;
        std::queue<AudioChunk>* buffer;

        bool seeking = false;
        long seekOffset = 0;
        long start = 0;
      };
      
      // Essential
      std::filesystem::path filePath;
      iamaprogrammer::AudioReader reader;

      std::queue<iamaprogrammer::AudioChunk> audioBuffer;
      AudioStreamData audioStreamData;
      std::thread audioReaderThread;
      PaStream* stream;

      // State
      PlayingState playingState = PlayingState::STOPPED;
      StreamState streamState = StreamState::CLOSED;
      PaError error;

      void handlePaError();
      void audioReaderThreadCallback();

      static int paCallback(
        const void *inputBuffer, void *outputBuffer,
        unsigned long framesPerBuffer,
        const PaStreamCallbackTimeInfo* timeInfo,
        PaStreamCallbackFlags statusFlags,
        void *userData 
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