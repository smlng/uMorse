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
 * @defgroup umorse
 * @brief uMorse provides slim Morse encoding, decoding and output functionality
 *
 * @{
 * @file
 * @brief       Definition of the public uMorse interface
 *
 * @author      Sebastian Meiling <s@mlng.net>
 */

#ifndef UMORSE_H
#define UMORSE_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @name Configure debugging options
 * @{
 */
#ifndef DEBUG
#define DEBUG                   (0)
#endif

#if DEBUG
#define UMORSE_DEBUG(...)       printf(__VA_ARGS__)
#else
#define UMORSE_DEBUG(...)
#endif
/** @} */

/**
 * @name Representation of morse code elements
 * @{
 */
#define UMORSE_NUL              (0x0)   /**< 00 */
#define UMORSE_DIT              (0x1)   /**< 01 */
#define UMORSE_DAH              (0x2)   /**< 10 */
#define UMORSE_END_CHAR         (0x3)   /**< 11 */
#define UMORSE_END_WORD         (0xF)   /**< 11 11 */
#define UMORSE_END_STOP         (0xFF)  /**< 11 11 11 11 */
/** @} */

/**
 * @name Configuration parameters, offset, flags, bit masks and shifts
 * @{
 */
#define UMORSE_SHIFT            (0x2)
#define UMORSE_MASK             (0x3)
#define UMORSE_MASK_COUNT       (0x0F)
#define UMORSE_LETTER_OFFSET    (65U)   /**< 'A' */
#define UMORSE_NUMBER_OFFSET    (48U)   /**< '0' */
#define UMORSE_FLAG_NODELAY     (0x80)

#define UMORSE_THRESHOLD        (2U)
/** @} */

/**
 * @name Function flags
 * @{
 */
#define UMORSE_CODE_ALIGNED     (0x0)
#define UMORSE_CODE_COMPACT     (0x1)
/** @} */

/**
 * @name Timing parameters, in milli seconds
 * @{
 */
#ifndef UMORSE_DELAY_DIT
#define UMORSE_DELAY_DIT        (60U)
#endif
#define UMORSE_DELAY_DAH        (3 * UMORSE_DELAY_DIT)
#define UMORSE_DELAY_CHAR       (3 * UMORSE_DELAY_DIT)
#define UMORSE_DELAY_WORD       (7 * UMORSE_DELAY_DIT)
/** @} */

/**
 * @brief Function pointer definition
 */
typedef void(*umorse_fp_t)(void *args, uint8_t flags);

/**
 * @brief Output stream
 */
typedef struct {
    umorse_fp_t dit;    /**< function pointer to output a morse dit */
    umorse_fp_t dah;    /**< function pointer to output a morse dah */
    umorse_fp_t nil;    /**< function pointer to output a morse silent */
    void *params;       /**< stores common parameters for output functions */
} umorse_out_t;

/**
 * @brief   Encodes a given sting into morse code
 *
 * @param[in]   text    Input text string
 * @param[in]   tlen    Length of input string
 * @param[out]  code    Output buffer for encoded text
 * @param[in]   clen    Length of output buffer
 * @param[in]   flags   Optional flags
 *
 * @returns     lenght of bytes written to output buffer
 * @returns     < 0 on error
 */
int umorse_encode(const char *text, size_t tlen,
                  uint8_t *code, size_t clen, uint8_t flags);

/**
 * @brief   Encodes a given sting into morse code in aligned mode
 *
 * @note    This is a short hand function calling umorse_encode with flags
 *          set to UMORSE_CODE_ALIGNED.
 *
 * @param[in]   text    Input text string
 * @param[in]   tlen    Length of input string
 * @param[out]  code    Output buffer for encoded text
 * @param[in]   clen    Length of output buffer
 *
 * @returns     lenght of bytes written to output buffer
 * @returns     < 0 on error
 */
int umorse_encode_aligned(const char *text, size_t tlen,
                          uint8_t *code, size_t clen);

/**
 * @brief   Encodes a given sting into morse code in compact mode
 *
 * @note    This is a short hand function calling umorse_encode with flags
 *          set to UMORSE_CODE_COMPACT.
 *
 * @param[in]   text    Input text string
 * @param[in]   tlen    Length of input string
 * @param[out]  code    Output buffer for encoded text
 * @param[in]   clen    Length of output buffer
 *
 * @returns     lenght of bytes written to output buffer
 * @returns     < 0 on error
 */
int umorse_encode_compact(const char *text, size_t tlen,
                          uint8_t *code, size_t clen);

/**
 * @brief   Decodes a given morse code into a text string
 *
 * @param[in]   code    Input buffer with encoded text
 * @param[in]   clen    Length of input buffer
 * @param[out]  text    Ouptut for decoded text string
 * @param[in]   tlen    Length of output string buffer
 *
 * @returns     lenght of bytes written to output buffer
 * @returns     < 0 on error
 */
int umorse_decode(const uint8_t *code, size_t clen, char *text, size_t tlen);

/**
 * @brief   Outputs an morse encoded string using a given output interface
 *
 * @param[in]   out     Interface or device to output morse encoded buffer
 * @param[in]   code    Buffer with morse encoded text
 * @param[in]   clen    Length of morse encoded text
 * @param[in]   flags   Pass optional params, with [0-3]=count and [4-7]=flags
 *
 * @returns     0 or >0 on success
 * @returns     <0 on error
 */
int umorse_output(const umorse_out_t *out,
                  const uint8_t *code, size_t clen, uint8_t flags);

#ifdef __cplusplus
}
#endif

#endif /* UMORSE_H */
/** @} */
