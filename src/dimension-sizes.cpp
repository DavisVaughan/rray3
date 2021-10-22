#include "dimension-sizes.h"

r_obj* ffi_rray_dimension_sizes(r_obj* x) {
  rray::dimension_sizes x_dimension_sizes(x);
  return x_dimension_sizes.data();
}

r_obj* ffi_rray_dimensionality(r_obj* x) {
  rray::dimension_sizes x_dimension_sizes(x);
  r_ssize x_dimensionality = x_dimension_sizes.size();
  return r_int(r_ssize_as_integer(x_dimensionality));
}
