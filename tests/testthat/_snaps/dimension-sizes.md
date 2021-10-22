# dimension sizes must come from an atomic object

    Code
      rray_dimension_sizes(expr(x + y))
    Error <rlang_error>
      `x` must be an atomic vector type, not a <language>.

# dimensionality must come from an atomic object

    Code
      rray_dimensionality(expr(x + y))
    Error <rlang_error>
      `x` must be an atomic vector type, not a <language>.

