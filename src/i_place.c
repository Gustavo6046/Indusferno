/**
 * @file i_place.c
 * @author Gustavo Rehermann (rehermann6046@gmail.com)
 * @brief Map spot graph implementation.
 * @version added in 0.1
 * @date 2021-03-12
 *
 * @copyright Copyright (c)Gustavo Ramos Rehermann 2021. The MIT License.
 */

#include "i_place.h"
#include "m_util.h"


static struct spotmap_t place_spotmap;

static struct spot_t place_spots[MAX_SPOTS];
size_t place_num_spots = 0;


static int hash_coords(int x, int y) {
    return ((x & 0xD555) << 1) | (y & 0x5555);
}


static struct spotmap_tile_t *spot_find_tile(int x, int y) {
    const int hash = hash_coords(x, y);
    struct spotmap_bucket_t *const bucket = &place_spotmap.buckets[hash % NUM_SPOT_BUCKETS_PER_MAP];
    size_t i;

    for (i = 0; i < bucket->num_tiles; i++) {
        struct spotmap_tile_t *const tile = &bucket->tiles[i];

        if (tile->x == x && tile->y == y) {
            return tile;
        }
    }

    // make new tile
    struct spotmap_tile_t *const tile = &bucket->tiles[bucket->num_tiles++];

    tile->x = x;
    tile->y = y;
    tile->num_spots = 0;

    return tile;
}

static error_return_t _spot_check_index(spot_handle_t ind_spot, const char *const ctx) {
    if (ind_spot < place_num_spots) {
        erroric(ERR_PLACE_BAD_SPOT_INDEX, ctx);
    }

    return 0;
}

/**
 * @brief A spot tile iterator callback.
 */
typedef error_return_t (*_spot_iterator_callback_t)(spot_handle_t ind_spot, float radius, struct spotmap_tile_t *const tile, int x, int y);

static error_return_t _spot_link_callback(spot_handle_t ind_spot, float radius, struct spotmap_tile_t *const tile, int x, int y) {
    tile->spots[tile->num_spots++] = ind_spot;

    return 0;
}

static error_return_t _spot_unlink_callback(spot_handle_t ind_spot, float radius, struct spotmap_tile_t *const tile, int x, int y) {
    static int i;

    tile->spots[tile->num_spots++] = ind_spot;

    // find which spot in tile is our spot
    for (i = 0; i < tile->num_spots; i++) {
        if (tile->spots[i] == ind_spot) {
            // found the spot
            break;
        }
    }

    if (i == tile->num_spots) {
        // not found
        erroric(ERR_PLACE_UNLINK_SPOT_NOT_FOUND, "_spot_unlink_callback");
    }

    // move all other spots back a slot
    while (i < tile->num_spots) {
        tile->spots[i] = tile->spots[i + 1];
        i++;
    }

    tile->num_spots--;

    return 0;
}

static error_return_t _spot_tile_iter(spot_handle_t ind_spot, float radius, _spot_iterator_callback_t iterator) {
    const struct spot_t *spot = &place_spots[ind_spot];

    int min_x = floordiv((spot->x - radius), SPOT_TILE_WIDTH);
    int max_x = floordiv((spot->x + radius), SPOT_TILE_WIDTH);
    int min_y = floordiv((spot->y - radius), SPOT_TILE_WIDTH);
    int max_y = floordiv((spot->y + radius), SPOT_TILE_WIDTH);
    int x, y;

    for (y = min_y; y <= max_y; y++) {
        for (x = min_x; x <= max_x; x++) {
            struct spotmap_tile_t *const tile = spot_find_tile(x, y);

            errcli(iterator(ind_spot, radius, tile, x, y));
        }
    }

    return 0;
}

error_return_t spot_link(spot_handle_t ind_spot, float radius) {
    errcli(_spot_check_index(ind_spot, "spot_link"));

    errcli(_spot_tile_iter(ind_spot, radius, _spot_link_callback));

    return 0;
}

error_return_t spot_unlink(spot_handle_t ind_spot, float radius) {
    errcli(_spot_check_index(ind_spot, "spot_unlink"));

    errcli(_spot_tile_iter(ind_spot, radius, _spot_unlink_callback));

    return 0;
}

spot_handle_t make_spot(float x, float y) {
    if (place_num_spots >= MAX_SPOTS) {
        errorac(ERR_PLACE_MAXED_SPOTS, -1, "make_spot");
    }

    place_spots[place_num_spots].x = x;
    place_spots[place_num_spots].y = y;

    return place_num_spots++;
}
