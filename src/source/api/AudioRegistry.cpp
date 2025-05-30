#include "AudioRegistry.h"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <chrono>

#include "md5.h"

namespace iamaprogrammer {
  std::vector<AudioEntry> AudioRegistry::entries;

  void AudioRegistry::load(std::filesystem::path audioDirectory) {
    if (!std::filesystem::exists(audioDirectory)) {
      std::cout << "Audio directory does not exist: " << audioDirectory << std::endl;
      return;
    }

    std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
    for (const std::filesystem::path file : std::filesystem::directory_iterator(audioDirectory)) {
      std::ifstream audioFile(file);

      AudioEntry entry;
      entry.filename = file.filename().string();

      if (audioFile.is_open()) {
        std::vector<char> buffer(56);
        MD5_CTX md5Context;
        MD5_Init(&md5Context);

        while (audioFile.read(buffer.data(), 56) || audioFile.gcount() > 0) {
          MD5_Update(&md5Context, buffer.data(), buffer.size());
        }

        MD5_Final(entry.hash, &md5Context);
        audioFile.close();

        AudioRegistry::entries.push_back(entry);
      }


      /*std::cout << "MD5 of: ";
      MDPrint(entry.hash);
      std::cout << " for file: " << file.filename() << std::endl;*/
    }

    std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
    std::cout << "Finished in: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << std::endl;

    for (const AudioEntry& entry : AudioRegistry::entries) {
      std::cout << "File: " << entry.filename << " Hash: ";
      MDPrint(entry.hash);
      std::cout << std::endl;
    }
  }

  void AudioRegistry::MDPrint(const unsigned char digest[16]) {
    unsigned int i;
    for (i = 0; i < 16; i++)
      printf("%02x", digest[i]);
  }
}