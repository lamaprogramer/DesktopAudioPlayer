#pragma once
#include <filesystem>
#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <functional>

#include "Registry.h"
#include "md5.h"

namespace iamaprogrammer {

  struct AudioFileData {
    std::string filename;
  };

  typedef std::pair<md5_hash, AudioFileData> AudioFileEntry;

  class AudioRegistry: public Registry<AudioFileEntry> {
  public:
    void write();
    void load(std::filesystem::path audioDirectory);

    const AudioFileEntry& getEntry(const md5_hash& hash);

    const std::vector<AudioFileEntry> getSortedEntries(std::function<bool(const AudioFileEntry&, const AudioFileEntry&)> sorter);

  private:
    static md5_hash hashFile(std::ifstream& audioFile);
  };
}