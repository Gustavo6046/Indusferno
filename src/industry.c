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


struct industry_t industries[MAX_INDUSTRIES];
int num_industries;

void industry_make_production(struct industry_t *const indus, const struct industry_type_t *const indtype, float amount) {
    int i;
    size_t cargo_type;
    float supply;

    for (i = 0; i < MAX_INDUS_MATS && indtype->supplies[i] != -1; i++) {
        supply = amount * indtype->supply_weight[i];
        cargo_type = indtype->supplies[i];

        indus->produced[i] += supply;
        
        // TODO: add actual cargo distribution code
    }
}

unsigned char industry_is_boosted(struct industry_t *const indus, const struct industry_type_t *const indtype) {
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

void industry_check_production(struct industry_t *const indus, const struct industry_type_t *const indtype) {
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
                    return;
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
            return;
    }

    // check if this industry is boosted
    boosted = industry_is_boosted(indus, indtype);

    if (boosted) {
        production *= indtype->boost_rate;
    }

    // apply production
    industry_make_production(indus, indtype, production);
}

void industry_accept_cargo(size_t ind_industry, size_t ind_accept, float amount) {
    struct industry_t *const indus = &industries[ind_industry];

    if (indus->type == -1) {
        error(ERR_INDUSTRY_BAD_INDEX);
    }

    const struct industry_type_t *const indtype = &industry_types[indus->type];

    if (indtype->supply_type == ISUPTYPE_UNKNOWN) {
        error(ERR_INDUSTRY_BAD_TYPE);
    }

    if (indtype->accepts[ind_accept] == -1) {
        error(ERR_INDUSTRY_BAD_ACCEPT);
    }

    indus->material[ind_accept] += amount;
    indus->material_tot += amount;

    industry_check_production(indus, indtype);
}
