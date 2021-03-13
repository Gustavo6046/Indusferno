/**
 * @file util.h
 * @author Gustavo Rehermann (rehermann6046@gmail.com)
 * @brief Some common, miscellaneous utility macros and functions.
 * @version added in 0.1
 * @date 2021-03-13
 *
 * @copyright Copyright (c)Gustavo Ramos Rehermann 2021. The MIT License.
 */

#ifndef UTIL_H
#define UTIL_H


/**
 * @brief A division whose return value is always floored.
 *
 * C's standard division operator truncates the return value towards
 * zero, instead of flooring it toward negative infinity as may be
 * desirable sometimes.
 */
#define floordiv(a, b) ( (int) ((a) > 0 ? (a) : ((a) - (b))) / (b) )


#endif // UTIL_H
