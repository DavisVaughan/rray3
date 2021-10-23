#include "stepper.h"
#include "dimension-sizes.h"
#include "strides.h"
#include "capacity.h"

r_obj* ffi_rray_test_iterate(r_obj* x, r_obj* dimension_sizes) {
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

  r_obj* out = KEEP(r_alloc_list(2));

  r_obj* out_names = r_alloc_character(2);
  r_attrib_poke_names(out, out_names);
  r_chr_poke(out_names, 0, r_str("locations"));
  r_chr_poke(out_names, 1, r_str("coordinates"));

  r_obj* out_locations = r_alloc_integer(capacity);
  int* v_out_locations = r_int_begin(out_locations);
  r_list_poke(out, 0, out_locations);

  r_obj* out_coordinates = r_alloc_integer(capacity * dimensionality);
  int* v_out_coordinates = r_int_begin(out_coordinates);
  r_list_poke(out, 1, out_coordinates);

  r_obj* out_coordinates_dimension_sizes = KEEP(r_alloc_integer(2));
  int* v_out_coordinates_dimension_sizes = r_int_begin(out_coordinates_dimension_sizes);
  v_out_coordinates_dimension_sizes[0] = r_ssize_as_integer(capacity);
  v_out_coordinates_dimension_sizes[1] = r_ssize_as_integer(dimensionality);
  rray::dimension_sizes_poke(out_coordinates, out_coordinates_dimension_sizes);

  for (r_ssize i = 0; i < capacity; ++i) {
    v_out_locations[i] = r_ssize_as_integer(x_stepper.location() + 1);

    for (r_ssize j = 0; j < dimensionality; ++j) {
      v_out_coordinates[i + j * capacity] = v_coordinates[j] + 1;
    }

    rray::stepper_utils::increment(
      v_dimension_sizes,
      dimensionality,
      v_coordinates,
      x_stepper
    );
  }

  FREE(6);
  return out;
}
