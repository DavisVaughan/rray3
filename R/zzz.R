rray_init_library <- function(ns) {
  .Call(ffi_rray_init_library, ns)
}

.onLoad <- function(libname, pkgname) {
  rray_init_library(ns_env())
}
