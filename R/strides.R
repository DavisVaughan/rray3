rray_strides <- function(x, ..., broadcastable = TRUE) {
  check_dots_empty0(...)
  .Call(ffi_rray_strides, x, broadcastable)
}
