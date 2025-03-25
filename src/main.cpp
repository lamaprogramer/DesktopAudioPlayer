#include <iostream>
#include <string>
#include <portaudio.h>
#include <sndfile.h>

#include "SoundFileReader.h"
#include "Buffer.h"

using namespace iamaprogrammer;

void test();

int main(int argc, char* argv[]) {
  std::cout << "Hello, World!" << std::endl;

  Buffer<float> buf;
  SoundFileReader::read("resources\\audio\\test.mp3", &buf);
  std::cout << "finished" << std::endl;
  std::cout << buf.toString() << std::endl;

  return 0;
}

void test() {
  PaError err;
  err = Pa_Initialize();
  if (err != paNoError) std::cout << Pa_GetErrorText(err) << std::endl;

  err = Pa_Terminate();
  if (err != paNoError) std::cout << Pa_GetErrorText(err) << std::endl;
}
