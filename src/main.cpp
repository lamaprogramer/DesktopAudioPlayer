#include <iostream>
#include <string>
#include <vector>

#include <portaudio.h>
#include <sndfile.h>
#include <algorithm>
#include <filesystem>

#define RMLUI_CUSTOM_RTTI
#include <RmlUi/Core.h>
#include <RmlUi/Debugger.h>
#include <RmlUi_Backend.h>

#include "SoundFileIO.h"
#include "AudioData.h"
#include "AudioStream.h"

#include "App.h"

bool processKeyDownShortcuts(Rml::Context* context, Rml::Input::KeyIdentifier key, int key_modifier, float native_dp_ratio, bool priority);

int main(int argc, char* argv[]) {
  PaError err;
  err = Pa_Initialize();
  if (err != paNoError) std::cout << Pa_GetErrorText(err) << std::endl;
  iamaprogrammer::AudioStream audio = iamaprogrammer::AudioStream(std::filesystem::current_path() / "resources\\library\\01 Spiritfarer.mp3");
  audio.setup();
  audio.start();
  Pa_Sleep(10000);
  audio.stop();
  audio.end();

  /*App app = App(1080, 540);
  app.init("VibeTunes");

	std::vector<App::FontFace> fontFaces{
		{ "fonts/LatoLatin-Regular.ttf", false },
		{ "fonts/LatoLatin-Italic.ttf", false },
		{ "fonts/LatoLatin-Bold.ttf", false },
		{ "fonts/LatoLatin-BoldItalic.ttf", false },
		{ "fonts/NotoEmoji-Regular.ttf", true },
	};

	app.initFonts(fontFaces);
  app.initDocument("app/demo.rml");


	bool running = true;
	while (running) {
		running = Backend::ProcessEvents(app.getContext(), &processKeyDownShortcuts, true);

		app.getContext()->Update();

		Backend::BeginFrame();
		app.getContext()->Render();
		Backend::PresentFrame();
	}

  app.shutdown();*/

  err = Pa_Terminate();
  if (err != paNoError) std::cout << Pa_GetErrorText(err) << std::endl;

  /*PaError err;
  err = Pa_Initialize();
  if (err != paNoError) std::cout << Pa_GetErrorText(err) << std::endl;

  iamaprogrammer::AudioStream audio = iamaprogrammer::AudioStream(std::filesystem::current_path() / "resources\\audio\\test.mp3");
  audio.setup();
  audio.start();
  Pa_Sleep(10000);
  audio.stop();
  Pa_Sleep(5000);
  audio.start();
  Pa_Sleep(10000);

  audio.end();;*/
  return 0;
}

bool processKeyDownShortcuts(Rml::Context* context, Rml::Input::KeyIdentifier key, int key_modifier, float native_dp_ratio, bool priority) {
	return true;
}