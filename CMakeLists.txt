# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)

project ("VibeTunes")

# Include sub-projects.
find_package(OpenGL REQUIRED)

add_subdirectory(libs/glfw-3.4)
add_subdirectory(libs/RmlUi/Backends)
add_subdirectory(libs/Catch2)

add_subdirectory("test")
add_subdirectory("src")

add_executable(${PROJECT_NAME}
	"src/main.cpp"
	"src/audio/AudioStream.cpp"
	"src/audio/SoundFileIO.cpp"
  "src/api/AudioManager.cpp"
  "src/api/Playlist.cpp"  
  "src/audio/AudioChunk.cpp" 
  "src/registry/AudioRegistry.cpp"

	"src/app/AppFileInterface.cpp"
  "src/app/App.cpp"
  "src/app/elements/AudioController.cpp"
  "src/crypt/md5.cpp"
  "src/registry/PlaylistRegistry.cpp" 
  "src/audio/stream/PortAudioStream.cpp" 
  "src/audio/backends/PortAudioBackend.cpp" 
  "src/audio/resampler/SRAudioResampler.cpp" 
  "src/audio/reader/SndlibAudioReader.cpp") # Define executable files


target_include_directories(${PROJECT_NAME}
  PRIVATE ${CMAKE_SOURCE_DIR}/libs/portaudio/include
  PRIVATE ${CMAKE_SOURCE_DIR}/libs/libsndfile/include
  PRIVATE ${CMAKE_SOURCE_DIR}/libs/libsamplerate/include
  PRIVATE ${CMAKE_SOURCE_DIR}/libs/glfw-3.4/include
  PRIVATE ${CMAKE_SOURCE_DIR}/libs/nlohmann/include

  PRIVATE ${CMAKE_SOURCE_DIR}/libs/RmlUi/Dependencies/include
  PRIVATE ${CMAKE_SOURCE_DIR}/libs/RmlUi/Include
  #PRIVATE ${CMAKE_SOURCE_DIR}/libs/lunasvg/include

  PRIVATE ${CMAKE_SOURCE_DIR}/include
  PRIVATE ${CMAKE_SOURCE_DIR}/include
  PRIVATE ${CMAKE_SOURCE_DIR}/include/api
  PRIVATE ${CMAKE_SOURCE_DIR}/include/api/buffers

  PRIVATE ${CMAKE_SOURCE_DIR}/include/app
  PRIVATE ${CMAKE_SOURCE_DIR}/include/app/elements

  PRIVATE ${CMAKE_SOURCE_DIR}/include/crypt
  PRIVATE ${CMAKE_SOURCE_DIR}/include/registry
) # Include header files

target_link_directories(${PROJECT_NAME} 
  PRIVATE ${CMAKE_SOURCE_DIR}/libs/portaudio/build/msvc/x64/Release

  PRIVATE ${CMAKE_SOURCE_DIR}/libs/RmlUi/Dependencies/lib/debug
  PRIVATE ${CMAKE_SOURCE_DIR}/libs/RmlUi/Lib/Debug

  PRIVATE ${CMAKE_SOURCE_DIR}/libs/libsndfile/lib
  PRIVATE ${CMAKE_SOURCE_DIR}/libs/libsamplerate/lib
  #PRIVATE ${CMAKE_SOURCE_DIR}/libs/lunasvg/lib
) # Define library directory


target_link_libraries(${PROJECT_NAME} 
  PRIVATE portaudio_x64 
  PRIVATE sndfile 
  PRIVATE samplerate
  PRIVATE glfw
  PRIVATE freetype
  PRIVATE lunasvg
  PRIVATE plutovg
  PRIVATE rmlui
  PRIVATE rmlui_debugger
  PRIVATE rmlui_backend_GLFW_GL3
) # Link library to executable

# Copy assets to build folder
file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR})