#pragma once

#include <RmlUi/Core/EventListener.h>
#include <RmlUi/Core/Element.h>

class WidgetAudioController : public Rml::EventListener {
public:
  WidgetAudioController(Rml::Element* element);
  virtual ~WidgetAudioController();

  void ProcessEvent(Rml::Event& event) override;

private:
  Rml::Element* parent;

  Rml::Element* trackBar;
  Rml::Element* seekLeft;
  Rml::Element* play;
  Rml::Element* seekRight;
};