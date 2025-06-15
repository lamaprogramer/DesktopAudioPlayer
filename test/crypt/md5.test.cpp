#include <catch2/catch_test_macros.hpp>
#include "md5.h"

const std::string STRING_HASH = "65a8e27d8879283831b664bd8b7f0ad4";
const unsigned char BYTE_HASH[16] = { 101, 168, 226, 125, 136, 121, 40, 56, 49, 182, 100, 189, 139, 127, 10, 212 };


TEST_CASE("BUILD MD5 HASH", "[md5]") {
  md5_builder builder;
  builder.update("Hello, World!", 13);
  md5_hash hash = builder.finalize();

  REQUIRE(hash == md5_hash(BYTE_HASH));
}

TEST_CASE("MD5 HASH TO STRING", "[md5]") {
  md5_hash hash = md5_hash(BYTE_HASH);
  REQUIRE(hash.to_string() == STRING_HASH);
}

TEST_CASE("MD5 HASH FROM STRING", "[md5]") {
  md5_hash hash = md5_hash::from_string(STRING_HASH);
  REQUIRE(hash == md5_hash(BYTE_HASH));
}

TEST_CASE("MD5 HASH COMPARISON - EQUALITY", "[md5]") {
  md5_hash hash1 = md5_hash::from_string(STRING_HASH);
  md5_hash hash2 = md5_hash::from_string(STRING_HASH);

  REQUIRE(hash1 == hash2);
  REQUIRE_FALSE(hash1 != hash2);
  REQUIRE_FALSE(hash1 < hash2);
  REQUIRE_FALSE(hash1 > hash2);
}