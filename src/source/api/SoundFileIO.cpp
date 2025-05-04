#include "SoundFileIO.h"

#include <iostream>
#include <sndfile.h>
#include <string>


namespace iamaprogrammer {
  AudioReader::AudioReader() {}

  AudioReader::AudioReader(std::filesystem::path filePath) {
    SF_INFO info;

    std::string pathStr = filePath.string();
    const char* pathCStr = pathStr.c_str();

    this->file = sf_open(pathCStr, SFM_READ, &info);
    if (this->file == nullptr) {
      std::cout << "Error opening file: " << pathCStr << std::endl;
    }

    this->data.frames = info.frames;
    this->data.channels = info.channels;
    this->data.sampleRate = info.samplerate;
  }

  long long AudioReader::read(std::queue<AudioChunk>& buffer, long bufferSize) {
    AudioChunk chunk(bufferSize*this->data.channels);
    long long readCount = sf_readf_float(this->file, chunk.data()->data(), bufferSize);
   
    if (readCount > 0) {
      /*if (readCount < bufferSize) {
        buffer.resize(readCount*this->data.channels);
      }*/
      //std::cout << "read chunk" << std::endl;
      buffer.push(chunk); 
    }
    return readCount;
  }

  AudioData* AudioReader::getAudioData() {
    return &this->data;
  }

  AudioData AudioReader::close() {
    sf_close(file);
    return this->data;
  }
}

// void iamaprogrammer::write(std::filesystem::path path, SF_INFO& fileInfo, std::vector<float>* buffer) {
//   std::string pathStr = path.string();
//   const char* pathCStr = pathStr.c_str();

//   SF_INFO writeInfo;
//   writeInfo.format = SF_FORMAT_WAV | SF_FORMAT_FLOAT;
//   writeInfo.samplerate = fileInfo.samplerate;
//   writeInfo.frames = buffer->size();
//   writeInfo.sections = 1;
//   writeInfo.seekable = SF_TRUE;
//   writeInfo.channels = fileInfo.channels;

//   SNDFILE* file = sf_open(pathCStr, SFM_WRITE, &writeInfo);
//   if (file == nullptr) {
//     std::cout << "Error opening file: " << pathCStr << std::endl;
//   }
//   writeInfo = fileInfo;

//   std::cout << "Channels: " << fileInfo.channels << std::endl;
//   std::cout << "Format: " << fileInfo.format << std::endl;
//   std::cout << "Frames: " << fileInfo.frames << std::endl;
//   std::cout << "Sample Rate: " << fileInfo.samplerate << std::endl;
//   std::cout << "Sections: " << fileInfo.sections << std::endl;
//   std::cout << "Seekable: " << fileInfo.seekable << std::endl;
//   std::cout << buffer->size() << std::endl;

//   sf_writef_float(file, buffer->data(), fileInfo.frames);
//   sf_close(file);
// }