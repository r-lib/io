#ifndef IO_READ_WINDOWS_MEMORY_MAPPED_CONNECTION_H
#define IO_READ_WINDOWS_MEMORY_MAPPED_CONNECTION_H

#include <windows.h>

#include <cstdio>

namespace io {
namespace detail {

class MemoryMappedConnection
{
public:

  MemoryMappedConnection(HANDLE handle, std::size_t size)
    : map_(NULL), size_(size)
  {
    handle_ = ::CreateFileMapping(handle, NULL, PAGE_READONLY, 0, 0, NULL);
    if (handle_ == NULL)
      return;

    map_ = (char*) ::MapViewOfFile(handle_, FILE_MAP_READ, 0, 0, size);
  }

  ~MemoryMappedConnection()
  {
    if (map_ != NULL)
      ::UnmapViewOfFile(map_);

    if (handle_ != NULL)
      ::CloseHandle(handle_);
  }

  bool open()
  {
    return map_ != NULL;
  }

  operator char*() const
  {
    return map_;
  }

private:
  char* map_;
  std::size_t size_;
  HANDLE handle_;
};

} // namespace detail
} // namespace io

#endif /* IO_READ_WINDOWS_MEMORY_MAPPED_CONNECTION_H */
