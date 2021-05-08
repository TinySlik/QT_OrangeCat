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

#include <windows.h>
#include "memorymapped.h"

#pragma once

namespace MemoryMapped {
  size_t GetPageSize()
  {
      SYSTEM_INFO sysInfo;
      GetSystemInfo(&sysInfo);
      return sysInfo.dwAllocationGranularity;
  }

  bool File::openReal(size_t mappedBytes, CacheHint hint) {
    DWORD winHint;
    // already open ?
    if(isValid()) {
      return false;
    }
    m_handle     = nullptr;
    m_filesize   = 0;
    m_hint       = hint;
    m_mappedFile = nullptr;
    m_mappedView = nullptr;
    winHint = 0;
    switch (m_hint) {
      case Normal:
          winHint = FILE_ATTRIBUTE_NORMAL;
          break;
      case SequentialScan:
          winHint = FILE_FLAG_SEQUENTIAL_SCAN;
          break;
      case RandomAccess:
          winHint = FILE_FLAG_RANDOM_ACCESS;
          break;
      default:
          break;
    }
    // open file
    m_handle = ::CreateFileA(
            m_filename.c_str(),
            GENERIC_READ, FILE_SHARE_READ, nullptr,
            OPEN_EXISTING, winHint, nullptr);
    if(!m_handle) {
// throw IOError(m_filename, "CreateFileA() failed");
      return false;
    }
    // file size
    LARGE_INTEGER result;
    if (!GetFileSizeEx(m_handle, &result)) {
// throw IOError(m_filename, "GetFileSizeEx() failed");
      return false;
    }
    m_filesize = static_cast<uint64_t>(result.QuadPart);
    // convert to mapped mode
    m_mappedFile = ::CreateFileMapping(m_handle, nullptr, PAGE_READONLY, 0, 0, nullptr);
    if (!m_mappedFile) {
// throw IOError(m_filename, "CreateFileMapping() failed");
      return false;
    }
    // initial mapping
    remap(0, mappedBytes);
    if (!m_mappedView) {
      // remap() may throw an exception already
      return false;
    }
    // everything's fine
    return true;
  }

  void File::close() {
    m_filesize = 0;
    // kill pointer
    if (m_mappedView) {
        ::UnmapViewOfFile(m_mappedView);
        m_mappedView = nullptr;
    }

    if(m_mappedFile) {
        ::CloseHandle(m_mappedFile);
        m_mappedFile = nullptr;
    }
    //close underlying file
    if(m_handle) {
        ::CloseHandle(m_handle);
        m_handle = 0;
    }
  }

  bool File::remap(uint64_t offset, size_t mappedBytes) {
    DWORD offsetLow;
    DWORD offsetHigh;
    if(!m_handle) {
// throw IOError(m_filename, "trying to operate on a closed handle");
      return false;
    }
    if (mappedBytes == WholeFile) {
      mappedBytes = m_filesize;
    }
    // close old mapping
    if(m_mappedView) {
      ::UnmapViewOfFile(m_mappedView);
      m_mappedView = nullptr;
    }
    // don't go further than end of file
    if(offset > m_filesize) {
      return errOffset();
    }
    if((offset + mappedBytes) > m_filesize) {
      mappedBytes = size_t(m_filesize - offset);
    }
    offsetLow  = DWORD(offset & 0xFFFFFFFF);
    offsetHigh = DWORD(offset >> 32);
    m_mappedBytes = mappedBytes;
    // get memory address
    m_mappedView = ::MapViewOfFile(m_mappedFile, FILE_MAP_READ, offsetHigh, offsetLow, mappedBytes);
    if(m_mappedView == nullptr) {
      m_mappedBytes = 0;
      m_mappedView  = nullptr;
//        throw IOError(m_filename, "MapViewOfFile() == NULL");
      return false;
    }
    return true;
  }
}
