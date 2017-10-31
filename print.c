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
 * @brief       Implementation of uMorse output interface printing to stdout
 *
 * @author      Sebastian Meiling <s@mlng.net>
 * @}
 */

#include <stdint.h>

#ifndef UMORSE_PRINT
#include <stdio.h>
#define UMORSE_PRINT(...)       printf(__VA_ARGS__)
#endif

#ifndef UMORSE_MSLEEP
#include <unistd.h>
#define UMORSE_MSLEEP(m)        usleep(m * 1000U)
#endif

#include "print.h"
#include "umorse.h"

void umorse_print_dit(void *args, uint8_t flags)
{
    (void) args;

    UMORSE_PRINT(".");
    if (!(flags & UMORSE_FLAG_NODELAY)) {
        UMORSE_MSLEEP(UMORSE_DELAY_DIT);
    }
}

void umorse_print_dah(void *args, uint8_t flags)
{
    (void) args;

    UMORSE_PRINT("_");
    if (!(flags & UMORSE_FLAG_NODELAY)) {
        UMORSE_MSLEEP(UMORSE_DELAY_DAH);
    }
}

void umorse_print_nil(void *args, uint8_t flags)
{
    (void) args;

    uint8_t cnt = flags & UMORSE_MASK_COUNT;
    if (cnt > 7) {
        UMORSE_PRINT("\n");
    }
    else if (cnt > 3) {
        UMORSE_PRINT(" / ");
    }
    else if (cnt > 1) {
        UMORSE_PRINT(" ");
    }

    if (!(flags & UMORSE_FLAG_NODELAY)) {
        while (cnt--) {
            UMORSE_MSLEEP(UMORSE_DELAY_DIT);
        }
    }
}
