add_library(crypt STATIC
  "md5.cpp"
)
target_include_directories(crypt PUBLIC ${CMAKE_SOURCE_DIR}/src/headers/crypt)