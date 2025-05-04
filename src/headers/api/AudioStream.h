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
      int CHUNK_SIZE = 1024;
      int MAX_LOADED_CHUNKS = 10;

      struct AudioBuffer {
        iamaprogrammer::AudioData* data;
        std::queue<AudioChunk>* buffer;
        bool seeking = false;
        long seekOffset = 0;
        long start = 0;
      };
      
      // Essential
      std::filesystem::path filePath;
      iamaprogrammer::AudioReader reader;

      std::queue<iamaprogrammer::AudioChunk> audioChunks;
      std::mutex audioChunksMutex;


      std::thread audioReaderThread;

      std::mutex audioBufferMutex;
      AudioBuffer audioBuffer;
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
        AudioBuffer* audioBuffer = static_cast<AudioBuffer*>(userData);
        AudioChunk chunk = audioBuffer->buffer->front();
        audioBuffer->buffer->pop();
        //std::cout << "popped chunk" << std::endl;

        if (audioBuffer->seeking) {
          audioBuffer->start += audioBuffer->seekOffset * audioBuffer->data->channels;
          audioBuffer->seeking = false;
        }

        long pos = 0;
        for (unsigned long i = 0; i < framesPerBuffer; i++) {
          for (int channelOffset = 0; channelOffset < audioBuffer->data->channels; channelOffset++) {
            *out++ = chunk.data()->at(pos + channelOffset);
          }

          pos += audioBuffer->data->channels;
          audioBuffer->start += audioBuffer->data->channels;
        }

        return paContinue;
      }
  };
}