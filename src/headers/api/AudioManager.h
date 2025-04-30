#pragma once

#include <map>
#include <vector>

#include "Playlist.h"
#include "AudioStream.h"

namespace iamaprogrammer {
  class AudioManager {
  public:
    AudioManager();

    void addAudioToPlaylist(std::string playlist, std::string audio);
    void removeAudioFromPlaylist(std::string playlist, std::string audio);

    void addStream(std::string name);
    void removeStream();

    void loadPlaylists();
  private:
    std::map<std::string, Playlist> playlists;
    std::map<std::string, AudioStream> currentStreams;
    std::vector<std::string> library;
    Playlist* activePlaylist;
  };
}