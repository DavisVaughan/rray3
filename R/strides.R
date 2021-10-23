rray_strides <- function(x) {
  .Call(ffi_rray_strides, x)
}

rray_backstrides <- function(x) {
  .Call(ffi_rray_backstrides, x)
}
