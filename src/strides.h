#ifndef RRAY_STRIDES
#define RRAY_STRIDES

#include "rlang.h"
#include "dimension-sizes.h"

namespace rray {

  static inline
  r_obj* strides_compute(const int* v_dimension_sizes, r_ssize dimensionality) {
    r_obj* strides = KEEP(r_alloc_integer(dimensionality));
    int* v_strides = r_int_begin(strides);

    int stride = 1;

    for (r_ssize i = 0; i < dimensionality - 1; ++i) {
      v_strides[i] = stride;
      stride += v_dimension_sizes[i];
    }

    v_strides[dimensionality - 1] = stride;

    FREE(1);
    return strides;
  }

  static inline
  void
  strides_convert_to_broadcastable(r_ssize dimensionality, int* v_strides) {
    for (r_ssize i = 0; i < dimensionality; ++i) {
      if (v_strides[i] == 1) {
        v_strides[i] = 0;
      }
    }
  }

}

#endif
