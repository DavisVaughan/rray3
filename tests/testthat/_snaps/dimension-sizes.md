# dimension sizes must come from an atomic object

    Code
      rray_dimension_sizes(expr(x + y))
    Condition
      Error in `rray_dimension_sizes()`:
      ! `x` must be an atomic vector type, not a <language>.

# dimensionality must come from an atomic object

    Code
      rray_dimensionality(expr(x + y))
    Condition
      Error in `rray_dimensionality()`:
      ! `x` must be an atomic vector type, not a <language>.

