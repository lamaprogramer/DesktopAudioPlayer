add_library(audio STATIC
  "AudioStream.cpp"
  
  "AudioChunk.cpp"
  "stream/PortAudioStream.cpp" 
  "backends/PortAudioBackend.cpp" 
  "resampler/SRAudioResampler.cpp" 
  "reader/SndlibAudioReader.cpp")

target_include_directories(audio PUBLIC ${CMAKE_SOURCE_DIR}/include/audio)
#target_include_directories(audio PUBLIC ${CMAKE_SOURCE_DIR}/include/audio/stream)

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
