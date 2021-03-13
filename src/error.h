/**
 * @file error.h
 * @author Gustavo Rehermann (rehermann6046@gmail.com)
 * @brief Error codes.
 * @version added in 0.1
 * @date 2021-03-11
 *
 * @copyright Copyright (c)Gustavo Ramos Rehermann 2021. The MIT License.
 */

#ifndef ERROR_H
#define ERROR_H

// Error codes.
enum error_code_t {
    ERR_INDUSTRY_BAD_INDEX,
    ERR_INDUSTRY_BAD_TYPE,
    ERR_INDUSTRY_BAD_ACCEPT,
    ERR_COMPANY_BAD_INDEX,
    
};

#define errori(error_code) { _error(error_code); return -error_code; }
#define error(error_code) { _error(error_code); return; }

#define errclv(expr) { int erri = (expr); if (erri < 0) { errv(-erri); } }
#define errcli(expr) { int erri = (expr); if (erri < 0) { erri(-erri); } }

/**
 * @brief Prints an error.
 * 
 * @param error_code The code of the error to be printed.
 */
void _error(enum error_code_t error_code);


#endif // ERROR_H