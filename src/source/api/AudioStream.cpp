#include "AudioStream.h"
#include "SoundFileIO.h"

#include <string>

namespace iamaprogrammer {
  AudioStream::AudioStream() {};

  AudioStream::AudioStream(std::filesystem::path filePath) {
    this->setFile(filePath);
  };

  void AudioStream::setup() {
    if (this->streamState == StreamState::OPEN) {
      throw std::runtime_error("Stream is already open.");
    }

    this->reader = AudioReader(this->filePath);
    std::cout << this->reader.getAudioData()->frames << std::endl;
    std::cout << this->reader.getAudioData()->sampleRate << std::endl;

    PaDeviceIndex device = Pa_GetDefaultOutputDevice();
    const PaDeviceInfo* deviceInfo = Pa_GetDeviceInfo(device);

    AudioData& audioData = *this->reader.getAudioData();
    PaStreamParameters outputParameters;
    outputParameters.device = device;
    outputParameters.channelCount = audioData.channels;
    outputParameters.sampleFormat = paFloat32;
    outputParameters.suggestedLatency = deviceInfo->defaultLowOutputLatency;
    outputParameters.hostApiSpecificStreamInfo = NULL;

    this->audioReaderThread = std::thread([this](){ audioReaderThreadCallback(); });

    this->audioBuffer = AudioBuffer{&audioData};
    this->error = Pa_OpenStream(
      &this->stream, 
      NULL, 
      &outputParameters, 
      deviceInfo->defaultSampleRate, 
      paFramesPerBufferUnspecified, 
      paNoFlag, 
      paCallback, 
      &audioBuffer
    );
    this->handlePaError();
    this->streamState = StreamState::OPEN;
    std::cout << "Stream opened" << std::endl;
  }

  void AudioStream::start() {
    this->error = Pa_StartStream(this->stream);
    this->handlePaError();
  
    this->playingState = PlayingState::PLAYING;
    std::cout << "Stream started" << std::endl;
  }

  void AudioStream::seek(float seconds) {
    long frames = seconds * this->reader.getAudioData()->sampleRate;
    this->audioBuffer.seekOffset = frames;
    this->audioBuffer.seeking = true;
  }

  void AudioStream::stop() {
    if (!Pa_IsStreamStopped(this->stream)) {
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

    this->error = Pa_CloseStream(this->stream);
    this->handlePaError();

    if (this->audioReaderThread.joinable()) {
      this->audioReaderThread.join();
    }
    this->streamState = StreamState::CLOSED;
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
    while (this->reader.read(1024) > 0) {}
    this->reader.close();
  }
}