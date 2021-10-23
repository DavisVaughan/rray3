#include "broadcast.h"

r_obj* ffi_rray_broadcast(r_obj* x, r_obj* dimension_sizes) {
  return rray::broadcast(x, dimension_sizes);
}
