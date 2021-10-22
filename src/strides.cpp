#include "strides.h"

r_obj* ffi_rray_strides(r_obj* x, r_obj* broadcastable) {
  bool c_broadcastable = r_arg_as_bool(broadcastable, "broadcastable");
  rray::dimension_sizes ds(x);
  rray::strides st(ds, c_broadcastable);
  return st.data();
}
