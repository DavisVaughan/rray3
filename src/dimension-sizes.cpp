#include "dimension-sizes.h"

r_obj* ffi_rray_dimension_sizes(r_obj* x) {
  return rray::dimension_sizes_compute(x);
}

r_obj* ffi_rray_dimensionality(r_obj* x) {
  r_ssize dimensionality = rray::dimensionality_compute(x);
  return r_int(r_ssize_as_integer(dimensionality));
}
