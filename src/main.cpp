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

#include <crypt/md5.h>
#include <audio/AudioFileDescriptor.h>
#include <audio/AudioStream.h>
#include <audio/resampler/SRAudioResampler.h>
#include <audio/reader/SndlibAudioReader.h>
#include <audio/stream/PortAudioStream.h>
#include <audio/backends/PortAudioBackend.h>

#include "AudioRegistry.h"
#include "Playlist.h"

#include "App.h"

bool processKeyDownShortcuts(Rml::Context* context, Rml::Input::KeyIdentifier key, int key_modifier, float native_dp_ratio, bool priority);

int main(int argc, char* argv[]) {
  iamaprogrammer::AudioRegistry audioRegistry;
  audioRegistry.load("resources/library");

  const std::vector<iamaprogrammer::AudioFileEntry> sortedEntries = audioRegistry.getSortedEntries(
    [](const iamaprogrammer::AudioFileEntry& a, const iamaprogrammer::AudioFileEntry& b) {
      return a.second.filename > b.second.filename; // Sort by hash
    }
  );

  for (const auto& entry : sortedEntries) {
    std::cout << "File: " << entry.second.filename << " Hash: ";
    std::cout << entry.first.to_string() << std::endl;
  }

  iamaprogrammer::PortAudioBackend backend;
  backend.initialize();

  iamaprogrammer::SndlibAudioReader reader(std::filesystem::current_path() / "resources" / "library" / "01 Spiritfarer.mp3", 1024);
  iamaprogrammer::SRAudioResampler resampler(&reader, backend.getDefaultAudioDevice().samplerate, 1024);
  iamaprogrammer::PortAudioStream basicStream = iamaprogrammer::PortAudioStream();

  iamaprogrammer::AudioStream advancedStream = iamaprogrammer::AudioStream(&reader, &resampler, &basicStream);

  advancedStream.setup();
  advancedStream.start();
  Pa_Sleep(10000);
  advancedStream.seek(-3);
  Pa_Sleep(10000);
  advancedStream.stop();
  advancedStream.end();

  reader.close();
  resampler.close();
  backend.terminate();



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