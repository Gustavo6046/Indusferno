/**
 * @file company.c
 * @author Gustavo Rehermann (rehermann6046@gmail.com)
 * @brief Company implementation and their interactions with the world.
 * @version added in 0.1
 * @date 2021-03-12
 *
 * @copyright Copyright (c)Gustavo Ramos Rehermann 2021. The MIT License.
 */

#include <string.h>

#include "company.h"

struct company_t companies[MAX_COMPANIES];
size_t num_companies = 0;
float max_loan = DEFAULT_MAX_LOAN;

company_handle_t company_found_company(const char *const name, float initial_loan) {
    const company_handle_t company = num_companies++;

    strcpy(companies[company].name, name);

    companies[company].balance = 0.0;
    companies[company].debt = 0.0;
    companies[company].num_chairmen = 0;

    if (initial_loan > 0) {
        company_loan(company, initial_loan);
    }

    return company;
}

void company_add_chairman(company_handle_t company, unsigned int player_num) {
    if (company_has_chairman(company, player_num) > 0) {
        // already has this player as chairman
        return;
    }

    int index = companies[company].num_chairmen++;

    companies[company].chairmen[index] = player_num;
}

void company_remove_chairman(company_handle_t company, unsigned int player_num) {
    int index = 0;

    while (companies[company].chairmen[index] != player_num && index < companies[company].num_chairmen) {
        index++;
    }

    if (index == companies[company].num_chairmen) {
        // chairman not found
        return;
    }

    while (index < companies[company].num_chairmen) {
        if (index < MAX_CHAIRMEN_PER_COMPANY) {
            companies[company].chairmen[index] = companies[company].chairmen[index + 1];
        }

        index++;
    }

    return;
}

int company_has_chairman(company_handle_t company, unsigned int player_num) {
    for (int index = 0; index < companies[company].num_chairmen; index++) {
        if (companies[company].chairmen[index] == player_num) {
            return 1;
        }
    }

    return 0;
}

static void _company_dissolve(company_handle_t company) {
    // TODO: add code for dissolving company
}

/**
 * @brief Checks a company's financial health and stability.
 * 
 * Checks if a company is financially stable. If the balance, minus all
 * unpaid value (debt), happens to be of a lower value than the
 * negative of max_loan, this company is not financially healthy; then
 * destitute it and dissolve its assets.
 */
static void _company_check_healthy(company_handle_t company) {
    if (companies[company].balance - companies[company].debt < -max_loan) {
        _company_dissolve(company);
    }
}

static void _company_charge_interest(company_handle_t company) {
    if (companies[company].debt > 0) {
        company_add_to_balance(company, -companies[company].debt * DEFAULT_LOAN_INTEREST);
    }
}

void company_add_to_balance(company_handle_t company, float amount) {
    companies[company].balance += amount;

    if (amount < 0) {
        _company_check_healthy(company);
    }
}

void company_loan(company_handle_t company, float amount) {
    // Add to balance, but also debt.
    companies[company].balance += amount;
    companies[company].debt += amount;
}
