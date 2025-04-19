# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)
#set(RMLUI_BACKEND GLFW_GL3)

project ("VibeTunes")

# Include sub-projects.
find_package(OpenGL REQUIRED)

add_subdirectory(libs/glfw-3.4)
add_subdirectory(libs/RmlUi/Backends)

add_executable(${PROJECT_NAME}
	src/main.cpp
	src/source/api/AudioStream.cpp
	src/source/api/SoundFileIO.cpp
	src/source/app/AppFileInterface.cpp
 "src/headers/app/App.h" "src/source/app/App.cpp"
) # Define executable files

target_include_directories(${PROJECT_NAME}
  PRIVATE ${CMAKE_SOURCE_DIR}/libs/portaudio/include
  PRIVATE ${CMAKE_SOURCE_DIR}/libs/libsndfile/include
  PRIVATE ${CMAKE_SOURCE_DIR}/libs/libsamplerate/include
  PRIVATE ${CMAKE_SOURCE_DIR}/libs/glfw-3.4/include
  PRIVATE ${CMAKE_SOURCE_DIR}/libs/RmlUi/Dependencies/Bin-Dynamic/include
  PRIVATE ${CMAKE_SOURCE_DIR}/libs/RmlUi/Include

  PRIVATE ${CMAKE_SOURCE_DIR}/src
  PRIVATE ${CMAKE_SOURCE_DIR}/src/headers
  PRIVATE ${CMAKE_SOURCE_DIR}/src/headers/api
  PRIVATE ${CMAKE_SOURCE_DIR}/src/headers/api/buffers

  PRIVATE ${CMAKE_SOURCE_DIR}/src/headers/app
) # Include header files

target_link_directories(${PROJECT_NAME} 
  PRIVATE ${CMAKE_SOURCE_DIR}/libs/portaudio/build/msvc/x64/Release
  PRIVATE ${CMAKE_SOURCE_DIR}/libs/RmlUi/Dependencies/Bin-Dynamic/lib
  PRIVATE ${CMAKE_SOURCE_DIR}/libs/RmlUi/Bin-Dynamic/Debug
  PRIVATE ${CMAKE_SOURCE_DIR}/libs/libsndfile/lib
  PRIVATE ${CMAKE_SOURCE_DIR}/libs/libsamplerate/lib
) # Define library directory


target_link_libraries(${PROJECT_NAME} 
  PRIVATE portaudio_x64 
  PRIVATE sndfile 
  PRIVATE samplerate
  PRIVATE glfw
  PRIVATE freetype
  PRIVATE rmlui
  PRIVATE rmlui_debugger
  PRIVATE rmlui_backend_GLFW_GL3
) # Link library to executable

# Copy assets to build folder
file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})
