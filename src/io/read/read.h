#ifndef IO_READ_READ_H
#define IO_READ_READ_H

#include <vector>
#include <string>

#include "MemoryMappedReader.h"

namespace io {

inline bool read(const std::string& absolutePath, std::string* pContent)
{
  return detail::MemoryMappedReader::read(absolutePath.c_str(), pContent);
}

inline bool read_lines(const std::string& absolutePath,
                       std::vector<std::string>* pLines)
{
  return detail::MemoryMappedReader::read_lines(absolutePath.c_str(), pLines);
}

}  // namespace io

#endif /* IO_READ_READ_H */
