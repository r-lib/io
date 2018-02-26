#ifndef IO_READ_WINDOWS_FILE_CONNECTION_H
#define IO_READ_WINDOWS_FILE_CONNECTION_H

#ifdef Realloc
# undef Realloc
#endif

#ifdef Free
# undef Free
#endif

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#ifdef ERROR
# undef ERROR
#endif

#include <cstdio>

namespace io {
namespace detail {

class FileConnection
{
public:
  typedef HANDLE FileDescriptor;

  FileConnection(const char* path, int flags = GENERIC_READ)
  {
    handle_ = ::CreateFile(path, flags, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
  }

  ~FileConnection()
  {
    if (open())
      ::CloseHandle(handle_);
  }

  bool open()
  {
    return handle_ != INVALID_HANDLE_VALUE;
  }

  bool size(std::size_t* pSize)
  {
    LARGE_INTEGER size;
    bool status = ::GetFileSizeEx(handle_, &size);
    if (status)
      *pSize = size.QuadPart;
    return status;
  }

  operator FileDescriptor() const
  {
    return handle_;
  }

private:
  FileDescriptor handle_;
};

} // namespace detail
} // namespace io

#endif /* IO_READ_WINDOWS_FILE_CONNECTION_H */
