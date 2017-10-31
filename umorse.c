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
 * @brief       Implementation of uMorse core functions
 *
 * @author      Sebastian Meiling <s@mlng.net>
 * @}
 */

#include <assert.h>

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include "umorse.h"

static const uint8_t umorse_letters[] = {
    (UMORSE_DIT | (UMORSE_DAH << (1 * UMORSE_SHIFT))),  /**< ._     = A */
    (UMORSE_DAH | (UMORSE_DIT << (1 * UMORSE_SHIFT))
                | (UMORSE_DIT << (2 * UMORSE_SHIFT))
                | (UMORSE_DIT << (3 * UMORSE_SHIFT))),  /**< _...   = B */
    (UMORSE_DAH | (UMORSE_DIT << (1 * UMORSE_SHIFT))
                | (UMORSE_DAH << (2 * UMORSE_SHIFT))
                | (UMORSE_DIT << (3 * UMORSE_SHIFT))),  /**< _._.   = C */
    (UMORSE_DAH | (UMORSE_DIT << (1 * UMORSE_SHIFT))
                | (UMORSE_DIT << (2 * UMORSE_SHIFT))),  /**< _..    = D */
    (UMORSE_DIT),                                       /**< .      = E */
    (UMORSE_DIT | (UMORSE_DIT << (1 * UMORSE_SHIFT))
                | (UMORSE_DAH << (2 * UMORSE_SHIFT))
                | (UMORSE_DIT << (3 * UMORSE_SHIFT))),  /**< .._.   = F */
    (UMORSE_DAH | (UMORSE_DAH << (1 * UMORSE_SHIFT))
                | (UMORSE_DIT << (2 * UMORSE_SHIFT))),  /**< __.    = G */
    (UMORSE_DIT | (UMORSE_DIT << (1 * UMORSE_SHIFT))
                | (UMORSE_DIT << (2 * UMORSE_SHIFT))
                | (UMORSE_DIT << (3 * UMORSE_SHIFT))),  /**< ....   = H */
    (UMORSE_DIT | (UMORSE_DIT << (1 * UMORSE_SHIFT))),  /**< ..     = I */
    (UMORSE_DIT | (UMORSE_DAH << (1 * UMORSE_SHIFT))
                | (UMORSE_DAH << (2 * UMORSE_SHIFT))
                | (UMORSE_DAH << (3 * UMORSE_SHIFT))),  /**< .___   = J */
    (UMORSE_DAH | (UMORSE_DIT << (1 * UMORSE_SHIFT))
                | (UMORSE_DAH << (2 * UMORSE_SHIFT))),  /**< _._    = K */
    (UMORSE_DIT | (UMORSE_DAH << (1 * UMORSE_SHIFT))
                | (UMORSE_DIT << (2 * UMORSE_SHIFT))
                | (UMORSE_DIT << (3 * UMORSE_SHIFT))),  /**< ._..   = L */
    (UMORSE_DAH | (UMORSE_DAH << (1 * UMORSE_SHIFT))),  /**< __     = M */
    (UMORSE_DAH | (UMORSE_DIT << (1 * UMORSE_SHIFT))),  /**< _.     = N */
    (UMORSE_DAH | (UMORSE_DAH << (1 * UMORSE_SHIFT))
                | (UMORSE_DAH << (2 * UMORSE_SHIFT))),  /**< ___    = O */
    (UMORSE_DIT | (UMORSE_DAH << (1 * UMORSE_SHIFT))
                | (UMORSE_DAH << (2 * UMORSE_SHIFT))
                | (UMORSE_DIT << (3 * UMORSE_SHIFT))),  /**< .__.   = P */
    (UMORSE_DAH | (UMORSE_DAH << (1 * UMORSE_SHIFT))
                | (UMORSE_DIT << (2 * UMORSE_SHIFT))
                | (UMORSE_DAH << (3 * UMORSE_SHIFT))),  /**< __._   = Q */
    (UMORSE_DIT | (UMORSE_DAH << (1 * UMORSE_SHIFT))
                | (UMORSE_DIT << (2 * UMORSE_SHIFT))),  /**< ._.    = R */
    (UMORSE_DIT | (UMORSE_DIT << (1 * UMORSE_SHIFT))
                | (UMORSE_DIT << (2 * UMORSE_SHIFT))),  /**< ...    = S */
    (UMORSE_DAH),                                       /**< _      = T */
    (UMORSE_DIT | (UMORSE_DIT << (1 * UMORSE_SHIFT))
                | (UMORSE_DAH << (2 * UMORSE_SHIFT))),  /**< .._    = U */
    (UMORSE_DIT | (UMORSE_DIT << (1 * UMORSE_SHIFT))
                | (UMORSE_DIT << (2 * UMORSE_SHIFT))
                | (UMORSE_DAH << (3 * UMORSE_SHIFT))),  /**< ..._   = V */
    (UMORSE_DIT | (UMORSE_DAH << (1 * UMORSE_SHIFT))
                | (UMORSE_DAH << (2 * UMORSE_SHIFT))),  /**< .__    = W */
    (UMORSE_DAH | (UMORSE_DIT << (1 * UMORSE_SHIFT))
                | (UMORSE_DIT << (2 * UMORSE_SHIFT))
                | (UMORSE_DAH << (3 * UMORSE_SHIFT))),  /**< _.._   = X */
    (UMORSE_DAH | (UMORSE_DIT << (1 * UMORSE_SHIFT))
                | (UMORSE_DAH << (2 * UMORSE_SHIFT))
                | (UMORSE_DAH << (3 * UMORSE_SHIFT))),  /**< _.__   = Y */
    (UMORSE_DAH | (UMORSE_DAH << (1 * UMORSE_SHIFT))
                | (UMORSE_DIT << (2 * UMORSE_SHIFT))
                | (UMORSE_DIT << (3 * UMORSE_SHIFT))),  /**< __..   = Z */
};

static const uint16_t umorse_numbers[] = {
    (UMORSE_DAH | (UMORSE_DAH << (1 * UMORSE_SHIFT))
                | (UMORSE_DAH << (2 * UMORSE_SHIFT))
                | (UMORSE_DAH << (3 * UMORSE_SHIFT))
                | (UMORSE_DAH << (4 * UMORSE_SHIFT))),  /**< _____  = 0 */
    (UMORSE_DIT | (UMORSE_DAH << (1 * UMORSE_SHIFT))
                | (UMORSE_DAH << (2 * UMORSE_SHIFT))
                | (UMORSE_DAH << (3 * UMORSE_SHIFT))
                | (UMORSE_DAH << (4 * UMORSE_SHIFT))),  /**< .____  = 1 */
    (UMORSE_DIT | (UMORSE_DIT << (1 * UMORSE_SHIFT))
                | (UMORSE_DAH << (2 * UMORSE_SHIFT))
                | (UMORSE_DAH << (3 * UMORSE_SHIFT))
                | (UMORSE_DAH << (4 * UMORSE_SHIFT))),  /**< ..___  = 2 */
    (UMORSE_DIT | (UMORSE_DIT << (1 * UMORSE_SHIFT))
                | (UMORSE_DIT << (2 * UMORSE_SHIFT))
                | (UMORSE_DAH << (3 * UMORSE_SHIFT))
                | (UMORSE_DAH << (4 * UMORSE_SHIFT))),  /**< ...__  = 3 */
    (UMORSE_DIT | (UMORSE_DIT << (1 * UMORSE_SHIFT))
                | (UMORSE_DIT << (2 * UMORSE_SHIFT))
                | (UMORSE_DIT << (3 * UMORSE_SHIFT))
                | (UMORSE_DAH << (4 * UMORSE_SHIFT))),  /**< ...._  = 4 */
    (UMORSE_DIT | (UMORSE_DIT << (1 * UMORSE_SHIFT))
                | (UMORSE_DIT << (2 * UMORSE_SHIFT))
                | (UMORSE_DIT << (3 * UMORSE_SHIFT))
                | (UMORSE_DIT << (4 * UMORSE_SHIFT))),  /**< .....  = 5 */
    (UMORSE_DAH | (UMORSE_DIT << (1 * UMORSE_SHIFT))
                | (UMORSE_DIT << (2 * UMORSE_SHIFT))
                | (UMORSE_DIT << (3 * UMORSE_SHIFT))
                | (UMORSE_DIT << (4 * UMORSE_SHIFT))),  /**< _....  = 6 */
    (UMORSE_DAH | (UMORSE_DAH << (1 * UMORSE_SHIFT))
                | (UMORSE_DIT << (2 * UMORSE_SHIFT))
                | (UMORSE_DIT << (3 * UMORSE_SHIFT))
                | (UMORSE_DIT << (4 * UMORSE_SHIFT))),  /**< __...  = 7 */
    (UMORSE_DAH | (UMORSE_DAH << (1 * UMORSE_SHIFT))
                | (UMORSE_DAH << (2 * UMORSE_SHIFT))
                | (UMORSE_DIT << (3 * UMORSE_SHIFT))
                | (UMORSE_DIT << (4 * UMORSE_SHIFT))),  /**< ___..  = 8 */
    (UMORSE_DAH | (UMORSE_DAH << (1 * UMORSE_SHIFT))
                | (UMORSE_DAH << (2 * UMORSE_SHIFT))
                | (UMORSE_DAH << (3 * UMORSE_SHIFT))
                | (UMORSE_DIT << (4 * UMORSE_SHIFT))),  /**< ____.  = 9 */
};

static inline char _to_upper(char c)
{
    assert ((c >= 'a') && (c <= 'z'));

    return (c - 32);
}

static inline char _is_letter(const char l)
{
    if ((l >= 'A') && (l <= 'Z')) {
        return l;
    }
    else if ((l >= 'a') && (l <= 'z')) {
        return _to_upper(l);
    }

    return 0;
}

static inline char _is_number(const char n)
{
    if ((n >= '0') && (n <= '9')) {
        return n;
    }
    return 0;
}

static inline char _is_space(const char s)
{
    if ((s == '\t') || (s == ' ')) {
        return ' ';
    }
    return 0;
}

static inline char _is_stop(const char s)
{
    if ((s > 0) && (s < ' ') && !_is_space(s)) {
        return '\n';
    }
    return 0;
}

size_t _encode_compact(uint16_t cc, uint8_t *code, size_t clen, size_t cpos)
{
    assert (cpos < clen);
    (void) clen;

    unsigned shift = 0;

    while (((code[cpos] >> (shift * UMORSE_SHIFT)) > 0) && (shift < 4)){
        ++shift;
    }

    UMORSE_DEBUG ("cc=0x%04x, cpos=%2lu, shift=%u\n", cc, cpos, shift);

    for (unsigned j = 0; (j < 8) && (cc >> (j * UMORSE_SHIFT)); ++j) {
        if (shift == 4) {
            ++cpos;
            shift = 0;
        }
        uint8_t tmp = (uint8_t)(cc >> (j * UMORSE_SHIFT)) & UMORSE_MASK;
        code[cpos] |= (tmp << (UMORSE_SHIFT * shift));
        ++shift;
    }
    if (shift == 4) {
        ++cpos;
        shift = 0;
    }
    if ((cc & UMORSE_MASK) != UMORSE_END_CHAR) {
        /* add inter char gap */
        code[cpos] |= (uint8_t)UMORSE_END_CHAR << (UMORSE_SHIFT * shift);
    }

    return cpos;
}

size_t _encode_aligned(uint16_t cc, uint8_t *code, size_t clen, size_t cpos)
{
    assert (cpos < clen);
    (void) clen;

    UMORSE_DEBUG ("cc=0x%04x, cpos=%2lu\n", cc, cpos);

    code[cpos++] = (uint8_t)(cc & 0xFF);
    if (cc > 0xFF) {
        /* a number or special char is encoded in 2 bytes */
        code[cpos++] = (uint8_t)(cc >> 8);
    }
    if ((cc & UMORSE_MASK) != UMORSE_END_CHAR) {
        /* add inter char gap */
        code[cpos++] = (uint8_t)(UMORSE_END_CHAR);
    }

    return cpos;
}

int umorse_encode(const char *text, size_t tlen,
                  uint8_t *code, size_t clen, uint8_t flags)
{
    size_t cpos = 0;
    uint16_t cc = 0;
    /* decrease code length for safe guard */
    clen -= UMORSE_THRESHOLD;
    /* encode give string into Morse code */
    for (size_t tpos = 0; (tpos < tlen) && (cpos < clen); ++tpos) {
        char tc = 0;
        cc = 0;
        if ((tc = _is_letter(text[tpos])) != 0) {
            cc = umorse_letters[tc - UMORSE_LETTER_OFFSET];
        }
        else if ((tc = _is_number(text[tpos])) != 0) {
            cc = umorse_numbers[tc - UMORSE_NUMBER_OFFSET];
        }
        else if (_is_space(text[tpos])) {
            cc = UMORSE_END_WORD;
        }
        else if (_is_stop(text[tpos])) {
            cc = UMORSE_END_STOP;
        }
        else {
            /* any other char is ignored */
            continue;
        }

        if (flags & UMORSE_CODE_COMPACT) {
            cpos = _encode_compact(cc, code, clen, cpos);
        }
        else {
            cpos = _encode_aligned(cc, code, clen, cpos);
        }
    }
    /* add final stop char to close code */
    cc = (uint8_t) UMORSE_END_STOP;
    if (flags & UMORSE_CODE_COMPACT) {
        cpos = _encode_compact(cc, code, clen, cpos);
    }
    else {
        cpos = _encode_aligned(cc, code, clen, cpos);
    }
    /* add 1 to return length and not current position */
    ++cpos;
    return cpos;
}

int umorse_encode_compact(const char *text, size_t tlen,
                          uint8_t *code, size_t clen)
{
    return umorse_encode(text, tlen, code, clen, UMORSE_CODE_COMPACT);
}

int umorse_encode_aligned(const char *text, size_t tlen,
                          uint8_t *code, size_t clen)
{
    return umorse_encode(text, tlen, code, clen, UMORSE_CODE_ALIGNED);
}

int umorse_decode(const uint8_t *code, size_t clen, char *text, size_t tlen)
{
    (void) code;
    (void) clen;
    (void) text;
    (void) tlen;

    UMORSE_DEBUG("NOT IMPLEMENTED YET!\n");

    return 0;
}

void _process_spaces (const umorse_out_t *out, size_t spaces, uint8_t flags)
{
    if (spaces > 3) {
        out->nil(out->params, 0xF | flags);
    }
    else if (spaces > 1) {
        out->nil(out->params, 0x7 | flags);
    }
    else if (spaces > 0) {
        out->nil(out->params, 0x3 | flags);
    }
}

int umorse_output(const umorse_out_t *out,
                  const uint8_t *code, size_t clen, uint8_t flags)
{
    size_t spaces = 0;
    for (size_t i = 0; i < clen; ++i) {
        for (unsigned j = 0; j < 4; ++j) {
            uint8_t cc = (code[i] >> (j * UMORSE_SHIFT)) & UMORSE_MASK;
            if (cc == UMORSE_END_CHAR) {
                ++spaces;
            }
            else if (cc != UMORSE_NUL) {
                _process_spaces(out, spaces, flags);
                spaces = 0;
                switch (cc) {
                    case UMORSE_DIT:
                        out->dit(out->params, flags);
                        out->nil(out->params, 0x1 | flags);
                        break;
                    case UMORSE_DAH:
                        out->dah(out->params, flags);
                        out->nil(out->params, 0x1 | flags);
                        break;
                    default:
                        break;
                }
            }
        }
    }
    _process_spaces(out, spaces, flags);
    return 0;
}
