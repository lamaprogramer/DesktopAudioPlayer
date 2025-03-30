#include <iostream>
#include <string>
#include <vector>
#include <portaudio.h>
#include <sndfile.h>
#include <algorithm>

#include "SoundFileIO.h"
#include "AudioData.h"
#include "AudioStream.h"

int main(int argc, char* argv[]) {
  PaError err;
  err = Pa_Initialize();
  if (err != paNoError) std::cout << Pa_GetErrorText(err) << std::endl;

  iamaprogrammer::AudioStream audio = iamaprogrammer::AudioStream(std::filesystem::current_path() / "resources\\audio\\test.mp3");
  audio.setup();
  audio.start();
  Pa_Sleep(10000);
  audio.stop();
  Pa_Sleep(5000);
  audio.start();
  Pa_Sleep(10000);

  audio.end();

  err = Pa_Terminate();
  if (err != paNoError) std::cout << Pa_GetErrorText(err) << std::endl;
  return 0;
}