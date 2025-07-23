#include "../../../include/audio/resampler/SRAudioResampler.h"

namespace iamaprogrammer {
  SRAudioResampler::SRAudioResampler(void* readBuffer, double sampleRateConversionRatio, int channels, int readSize):
    sampleRateConversionRatio(sampleRateConversionRatio)
  {
    this->srcState = src_new(SRC_SINC_FASTEST, channels, &this->error);
    this->srcData.data_in = (float*)readBuffer;
    this->srcData.input_frames = readSize;
    this->srcData.output_frames = readSize * sampleRateConversionRatio;
    this->srcData.src_ratio = sampleRateConversionRatio;
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