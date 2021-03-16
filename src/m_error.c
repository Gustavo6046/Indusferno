/**
 * @file m_error.c
 * @author Gustavo Rehermann (rehermann6046@gmail.com)
 * @brief Error handling logic.
 * @version added in 0.1
 * @date 2021-03-11
 *
 * @copyright Copyright (c)Gustavo Ramos Rehermann 2021. The MIT License.
 */

#include <stdio.h>

#include "m_error.h"


/**
 * @brief The last error value stored from an iferr macro call.
 */
error_return_t _err;


static const char *const error_strings[] = {
    "No industry exists with index passed",
    "Industry type is unknown",
    "Industry supply type is unknown",
    "Industry does not have accepted-cargo type passed",
    "No company exists with index passed",
    "Company already has chairman",
    "Company already doesn't have chairman",
    "Company does not have sufficient money to pay back",
    "Company cannot loan more; debt alreadcy maxed out",
    "No station exists with index passed",
    "No spot exists with index passed",
    "Spot index not found in tile for unlinking; probably incorrect" \
        "radius value passed",
    "Too many spots defined",
    "Invalid cargo type index passed"
};


void _error(enum error_code_t error_code) {
#ifdef DEBUG
    printf("\\cx[WARNING] %s\\c-", error_strings[error_code]);
#endif
}

void _error_c(enum error_code_t error_code, const char *context) {
#ifdef DEBUG
    printf("\\cx[WARNING] In %s: %s\\c-", context, error_strings[error_code]);
#endif
}
