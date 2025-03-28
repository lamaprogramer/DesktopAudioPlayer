#include <iostream>
#include <string>
#include <vector>
#include <portaudio.h>
#include <sndfile.h>
#include <algorithm>

#include "SoundFileReader.h"
#include "Buffer.h"

using namespace iamaprogrammer;

struct AudioBuffer {
  std::vector<float> data;
  long start = 0;
};

std::string toString(float* buf, int size);
static int patestCallback( const void *inputBuffer, void *outputBuffer,
  unsigned long framesPerBuffer,
  const PaStreamCallbackTimeInfo* timeInfo,
  PaStreamCallbackFlags statusFlags,
  void *userData ) {

  float* out = static_cast<float*>(outputBuffer);
  AudioBuffer* audioBuffer = static_cast<AudioBuffer*>(userData);

  for (unsigned long i = 0; i < framesPerBuffer; i++) {
    *out++ = audioBuffer->data.at(audioBuffer->start); // Copy from buffer to output
    audioBuffer->start++;

    *out++ = audioBuffer->data.at(audioBuffer->start);
    audioBuffer->start++;

  }

  //std::cout << toString((float*)outputBuffer, framesPerBuffer) << "\n\n" << std::endl;
  //audioBuffer->start += framesPerBuffer;

  return paContinue;
}

int main(int argc, char* argv[]) {
  std::cout << "Hello, World!" << std::endl;

  SoundFileReader::AudioInfo audioInfo = SoundFileReader::read("resources\\audio\\test.mp3");
  SF_INFO fileInfo = audioInfo.info;
  std::vector<float> buf = audioInfo.buffer;

  std::cout << audioInfo.info.frames << std::endl;

  PaError err;
  err = Pa_Initialize();
  if (err != paNoError) std::cout << Pa_GetErrorText(err) << std::endl;

  PaDeviceIndex device = Pa_GetDefaultOutputDevice();
  const PaDeviceInfo* deviceInfo = Pa_GetDeviceInfo(device);
  std::cout << audioInfo.info.frames << std::endl;


  
  PaStreamParameters outputParameters;
  outputParameters.device = device;
  outputParameters.channelCount = audioInfo.info.channels;
  outputParameters.sampleFormat = paFloat32;
  outputParameters.suggestedLatency = deviceInfo->defaultLowOutputLatency;
  outputParameters.hostApiSpecificStreamInfo = NULL;

  AudioBuffer audiobuf{buf};

  PaStream* stream;
  err = Pa_OpenStream(&stream, NULL, &outputParameters, deviceInfo->defaultSampleRate, paFramesPerBufferUnspecified, paNoFlag, patestCallback, &audiobuf);

  if (err != paNoError) std::cout << Pa_GetErrorText(err) << std::endl;
  err = Pa_StartStream( stream );
  if (err != paNoError) std::cout << Pa_GetErrorText(err) << std::endl;
  Pa_Sleep(10000); // Play for 2 seconds
  Pa_StopStream(stream);
  Pa_CloseStream(stream);

  err = Pa_Terminate();
  if (err != paNoError) std::cout << Pa_GetErrorText(err) << std::endl;
  return 0;
}

std::string toString(float* buf, int size) {
  if (buf == nullptr || size == 0) {
    return "[]";
  }

  std::string str = "[";
  for (int i = 0; i < size; i++) {
    str += std::to_string(buf[i]);
    if (i < size - 1) str += ", ";
  }
  str += "]";
  return str;
};