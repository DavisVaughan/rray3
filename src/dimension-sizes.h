#ifndef RRAY_DIMENSION_SIZES
#define RRAY_DIMENSION_SIZES

#include "rlang.h"

namespace rray {

  namespace detail {

    static inline
    bool is_atomic(const enum r_type& type) {
      switch(type) {
      case R_TYPE_logical:
      case R_TYPE_integer:
      case R_TYPE_double:
      case R_TYPE_complex:
      case R_TYPE_raw:
      case R_TYPE_character:
      case R_TYPE_list:
        return true;
      default:
        return false;
      }
    }

    [[noreturn]]
    static inline
    void stop_non_atomic_typeof(const enum r_type& type) {
      r_abort(
        "`x` must be an atomic vector type, not a <%s>.",
        r_type_as_c_string(type)
      );
    }

  }

  static inline
  r_obj* dimension_sizes_compute(r_obj* x) {
    r_obj* dimension_sizes = r_dim(x);

    if (dimension_sizes != r_null) {
      return dimension_sizes;
    }

    const r_type type = r_typeof(x);

    if (!detail::is_atomic(type)) {
      detail::stop_non_atomic_typeof(type);
    }

    return r_int(r_ssize_as_integer(r_length(x)));
  }

  static inline
  void dimension_sizes_poke(r_obj* x, r_obj* dimension_sizes) {
    r_attrib_poke_dim(x, dimension_sizes);
  }

  static inline
  r_ssize dimensionality_compute(r_obj* x) {
    r_obj* dimension_sizes = r_dim(x);

    if (dimension_sizes != r_null) {
      return r_length(dimension_sizes);
    }

    const r_type type = r_typeof(x);

    if (!detail::is_atomic(type)) {
      detail::stop_non_atomic_typeof(type);
    }

    return 1;
  }

  static inline
  r_ssize capacity_compute(const int* v_dimension_sizes,
                           r_ssize dimensionality) {
    r_ssize capacity = 1;

    for (r_ssize i = 0; i < dimensionality; ++i) {
      const r_ssize dimension_size = static_cast<r_ssize>(v_dimension_sizes[i]);
      capacity = r_ssize_mult(capacity, dimension_size);
    }

    return capacity;
  }
}

#endif
