add_library(audio STATIC
  "AudioStream.cpp"
  "SoundFileIO.cpp"
  "AudioChunk.cpp"
)
target_include_directories(audio PUBLIC ${CMAKE_SOURCE_DIR}/src/headers/audio)

target_include_directories(audio
  PRIVATE ${CMAKE_SOURCE_DIR}/libs/portaudio/include
  PRIVATE ${CMAKE_SOURCE_DIR}/libs/libsamplerate/include
  PRIVATE ${CMAKE_SOURCE_DIR}/libs/libsndfile/include
)

target_link_directories(audio 
  PRIVATE ${CMAKE_SOURCE_DIR}/libs/portaudio/build/msvc/x64/Release
  PRIVATE ${CMAKE_SOURCE_DIR}/libs/libsamplerate/lib
  PRIVATE ${CMAKE_SOURCE_DIR}/libs/libsndfile/lib
)

target_link_libraries(audio 
  PRIVATE portaudio_x64 
  PRIVATE sndfile 
  PRIVATE samplerate
)
