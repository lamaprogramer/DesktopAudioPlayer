#include "SoundFileIO.h"

#include <iostream>
#include <sndfile.h>
#include <string>


namespace iamaprogrammer {
  AudioReader::AudioReader() {}

  AudioReader::AudioReader(std::filesystem::path filePath, int deviceSampleRate, int readSize): 
    deviceSampleRate(deviceSampleRate), 
    readSize(readSize)
  {
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

    // Set up read buffer and initialize sample rate converter.
    this->readBuffer = std::vector<float>(readSize * info.channels);
    this->srcState = src_new(SRC_SINC_FASTEST, info.channels, &this->error);

    this->srcData.data_in = this->readBuffer.data();
    this->srcData.input_frames = readSize;
    this->srcData.output_frames = readSize * this->getSampleRateRatio();
    this->srcData.src_ratio = this->getSampleRateRatio();
    this->srcData.end_of_input = 0;
  }

  size_t AudioReader::read(std::queue<AudioChunk>& buffer) {
    AudioChunk chunk((this->readSize * this->getSampleRateRatio()) * this->data.channels); 

    long long readCount = sf_readf_float(this->file, this->readBuffer.data(), this->readSize);

    if (this->getSampleRateRatio() == 1.0) { // The ratio is the same, no need to convert.
      *(chunk.data()) = this->readBuffer;
    } else {
      this->srcData.data_out = chunk.data()->data();
      src_process(this->srcState, &this->srcData);
    }

    if (readCount > 0) {
      /*if (readCount < bufferSize) {
        buffer.resize(readCount*this->data.channels);
      }*/
      buffer.push(chunk); 
    }
    return readCount;
  }

  void AudioReader::seek(size_t frames, int whence) {
    sf_seek(this->file, frames, whence);
  }

  AudioData* AudioReader::getAudioData() {
    return &this->data;
  }

  double AudioReader::getSampleRateRatio() {
    return (double)this->deviceSampleRate / this->data.sampleRate;
  }

  void AudioReader::close() {
    sf_close(file);
    src_delete(srcState);
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