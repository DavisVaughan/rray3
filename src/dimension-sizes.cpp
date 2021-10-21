#include "dimension-sizes.h"

r_obj* ffi_rray_dimension_sizes(r_obj* x) {
  return rray::dimension_sizes(x);
}
