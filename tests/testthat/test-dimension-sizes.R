test_that("can get the dimension sizes of an array", {
  x <- array(1, c(2, 2, 2))
  expect_identical(rray_dimension_sizes(x), c(2L, 2L, 2L))
})

test_that("dimension sizes of a vector are its length", {
  expect_identical(rray_dimension_sizes(1:5), 5L)
})

test_that("dimension sizes must come from an atomic object", {
  expect_snapshot(error = TRUE, rray_dimension_sizes(expr(x+y)))
})
