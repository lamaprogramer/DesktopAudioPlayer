#include "Playlist.h"

namespace iamaprogrammer {
  Playlist::Playlist() {

  }

  Playlist::Playlist(std::string name) {
    this->name = name;
  }

  void Playlist::add(std::string name) {
    this->audio.push_back(name);
  }

  void Playlist::remove(std::string name) {
    this->audio.erase(std::find(this->audio.begin(), this->audio.end(), name));
  }

  void Playlist::writeTo(std::filesystem::path filePath) {

  }

  Playlist Playlist::loadFrom(std::filesystem::path filePath) {
    return Playlist();
  }
}