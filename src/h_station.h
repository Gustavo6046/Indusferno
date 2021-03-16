/**
 * @file h_station.h
 * @author Gustavo Rehermann (rehermann6046@gmail.com)
 * @brief Stations.
 * @version added in 0.1
 * @date 2021-03-11
 *
 * @copyright Copyright (c)Gustavo Ramos Rehermann 2021. The MIT License.
 */

#ifndef STATIONS_H
#define STATIONS_H

#include <stddef.h>
#include "m_error.h"
#include "h_cargo.h"

/**
 * @brief The maximum number of distinct cargo loads in a single station.
 */
#define MAX_CARGO_LOADS 32

/**
 * @brief The maximum number of stations in the entire world.
 */
#define MAX_STATIONS 128

/**
 * @brief An index handle to a station.
 */
typedef size_t station_handle_t;

/**
 * @brief A distinct load of cargo in a station.
 *
 * A 'load' of cargo is an amount of cargo waiting in
 * a station, with a cargo type and a defined origin station.
 *
 * Any cargo of a different type or origin must be grouped into
 * a different 'load'. Conversely, no two loads exist with the
 * exact same cargo type *and* origin.
 */
struct station_load_t {
    /**
     * @brief Indef of this load's cargo type.
     */
    cargo_handle_t  cargo_type;

    /**
     * @brief Amount of cargo in this load, in Cargo Units.
     */
    float   amount;

    /**
     * @brief Index of the origin station.
     *
     * The index of the station from which all cargo in this
     * 'load' originated.
     */
    size_t  origin;
};

/**
 * @brief A station.
 *
 * All state of a station in the world.
 */
struct station_t {
    /**
     * @brief The X position of this station in the world.
     *
     * The position of this station in the world is stored as X and Y
     * coordinates. Due to the nature of the (Z)Doom engine, vertical
     * position is omitted.
     */
    float pos_x;

    /**
     * @brief The Y position of this station in the world.
     *
     * The position of this station in the world is stored as X and Y
     * coordinates. Due to the nature of the (Z)Doom engine, vertical
     * position is omitted.
     */
    float pos_y;

    /**
     * @brief All cargo loads in this station.
     *
     * @note Only items up to (num_cargo_loads - 1) should be iterated.
     */
    struct station_load_t cargo_loads[MAX_CARGO_LOADS];

    /**
     * @brief The number of cargo loads in this station.
     */
    size_t num_cargo_loads;
};

/**
 * @brief Add an amount of a cargo type to this station.
 *
 * @param ind_station The station to the which to add cargo.
 * @param cargo_type The type of the cargo to be added.
 * @param origin The origin of the cargo, or -1 to default to the station itself.
 * @param amount The amount of cargo to add.
 * @return error_return_t 0 if successful, an error code otherwise.
 */
error_return_t station_add_cargo(station_handle_t ind_station, cargo_handle_t cargo_type, int origin, float amount);

/**
 * @brief Get the amount of cargo of a specific type in this station.
 *
 * Precisely, this function returns the sum of the amounts of all cargo
 * loads with a matching cargo type.
 *
 * @param ind_station The station on the which to query for cargo.
 * @param cargo_type The type of cargo to be queried.
 * @param amount A pointer to a float in the which to store the amount.
 * @return error_return_t 0 if successful, an error code otherwise.
 */
error_return_t station_get_cargo_amount(station_handle_t ind_station, cargo_handle_t cargo_type, float *amount);


#endif // STATIONS_H
