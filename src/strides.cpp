#include "strides.h"

r_obj* ffi_rray_strides(r_obj* x) {
  int n_prot = 0;

  rray::dimension_sizes ds(x);
  KEEP_SHELTER(ds, &n_prot);

  rray::strides st(ds);

  FREE(n_prot);
  return st.data();
}
