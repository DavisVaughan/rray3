#ifndef RRAY_BROADCAST
#define RRAY_BROADCAST

#include "rlang.h"
#include "dimension-sizes.h"
#include "strides.h"
#include "stepper.h"
#include "capacity.h"

namespace rray {

static inline
r_obj* broadcast(r_obj* x, r_obj* dimension_sizes) {
  // TODO: Validate `dimension_sizes` type and non-negative values
  // TODO: Check castable `x_dimension_sizes` to `dimension_sizes`
  // TODO: Generalize type of `x`
  // TODO: Helper for creating empty `coordinates` (possibly with initial offset)
  // TODO: Take proxy of `x` and restore
  // TODO: Broadcast names of `x`

  const int* v_x = r_int_cbegin(x);

  r_obj* x_dimension_sizes = KEEP(rray::dimension_sizes_compute(x));
  const int* v_x_dimension_sizes = r_int_cbegin(x_dimension_sizes);

  const r_ssize x_dimensionality = r_length(x_dimension_sizes);

  r_obj* x_strides = KEEP(rray::strides_compute(v_x_dimension_sizes, x_dimensionality));
  const int* v_x_strides = r_int_cbegin(x_strides);

  r_obj* x_backstrides = KEEP(rray::backstrides_compute(v_x_dimension_sizes, v_x_strides, x_dimensionality));
  const int* v_x_backstrides = r_int_cbegin(x_backstrides);

  rray::rstepper x_stepper(v_x_strides, v_x_backstrides, x_dimensionality);

  const r_ssize dimensionality = r_length(dimension_sizes);
  const int* v_dimension_sizes = r_int_cbegin(dimension_sizes);

  const r_ssize capacity = rray::capacity_compute(v_dimension_sizes, dimensionality);

  r_obj* coordinates = KEEP(r_alloc_integer(dimensionality));
  int* v_coordinates = r_int_begin(coordinates);
  memset(v_coordinates, 0, dimensionality * sizeof(int));

  r_obj* out = KEEP(r_alloc_integer(capacity));
  int* v_out = r_int_begin(out);
  rray::dimension_sizes_poke(out, dimension_sizes);

  for (r_ssize i = 0; i < capacity; ++i) {
    const r_ssize location = x_stepper.location();

    v_out[i] = v_x[location];

    rray::stepper_utils::increment(
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

#endif
