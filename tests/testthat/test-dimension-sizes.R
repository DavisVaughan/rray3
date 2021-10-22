# ------------------------------------------------------------------------------
# rray_dimension_sizes()

test_that("can get the dimension sizes of an array", {
  x <- array(1, c(2, 2, 2))
  expect_identical(rray_dimension_sizes(x), c(2L, 2L, 2L))
})

test_that("dimension sizes of a vector are its length", {
  expect_identical(rray_dimension_sizes(1:5), 5L)
})

test_that("dimension sizes of empty objects are correct", {
  expect_identical(rray_dimension_sizes(integer()), 0L)
  expect_identical(rray_dimension_sizes(matrix(integer(), ncol = 2)), c(0L, 2L))
})

test_that("dimension sizes must come from an atomic object", {
  expect_snapshot(error = TRUE, rray_dimension_sizes(expr(x+y)))
})

# ------------------------------------------------------------------------------
# rray_dimensionality()

test_that("can get the dimensionality of an array", {
  x <- array(1, c(2, 2, 2))
  expect_identical(rray_dimensionality(x), 3L)
})

test_that("dimensionality of a vector is 1", {
  expect_identical(rray_dimensionality(1:5), 1L)
})

test_that("dimensionality of empty objects is correct", {
  expect_identical(rray_dimensionality(integer()), 1L)
  expect_identical(rray_dimensionality(matrix(integer(), ncol = 2)), 2L)
})

test_that("dimensionality must come from an atomic object", {
  expect_snapshot(error = TRUE, rray_dimensionality(expr(x+y)))
})
