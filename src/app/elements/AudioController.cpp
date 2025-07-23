#include "AudioController.h"

#include <iostream>
#include <filesystem>
#include <RmlUi/Core/Factory.h>
#include <RmlUi/Core/ElementDocument.h>
#include <RmlUi/Core/SystemInterface.h>
#include <RmlUi/SVG/ElementSVG.h>
#include <RmlUi/Core/ElementUtilities.h>

AudioController::AudioController(const Rml::String& tag) : Element(tag) {

  Rml::XMLAttributes trackBarAttributes;
  trackBarAttributes["type"] = "range";
  trackBarAttributes["min"] = 0;
  trackBarAttributes["value"] = 0;
  trackBarAttributes["max"] = 0;

  Rml::XMLAttributes seekLeftIconAttributes;
  seekLeftIconAttributes["src"] = "../icons/media/backward-step-solid.svg";

  Rml::XMLAttributes playIconAttributes;
  playIconAttributes["src"] = this->STATES[this->activeState].playIcon;

  Rml::XMLAttributes seekRightIconAttributes;
  seekRightIconAttributes["src"] = "../icons/media/forward-step-solid.svg";

  this->trackBar = this->AppendChild(
    Rml::Factory::InstanceElement(
      this,
      "input",
      "trackbar",
      trackBarAttributes
    ), false);

  this->seekLeft = this->AppendChild(
    Rml::Factory::InstanceElement(
      this,
      "svg",
      "seekleft",
      seekLeftIconAttributes
    ), false);

  this->play = this->AppendChild(
    Rml::Factory::InstanceElement(
      this,
      "svg",
      "play",
      playIconAttributes
    ), false);

  this->seekRight = this->AppendChild(
    Rml::Factory::InstanceElement(
      this,
      "svg",
      "seekright",
      seekRightIconAttributes
    ), false);


  this->AddEventListener(Rml::EventId::Click, this, false);
}

AudioController::~AudioController() {
  this->RemoveEventListener(Rml::EventId::Click, this, true);
}

bool AudioController::GetIntrinsicDimensions(Rml::Vector2f& dimensions, float& ratio) {
  dimensions = Rml::Vector2f{ 300, 50 };

  if (HasAttribute("width")) {
    dimensions.x = GetAttribute<float>("width", -1);
  }

  if (HasAttribute("height")) {
    dimensions.y = GetAttribute<float>("height", -1);
  }

  if (HasAttribute("duration")) {
    this->trackBar->SetAttribute("max", GetAttribute<int>("duration", 0));
  }

 /* if (HasAttribute("src")) {
    this->stream = new iamaprogrammer::AudioStream(this->GetAttribute<std::string>("src", ""));
    std::cout << "set src" << std::endl;
  }*/

  if (dimensions.y > 0) {
    ratio = dimensions.x / dimensions.y;
  }



  rmlui_dynamic_cast<Rml::ElementSVG*>(this->seekLeft)->EnsureSourceLoaded();
  rmlui_dynamic_cast<Rml::ElementSVG*>(this->play)->EnsureSourceLoaded();
  rmlui_dynamic_cast<Rml::ElementSVG*>(this->seekRight)->EnsureSourceLoaded();
  
  this->ResizeElements(dimensions);

  return true;
}

void AudioController::OnRender() {
  if (this->stateDirty) {
    this->SetState();
    this->stateDirty = false;
  }
}

void AudioController::OnResize() {
  Rml::Vector2f size = this->GetBox().GetSize();
  this->ResizeElements(size);
}

void AudioController::OnAttributeChange(const Rml::ElementAttributes& changed_attributes) {
  if (changed_attributes.find("src") != changed_attributes.end()) {
    //this->stream = new iamaprogrammer::AudioStream(this->GetAttribute<std::string>("src", ""));
    std::cout << "set src" << std::endl;
  }
}

void AudioController::SetStream(iamaprogrammer::AudioStream* stream) {
  this->stream = stream;
}

void AudioController::ProcessEvent(Rml::Event& event) {
  switch (event.GetId()) {
    case Rml::EventId::Click: {
      if (this->stream == nullptr) {
        break;
      }

      if (event.GetTargetElement() == this->play) {
        this->activeState = (this->activeState + 1) % 2;
        this->stateDirty = true;
      }

    } break;
  }
}

void AudioController::ResizeElements(Rml::Vector2f size) {
  Rml::Vector2f trackBarDimensions{ size.x, size.y / 4 };
  Rml::Vector2f controlDimensions{ std::min(size.x / 2, size.y / 2), std::min(size.x / 2, size.y / 2) };

  float seekLeftRatio = this->GetElementRatio(this->seekLeft);
  float playRatio = this->GetElementRatio(this->play);
  float seekRightRatio = this->GetElementRatio(this->seekRight);

  Rml::Box seekLeftBox = this->CreateButtonBox(controlDimensions, seekLeftRatio);
  Rml::Box playBox = this->CreateButtonBox(controlDimensions, playRatio);
  Rml::Box seekRightBox = this->CreateButtonBox(controlDimensions, seekRightRatio);

  float seekLeftWidth = seekLeftBox.GetSizeAcross(Rml::BoxDirection::Horizontal, Rml::BoxArea::Padding);
  float playWidth = playBox.GetSizeAcross(Rml::BoxDirection::Horizontal, Rml::BoxArea::Padding);
  float seekRightWidth = seekRightBox.GetSizeAcross(Rml::BoxDirection::Horizontal, Rml::BoxArea::Padding);

  this->trackBar->SetBox(Rml::Box{ trackBarDimensions });
  this->seekLeft->SetBox(seekLeftBox);
  this->play->SetBox(playBox);
  this->seekRight->SetBox(seekRightBox);

  this->seekLeft->SetOffset({ ((size.x - seekLeftWidth) / 2) - seekLeftWidth - 50, trackBarDimensions.y * 2}, this, false);
  this->play->SetOffset({ (size.x - playWidth) / 2, trackBarDimensions.y * 2}, this, false);
  this->seekRight->SetOffset({ ((size.x - seekRightWidth) / 2) + seekRightWidth + 50, trackBarDimensions.y * 2 }, this, false);
}

void AudioController::SetState() {
  this->play->SetAttribute("src", this->STATES[this->activeState].playIcon);


  if (this->stream->getStreamState() == iamaprogrammer::AudioStream::StreamState::CLOSED) {
    std::cout << "setting up" << std::endl;
    this->stream->setup();
  }

  if (this->STATES[this->activeState].playing) {
    this->stream->start();
  }
  else {
    this->stream->stop();
  }
}

float AudioController::GetElementRatio(Rml::Element* element) {
  Rml::Vector2f dimensions{};
  float ratio = 0.0f;
  element->GetIntrinsicDimensions(dimensions, ratio);
  return ratio;
}

Rml::Box AudioController::CreateButtonBox(Rml::Vector2f initialDimensions, float ratio) {
  Rml::Box b{ {initialDimensions.x * ratio, initialDimensions.y} };
  b.SetEdge(Rml::BoxArea::Padding, Rml::BoxEdge::Left, (initialDimensions.x - b.GetSize().x) / 2);
  b.SetEdge(Rml::BoxArea::Padding, Rml::BoxEdge::Right, (initialDimensions.x - b.GetSize().x) / 2);
  b.SetEdge(Rml::BoxArea::Padding, Rml::BoxEdge::Top, (initialDimensions.y - b.GetSize().y) / 2);
  b.SetEdge(Rml::BoxArea::Padding, Rml::BoxEdge::Bottom, (initialDimensions.y - b.GetSize().y) / 2);

  return b;
}