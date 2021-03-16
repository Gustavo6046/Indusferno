/**
 * @file m_error.h
 * @author Gustavo Rehermann (rehermann6046@gmail.com)
 * @brief Error handling and signal propagation.
 * @version added in 0.1
 * @date 2021-03-11
 * 
 * Error signals in Indusferno, unlike the name might imply, actually
 * are responsible for handling many different kinds of edge cases,
 * most of which are, in fact, not fatal. Some, such as maxing out the
 * loan limit, aren't even out of the realm of possibilities in regular
 * gameplay, and thus aren't printed to the console even in the debug
 * build.
 * 
 * Many different error signal definitions exist within Indusferno, and
 * each serve their own specific purpose, but usually are grouped with
 * other error signals that are used in a similar context, such as
 * errors related to industry code.
 *
 * @copyright Copyright (c)Gustavo Ramos Rehermann 2021. The MIT License.
 */

#ifndef ERROR_H
#define ERROR_H

/**
 * @brief A list of error codes.
 *
 * An enum type that contains all the error codes that can be returned.
 *
 * Functions whose return type is of error_return_t can be interpreted
 * as possibly returning an error code if they are called under invalid
 * or otherwise erroneous circumstances. More precisely, they will
 * return the negative value of any error code in this list.
 *
 * Often, a function will produce an error and log it to the console if
 * a debug build is used. Other times, it will simply never log it; the
 * latter is generally used purely for caller signaling.
 *
 * It is better to use these error macros, as they handle those
 * details already: errori(), error(), codei(), errcli() and errclv().
 *
 * @see errori
 * @see error
 * @see codei
 * @see errcli
 * @see errclv
 */
enum error_code_t {
    ERR_INDUSTRY_BAD_INDEX,
    ERR_INDUSTRY_BAD_TYPE,
    ERR_INDUSTRY_BAD_SUP_TYPE,
    ERR_INDUSTRY_BAD_ACCEPT,
    ERR_COMPANY_BAD_INDEX,
    ERR_COMPANY_ALREADY_HAS_CHAIRMAN,
    ERR_COMPANY_ALREADY_HAS_NOT_CHAIRMAN,
    ERR_COMPANY_LOAN_PAYBACK_EXCEED_BALANCE,
    ERR_COMPANY_LOAN_MAXED_OUT,
    ERR_STATION_BAD_INDEX,
    ERR_PLACE_BAD_SPOT_INDEX,
    ERR_PLACE_UNLINK_SPOT_NOT_FOUND,
    ERR_PLACE_MAXED_SPOTS,
    ERR_BAD_MATERIAL
};

/**
 * @brief An error code returned from afunction.
 *
 * More specifically, it is a type that denotes that a
 * negative value is an error code, more precisely the
 * negative of any value in error_code_t.
 */
typedef signed int error_return_t;

/**
 * @brief Logs an error to the console if debugging, and returns it.
 */
#define errori(error_code) { _error((error_code)); return -(error_code); }

/**
 * @brief Logs an error to the console if debugging, and returns void.
 */
#define errorv(error_code) { _error((error_code)); return; }

/**
 * @brief Logs an error to the console if debugging, and returns value.
 */
#define errora(error_code, value) { _error((error_code)); return value; }

/**
 * @brief Logs an error with context if debugging, and returns it.
 */
#define erroric(error_code, ctx) { _error_c((error_code), (ctx)); return -(error_code); }

/**
 * @brief Logs an error with context if debugging, and returns void.
 */
#define errorvc(error_code, ctx) { _error_c((error_code), (ctx)); return; }

/**
 * @brief Logs an error with context if debugging, and returns value.
 */
#define errorac(error_code, value, ctx) { _error_c((error_code), (ctx)); return value; }

/**
 * @brief Returns an error code as a signal. without ever logging it.
 */
#define codei(error_code) { return -error_code; }

/**
 * @brief Checks if a function returns an error, and if so returns.
 *
 * Can be used to abort the normal execution of a function when an
 * error is encountered.
 *
 * Please note that 'errcli' (and returning the * error code) is
 * preferred, if possible; otherwise, there may be no way of notifying
 * the caller that an error occurred.
 */
#define errclv(expr) { int erri = (expr); if (erri < 0) { return; } }

/**
 * @brief Checks if a function returns an error, and if so returns it.
 *
 * Can be used to propagate error codes back when they occur in called
 * functions. This is, indeed, the preferred method, as it allows the
 * further propagation of error values by signal-aware callers.
 */
#define errcli(expr) { int erri = (expr); if (erri < 0) { return erri; } }

/**
 * @brief Checks if a function returns an error, and if so returns.
 *
 * Can be used to abort the normal execution of a function when an
 * error is encountered, by returning value.
 *
 * Please note that 'errcli' (and returning the error code) is
 * preferred, if possible; otherwise, there may be no way of notifying
 * the caller that an error occurred.
 */
#define errcla(expr, value) { int erri = (expr); if (erri < 0) { return value; } }

/**
 *
 * @brief Checks if a function returns an error, and if so run block.
 *
 * Use this as an if statement with your desired expression, if you
 * want to run code conditionally and use the error value (use _err for
 * the latter purpose). If you instead merely want to return, use
 * errcli if you want to return it back too, or errclv otherwise.
 *
 * E.g.
 *
 *  <code>
 *      iferr(my_very_flimsy_carousel(CAROUSEL_SPEED_VERY_FAST)) {
 *          printf("\"Ouch! The carousel broke!\\" \n");
 *          return _err;
 *      }
 *  </code>
 *
 * @see _err
 * @see errcli
 * @see errclv
 */
#define iferr(expr) _err = (expr); if (_err < 0)

/**
 * @brief The last error value stored from an iferr macro call.
 */
extern error_return_t _err;

/**
 * @brief Prints an error.
 *
 * @param error_code The positive code of the error to be printed.
 */
void _error(enum error_code_t error_code);

/**
 * @brief Prints an error with context.
 *
 * @param error_code The positive code of the error to be printed.
 * @param context The context name to be printed alongside the error.
 */
void _error_c(enum error_code_t error_code, const char *context);

/**
 * @brief The context of an error.
 *
 * Set to include the context of an error when printing it.
 */
extern const char *error_ctx;


#endif // ERROR_H
