#include "Playlist.h"
#include <algorithm>

namespace iamaprogrammer {
  Playlist::Playlist() {

  }

  Playlist::Playlist(std::string name) {
    this->name = name;
  }

  Playlist::Playlist(std::vector<md5_hash> audio, std::string name) {
    this->audio = audio;
    this->name = name;
  }

  void Playlist::add(md5_hash fileHash) {
    this->audio.push_back(fileHash);
  }

  void Playlist::remove(const md5_hash fileHash) {
    this->audio.erase(std::find(this->audio.begin(), this->audio.end(), fileHash));
  }

  Playlist Playlist::load(std::filesystem::path filePath) {
    std::filesystem::path filename = filePath.filename().stem();
    //std::cout << this->playlistDir / filename << std::endl;

    if (!std::filesystem::exists(filePath)) {
      std::cout << "Playlist file does not exist. Creating new playlist." << std::endl;
      std::filesystem::create_directories(filePath.parent_path());

      std::ofstream file(filePath);
      if (file.is_open()) {
        file.close();
      }

      return Playlist(filename.string());
    }

    // Read the playlist file
    std::ifstream file(filePath);
    std::vector<md5_hash> audioFiles;

    if (file.is_open()) {
      std::string line;
      long readLines = 0;

      while (std::getline(file, line)) {
        if (line.empty()) continue; // Skip empty lines

        //audioFiles.push_back(line);
        readLines++;
      }
      file.close();
    }

    return Playlist(audioFiles, filename.string());
  }
}