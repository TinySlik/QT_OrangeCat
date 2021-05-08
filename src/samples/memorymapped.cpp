/** Copyright 2021 Tiny Oh, Ltd. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
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
    m_handle     (nullptr),
    m_mappedBytes(0),
    m_mappedView (nullptr),
    m_mappedFile (nullptr) {
  }

  File::File(const std::string& filename, size_t mappedBytes, CacheHint hint):
    m_filename   (filename),
    m_filesize   (0),
    m_hint       (hint),
    m_handle     (nullptr),
    m_mappedBytes(mappedBytes),
    m_mappedView (nullptr),
    m_mappedFile (nullptr) {
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

//#if defined(MEMMAPPED_USING_WINDOWS)
//    #include "impl.win32.cpp"
//#else
//    #include "impl.linux.cpp"
//#endif
