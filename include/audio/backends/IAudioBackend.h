#pragma once
#include <memory>
#include "../stream/IBasicAudioStream.h"
#include "../AudioDevice.h"

namespace iamaprogrammer {
  typedef std::unique_ptr<IBasicAudioStream> AudioStreamPtr;

  class IAudioBackend {
  public:
    virtual void initialize() = 0;
    virtual void terminate() = 0;

    virtual AudioDevice getDefaultAudioDevice() = 0;
    virtual AudioDevice getAudioDevice(int id) = 0;
  };
}