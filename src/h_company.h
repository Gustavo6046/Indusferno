/**
 * @file h_company.h
 * @author Gustavo Rehermann (rehermann6046@gmail.com)
 * @brief Companies and their assets.
 * @version added in 0.1
 * @date 2021-03-12
 *
 * @copyright Copyright (c)Gustavo Ramos Rehermann 2021. The MIT License.
 */

#ifndef COMPANY_H
#define COMPANY_H

#include <stddef.h>

#include "m_error.h"


/**
 * @brief The maximum number of chairmen that can share a company.
 */
#define MAX_CHAIRMEN_PER_COMPANY 8

/**
 * @brief The maximum number of companies that can populate the world.
 */
#define MAX_COMPANIES 64

/**
 * @brief The initial maximum amount that can be owed to the bank.
 */
#define DEFAULT_MAX_LOAN 20000

/**
 * @brief The initial interest rate of loans taken from the bank.
 */
#define DEFAULT_LOAN_INTEREST 5


/**
 * @brief A company.
 */
struct company_t {
    /**
     * @brief The name of the company.
     */
    char name[128];

    /**
     * @brief The current liquid balance of the company.
     *
     * What gold there is available to be immediately spent
     * (i.e. liquid assets).
     */
    float balance;

    /**
     * @brief How much this company owes to the bank.
     *
     * Debt is the amount of money in loans a company has taken out and
     * not yet paid back.
     */
    float debt;

    /**
     * @brief The list of managing players.
     *
     * Each number is the PlayerNumber of a player managing this
     * company.
     *
     * In a singleplayer game, only the first item will be set. In a
     * multiplayer game, this must be updated manually when players
     * join and leave.
     */
    unsigned int chairmen[MAX_CHAIRMEN_PER_COMPANY];

    /**
     * @brief The number of managing players.
     *
     * The number, between 0 and 8, of players managing this company.
     */
    unsigned char num_chairmen;
};

/**
 * @brief Count of all companies currently in the game.
 */
extern size_t num_companies;

/**
 * @brief The maximum loan that can be taken out by a company.
 */
extern float max_loan;

/**
 * @brief An index to a company.
 */
typedef const size_t company_handle_t;

/**
 * @brief Founds a new company.
 *
 * @param name The name of the new company, as a string.
 * @param initial_loan An initial loan to be taken out, up to max_loan.
 * @return company_handle_t The handle to the new company created.
 */
company_handle_t company_found_company(const char *const name, float initial_loan);

/**
 * @brief Adds a player as a chairman of a company.
 *
 * @param company The company to add the chairman to.
 * @param player_num The player number to add as a chairman.
 */
error_return_t company_add_chairman(company_handle_t company, unsigned int player_num);

/**
 * @brief Removes a player as a chairman from a company.
 *
 * @param company The company to remove the chairman from.
 * @param player_num The player number to remove as a chairman.
 */
error_return_t company_remove_chairman(company_handle_t company, unsigned int player_num);

/**
 * @brief Checks whether a company has a specified player as chairman.
 *
 * @param company The company on the which to check.
 * @param player_num The player number to check about.
 * @return int 1 if the player is found to be a chairman, otherwise 0.
 */
error_return_t company_has_chairman(company_handle_t company, unsigned int player_num);

/**
 * @brief Adds to the balance of a company.
 *
 * Adds a certain amount to the liquid and immediately spendable
 * balance of a company, effective immediately.
 *
 * Use a negative amount to withdraw an arbitrary amount of money
 * from the company.
 *
 * @param company The company to add the amount to.
 * @param amount The amount to add to the company's balance.
 */
error_return_t company_add_to_balance(company_handle_t company, float amount);

/**
 * @brief Loans to the balance of a company.
 *
 * Adds a loan to the liquid and immediately spendable balance of a
 * company, effective immediately.
 *
 * The loan is counted toward the company's loan counter. It is capped
 * to max_loan, as usual.
 *
 * Use negative amounst to try to pay back existing debt. This will
 * fail if:
 *
 * a) the company has already paid back all their loans;
 *
 * b) the value to be paid back exceeds the company's balance.
 *
 * @param company The company to loan to or pay back from.
 * @param amount The amount to be loaned, or if negative, to be paid back.
 */
error_return_t company_loan(company_handle_t company, float amount);


#endif // COMPANY_H
