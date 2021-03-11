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


struct station_t stations[MAX_STATIONS];

int num_stations;


void station_add_cargo(size_t ind_station, size_t cargo_type, int origin, float amount) {
    int i;
    struct station_load_t *load;
    struct station_t *station;

    if (origin == -1) {
        origin = ind_station;
    }

    station = &stations[ind_station];

    for (i = 0; i < station->num_cargo_loads; i++) {
        if (station->cargo_loads[i].cargo_type == cargo_type && station->cargo_loads[i].origin == origin) {
            station->cargo_loads[i].amount += amount;
            return;
        }
    }

    load = &station->cargo_loads[station->num_cargo_loads++];

    load->amount = amount;
    load->cargo_type = cargo_type;
    load->origin = origin;
}

float stations_get_cargo_amount(struct station_t *const station, size_t cargo_type) {
    int i;
    float amount = 0;

    for (i = 0; i < station->num_cargo_loads; i++) {
        if (station->cargo_loads[i].cargo_type == cargo_type) {
            amount += station->cargo_loads[i].amount;
        }
    }

    return amount;
}
