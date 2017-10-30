/*
 * Copyright (C) 2017 Sebastian Meiling <s@mlng.net>
 *
 * This file is part of uMorse, see
 * https://github.com/smlng/uMorse
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file LICENSE in the top level directory for more details.
 *
 * If you did not receive a copy of the license file, see
 * https://choosealicense.com/licenses/mit/
 */

/**
 * @ingroup     umorse
 * @{
 * @file
 * @brief       Definition of a uMorse output interface printing to stdout
 *
 * @author      Sebastian Meiling <s@mlng.net>
 */
#ifndef UMORSE_PRINT_H
#define UMORSE_PRINT_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief   Print Morse Code DIT (short)
 *
 * @param[in]   args    unused
 * @param[in]   flags   Control flags
 */
void umorse_print_dit(void *args, uint8_t flags);

/**
 * @brief   Print Morse Code DAH (long)
 *
 * @param[in]   args    unused
 * @param[in]   flags   Control flags
 */
void umorse_print_dah(void *args, uint8_t flags);

/**
 * @brief   Print Morse Code NIL (silent)
 *
 * @param[in]   args    unused
 * @param[in]   flags   Control flags
 */
void umorse_print_nil(void *args, uint8_t flags);

#ifdef __cplusplus
}
#endif

#endif /* UMORSE_PRINT_H */
/** @} */
