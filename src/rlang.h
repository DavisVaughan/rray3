#ifndef RRAY_RLANG_H
#define RRAY_RLANG_H

// Include Rinternals.h with C++ linkage to avoid rlang including it while
// having C linkage, which causes issues with the GHA Mac machine
#include <Rinternals.h>

extern "C" {
#include "rlang/rlang.h"
}

#define KEEP_SHELTER(x, n_prot) do {                           \
  KEEP((x).shelter());                                         \
  *(n_prot) += 1;                                              \
} while (0);

#endif
