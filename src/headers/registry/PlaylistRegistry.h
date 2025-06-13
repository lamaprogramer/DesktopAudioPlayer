#pragma once
#include <vector>

#include "Registry.h"
#include "Playlist.h"

namespace iamaprogrammer {
  class PlaylistRegistry: public Registry<Playlist> {
  public:
    /*void load(std::filesystem::path audioDirectory);

    const std::vector<Playlist> getSortedEntries(std::function<bool(const Playlist&, const Playlist&)> sorter);*/
  };
}