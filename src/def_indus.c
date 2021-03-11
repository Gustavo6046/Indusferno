/**
 * @file def_indus.c
 * @author Gustavo Rehermann (rehermann6046@gmail.com)
 * @brief Industry type definitions.
 * @version added in 0.1
 * @date 2021-03-11
 * 
 * @copyright Copyright (c)Gustavo Ramos Rehermann 2021. The MIT License.
 * 
 * All industry definitions.
 */

#include "industry.h"



/* Cargo Types

-1      (none)
0       Flesh
1       Bones
2       Brains
3       Hooves
4       Wart
5       Blood
6       Bottled Pain
7       Steel
8       Bonesteel
9       Fertilizer
10      Energy
11      Bottled Pride
12      Hate Ale
13      Gas
14      Goods
*/

const struct industry_type_t industry_types[MAX_INDUS_TYPES] = {
    { // Flesh Exsanguiner
        ISUPTYPE_CONVERT, // supply_type
        "Flesh Exsanguiner", // label
        "Seed_Industry_FleshExsanguiner", // spawner_type

        0.0, // base_production
        0.0, // boost_rate
        0.0, // boost_threshold
        512.0, // reach

        // accept
        { 0 /* Flesh */, -1 },
        { 1.0 },

        // supply
        { 5 /* Blood */, -1 },
        { 0.7 }
    },

    { // Hoof Smeltery
        ISUPTYPE_CONVERT, // supply_type
        "Hoof Smeltery", // label
        "Seed_Industry_HoofSmeltery", // spawner_type

        0.0, // base_production
        2.5, // boost_rate
        0.0, // boost_threshold
        512.0, // reach

        // accept
        { 3 /* Hooves */, 10 /* Energy */, -1 },
        { 0.8, 2.0, 0, 0 },

        // supply
        { 7 /* Steel */, 5 /* Blood */, -1 },
        { 1.1, 0.15 }
    },

    { // Wart Fields
        ISUPTYPE_BOOST, // supply_type
        "Wart Fields", // label
        "Seed_Industry_WartFields", // spawner_type

        12.0, // base_production
        3.0, // boost_rate
        20.0, // boost_threshold
        1200.0, // reach

        // accept
        { 9 /*Fertilizer */, -1 },
        { 1.0 },

        // supply
        { 4 /* Wart */, -1 },
        { 5.0 }
    },

    { // Neural Exciter
        ISUPTYPE_CONVERT, // supply_type
        "Neural Exciter", // label
        "Seed_Industry_NeuralExciter", // spawner_type

        0, // base_production
        1.6, // boost_rate
        0.0, // boost_threshold
        600.0, // reach

        // accept
        { 2 /* Brains */, 6 /* Bottled Pain */, -1 },
        { 0.4, 1.2 },

        // supply
        { 11 /* Bottled Pride */, -1 },
        { 2.0 }
    },  

    { // Bonesteel Refinery
        ISUPTYPE_CONVERT, // supply_type
        "Bonesteel Refinery", // label
        "Seed_Industry_BonesteelRefinery", // spawner_type

        0, // base_production
        1.8, // boost_rate
        0.0, // boost_threshold
        700.0, // reach

        // accept
        { 7 /* Steel */, 1 /* Bones */, -1 },
        { 0.6, 0.4 },

        // supply
        { 8 /* Bonesteel */, -1 },
        { 0.3 }
    },

    { // Brewery
        ISUPTYPE_CONVERT, // supply_type
        "Brewery", // label
        "Seed_Industry_Brewery", // spawner_type

        0, // base_production
        1.6, // boost_rate
        0.0, // boost_threshold
        512.0, // reach

        // accept
        { 11 /* Bottled Pride */, 4 /* Wart */, 0 /* Flesh */, -1 },
        { 1.2, 0.8, 0.3 },

        // supply
        { 9 /* Fertilizer */, 12  /* Hate Ale */, -1 },
        { 1.1, 0.4 }
    },

    { // Fermenting Pit
        ISUPTYPE_CONVERT, // supply_type
        "Fermenting Pit", // label
        "Seed_Industry_FermentingPit", // spawner_type

        0, // base_production
        1.6, // boost_rate
        0.0, // boost_threshold
        768.0, // reach

        // accept
        { 6 /* Bottled Pain */, 5 /* Blood */, 0 /* Flesh */, -1 },
        { 1.1, 0.8, 0.3 },

        // supply
        { 9 /* Fertilizer */, 13 /* Gas */, -1 },
        { 3.0, 8.0 }
    },

    { // Gas Furnace
        ISUPTYPE_CONVERT,
        "Gas Furnace",
        "Seed_Industry_GasFurnace",

        0,
        3.0,
        0.0,
        768.0,

        { 13 /* Gas */, -1 },
        { 1.0 },

        { 10 /* Energy */, -1 },
        { 0.2 }
    },

    { // Workshop
        ISUPTYPE_ASSEMBLE,
        "Workshop",
        "Seed_Industry_Workshop",

        0,
        2.5,
        0.0,
        512.0,

        { 8 /* Bonesteel */, 12 /* Hate Ale */, -1 },
        { 0.5, 1.25 },

        { 14 /* Goods */, -1 },
        { 1.75 }
    }
};