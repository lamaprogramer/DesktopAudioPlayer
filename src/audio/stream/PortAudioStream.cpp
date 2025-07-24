#include "../../../include/audio/stream/PortAudioStream.h"

namespace iamaprogrammer {

  PortAudioStream::PortAudioStream() {
  }

  void PortAudioStream::openStream(IAudioReader* reader, IAudioResampler* resampler) {

    this->audioStreamData = AudioStreamData{
      reader->getAudioFileDescriptor(),
      &this->audioBuffer
    };

    PaDeviceIndex device = Pa_GetDefaultOutputDevice();
    const PaDeviceInfo* deviceInfo = Pa_GetDeviceInfo(device);

    PaStreamParameters outputParameters;
    outputParameters.device = device;
    outputParameters.channelCount = reader->getAudioFileDescriptor()->channels;
    outputParameters.sampleFormat = paFloat32;
    outputParameters.suggestedLatency = deviceInfo->defaultLowOutputLatency;
    outputParameters.hostApiSpecificStreamInfo = NULL;

    this->error = Pa_OpenStream(
      &this->stream,
      NULL,
      &outputParameters,
      deviceInfo->defaultSampleRate,
      reader->getReadSize() * resampler->getSampleRateConversionRatio(), // paFramesPerBufferUnspecified
      paNoFlag,
      paCallback,
      &this->audioStreamData
    );
  }

  void PortAudioStream::closeStream() {
    this->error = Pa_CloseStream(this->stream);
  }

  void PortAudioStream::startStream() {
    this->error = Pa_StartStream(this->stream);
  }

  void PortAudioStream::seekStream(int frames) {
    this->audioStreamData.seekOffset = frames;
    this->audioStreamData.seeking = true;
  }

  void PortAudioStream::stopStream() {
    this->error = Pa_StopStream(this->stream);
  }

  bool PortAudioStream::isStreamStopped() {
    return Pa_IsStreamStopped(this->stream);
  }

  bool PortAudioStream::isStreamActive() {
    return Pa_IsStreamActive(this->stream);
  }

  int PortAudioStream::getChannelCount() {
    return this->audioStreamData.data->channels;
  }

  AudioBuffer* PortAudioStream::getAudioBuffer() {
    return &this->audioBuffer;
  }

  std::string PortAudioStream::getError() {
    return std::string(Pa_GetErrorText(this->error));
  }

  bool PortAudioStream::hasError() {
    return this->error != paNoError;
  }

  int PortAudioStream::getDeviceIndex() {
    PaDeviceIndex device = Pa_GetDefaultOutputDevice();
    if (device == paNoDevice) {
      throw std::runtime_error("No default output device found.");
    }
    return device;
  }

  const PaDeviceInfo* PortAudioStream::getDeviceInfo() {
    return Pa_GetDeviceInfo(getDeviceIndex());
  }
}