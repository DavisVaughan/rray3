#ifndef RRAY_RLANG_H
#define RRAY_RLANG_H

// Include Rinternals.h with C++ linkage to avoid rlang including it while
// having C linkage, which causes issues with the GHA Mac machine
#include <Rinternals.h>

extern "C" {
#include "rlang/rlang.h"
}

#endif
