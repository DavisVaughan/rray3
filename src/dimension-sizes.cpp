#include "dimension-sizes.h"

r_obj* ffi_rray_dimension_sizes(r_obj* x) {
  return rray::dimension_sizes(x).data();
}

r_obj* ffi_rray_dimensionality(r_obj* x) {
  int n_prot = 0;

  rray::dimension_sizes ds(x);
  KEEP_SHELTER(ds, &n_prot);

  r_obj* out = r_int(r_ssize_as_integer(ds.size()));

  FREE(n_prot);
  return out;
}
