/**
 * @file place.h
 * @author Gustavo Rehermann (rehermann6046@gmail.com)
 * @brief Map spot graph.
 * @version added in 0.1
 * @date 2021-03-11
 * 
 * An list of locations in the map where industries can spawn.
 * 
 * Each location has a list of edges to other nearby locations,
 * preventing industries with matching accept types from spawning
 * too close to industries with matching supply types, in a sort of
 * cellular-automata-esque propagation.
 *
 * @copyright Copyright (c)Gustavo Ramos Rehermann 2021. The MIT License.
 */

#ifndef PLACE_H
#define PLACE_H

#include "stddef.h"


/**
 * @brief A map spot.
 */
struct spot_t {
    /**
     * @brief X and Y position of this spot in the world.
     */
    float x, y;
};

#define MAX_SPOTS 512
#define MAX_SPOTS_PER_TILE 4
#define MAX_SPOT_TILES_PER_BUCKET 64
#define MAX_SPOT_BUCKETS_PER_MAP 40
#define SPOT_TILE_WIDTH 1024

/**
 * @brief A tile subdivision of a spotmap.
 * 
 * A spotmap is a way to index a spot by its proximity to
 * a region along the X and Y axes.
 */
struct spotmap_tile_t {
    /**
     * @brief Minimum coordinates of spotmap tile.
     * 
     * Used when calculating which spots go in which spotmap tiles.
     */
    int x, y;

    /**
     * @brief Spots linked to in this spotmap tile.
     */
    size_t spots[MAX_SPOTS_PER_TILE];

    /**
     * @brief The number of spots in this spotmap tile.
     */
    int num_spots;
};

/**
 * @brief A bucket of the spotmap.
 */
struct spotmap_bucket_t {
    /**
     * @brief The spotmap tiles in this spotmap bucket.
     */
    struct spotmap_tile_t tiles[MAX_SPOT_TILES_PER_BUCKET];

    /**
     * @brief The number of spotmap tiles in this spotmap bucket.
     */
    int num_tiles;
};

/**
 * @brief A spotmap.
 * 
 * Akin to a hashmap, a spotmap is a way to index a spot by its
 * proximity to a region along the X and Y axes. It is used to
 * reduce the number of computations needed to find industries
 * close to a station, for instance.
 */
struct spotmap_t {
    /**
     * @brief The list of spotmap buckets in this spotmap.
     */
    struct spotmap_bucket_t buckets[MAX_SPOT_BUCKETS_PER_MAP];
};

/**
 * @brief All defined spots in the world.
 */
extern struct spot_t place_spots[];

/**
 * @brief The number of all spots defined in the world.
 */
extern size_t place_num_spots;

typedef size_t spot_handle_t;

/**
 * @brief Define a new spot.
 * 
 * @param x X location of this spot.
 * @param y Y location of this spot.
 * @return size_t The opaque handle index to this spot.
 */
spot_handle_t make_spot(float x, float y);

/**
 * @brief Links a spot to all tiles within a radius from it.
 * 
 * @param ind_spot The opaque handle index to the spot.
 * @param radius The radius around the spot within which to link tiles.
 */
void spot_link(spot_handle_t ind_spot, float radius);

/**
 * @brief Unlinks a spot from all tiles within a radius from it.
 * 
 * @param ind_spot The opaque handle index to the spot.
 * @param radius The radius around the spot within which to unlink tiles.
 */
void spot_unlink(spot_handle_t ind_spot, float radius);


#endif //PLACE_H