#include "WidgetAudioController.h"

#include <RmlUi/Core/Factory.h>

WidgetAudioController::WidgetAudioController(Rml::Element* element) {
  this->parent = element;

  this->trackBar = this->parent->AppendChild(
    Rml::Factory::InstanceElement(
      this->parent, 
      "input", 
      "range",
      Rml::XMLAttributes()
    ), false);

  this->seekLeft = this->parent->AppendChild(
    Rml::Factory::InstanceElement(
      this->parent,
      "*",
      "button",
      Rml::XMLAttributes()
    ), false);

  this->play = this->parent->AppendChild(
    Rml::Factory::InstanceElement(
      this->parent,
      "*",
      "button",
      Rml::XMLAttributes()
    ), false);

  this->seekRight = this->parent->AppendChild(
    Rml::Factory::InstanceElement(
      this->parent,
      "*",
      "button",
      Rml::XMLAttributes()
    ), false);

  this->play->SetAttribute("value", "hello world");
}

WidgetAudioController::~WidgetAudioController() {
  /*this->parent = nullptr;
  this->trackBar = nullptr;
  this->seekLeft = nullptr;
  this->play = nullptr;
  this->seekRight = nullptr;*/
}

void WidgetAudioController::ProcessEvent(Rml::Event& event) {

}