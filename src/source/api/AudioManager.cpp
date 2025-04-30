#include "AudioManager.h"

namespace iamaprogrammer {
  AudioManager::AudioManager() {

  }

  void AudioManager::addAudioToPlaylist(std::string playlist, std::string audio) {
    this->playlists[playlist].add(audio);
  }

  void AudioManager::removeAudioFromPlaylist(std::string playlist, std::string audio) {
    this->playlists[playlist].remove(audio);
  }

  void addStream(std::string name) {

  }

  void removeStream() {

  }
}