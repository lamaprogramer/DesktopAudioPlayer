cmake_minimum_required(VERSION 4.0.0) # Define minimum CMake version
set(CMAKE_BUILD_TYPE Debug) # Define build type

project(Tunes) # Define Project Name

add_executable(${PROJECT_NAME}
  src/source/api/SoundFileReader.cpp
  src/main.cpp
) # Define executable file

target_include_directories(${PROJECT_NAME} 
  PRIVATE ${CMAKE_SOURCE_DIR}/libs/portaudio/include
  PRIVATE ${CMAKE_SOURCE_DIR}/libs/libsndfile/include

  PRIVATE ${CMAKE_SOURCE_DIR}/src/headers/api
  PRIVATE ${CMAKE_SOURCE_DIR}/src/headers/api/buffers
) # Include header files

target_link_directories(${PROJECT_NAME} 
  PRIVATE ${CMAKE_SOURCE_DIR}/libs/portaudio/build
  PRIVATE ${CMAKE_SOURCE_DIR}/libs/libsndfile/lib
) # Define library directory

target_link_libraries(${PROJECT_NAME} portaudio sndfile) # Link library to executable
