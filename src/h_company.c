/**
 * @file h_company.c
 * @author Gustavo Rehermann (rehermann6046@gmail.com)
 * @brief Company implementation and their interactions with the world.
 * @version added in 0.1
 * @date 2021-03-12
 *
 * @copyright Copyright (c)Gustavo Ramos Rehermann 2021. The MIT License.
 */

#include <string.h>

#include "m_error.h"
#include "h_company.h"


static struct company_t companies[MAX_COMPANIES];
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

static error_return_t _company_check_index(company_handle_t company) {
    if (company >= num_companies) {
        errori(ERR_COMPANY_BAD_INDEX);
    }

    return 0;
}

error_return_t company_add_chairman(company_handle_t company, unsigned int player_num) {
    static int index;

    errcli(_company_check_index(company));

    if (company_has_chairman(company, player_num) > 0) {
        errori(ERR_COMPANY_ALREADY_HAS_CHAIRMAN);
    }

    index = companies[company].num_chairmen++;

    companies[company].chairmen[index] = player_num;

    return 0;
}

error_return_t company_remove_chairman(company_handle_t company, unsigned int player_num) {
    static int index;

    errcli(_company_check_index(company));

    index = 0;

    while (companies[company].chairmen[index] != player_num && index < companies[company].num_chairmen) {
        index++;
    }

    if (index == companies[company].num_chairmen) {
        // chairman not found
        errori(ERR_COMPANY_ALREADY_HAS_NOT_CHAIRMAN);
    }

    while (index < companies[company].num_chairmen) {
        if (index < MAX_CHAIRMEN_PER_COMPANY) {
            companies[company].chairmen[index] = companies[company].chairmen[index + 1];
        }

        index++;
    }

    return 0;
}

error_return_t company_has_chairman(company_handle_t company, unsigned int player_num) {
    errcli(_company_check_index(company));

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

error_return_t company_add_to_balance(company_handle_t company, float amount) {
    errcli(_company_check_index(company));

    companies[company].balance += amount;

    if (amount < 0) {
        _company_check_healthy(company);
    }

    return 0;
}

error_return_t company_loan(company_handle_t company, float amount) {
    errcli(_company_check_index(company));

    if (amount > 0) {
        // offset to fit within max_loan
        if (companies[company].debt + amount > max_loan) {
            amount = max_loan - companies[company].debt;
        }

        if (amount == 0.0) {
            // amount cannot be loaned
            // (debt is already at max_loan)
            codei(ERR_COMPANY_LOAN_MAXED_OUT);
        }

        // add to balance, but also debt
        companies[company].balance += amount;
        companies[company].debt += amount;
    }

    else if (amount < 0) {
        // negate 'amount' for intuition's sake
        // (pay back a positive value, not loan a negative one)
        amount = -amount;

        // try to pay back
        if (amount > companies[company].debt) {
            amount = companies[company].debt;
        }

        if (amount > companies[company].balance) {
            // not within balance
            codei(ERR_COMPANY_LOAN_PAYBACK_EXCEED_BALANCE);
        }

        // withdraw from debt, but also balance
        companies[company].debt -= amount;
        companies[company].balance -= amount;
    }

    return 0;
}
