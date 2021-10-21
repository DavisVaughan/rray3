#include "dimension-sizes.h"

r_obj* ffi_rray_dimension_sizes(r_obj* x) {
  return rray::dimension_sizes(x);
}

r_obj* ffi_rray_dimensionality(r_obj* x) {
  return r_int(r_ssize_as_integer(rray::dimensionality(x)));
}
