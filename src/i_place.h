/**
 * @file i_place.h
 * @author Gustavo Rehermann (rehermann6046@gmail.com)
 * @brief Map spot graph.
 * @version added in 0.1
 * @date 2021-03-12
 *
 * A list of locations in the map where map features, such as
 * industries, can spawn.
 * 
 * Places serve as a way to define specific waypoints in the level,
 * where there is room for a map feature to spawn. They are defined
 * manually in the map itself, rather than generated automatically in
 * the code.
 * 
 * In the initialization process, once all IndusfernoMapSpot
 * actors are done adding their own positions to Indusferno's
 * internal spot list, the map feature generation code is run.
 *
 * @copyright Copyright (c)Gustavo Ramos Rehermann 2021. The MIT License.
 */

#ifndef PLACE_H
#define PLACE_H

#include <stddef.h>
#include "m_error.h"


/**
 * @brief A map spot.
 */
struct spot_t {
    /**
     * @brief X coordinate of the position of this spot in the world.
     */
    float x;

    /**
     * @brief Y coordinate of the position of this spot in the world.
     */
    float y;
};

/**
 * @brief The max number of spots that can be defined within the world.
 */
#define MAX_SPOTS 512

/**
 * @brief The max number of spots that can be linked to a single tile.
 */
#define MAX_SPOTS_PER_TILE 4

/**
 * @brief The max number of spotmap tiles that can be in a bucket.
 */
#define MAX_SPOT_TILES_PER_BUCKET 64

/**
 * @brief The number of spotmap buckets in a spotmap.
 */
#define NUM_SPOT_BUCKETS_PER_MAP 40

/**
 * @brief The width of a spot tile, along the X and Y axes.
 */
#define SPOT_TILE_WIDTH 1024

/**
 * @brief A tile subdivision of a spotmap.
 *
 * A spotmap is a way to index a spot by its proximity to
 * a region along the X and Y axes.
 */
struct spotmap_tile_t {
    /**
     * @brief X coordinate of the position of this spotmap tile.
     *
     * Used when calculating which spots go in which spotmap tiles.
     */
    int x;

    /**
     * @brief Y coordinate of the position of this spotmap tile.
     *
     * Used when calculating which spots go in which spotmap tiles.
     */
    int y;

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
    struct spotmap_bucket_t buckets[NUM_SPOT_BUCKETS_PER_MAP];
};

/**
 * @brief The number of all spots defined in the world.
 */
extern size_t place_num_spots;

/**
 * @brief An index handle to a spot.
 */
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
error_return_t spot_link(spot_handle_t ind_spot, float radius);

/**
 * @brief Unlinks a spot from all tiles within a radius from it.
 *
 * @param ind_spot The opaque handle index to the spot.
 * @param radius The radius around the spot within which to unlink tiles.
 */
error_return_t spot_unlink(spot_handle_t ind_spot, float radius);


#endif //PLACE_H
