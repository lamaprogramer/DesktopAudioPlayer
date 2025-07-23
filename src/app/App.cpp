#include "App.h"

#include <RmlUi/Core/Factory.h>

App::App() {
  this->audioManager = iamaprogrammer::AudioManager();
}

App::App(int width, int height) {
  this->audioManager = iamaprogrammer::AudioManager();
  this->width = width;
  this->height = height;
}

void App::initFonts(const std::vector<FontFace>& fontFaces) {
  for (FontFace face : fontFaces) {
    std::cout << "Loading font: " << face.filename << std::endl;
    Rml::LoadFontFace(this->assetsDir + face.filename, face.fallback_face);
  }
}

void App::initDocument(const std::string documentPath) {
  if (Rml::ElementDocument* document = context->LoadDocument(this->assetsDir + documentPath)) {
    document->Show();
  }
    
}

void App::init(std::string name) {
  //std::cout << "RmlUi Template Tutorial" << std::endl;
  if (!Backend::Initialize("TemplateTutorial", this->width, this->height, this->resizable)) {
    std::cout << "Failed to initialize backend." << std::endl;
  }

  Rml::SetSystemInterface(Backend::GetSystemInterface());
  Rml::SetRenderInterface(Backend::GetRenderInterface());
  Rml::Initialise();

  this->instancer = Rml::MakeUnique<Rml::ElementInstancerGeneric<AudioController>>(); // TODO: Better handler for custom elements.
  Rml::Factory::RegisterElementInstancer("audiocontrol", this->instancer.get());

  this->context = Rml::CreateContext(name, Rml::Vector2i(this->width, this->height));
  if (!context) {
    Rml::Shutdown();
    Backend::Shutdown();

    std::cout << "Failed to create RmlUi context." << std::endl;
  }

  if (this->debug) {
    Rml::Debugger::Initialise(context);
    Rml::Debugger::SetVisible(true);
  }
}

void App::shutdown() {
  Rml::Shutdown();
  Backend::Shutdown();
}

Rml::Context* App::getContext() {
  return this->context;
}

// Private
