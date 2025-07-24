add_library(logger STATIC
  "Logger.cpp" "Colors.cpp" "LogInfoComponents.cpp")

target_include_directories(logger PUBLIC ${CMAKE_SOURCE_DIR}/include/logger)
#target_include_directories(audio PUBLIC ${CMAKE_SOURCE_DIR}/include/audio/stream)
