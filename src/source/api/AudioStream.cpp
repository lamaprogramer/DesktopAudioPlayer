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
    //std::cout << this->reader.getAudioData()->frames << std::endl;
   // std::cout << this->reader.getAudioData()->sampleRate << std::endl;

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

    this->audioBuffer = AudioBuffer{
      &audioData,
      &this->audioChunks,
    };

    this->error = Pa_OpenStream(
      &this->stream, 
      NULL, 
      &outputParameters, 
      deviceInfo->defaultSampleRate, 
      1024, // paFramesPerBufferUnspecified
      paNoFlag, 
      paCallback, 
      &audioBuffer
    );
    this->handlePaError();
    this->streamState = StreamState::OPEN;
    std::cout << "Stream opened" << std::endl;
  }

  void AudioStream::start() {
    if (Pa_IsStreamStopped(this->stream)) {
      this->error = Pa_StartStream(this->stream);
      this->handlePaError();

      this->playingState = PlayingState::PLAYING;
    }
    //std::cout << "Stream started" << std::endl;
  }

  void AudioStream::seek(float seconds) {
    while (this->audioChunks.size() > 0) {
      this->audioChunks.pop();
    }

    long frames = seconds * this->reader.getAudioData()->sampleRate;
    this->reader.seek(frames);

    /*
    TODO:
     - Implement seek() method in AudioReader with sf_seek()

     - Handle thread safety

    */

    this->audioBuffer.seekOffset = frames;
    this->audioBuffer.seeking = true;
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
    while (true) {
      if (this->audioChunks.size() >= this->MAX_LOADED_CHUNKS) {
        //std::this_thread::sleep_for(std::chrono::milliseconds(100));
        continue;
      }

      long long readSize = this->reader.read(this->audioChunks, 1024);

      if (readSize <= 0) {
        //std::cout << "End of stream" << std::endl;
        break;
      }
    }
    this->reader.close();
  }
}