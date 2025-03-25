#include "SoundFileReader.h"

#include <iostream>
#include <sndfile.h>

void SoundFileReader::read(std::filesystem::path localPath, Buffer<float>* buffer) {
  SF_INFO info;

  std::filesystem::path path = std::filesystem::current_path() / localPath;

  std::string pathStr = path.string();
  const char* pathCStr = pathStr.c_str();

  SNDFILE* file = sf_open(pathCStr, SFM_READ, &info);
  if (file == nullptr) {
    std::cout << "Error opening file: " << pathCStr << std::endl;
    return;
  }

  std::cout << "Channels: " << info.channels << std::endl;
  std::cout << "Format: " << info.format << std::endl;
  std::cout << "Frames: " << info.frames << std::endl;
  std::cout << "Sample Rate: " << info.samplerate << std::endl;
  std::cout << "Sections: " << info.sections << std::endl;
  std::cout << "Seekable: " << info.seekable << std::endl;

  buffer->resize(info.frames * info.channels);
  sf_read_float(file, buffer->getBuffer(), info.frames * info.channels);
  sf_close(file);
}