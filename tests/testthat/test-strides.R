test_that("strides are computed correctly and are always broadcastable", {
  x <- array(1, dim = c(2, 3, 4))
  expect_identical(rray_strides(x), c(0L, 3L, 6L))
})
