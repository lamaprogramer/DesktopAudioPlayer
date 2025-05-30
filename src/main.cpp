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
#include "AudioRegistry.h"
#include "Playlist.h"

#include "App.h"

#include "md5.h"

bool processKeyDownShortcuts(Rml::Context* context, Rml::Input::KeyIdentifier key, int key_modifier, float native_dp_ratio, bool priority);

int main(int argc, char* argv[]) {

  iamaprogrammer::AudioRegistry::load("resources/library");
  /*MD5_CTX md5Context;
  unsigned char result[16];

  MD5_Init(&md5Context);
  MD5_Update(&md5Context, "Hello, World!", 13);
  MD5_Final(result, &md5Context);

  MDPrint(result);*/
	
  //iamaprogrammer::Playlist playlist = iamaprogrammer::Playlist::load("resources/playlists/test.txt");

	

  /*PaError err;
  err = Pa_Initialize();
  if (err != paNoError) std::cout << Pa_GetErrorText(err) << std::endl;

  iamaprogrammer::AudioStream audio = iamaprogrammer::AudioStream(std::filesystem::current_path() / "resources\\library\\01 Spiritfarer.mp3");
  audio.setup();
  audio.start();
  Pa_Sleep(10000);
  audio.seek(-3);
  Pa_Sleep(10000);
  audio.stop();
  audio.end();

	err = Pa_Terminate();
	if (err != paNoError) std::cout << Pa_GetErrorText(err) << std::endl;*/


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
  return 0;
}

bool processKeyDownShortcuts(Rml::Context* context, Rml::Input::KeyIdentifier key, int key_modifier, float native_dp_ratio, bool priority) {
	return true;
}