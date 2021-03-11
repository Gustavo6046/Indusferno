/**
 * @file error.c
 * @author Gustavo Rehermann (rehermann6046@gmail.com)
 * @brief Error handling logic.
 * @version added in 0.1
 * @date 2021-03-11
 *
 * @copyright Copyright (c)Gustavo Ramos Rehermann 2021. The MIT License.
 */

#include <ACS_ZDoom.h>
#include <stdio.h>

#include "error.h"


static const char *const error_strings[] = {
    "Industry does not exist with index passed",
    "Industry type is unknown",
    "Industry does not have accepted-cargo type passed"
};

void error(enum error_code_t error_code) {
    printf("\\cx[WARNING] %s\\c-", error_strings[error_code]);
}
