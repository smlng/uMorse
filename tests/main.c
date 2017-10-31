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

static const umorse_out_t out = {
	.dit = umorse_print_dit,
	.dah = umorse_print_dah,
	.nil = umorse_print_nil,
	.params = NULL
};

 static const char text[] = "Hello World!\nThis is uMorse.\n0123456789";

int test_umorse_print(void)
{
	setbuf(stdout, NULL);
	uint8_t code[CODE_LEN];
	int ret = -1;
	printf("> Translate text of length %lu into Morse code:\n\"%s\"\n",
		   strlen(text), text);

	memset(code, 0, CODE_LEN);
	printf("> using aligned encoding:\n");
	ret = umorse_encode_aligned(text, sizeof(text), code, sizeof(code));
	if (ret < 0) {
		return 1;
	}
	umorse_output(&out, code, ret, 0x0);
	printf("> encoded length=%d\n", ret);

	memset(code, 0, CODE_LEN);
	printf("> using compact encoding:\n");
	ret = umorse_encode_compact(text, sizeof(text), code, sizeof(code));
	if (ret < 0) {
		return 2;
	}
	umorse_output(&out, code, ret, 0x0);
	printf("> encoded length=%d\n", ret);

	return 0;
}

int main(void)
{
	int ret = 1;
	ret = test_umorse_print();
	return ret;
}
