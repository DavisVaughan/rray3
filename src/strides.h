#ifndef RRAY_STRIDES
#define RRAY_STRIDES

#include "rlang.h"

namespace rray {

  static inline
  r_obj* strides_compute(const int* v_dimension_sizes, r_ssize dimensionality) {
    r_obj* strides = KEEP(r_alloc_integer(dimensionality));
    int* v_strides = r_int_begin(strides);

    int stride = 1;

    for (r_ssize i = 0; i < dimensionality - 1; ++i) {
      v_strides[i] = stride;
      stride *= v_dimension_sizes[i];
    }

    v_strides[dimensionality - 1] = stride;

    // Convert to broadcastable strides
    for (r_ssize i = 0; i < dimensionality; ++i) {
      if (v_dimension_sizes[i] == 1) {
        v_strides[i] = 0;
      }
    }

    FREE(1);
    return strides;
  }

  /*
   * Backstrides "reset" a dimension after we get to the end of it by stepping
   * through with broadcastable strides.
   *
   * Backstrides may be negative for a dimension size of 0 (i.e. dimension sizes
   * of [1, 0, 2]). But remember that computing backstrides ahead of time is
   * purely for performance. If we were to inline the computation that
   * computes the backstride into the location where it is used, it would never
   * be called for these situations that give a negative backstride.
   */
  static inline
  r_obj* backstrides_compute(const int* v_dimension_sizes,
                             const int* v_strides,
                             r_ssize dimensionality) {
    r_obj* backstrides = KEEP(r_alloc_integer(dimensionality));
    int* v_backstrides = r_int_begin(backstrides);

    for (r_ssize i = 0; i < dimensionality; ++i) {
      v_backstrides[i] = v_strides[i] * (v_dimension_sizes[i] - 1);
    }

    FREE(1);
    return backstrides;
  }
}

#endif
