#pragma once
#include "IAudioBackend.h"
#include "../stream/PortAudioStream.h"
#include "../AudioDevice.h"
#include <portaudio.h>
#include <memory>

namespace iamaprogrammer {
  class PortAudioBackend : public IAudioBackend {
  public:
    PortAudioBackend();

    void initialize() override;
    void terminate() override;

    AudioDevice getDefaultAudioDevice() override;
    AudioDevice getAudioDevice(int id) override;
  private:
    PaError error;
  };
}