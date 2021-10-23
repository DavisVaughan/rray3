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
}

#endif
