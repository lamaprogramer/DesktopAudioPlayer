#pragma once
#include "IAudioResampler.h"
#include "../reader/IAudioReader.h"
#include <samplerate.h>

namespace iamaprogrammer {
  class SRAudioResampler: public IAudioResampler {
  public:
    SRAudioResampler(IAudioReader* reader, double deviceSampleRate);

    void resample(void* writeBuffer) override;
    double getSampleRateConversionRatio() override;
    void close() override;

  private:
    SRC_STATE* srcState; // Samplerate Converter state
    SRC_DATA srcData; // Samplerate Converter data

    double sampleRateConversionRatio;
    int error = 0;
  };
}