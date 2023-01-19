/* ****************************************************************************
 *
 * MIT License
 *
 * Copyright (c) 2023 erysdren
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 * ************************************************************************* */

/* *************************************
 *
 * project: librex
 *
 * file: rexargs.h
 *
 * authors: erysdren
 *
 * last modified: january 19 2023
 *
 * description: args parsing
 * 
 * ********************************** */

/* header guard */
#pragma once
#ifndef __LIBREX_ARGS_H__
#define __LIBREX_ARGS_H__

/* cpp guard */
#ifdef __cplusplus
extern "C" {
#endif

/* *************************************
 *
 * the headers
 *
 * ********************************** */

/* if we're included outside of rex.h */
#ifndef __LIBREX_H__

/* std */
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/* rex */
#include "rexstring.h"

#endif

/* *************************************
 *
 * the types
 *
 * ********************************** */

/* args parsing callback function */
typedef void (*args_cbfn)(const char arg, const char *opt);

/* *************************************
 *
 * the forward declarations
 *
 * ********************************** */

/* argument parsing */
void args_parse(int argc, char **argv, char *expected, args_cbfn cbfn);
void args_parse_str(char *args, char *expected, args_cbfn cbfn);

/* *************************************
 *
 * the functions
 *
 * ********************************** */

/* parse args, calling cbfn for each one */
void args_parse(int argc, char **argv, char *expected, args_cbfn cbfn)
{
	/* variables */
	char arg;
	char *opt;
	int i, c;

	/* set defaults */
	arg = '\0';
	opt = NULL;
	i = 0;
	c = 0;

	/* sanity checks */
	if (argc < 1 || !argv || !expected) return;

	/* parse loop */
	while (i < argc)
	{
		/* its an arg */
		if (strlen(argv[i]) > 1 && argv[i][0] == '-')
		{
			arg = argv[i][1];

			if (expected)
			{
				c = 0;
				while (c < strlen(expected))
				{
					if (expected[c] == arg)
					{
						if (c + 1 < strlen(expected) && i + 1 < argc)
						{
							if (expected[c + 1] == ':')
							{
								opt = argv[i + 1];
								i++;
							}
						}

						cbfn(arg, opt);
					}

					c++;
				}
			}
		}

		/* iterate */
		i++;
	}
}

/* parse args from a single string, calling cbfn for each one */
void args_parse_str(char *args, char *expected, args_cbfn cbfn)
{
	/* variables */
	char arg;
	char *opt;

	/* call the callback function */
	cbfn(arg, opt);
}

#ifdef __cplusplus
}
#endif

#endif /* __LIBREX_ARGS_H__ */
