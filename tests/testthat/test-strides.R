test_that("strides are computed correctly", {
  x <- array(1, dim = c(2, 3, 4))
  expect_identical(rray_strides(x), c(1L, 3L, 6L))
})
