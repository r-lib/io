#include <io/read/read.h>

#include <cstring>

#define R_NO_REMAP
#include <R.h>
#include <Rinternals.h>

extern "C" SEXP io_read(SEXP absolutePathSEXP)
{
  const char* absolutePath = CHAR(STRING_ELT(absolutePathSEXP, 0));

  std::string contents;
  bool result = io::read(absolutePath, &contents);
  if (!result)
  {
    Rf_warning("Failed to read file");
    return R_NilValue;
  }

  SEXP resultSEXP = PROTECT(Rf_allocVector(STRSXP, 1));
  SET_STRING_ELT(resultSEXP, 0, Rf_mkCharLen(contents.c_str(), contents.size()));
  UNPROTECT(1);
  return resultSEXP;
}

extern "C" SEXP io_read_lines(SEXP absolutePathSEXP)
{
  const char* absolutePath = CHAR(STRING_ELT(absolutePathSEXP, 0));

  std::vector<std::string> lines;
  bool result = io::read_lines(absolutePath, &lines);
  if (!result)
  {
    Rf_warning("Failed to read file");
    return R_NilValue;
  }

  int n = lines.size();
  SEXP resultSEXP = PROTECT(Rf_allocVector(STRSXP, n));
  for (int i = 0; i < n; ++i)
    SET_STRING_ELT(resultSEXP, i, Rf_mkCharLen(lines[i].c_str(), lines[i].size()));
  UNPROTECT(1);
  return resultSEXP;
}

extern "C" SEXP io_read_bytes(SEXP absolutePathSEXP)
{
  const char* absolutePath = CHAR(STRING_ELT(absolutePathSEXP, 0));

  std::string contents;
  bool result = io::read(absolutePath, &contents);
  if (!result)
  {
    Rf_warning("Failed to read file");
    return R_NilValue;
  }

  SEXP resultSEXP = PROTECT(Rf_allocVector(RAWSXP, contents.size()));
  std::memcpy(RAW(resultSEXP), contents.c_str(), contents.size());
  UNPROTECT(1);
  return resultSEXP;
}

extern "C" SEXP io_read_lines_bytes(SEXP absolutePathSEXP)
{
  const char* absolutePath = CHAR(STRING_ELT(absolutePathSEXP, 0));

  std::vector<std::string> lines;
  bool result = io::read_lines(absolutePath, &lines);
  if (!result)
  {
    Rf_warning("Failed to read file");
    return R_NilValue;
  }

  int n = lines.size();
  SEXP resultSEXP = PROTECT(Rf_allocVector(VECSXP, n));
  for (int i = 0; i < n; ++i)
  {
    SEXP rawSEXP = Rf_allocVector(RAWSXP, lines[i].size());
    std::memcpy(RAW(rawSEXP), lines[i].c_str(), lines[i].size());
    SET_VECTOR_ELT(resultSEXP, i, rawSEXP);
  }
  UNPROTECT(1);
  return resultSEXP;
}
