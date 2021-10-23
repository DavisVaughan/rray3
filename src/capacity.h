#ifndef RRAY_CAPACITY
#define RRAY_CAPACITY

#include "rlang.h"

namespace rray {

  static inline
  r_ssize capacity_compute(const int* v_dimension_sizes, r_ssize dimensionality) {
    r_ssize capacity = 1;

    for (r_ssize i = 0; i < dimensionality; ++i) {
      const r_ssize dimension_size = static_cast<r_ssize>(v_dimension_sizes[i]);
      capacity = r_ssize_mult(capacity, dimension_size);
    }

    return capacity;
  }

}

#endif
