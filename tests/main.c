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
 * @defgroup	umorse_tests
 * @ingroup     umorse
 * @brief		Test framework of uMorse
 *
 * @{
 * @file
 * @brief       Test of uMorse core functionality
 *
 * @author      Sebastian Meiling <s@mlng.net>
 * @}
 */

#include <stdio.h>
#include <string.h>

#include "umorse.h"
#include "print.h"

#define CODE_LEN	(128U)

const static umorse_out_t out = {
	.dit = umorse_print_dit,
	.dah = umorse_print_dah,
	.nil = umorse_print_nil,
	.params = NULL
};

const static char text[] = "Hello World!\nThis is uMorse.\n0123456789";

int test_umorse_print(void)
{
	setbuf(stdout, NULL);
	uint8_t code[CODE_LEN];
	printf("> Translate text of length %lu into Morse code:\n\"%s\"\n",
		   strlen(text), text);

	memset(code, 0, CODE_LEN);
	printf("> using aligned encoding:\n");
	int ret1 = umorse_encode_aligned(text, sizeof(text), code, sizeof(code));
	umorse_output(&out, code, ret1, 0x0);
	printf("> encoded length=%d\n", ret1);

	memset(code, 0, CODE_LEN);
	int ret2 = umorse_encode_compact(text, sizeof(text), code, sizeof(code));
	printf("> using compact encoding:\n");
	umorse_output(&out, code, ret2, 0x0);
	printf("> encoded length=%d\n", ret2);
	return 0;
}

int main(void)
{
	int ret = 1;
	ret = test_umorse_print();
	return ret;
}
