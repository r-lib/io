#' Read the Contents of a File
#'
#' Read the contents of a file into a string (or, in the case of
#' \code{read_lines}, a vector of strings).
#'
#' @param path A file path.
#'
#' @name read
#' @rdname read
#' @export
read <- function(path) {
  path <- normalizePath(path, mustWork = TRUE)
  .Call(C_io_read, path)
}

#' @name read
#' @rdname read
#' @export
read_lines <- function(path) {
  path <- normalizePath(path, mustWork = TRUE)
  .Call(C_io_read_lines, path)
}

#' @name read
#' @rdname read
#' @export
read_bytes <- function(path) {
  path <- normalizePath(path, mustWork = TRUE)
  .Call(C_io_read_bytes, path)
}

#' @name read
#' @rdname read
#' @export
read_lines_bytes <- function(path) {
  path <- normalizePath(path, mustWork = TRUE)
  .Call(C_io_read_lines_bytes, path)
}

