#include "SoundFileReader.h"

#include <iostream>
#include <sndfile.h>
#include <string>

SoundFileReader::AudioInfo SoundFileReader::read(std::filesystem::path localPath) {
  SF_INFO info;

  std::filesystem::path path = std::filesystem::current_path() / localPath;

  std::string pathStr = path.string();
  const char* pathCStr = pathStr.c_str();

  SNDFILE* file = sf_open(pathCStr, SFM_READ, &info);
  if (file == nullptr) {
    std::cout << "Error opening file: " << pathCStr << std::endl;
    return AudioInfo();
  }

  std::cout << "Channels: " << info.channels << std::endl;
  std::cout << "Format: " << info.format << std::endl;
  std::cout << "Frames: " << info.frames << std::endl;
  std::cout << "Sample Rate: " << info.samplerate << std::endl;
  std::cout << "Sections: " << info.sections << std::endl;
  std::cout << "Seekable: " << info.seekable << std::endl;
  //std::cout << (info.format & SF_FORMAT_SUBMASK) << std::endl;
  
  size_t totalSamples = info.frames * info.channels;
  std::vector<float> buffer(totalSamples);

  sf_readf_float(file, buffer.data(), info.frames);
  sf_close(file);

  return AudioInfo{buffer, info};
}

void SoundFileReader::write(std::filesystem::path localPath, SF_INFO& fileInfo, std::vector<float>* buffer) {
  std::filesystem::path path = std::filesystem::current_path() / localPath;

  std::string pathStr = path.string();
  const char* pathCStr = pathStr.c_str();

  SF_INFO writeInfo;
  writeInfo.format = SF_FORMAT_WAV | SF_FORMAT_FLOAT;
  writeInfo.samplerate = fileInfo.samplerate;
  writeInfo.frames = buffer->size();
  writeInfo.sections = 1;
  writeInfo.seekable = SF_TRUE;
  writeInfo.channels = fileInfo.channels;

  SNDFILE* file = sf_open(pathCStr, SFM_WRITE, &writeInfo);
  if (file == nullptr) {
    std::cout << "Error opening file: " << pathCStr << std::endl;
  }
  writeInfo = fileInfo;

  std::cout << "Channels: " << fileInfo.channels << std::endl;
  std::cout << "Format: " << fileInfo.format << std::endl;
  std::cout << "Frames: " << fileInfo.frames << std::endl;
  std::cout << "Sample Rate: " << fileInfo.samplerate << std::endl;
  std::cout << "Sections: " << fileInfo.sections << std::endl;
  std::cout << "Seekable: " << fileInfo.seekable << std::endl;
  std::cout << buffer->size() << std::endl;

  sf_writef_float(file, buffer->data(), fileInfo.frames);
  sf_close(file);
}