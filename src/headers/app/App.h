#pragma once
#include <vector>
#include <iostream>
#include <string>

#define RMLUI_CUSTOM_RTTI
#include <RmlUi/Core.h>
#include <RmlUi/Debugger.h>
#include <RmlUi_Backend.h>

#include "AudioManager.h";
#include "AudioController.h"

class App {
public:
  struct FontFace {
    const char* filename;
    bool fallback_face;
  };

  App();
  App(int width, int height);

  void initFonts(const std::vector<FontFace>& fontFaces);
  void initDocument(const std::string documentPath);

  void init(std::string name);
  void shutdown();


  Rml::Context* getContext();

private:
  iamaprogrammer::AudioManager audioManager;
  Rml::Context* context;

  int width = 1080;
  int height = 540;
  bool resizable = true;
  bool debug = false;

  std::string assetsDir = "assets/";

  Rml::UniquePtr<Rml::ElementInstancerGeneric<AudioController>> instancer;
};