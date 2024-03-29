
/*
 * Copyright (c) 2021-2024 Tini Software Limited
 * All rights reserved
 *
 */

#include <sstream>
#include <cstdio>
#include "memorymapped.h"

// OS-specific
#if defined(MEMMAPPED_USING_WINDOWS)
  // Windows
  #include <windows.h>
#else
  // Linux
  // enable large file support on 32 bit systems
  #ifndef _LARGEFILE64_SOURCE
    #define _LARGEFILE64_SOURCE
  #endif
  #ifdef  _FILE_OFFSET_BITS
    #undef  _FILE_OFFSET_BITS
  #endif
  #define _FILE_OFFSET_BITS 64
  #ifndef O_LARGEFILE
    #define O_LARGEFILE 0
  #endif
  // and include needed headers
  #include <sys/stat.h>
  #include <sys/mman.h>
  #include <fcntl.h>
  #include <errno.h>
  #include <unistd.h>
#endif

namespace MemoryMapped {
  File::File():
    m_filename   (),
    m_filesize   (0),
    m_hint       (Normal),
    m_handle     (0),
    m_mappedBytes(0),
    m_mappedView (nullptr),
    m_mappedFile (0) {
  }

  File::File(const std::string& filename, size_t mappedBytes, CacheHint hint):
    m_filename   (filename),
    m_filesize   (0),
    m_hint       (hint),
    m_handle     (0),
    m_mappedBytes(mappedBytes),
    m_mappedView (nullptr),
    m_mappedFile (0) {
    open(filename, mappedBytes, hint);
  }

  File::~File() {
    close();
  }

  bool File::open(const std::string& filename, size_t mappedBytes, CacheHint hint) {
    m_filename = filename;
    return openReal(mappedBytes, hint);
  }

  bool File::errOffset() {
    //  throw IOError(m_filename, "trying to read beyond file (offset > filesize)");
    return false;
  }

  unsigned char File::operator[](size_t offset) const {
    return data()[offset];
  }

  unsigned char File::at(size_t offset) const {
    // checks
    if(!m_mappedView) {
//            throw IOError(m_filename, "no view mapped");
    }
    if (offset >= m_filesize) {
//            throw IOError(m_filename, "mapped view is not large enough");
    }
    return operator[](offset);
  }

  const unsigned char* File::data() const {
    return (const unsigned char*)m_mappedView;
  }

  bool File::isValid() const {
    return (m_mappedView != nullptr);
  }

  uint64_t File::size() const {
    return m_filesize;
  }

  size_t File::mappedSize() const {
    return m_mappedBytes;
  }
}

