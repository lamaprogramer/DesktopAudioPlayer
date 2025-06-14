add_executable(tests "crypt/md5.test.cpp")

target_link_libraries(tests PRIVATE crypt Catch2::Catch2WithMain)

include(CTest)
include(Catch)

catch_discover_tests(tests)