#include "strides.h"
#include "dimension-sizes.h"

r_obj* ffi_rray_strides(r_obj* x) {
  r_obj* dimension_sizes = KEEP(rray::dimension_sizes_compute(x));
  const int* v_dimension_sizes = r_int_cbegin(dimension_sizes);

  const r_ssize dimensionality = r_length(dimension_sizes);

  r_obj* strides = rray::strides_compute(v_dimension_sizes, dimensionality);

  FREE(1);
  return strides;
}

r_obj* ffi_rray_backstrides(r_obj* x) {
  r_obj* dimension_sizes = KEEP(rray::dimension_sizes_compute(x));
  const int* v_dimension_sizes = r_int_cbegin(dimension_sizes);

  const r_ssize dimensionality = r_length(dimension_sizes);

  r_obj* strides = KEEP(rray::strides_compute(v_dimension_sizes, dimensionality));
  const int* v_strides = r_int_cbegin(strides);

  r_obj* backstrides = rray::backstrides_compute(v_dimension_sizes, v_strides, dimensionality);

  FREE(2);
  return backstrides;
}
