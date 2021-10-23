# ------------------------------------------------------------------------------
# rray_strides()

test_that("strides are computed correctly and are always broadcastable", {
  x <- array(1, dim = c(2, 3, 4))
  expect_identical(rray_strides(x), c(1L, 2L, 6L))
})

test_that("strides are broadcastable strides (0 where size was 1)", {
  x <- array(1, dim = c(2, 1, 4, 1))
  expect_identical(rray_strides(x), c(1L, 0L, 2L, 0L))
})

# ------------------------------------------------------------------------------
# rray_backstrides()

test_that("backstrides are a function of dimension sizes and strides", {
  x <- array(1, dim = c(2, 3, 4))

  expect_identical(
    rray_backstrides(x),
    rray_strides(x) * (rray_dimension_sizes(x) - 1L)
  )
})

test_that("backstrides are computed with broadcastable strides", {
  x <- array(1, dim = c(2, 1, 4, 1))

  expect_identical(
    rray_backstrides(x),
    c(1L, 0L, 6L, 0L)
  )
})
