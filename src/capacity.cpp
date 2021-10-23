#include "capacity.h"
#include "dimension-sizes.h"

r_obj* ffi_rray_capacity(r_obj* x) {
  r_obj* dimension_sizes = KEEP(rray::dimension_sizes_compute(x));
  const int* v_dimension_sizes = r_int_cbegin(dimension_sizes);

  const r_ssize dimensionality = r_length(dimension_sizes);

  r_ssize capacity = rray::capacity_compute(v_dimension_sizes, dimensionality);

  FREE(1);
  return r_int(r_ssize_as_integer(capacity));
}
