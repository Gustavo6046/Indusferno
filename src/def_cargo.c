/**
 * @file def_cargo.c
 * @author Gustavo Rehermann (rehermann6046@gmail.com)
 * @brief Cargo type definitions.
 * @version added in 0.1
 * @date 2021-03-11
 * 
 * @copyright Copyright (c)Gustavo Ramos Rehermann 2021. The MIT License.
 * 
 * All cargo definitions.
 */

#include "cargo.h"


const struct cargo_t cargo_types[] = {
    {
        "Flesh",
        "kg",

        // there are 920 grams in a litre of human adipose tissue, and
        // a thousand grams in a kg
        (920 << 9) / 1000 
    },

    {
        "Bones",
        "l",

        // in litres    
        512
    },

    {
        "Brains",
        "kg",

        // an average human brain's density is 1.1 grams per cubic
        // centimetre (1100 grams per litre)
        (1100 << 9) / 1000
    },

    {
        "Hooves",
        "kg",

        // hell's hooves are made out of steel.
        // see Steel
        (7859 << 9) / 1000
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
        "Steel",
        "kg",

        // the density of average steel is 7859 g/L
        (7859 << 9) / 1000
    },

    {
        "Bonesteel",
        "kg",

        // Steel, except a bit lighter due to the infusion
        // of bone tissue.
        (7100 << 9) / 1000
    },

    {
        "Fertilizer",
        "kg",

        // WolframAlpha's average fertilizer has 961 grams per litre
        (961 << 9) / 1000
    },

    {
        "Energy",
        "l",

        512 // I know, not very lifelike
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
        (3500 << 9) / 1000
    }
};