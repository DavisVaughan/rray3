rray_broadcast <- function(x, dimension_sizes) {
  .Call(ffi_rray_broadcast, x, dimension_sizes)
}
