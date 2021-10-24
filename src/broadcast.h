#ifndef RRAY_BROADCAST
#define RRAY_BROADCAST

#include "rlang.h"
#include "dimension-sizes.h"
#include "strides.h"
#include "stepper.h"
#include "capacity.h"
#include "accessor.h"

namespace rray {

  namespace detail {

    template <r_type T>
    static inline
    r_obj* broadcast(r_obj* x, r_obj* dimension_sizes) {
      // TODO: Validate `dimension_sizes` type and non-negative values
      // TODO: Check castable `x_dimension_sizes` to `dimension_sizes`
      // TODO: Helper for creating empty `coordinates` (possibly with initial offset)
      // TODO: Take proxy of `x` and restore
      // TODO: Broadcast names of `x`

      rgetter<T> x_getter(x);

      r_obj* x_dimension_sizes = KEEP(dimension_sizes_compute(x));
      const int* v_x_dimension_sizes = r_int_cbegin(x_dimension_sizes);

      const r_ssize x_dimensionality = r_length(x_dimension_sizes);

      r_obj* x_strides = KEEP(strides_compute(v_x_dimension_sizes, x_dimensionality));
      const int* v_x_strides = r_int_cbegin(x_strides);

      r_obj* x_backstrides = KEEP(backstrides_compute(v_x_dimension_sizes, v_x_strides, x_dimensionality));
      const int* v_x_backstrides = r_int_cbegin(x_backstrides);

      rstepper x_stepper(v_x_strides, v_x_backstrides, x_dimensionality);

      const r_ssize dimensionality = r_length(dimension_sizes);
      const int* v_dimension_sizes = r_int_cbegin(dimension_sizes);

      const r_ssize capacity = capacity_compute(v_dimension_sizes, dimensionality);

      r_obj* coordinates = KEEP(r_alloc_integer(dimensionality));
      int* v_coordinates = r_int_begin(coordinates);
      memset(v_coordinates, 0, dimensionality * sizeof(int));

      r_obj* out = KEEP(r_alloc_vector(T, capacity));
      dimension_sizes_poke(out, dimension_sizes);
      rsetter<T> out_setter(out);

      for (r_ssize i = 0; i < capacity; ++i) {
        const r_ssize location = x_stepper.location();

        out_setter.set(i, x_getter.get(location));

        stepper_utils::increment(
          v_dimension_sizes,
          dimensionality,
          v_coordinates,
          x_stepper
        );
      }

      FREE(5);
      return out;
    }

  }

  r_obj* broadcast(r_obj* x, r_obj* dimension_sizes) {
    switch (r_typeof(x)) {
    case R_TYPE_logical: return detail::broadcast<R_TYPE_logical>(x, dimension_sizes);
    case R_TYPE_integer: return detail::broadcast<R_TYPE_integer>(x, dimension_sizes);
    case R_TYPE_double: return detail::broadcast<R_TYPE_double>(x, dimension_sizes);
    case R_TYPE_complex: return detail::broadcast<R_TYPE_complex>(x, dimension_sizes);
    case R_TYPE_raw: return detail::broadcast<R_TYPE_raw>(x, dimension_sizes);
    case R_TYPE_character: return detail::broadcast<R_TYPE_character>(x, dimension_sizes);
    case R_TYPE_list: return detail::broadcast<R_TYPE_list>(x, dimension_sizes);
    default: r_stop_internal("broadcast", "Unsupported object with type '%s'.", r_typeof(x));
    }
  }
}

#endif
