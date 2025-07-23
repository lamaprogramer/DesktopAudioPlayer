/*
 * This is an OpenSSL-compatible implementation of the RSA Data Security, Inc.
 * MD5 Message-Digest Algorithm (RFC 1321).
 *
 * Homepage:
 * http://openwall.info/wiki/people/solar/software/public-domain-source-code/md5
 *
 * Author:
 * Alexander Peslyak, better known as Solar Designer <solar at openwall.com>
 *
 * This software was written by Alexander Peslyak in 2001.  No copyright is
 * claimed, and the software is hereby placed in the public domain.
 * In case this attempt to disclaim copyright and place the software in the
 * public domain is deemed null and void, then the software is
 * Copyright (c) 2001 Alexander Peslyak and it is hereby released to the
 * general public under the following terms:
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted.
 *
 * There's ABSOLUTELY NO WARRANTY, express or implied.
 *
 * See md5.c for more information.
 */

#ifdef HAVE_OPENSSL
#include <openssl/md5.h>
#elif !defined(_MD5_H)
#define _MD5_H

#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>

/* Any 32-bit or wider unsigned integer data type will do */
typedef unsigned int MD5_u32plus;
//typedef unsigned char md5_hash[16]; // Added by Iamaprogrammer
typedef struct {
  MD5_u32plus lo, hi;
  MD5_u32plus a, b, c, d;
  unsigned char buffer[64];
  MD5_u32plus block[16];
} MD5_CTX;

class md5_hash {
public:
  md5_hash(MD5_u32plus a, MD5_u32plus b, MD5_u32plus c, MD5_u32plus d);

  md5_hash(const unsigned char data[16]);

  unsigned char operator[](int index) const {
    return hash[index];
  }

	bool operator==(const md5_hash &hash1) const {
    for (int i = 0; i < 16; i++) {
      if (hash[i] != hash1.hash[i]) {
        return false;
      }
    }
    return true;
	}

  bool operator!=(const md5_hash& hash1) const {
    for (int i = 0; i < 16; i++) {
      if (hash[i] == hash1.hash[i]) {
        return false;
      }
    }
    return true;
  }

  bool operator<(const md5_hash &hash1) const {
    for (int i = 0; i < 16; i++) {
      if (hash[i] < hash1.hash[i]) {
        return true;
      } else if (hash[i] > hash1.hash[i]) {
        return false;
      }
    }
    return false;
  }

  bool operator>(const md5_hash &hash1) const {
    for (int i = 0; i < 16; i++) {
      if (hash[i] > hash1.hash[i]) {
        return true;
      }
      else if (hash[i] < hash1.hash[i]) {
        return false;
      }
    }
    return false;
  }

  md5_hash operator=(const unsigned char data[16]) {
    for (int i = 0; i < 16; i++) {
      hash[i] = data[i];
    }
    return *this;
  }

  std::string to_string() const;
  static md5_hash from_string(const std::string& str);

  operator const unsigned char* () {
    return hash;
  }

private:
	unsigned char hash[16];
};


class md5_builder {
public:
  md5_builder();

  void update(const void* data, unsigned long size);
  md5_hash finalize();

private:
  MD5_CTX ctx;

  void* body(const void* data, unsigned long size);
};

namespace std {
  template <>
  struct hash<md5_hash> {
    std::size_t operator()(const md5_hash& k) const {
      return std::hash<std::string>()(k.to_string());
    }
  };
}

#endif
