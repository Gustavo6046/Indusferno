/**
 * @file h_cargo.c
 * @author Gustavo Rehermann (rehermann6046@gmail.com)
 * @brief Cargo type definitions.
 * @version added in 0.1
 * @date 2021-03-11
 *
 * @copyright Copyright (c)Gustavo Ramos Rehermann 2021. The MIT License.
 *
 * All cargo definitions.
 */

#include "h_cargo.h"


const struct cargo_t cargo_types[] = {
    {
        // there are 920 grams in a litre of human adipose tissue, and
        // a thousand grams in a kg

        "Flesh",
        "kg",
        (920 * 512) / 1000
    },

    {
        "Bones",
        "l",

        // in litres
        512
    },

    {
        // an average human brain's density is 1.1 grams per cubic
        // centimetre (1100 grams per litre)

        "Brains",
        "kg",
        (1100 * 512) / 1000
    },

    {
        // hell's hooves are made out of steel.
        // see Steel

        "Hooves",
        "kg",
        (7859 * 512) / 1000
    },

    {
        "Wart",
        "l",
        512 // litres of crop harvest
    },

    {
        "Blood",
        "l",
        512 // litres of blood
    },

    {
        "Bottled Pain",
        "l",
        512 // litres of pain lol
    },

    {
        // the density of average steel is 7859 g/L

        "Steel",
        "kg",
        (7859 * 512) / 1000
    },

    {
        // Steel, except a bit lighter due to the infusion
        // of bone tissue.

        "Bonesteel",
        "kg",
        (7100 * 512) / 1000
    },

    {
        // WolframAlpha's average fertilizer has 961 grams per litre

        "Fertilizer",
        "kg",
        (961 * 512) / 1000
    },

    {
        "Energy",
        "kJ",
        (25400 * 512) // 25400 kJ required to boil 10L of water, in 1L of energy
    },

    {
        "Bottled Pride",
        "l",
        512
    },

    {
        "Hate Ale",
        "l",
        512
    },

    {
        // 'Biogas' would be a bit of an oxymoron; it is made from the dead.
        // 'Necrogas' on the other hand sounds too much like a nerve agent.
        // Not very fuel-grade.

        "Gas",
        "l",
        512
    },

    {
        "Goods",
        "kg",
        (3500 * 512) / 1000
    },

    {
        // The density of silicon is 2330 g/L.
        "Silicon",
        "kg",
        (2330 * 512) / 1000
    },

    {
        "Microchips",
        "l",
        512
    }
};