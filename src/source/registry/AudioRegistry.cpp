#include "AudioRegistry.h"


namespace iamaprogrammer {

  void AudioRegistry::load(std::filesystem::path audioDirectory) {
    if (!std::filesystem::exists(audioDirectory)) {
      std::cout << "Audio directory does not exist: " << audioDirectory << std::endl;
      return;
    }

    std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
    for (const std::filesystem::path file : std::filesystem::directory_iterator(audioDirectory)) {
      std::ifstream audioFile(file);

      if (audioFile.is_open()) {
        //std::filesystem::last_write_time(file);

        md5_hash hash = AudioRegistry::hashFile(audioFile);
        audioFile.close();

        // Add file entry.
        AudioFileData entry;
        entry.filename = file.filename().string();

        AudioRegistry::entries.push_back({hash, entry});
      }
    }

    std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
    std::cout << "Finished in: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << std::endl;

    /*std::cout << AudioRegistry::entries.size() << " audio files loaded." << std::endl;
    for (const auto& entry : AudioRegistry::entries) {
      std::cout << "File: " << entry.second.filename << " Hash: ";
      std::cout << entry.first.to_string() << std::endl;
    }*/
  }

  const AudioFileEntry& AudioRegistry::getEntry(const md5_hash& hash) {
    auto it = std::find_if(
      entries.begin(), 
      entries.end(),
      [&hash](const AudioFileEntry& entry) { 
        return entry.first == hash; 
      });  

    if (it != entries.end()) {
      return *it;
    }

    return *it;
  }

  const std::vector<AudioFileEntry> AudioRegistry::getSortedEntries(std::function<bool(const AudioFileEntry&, const AudioFileEntry&)> sorter) {
    std::vector<std::pair<md5_hash, AudioFileData>> entriesCopy = entries;
    std::sort(entriesCopy.begin(), entriesCopy.end(), sorter);

    return entriesCopy;
  }

  md5_hash AudioRegistry::hashFile(std::ifstream& audioFile) {
    std::vector<char> buffer(56);
    md5_builder builder;

    while (audioFile.read(buffer.data(), 56) || audioFile.gcount() > 0) {
      builder.update(buffer.data(), buffer.size());
    }

    return builder.finalize();
  }
}