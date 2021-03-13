/**
 * @file industry.c
 * @author Gustavo Rehermann (rehermann6046@gmail.com)
 * @brief Industry logic.
 * @version added in 0.1
 * @date 2021-03-11
 *
 * @copyright Copyright (c)Gustavo Ramos Rehermann 2021. The MIT License.
 *
 * The logic of how industries operate and produce.
 */

#include "industry.h"
#include "error.h"


static struct industry_t industries[MAX_INDUSTRIES];
int num_industries;

/**
 * @brief All definitions of industry types in the game.
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
        1, { 0 /* Flesh */ },
        { 1.0 },

        // supply
        1, { 5 /* Blood */ },
        { 0.7, }
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
        2, { 3 /* Hooves */, 10 /* Energy */ },
        { 0.8, 2.0, 0, 0 },

        // supply
        2, { 7 /* Steel */, 5 /* Blood */ },
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
        1, { 9 /*Fertilizer */ },
        { 1.0 },

        // supply
        1, { 4 /* Wart */ },
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
        2, { 2 /* Brains */, 6 /* Bottled Pain */ },
        { 0.4, 1.2 },

        // supply
        1, { 11 /* Bottled Pride */ },
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
        2, { 7 /* Steel */, 1 /* Bones */ },
        { 0.6, 0.4 },

        // supply
        1, { 8 /* Bonesteel */ },
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
        3, { 11 /* Bottled Pride */, 4 /* Wart */, 0 /* Flesh */ },
        { 1.2, 0.8, 0.3 },

        // supply
        2, { 9 /* Fertilizer */, 12  /* Hate Ale */ },
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
        3, { 6 /* Bottled Pain */, 5 /* Blood */, 0 /* Flesh */ },
        { 1.1, 0.8, 0.3 },

        // supply
        2, { 9 /* Fertilizer */, 13 /* Gas */ },
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

        1, { 13 /* Gas */ },
        { 1.0 },

        1, { 10 /* Energy */ },
        { 0.2 }
    },

    { // Artisan Workshop
        ISUPTYPE_CONVERT,
        "Artisan Workshop",
        "Seed_Industry_ArtisanWorkshop",

        0,
        2.5,
        0.0,
        512.0,

        3, { 8 /* Bonesteel */, 12 /* Hate Ale */, 16 /* Microchips */ },
        { 0.5, 1.8, 1.1 },

        1, { 14 /* Goods */ },
        { 1.5 }
    },

    { // Silicon Furnace
        ISUPTYPE_ASSEMBLE,
        "Silicon Furnace",
        "Seed_Industry_SiliconFurnace",

        0,
        2.5,
        0.0,
        512.0,

        2, { 1 /* Bonesteel */, 13 /* Gas */ },
        { 0.5, 1.25 },

        1, { 15 /* Silicon */ },
        { 0.8 }
    },

    { // Semiconductor Factory
        ISUPTYPE_CONVERT,
        "Semiconductor Factory",
        "Seed_Industry_SemiconductorFactory",

        0,
        2.5,
        0.0,
        768.0,

        3, { 15 /* Silicon */, 2 /* Brains */, 10 /* Energy */ },
        { 0.5, 1.0, 0.5 },

        1, { 16 /* Microchips */ },
        { 2.5 }
    }
};


static error_return_t _industry_check_index(industry_handle_t ind_industry, const char *const ctx) {
    if (ind_industry >= num_industries || industries[ind_industry].type == -1) {
        erroric(ERR_INDUSTRY_BAD_INDEX, ctx);
    }

    if (industry_types[industries[ind_industry].type].supply_type == ISUPTYPE_UNKNOWN) {
        erroric(ERR_INDUSTRY_BAD_TYPE, ctx);
    }

    return 0;
}

static error_return_t _industry_check_index_and_accept(industry_handle_t ind_industry, size_t accept, const char *const ctx) {
    errcli(_industry_check_index(ind_industry, ctx));

    if (accept >= industry_types[industries[ind_industry].type].num_accepts || industry_types[industries[ind_industry].type].accepts[accept] == -1) {
        erroric(ERR_INDUSTRY_BAD_ACCEPT, ctx);
    }

    return 0;
}

error_return_t industry_make_production(industry_handle_t ind_industry, float amount) {
    errcli(_industry_check_index(ind_industry, "industry_check_production"));

    struct industry_t *const indus = &industries[ind_industry];
    const struct industry_type_t *const indtype = &industry_types[indus->type];

    int i;
    size_t cargo_type;
    float supply;

    for (i = 0; i < MAX_INDUS_MATS && indtype->supplies[i] != -1; i++) {
        supply = amount * indtype->supply_weight[i];
        cargo_type = indtype->supplies[i];

        indus->produced[i] += supply;

        // TODO: add actual cargo distribution code
    }

    return 0;
}

unsigned char industry_is_boosted(industry_handle_t ind_industry) {
    errcla(_industry_check_index(ind_industry, "industry_check_production"), 0);

    struct industry_t *const indus = &industries[ind_industry];
    const struct industry_type_t *const indtype = &industry_types[indus->type];

    int i;

    switch (indtype->supply_type) {
        case ISUPTYPE_CONVERT:
            // check if all cargo types are received
            for (i = 0; i < MAX_INDUS_MATS && indtype->accepts[i] != -1; i++) {
                if (indus->material[i] == 0) {
                    // this cargo type is not received
                    return 0;
                }
            }

            return 1;

        case ISUPTYPE_BOOST:
            return indus->material_tot >= indtype->boost_threshold;

        default:
            break;
    }

    return 0;
}

error_return_t industry_check_production(industry_handle_t ind_industry) {
    errcli(_industry_check_index(ind_industry, "industry_check_production"));

    struct industry_t *const indus = &industries[ind_industry];
    const struct industry_type_t *const indtype = &industry_types[indus->type];

    int boosted = 0;
    int i;
    float production = 0.0;
    float spent_mat = 0.0;

    // check if industry is producing at all, and spend cargos
    switch (indtype->supply_type) {
        case ISUPTYPE_ASSEMBLE:
            // produce only if all cargo types are received
            for (i = 0; i < MAX_INDUS_MATS && indtype->accepts[i] != -1; i++) {
                if (indus->material[i] == 0) {
                    // do not produce, no material of this type
                    erroric(ERR_BAD_MATERIAL, "industry_check_production");
                }

                if (spent_mat == 0.0 || spent_mat > indus->material[i]) {
                    spent_mat = indus->material[i];
                }
            }

            // spend cargos
            for (i = 0; i < MAX_INDUS_MATS; i++) {
                if (indtype->accepts[i] == -1) {
                    break;
                }

                production += spent_mat;
                indus->material[i] -= spent_mat;
            }

        case ISUPTYPE_CONVERT:
            // produce for every cargo type
            for (i = 0; i < MAX_INDUS_MATS && indtype->accepts[i] != -1; i++) {
                if (indus->material[i] == 0.0) {
                    continue;
                }

                production += indus->material[i];
                indus->material[i] = 0.0;
            }

            break;

        case ISUPTYPE_BOOST:
            // always produce at least base rate
            production = indtype->base_production;
            break;

        default:
            erroric(ERR_INDUSTRY_BAD_SUP_TYPE, "industry_check_production");
    }

    // check if this industry is boosted
    boosted = industry_is_boosted(ind_industry);

    if (boosted) {
        production *= indtype->boost_rate;
    }

    // apply production
    industry_make_production(ind_industry, production);

    return 0;
}

error_return_t industry_accept_cargo(industry_handle_t ind_industry, size_t ind_accept, float amount) {
    errcli(_industry_check_index_and_accept(ind_industry, ind_accept, "industry_accept_cargo"));

    struct industry_t *const indus = &industries[ind_industry];

    indus->material[ind_accept] += amount;
    indus->material_tot += amount;

    industry_check_production(ind_industry);

    return 0;
}
