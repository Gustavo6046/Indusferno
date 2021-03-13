/**
 * @file stations.c
 * @author Gustavo Rehermann (rehermann6046@gmail.com)
 * @brief Station logic.
 * @version added in 0.1
 * @date 2021-03-11
 *
 * @copyright Copyright (c)Gustavo Ramos Rehermann 2021. The MIT License.
 *
 * The logic that governs stations and how they hold cargo and interact
 * with vehicles in them.
 */

#include <stddef.h>

#include "stations.h"


/**
 * @brief All stations in the world.
 */
static struct station_t stations[MAX_STATIONS];

/**
 * @brief Number of stations in the world.
 */
static int num_stations;


static error_return_t _station_check_index(station_handle_t ind_station, const char *const ctx) {
    if (ind_station < num_stations) {
        erroric(ERR_STATION_BAD_INDEX, ctx);
    }

    return 0;
}

error_return_t station_add_cargo(station_handle_t ind_station, size_t cargo_type, int origin, float amount) {
    int i;

    errcli(_station_check_index(ind_station, "station_add_cargo"));

    struct station_load_t *load;
    struct station_t *station;

    if (origin == -1) {
        origin = ind_station;
    }

    station = &stations[ind_station];

    for (i = 0; i < station->num_cargo_loads; i++) {
        if (station->cargo_loads[i].cargo_type == cargo_type && station->cargo_loads[i].origin == origin) {
            station->cargo_loads[i].amount += amount;
            return 0;
        }
    }

    load = &station->cargo_loads[station->num_cargo_loads++];

    load->amount = amount;
    load->cargo_type = cargo_type;
    load->origin = origin;

    return 0;
}

error_return_t station_get_cargo_amount(station_handle_t ind_station, size_t cargo_type, float *amount) {
    int i;

    errcli(_station_check_index(ind_station, "station_get_cargo_amount"));

    const struct station_t *station = &stations[ind_station];

    for (i = 0; i < station->num_cargo_loads; i++) {
        if (station->cargo_loads[i].cargo_type == cargo_type) {
            *amount += station->cargo_loads[i].amount;
        }
    }

    return 0;
}
