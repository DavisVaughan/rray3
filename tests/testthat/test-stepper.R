# ------------------------------------------------------------------------------

test_that("can iterate through a 1D vector", {
  x <- 1:5
  res <- rray_test_iterate(x, rray_dimension_sizes(x))
  expect_identical(res$locations, seq_along(x))
  expect_identical(res$coordinates, matrix(1:5, nrow = 5))
})

test_that("can iterate through a 3D vector", {
  x <- array(1, c(2, 3, 4))

  coordinates <- unname(as.matrix(expand.grid(1:2, 1:3, 1:4)))

  res <- rray_test_iterate(x, rray_dimension_sizes(x))
  expect_identical(res$locations, seq_along(x))
  expect_identical(res$coordinates, coordinates)
})

test_that("can iterate through a vector with size 1 dimensions", {
  x <- array(1, c(2, 1, 3, 1))

  coordinates <- unname(as.matrix(expand.grid(1:2, 1L, 1:3, 1L)))

  res <- rray_test_iterate(x, rray_dimension_sizes(x))
  expect_identical(res$locations, seq_along(x))
  expect_identical(res$coordinates, coordinates)
})

test_that("can iterate through a vector with size 0 dimensions", {
  x <- array(1, c(0, 1, 3, 1))

  res <- rray_test_iterate(x, rray_dimension_sizes(x))
  expect_identical(res$locations, integer())
  expect_identical(res$coordinates, matrix(integer(), nrow = 0L, ncol = 4L))
})

test_that("can iterate with broadcasting along existing dimensions", {
  x <- array(1, c(2, 1, 2))
  dimension_sizes <- c(2L, 3L, 2L)

  locations <- c(rep(1:2, times = 3), rep(3:4, times = 3))
  coordinates <- unname(as.matrix(expand.grid(1:2, 1:3, 1:2)))

  res <- rray_test_iterate(x, dimension_sizes)
  expect_identical(res$locations, locations)
  expect_identical(res$coordinates, coordinates)
})
