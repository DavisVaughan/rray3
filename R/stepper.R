rray_test_iterate <- function(x, dimension_sizes) {
  .Call(ffi_rray_test_iterate, x, dimension_sizes)
}
