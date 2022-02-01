#ifndef RRAY_STEPPER
#define RRAY_STEPPER

#include <rlang.hpp>

namespace rray {

  class rstepper {
  private:
    r_ssize m_location;
    const int* m_v_strides;
    const int* m_v_backstrides;
    r_ssize m_dimensionality;
  public:
    explicit rstepper(const int* v_strides,
                      const int* v_backstrides,
                      r_ssize dimensionality);
    explicit rstepper(r_ssize offset,
                      const int* v_strides,
                      const int* v_backstrides,
                      r_ssize dimensionality);

    r_ssize location() const;

    void step(r_ssize dimension);
    void reset(r_ssize dimension);
  };

  inline
  rstepper::rstepper(const int* v_strides,
                     const int* v_backstrides,
                     r_ssize dimensionality)
    : rstepper::rstepper(
        0,
        v_strides,
        v_backstrides,
        dimensionality
    ) {

  }

  inline
  rstepper::rstepper(r_ssize offset,
                     const int* v_strides,
                     const int* v_backstrides,
                     r_ssize dimensionality)
    : m_location(offset),
      m_v_strides(v_strides),
      m_v_backstrides(v_backstrides),
      m_dimensionality(dimensionality) {

  }

  inline
  r_ssize
  rstepper::location() const {
    return m_location;
  }

  inline
  void
  rstepper::step(r_ssize dimension) {
    if (dimension < m_dimensionality) {
      m_location += static_cast<r_ssize>(m_v_strides[dimension]);
    }
  }

  inline
  void
  rstepper::reset(r_ssize dimension) {
    if (dimension < m_dimensionality) {
      m_location -= static_cast<r_ssize>(m_v_backstrides[dimension]);
    }
  }

  struct stepper_utils {

    static
    void
    increment(const int* v_dimension_sizes,
              r_ssize dimensionality,
              int* v_coordinates,
              rstepper& stepper);

  };

  inline
  void
  stepper_utils::increment(const int* v_dimension_sizes,
                           r_ssize dimensionality,
                           int* v_coordinates,
                           rstepper& stepper) {
    for (r_ssize i = 0; i < dimensionality; ++i) {
      const int coordinate = v_coordinates[i];
      const int dimension_size = v_dimension_sizes[i];

      if (coordinate != (dimension_size - 1)) {
        // Increment in this dimension
        ++v_coordinates[i];
        stepper.step(i);
        return;
      }

      // Reset and move to next dimension
      v_coordinates[i] = 0;
      stepper.reset(i);
    }
  }
}

#endif
