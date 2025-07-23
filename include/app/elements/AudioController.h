#pragma once

#define RMLUI_CUSTOM_RTTI
#include <string>
#include <RmlUi/Core/EventListener.h>
#include <RmlUi/Core/Element.h>

#include <audio/AudioStream.h>

class AudioController : public Rml::Element, public Rml::EventListener {
public:
  //RMLUI_RTTI_DefineWithParent(AudioController, Element)

  AudioController(const Rml::String& tag);
  virtual ~AudioController();

  bool GetIntrinsicDimensions(Rml::Vector2f& dimensions, float& ratio) override;

protected:
  void OnRender() override;

  void OnResize() override;

  void OnAttributeChange(const Rml::ElementAttributes& changed_attributes) override;

  void ProcessEvent(Rml::Event& event) override;


  void SetStream(iamaprogrammer::AudioStream* stream);

private:
  struct State {
    std::string playIcon = "";
    bool playing = false;
  };

  iamaprogrammer::AudioStream* stream;

  Rml::Element* trackBar;
  Rml::Element* seekLeft;
  Rml::Element* play;
  Rml::Element* seekRight;

  Rml::Element* seekLeftIcon;
  Rml::Element* playIcon;
  Rml::Element* seekRightIcon;
  
  const State STATES[2] = {
    {
      "../icons/media/play-solid.svg",
      false
    }, 
    {
      "../icons/media/pause-solid.svg",
      true
    }
  };
  int activeState = 0;
  bool stateDirty = false;

  void SetState();

  void ResizeElements(Rml::Vector2f size);

  float GetElementRatio(Rml::Element* element);
  Rml::Box CreateButtonBox(Rml::Vector2f initialDimensions, float ratio);
};