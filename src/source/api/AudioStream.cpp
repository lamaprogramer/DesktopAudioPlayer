#include "AudioStream.h"
#include "SoundFileIO.h"

namespace iamaprogrammer {
  AudioStream::AudioStream() {};

  AudioStream::AudioStream(std::filesystem::path filePath) {
    this->setFile(filePath);
  };

  void AudioStream::setup() {
    this->reader = AudioReader(this->filePath);

    PaDeviceIndex device = Pa_GetDefaultOutputDevice();
    const PaDeviceInfo* deviceInfo = Pa_GetDeviceInfo(device);

    AudioData& audioData = *this->reader.getAudioData();
    PaStreamParameters outputParameters;
    outputParameters.device = device;
    outputParameters.channelCount = audioData.channels;
    outputParameters.sampleFormat = paFloat32;
    outputParameters.suggestedLatency = deviceInfo->defaultLowOutputLatency;
    outputParameters.hostApiSpecificStreamInfo = NULL;

    this->audioReaderThread = std::thread(audioReaderThreadCallback, this);

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
    std::cout << "Stream opened" << std::endl;
  }

  void AudioStream::start() {
    this->error = Pa_StartStream(this->stream);
    this->handlePaError();
  
    this->state = State::PLAYING;
    std::cout << "Stream started" << std::endl;
  }

  void AudioStream::stop() {
    this->error = Pa_StopStream(this->stream);
    this->handlePaError();
    this->state = State::STOPPED;
  }

  void AudioStream::end() {
    this->stop();
    this->error = Pa_CloseStream(this->stream);
    this->handlePaError();
    std::cout << "Stream closed" << std::endl;

    if (this->audioReaderThread.joinable()) {
      this->audioReaderThread.join();
    }
  }

  std::filesystem::path AudioStream::getFilePath() {
    return this->filePath;
  }

  AudioStream::State AudioStream::getState() {
    return this->state;
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
      std::cout << Pa_GetErrorText(error) << std::endl;
    }
  }

  void AudioStream::audioReaderThreadCallback() {
    while (this->reader.read(1024) > 0) {}
    this->reader.close();
  }
}