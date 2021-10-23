test_that("capacity is computed correctly", {
  x <- array(1, c(2, 3, 4))
  expect_identical(rray_capacity(x), as.integer(prod(rray_dimension_sizes(x))))
})

test_that("capacity is computed correctly with a size 0 dimension", {
  x <- array(1, c(2, 0, 4))
  expect_identical(rray_capacity(x), 0L)
})
