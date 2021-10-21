#include "rlang.h"
#include <stdlib.h> // for NULL
#include <stdbool.h>
#include <R_ext/Rdynload.h>
#include <R_ext/Visibility.h>

r_obj* ffi_rray_init_library(r_obj* ns) {
  r_init_library(ns);
  return r_null;
}

r_obj* ffi_rray_dimension_sizes(r_obj* x);

extern "C" {
static const R_CallMethodDef CallEntries[] = {
  {"ffi_rray_init_library", (DL_FUNC) &ffi_rray_init_library, 1},
  {"ffi_rray_dimension_sizes", (DL_FUNC) &ffi_rray_dimension_sizes, 1},
  {NULL, NULL, 0}
};

attribute_visible void R_init_rray3(DllInfo *dll) {
  R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
  R_useDynamicSymbols(dll, FALSE);
}
}
