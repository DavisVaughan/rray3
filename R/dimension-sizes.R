rray_dimension_sizes <- function(x) {
  .Call(ffi_rray_dimension_sizes, x)
}

rray_dimensionality <- function(x) {
  .Call(ffi_rray_dimensionality, x)
}
