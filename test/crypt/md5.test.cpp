#include <catch2/catch_test_macros.hpp>
#include "md5.h"



TEST_CASE("BUILD MD5 HASH", "[md5]") {
  md5_builder builder;
  builder.update("Hello, World!", 13);
  md5_hash hash = builder.finalize();

  REQUIRE(hash.to_string() == "65a8e27d8879283831b664bd8b7f0ad4");
}

TEST_CASE("MD5 HASH COMPARISON", "[md5]") {
  md5_hash hash1 = md5_hash::from_string("65a8e27d8879283831b664bd8b7f0ad4");
  md5_hash hash2 = md5_hash::from_string("65a8e27d8879283831b664bd8b7f0ad4");

  REQUIRE(hash1 == hash2);
  REQUIRE_FALSE(hash1 != hash2);
  REQUIRE_FALSE(hash1 < hash2);
  REQUIRE_FALSE(hash1 > hash2);
}