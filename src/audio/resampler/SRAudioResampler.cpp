#include "../../../include/audio/resampler/SRAudioResampler.h"

namespace iamaprogrammer {
  SRAudioResampler::SRAudioResampler(IAudioReader* reader, double deviceSampleRate) {

    AudioFileDescriptor* fileDescriptor = reader->getAudioFileDescriptor();
    int readSize = reader->getReadSize();
    this->sampleRateConversionRatio = deviceSampleRate / fileDescriptor->sampleRate;

    this->srcState = src_new(SRC_SINC_FASTEST, fileDescriptor->channels, &this->error);
    this->srcData.data_in = (float*)reader->getReadBuffer();
    this->srcData.input_frames = readSize;
    this->srcData.output_frames = readSize * this->sampleRateConversionRatio;
    this->srcData.src_ratio = this->sampleRateConversionRatio;
    this->srcData.end_of_input = 0;
  }

  void SRAudioResampler::resample(void* buffer) {
    this->srcData.data_out = (float*)buffer;
    src_process(this->srcState, &this->srcData);
  }

  void SRAudioResampler::close() {
    src_delete(this->srcState);
  }

  double SRAudioResampler::getSampleRateConversionRatio() {
    return this->sampleRateConversionRatio;
  }
}