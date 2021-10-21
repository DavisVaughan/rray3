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

  } // namespace detail

  static inline
  r_obj* dimension_sizes(r_obj* x) {
    r_obj* out = r_dim(x);

    if (out != r_null) {
      return out;
    }

    const r_type type = r_typeof(x);

    if (!detail::is_atomic(type)) {
      detail::stop_non_atomic_typeof(type);
    }

    return r_int(r_ssize_as_integer(r_length(x)));
  }

  static inline
  r_ssize dimensionality(r_obj* x) {
    r_obj* out = r_dim(x);

    if (out != r_null) {
      return r_length(out);
    }

    const r_type type = r_typeof(x);

    if (!detail::is_atomic(type)) {
      detail::stop_non_atomic_typeof(type);
    }

    return 1;
  }

} // namespace rray

#endif
