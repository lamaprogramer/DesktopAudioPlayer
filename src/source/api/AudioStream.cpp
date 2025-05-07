#include "AudioStream.h"
#include "SoundFileIO.h"

#include <string>

namespace iamaprogrammer {
  int AudioStream::READ_SIZE = 1024;
  int AudioStream::MAX_LOADED_CHUNKS = 10;


  AudioStream::AudioStream() {};

  AudioStream::AudioStream(std::filesystem::path filePath) {
    this->setFile(filePath);
  };

  void AudioStream::setup() {
    if (this->streamState == StreamState::OPEN) {
      throw std::runtime_error("Stream is already open.");
    }
    this->streamState = StreamState::OPEN;


    PaDeviceIndex device = Pa_GetDefaultOutputDevice();
    const PaDeviceInfo* deviceInfo = Pa_GetDeviceInfo(device);

    this->reader = AudioReader(this->filePath, deviceInfo->defaultSampleRate, READ_SIZE);
    AudioData& audioData = *this->reader.getAudioData();

    //long long bufferSize = CHUNK_SIZE * this->reader.getSampleRateRatio();

    PaStreamParameters outputParameters;
    outputParameters.device = device;
    outputParameters.channelCount = audioData.channels;
    outputParameters.sampleFormat = paFloat32;
    outputParameters.suggestedLatency = deviceInfo->defaultLowOutputLatency;
    outputParameters.hostApiSpecificStreamInfo = NULL;

    this->audioReaderThread = std::thread([this](){ audioReaderThreadCallback(); }); // Start reader thread.

    this->audioBuffer = AudioBuffer{
      &audioData,
      &this->audioChunks,
      &this->audioChunksMutex
    };

    this->error = Pa_OpenStream(
      &this->stream, 
      NULL, 
      &outputParameters, 
      deviceInfo->defaultSampleRate, 
      READ_SIZE * this->reader.getSampleRateRatio(), // paFramesPerBufferUnspecified
      paNoFlag, 
      paCallback, 
      &audioBuffer
    );

    this->handlePaError();
    std::cout << "Stream opened" << std::endl;
  }

  void AudioStream::start() {
    if (Pa_IsStreamStopped(this->stream)) {
      this->error = Pa_StartStream(this->stream);
      this->handlePaError();

      this->playingState = PlayingState::PLAYING;
    }
  }

  void AudioStream::seek(float seconds) {
    this->playingState = PlayingState::SEEKING;

    while (this->audioChunks.size() > 0) { // Clear chunk buffer
      this->audioChunks.pop();
    }

    long frames = seconds * this->reader.getAudioData()->sampleRate;
    this->reader.seek(frames, SEEK_CUR);

    this->audioBuffer.seekOffset = frames;
    this->audioBuffer.seeking = true;

    this->playingState = PlayingState::PLAYING;
  }

  void AudioStream::stop() {
    if (Pa_IsStreamActive(this->stream)) {
      this->error = Pa_StopStream(this->stream);
      //this->error = Pa_AbortStream(this->stream);
      this->handlePaError();
      this->playingState = PlayingState::STOPPED;
    }
  }

  void AudioStream::end() {
    if (this->streamState == StreamState::CLOSED) {
      throw std::runtime_error("Stream is already closed.");
    }
    this->streamState = StreamState::CLOSED;

    this->error = Pa_CloseStream(this->stream);
    this->handlePaError();

    if (this->audioReaderThread.joinable()) {
      this->audioReaderThread.join();
    }
    std::cout << "Stream closed" << std::endl;
  }

  std::filesystem::path AudioStream::getFilePath() {
    return this->filePath;
  }

  AudioStream::PlayingState AudioStream::getPlayingState() {
    return this->playingState;
  }

  AudioStream::StreamState AudioStream::getStreamState() {
    return this->streamState;
  }

  void AudioStream::setFile(std::filesystem::path filePath) {
    if (!std::filesystem::exists(filePath)) {
      throw std::runtime_error("File not found: " + filePath.string());
    };
    this->filePath = filePath;
  }


  // Private
  void AudioStream::handlePaError() {
    if (this->error != paNoError) {
      throw std::runtime_error("PortAudio error: " + std::string(Pa_GetErrorText(this->error)));
    }
  }

  void AudioStream::audioReaderThreadCallback() {
    while (true) {
      if (this->streamState == StreamState::CLOSED) {
        break;
      }

      if (this->audioChunks.size() >= this->MAX_LOADED_CHUNKS || this->getPlayingState() == PlayingState::SEEKING) {
        continue;
      }

      long long readSize = this->reader.read(this->audioChunks);
    }
    this->reader.close();
  }
}