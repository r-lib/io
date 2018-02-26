#include <R.h>
#include <Rinternals.h>
#include <stdlib.h> // for NULL
#include <R_ext/Rdynload.h>

/* .Call calls */
extern SEXP io_read(SEXP);
extern SEXP io_read_bytes(SEXP);
extern SEXP io_read_lines(SEXP);
extern SEXP io_read_lines_bytes(SEXP);

static const R_CallMethodDef CallEntries[] = {
    {"io_read",             (DL_FUNC) &io_read,             1},
    {"io_read_bytes",       (DL_FUNC) &io_read_bytes,       1},
    {"io_read_lines",       (DL_FUNC) &io_read_lines,       1},
    {"io_read_lines_bytes", (DL_FUNC) &io_read_lines_bytes, 1},
    {NULL, NULL, 0}
};

void R_init_io(DllInfo *dll)
{
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
