/**
 * @file cargo.h
 * @author Gustavo Rehermann (rehermann6046@gmail.com)
 * @brief Cargo.
 * @version added in 0.1
 * @date 2021-03-11
 *
 * @copyright Copyright (c)Gustavo Ramos Rehermann 2021. The MIT License.
 */

#ifndef CARGO_H
#define CARGO_H

#include <stddef.h>


/**
 * @brief The maximum number of cargo types.
 */
#define MAX_CARGO_TYPES 64;


/**
 * @brief A cargo type definition.
 */
struct cargo_t {
    /**
     * @brief A human-readable name for this cargo type.
     */
    char label[64];

    /**
     * @brief Cargo-specific unit of amount.
     *
     * Every cargo is internally amounted in Cargo Units. However,
     * cargos may specify their own unit to display to the player.
     *
     * If 'unit' is an empty string (where the first byte is a
     * null byte, and thus strlen(unit) is zero), the amount
     * displayed should be in regular Cargo Units. The usual
     * denomination of Cargo Unist is in cubic decimeters (which
     * is to say, a litre). This may vary, depending on the
     * localization.
     */
    char unit[32];

    /**
     * @brief Cargo-specific unit conversion rate.
     *
     * How many of the the cargo-specific unit exist in 512 Cargo
     * Units of this cargo type.
     */
    int conversion;
};

/**
 * @brief A list of all known cargo types.
 */
extern const struct cargo_t cargo_types[];

/**
 * @brief An index into a cargo type.
 */
typedef size_t cargo_handle_t;


#endif // CARGO_H
