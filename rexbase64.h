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
 * file: rexbase64.h
 *
 * authors: erysdren
 *
 * last modified: january 16 2023
 *
 * ********************************** */

/* header guard */
#pragma once
#ifndef __LIBREX_BASE64_H__
#define __LIBREX_BASE64_H__

/* cpp guard */
#ifdef __cplusplus
extern "C" {
#endif

/* *************************************
 *
 * the globals
 *
 * ********************************** */

const char base64_chars[] = \
	"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

const int base64_invs[] = {
	62, -1, -1, -1, 63, 52, 53, 54, 55, 56, 57, 58,
	59, 60, 61, -1, -1, -1, -1, -1, -1, -1, 0, 1, 2, 3, 4, 5,
	6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
	21, 22, 23, 24, 25, -1, -1, -1, -1, -1, -1, 26, 27, 28,
	29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42,
	43, 44, 45, 46, 47, 48, 49, 50, 51
};

/* *************************************
 *
 * the forward declarations
 *
 * ********************************** */

/* encoding and decoding char sequences */
static char *base64_encode(const char *in, size_t len);
static int base64_decode(const char *in, char *out, size_t outlen);

/* encoding and decoding strings */
static string_t base64_encode_string(string_t *src);
static string_t base64_decode_string(string_t *src);

/* utility functions */
static size_t base64_encoded_size(size_t in);
static size_t base64_decoded_size(const char *in);
static void base64_generate_decode_table();
static int base64_is_valid_char(char c);

/* *************************************
 *
 * the functions
 *
 * ********************************** */

/*
 * encoding and decoding char sequences
 */

/* encode base64 char sequence */
static char *base64_encode(const char *in, size_t len)
{
	/* variables */
	char *out;
	size_t elen;
	size_t i;
	size_t j;
	size_t v;

	/* sanity check */
	assert(in && len > 0);

	/* allocate string */
	elen = base64_encoded_size(len);
	out = (char *)LIBREX_MALLOC(elen + 1);
	out[elen] = '\0';

	/* encode loop */
	for (i = 0, j = 0; i < len; i += 3, j += 4)
	{
		v = in[i];
		v = i + 1 < len ? v << 8 | in[i + 1] : v << 8;
		v = i + 2 < len ? v << 8 | in[i + 2] : v << 8;

		out[j] = base64_chars[(v >> 18) & 0x3F];
		out[j + 1] = base64_chars[(v >> 12) & 0x3F];

		if (i + 1 < len)
			out[j + 2] = base64_chars[(v >> 6) & 0x3F];
		else
			out[j + 2] = '=';

		if (i + 2 < len)
			out[j + 3] = base64_chars[v & 0x3F];
		else
			out[j + 3] = '=';
	}

	return out;
}

/* decode base64 char sequence */
static int base64_decode(const char *in, char *out, size_t outlen)
{
	/* variables */
	size_t len;
	size_t i;
	size_t j;
	int v;

	/* sanity check */
	assert(in && out);

	len = strlen(in);

	if (outlen < base64_decoded_size(in) || len % 4 != 0)
		return 0;

	/* validation loop */
	for (i= 0; i < len; i++)
	{
		if (!base64_is_valid_char(in[i]))
			return 0;
	}

	/* decode loop */
	for (i = 0, j = 0; i < len; i += 4, j += 3)
	{
		v = base64_invs[in[i]-43];
		v = (v << 6) | base64_invs[in[i + 1] - 43];
		v = in[i + 2]=='=' ? v << 6 : (v << 6) | base64_invs[in[i + 2] - 43];
		v = in[i + 3]=='=' ? v << 6 : (v << 6) | base64_invs[in[i + 3] - 43];

		out[j] = (v >> 16) & 0xFF;

		if (in[i + 2] != '=')
			out[j + 1] = (v >> 8) & 0xFF;

		if (in[i + 3] != '=')
			out[j + 2] = v & 0xFF;
	}

	return 1;
}

/*
 * encoding and decoding strings
 */

/* returns new allocated base64 string encoded from src */
static string_t base64_encode_string(string_t *src)
{
	/* variables */
	string_t ret;
	size_t i;
	size_t j;
	size_t v;

	/* sanity check */
	assert(src);

	/* allocate string */
	ret = string_alloc(base64_encoded_size(src->len));

	/* encode loop */
	for (i = 0, j = 0; i < src->len; i += 3, j += 4)
	{
		v = src->buf[i];
		v = i + 1 < src->len ? v << 8 | src->buf[i + 1] : v << 8;
		v = i + 2 < src->len ? v << 8 | src->buf[i + 2] : v << 8;

		ret.buf[j] = base64_chars[(v >> 18) & 0x3F];
		ret.buf[j + 1] = base64_chars[(v >> 12) & 0x3F];

		if (i + 1 < src->len)
			ret.buf[j + 2] = base64_chars[(v >> 6) & 0x3F];
		else
			ret.buf[j + 2] = '=';

		if (i + 2 < src->len)
			ret.buf[j + 3] = base64_chars[v & 0x3F];
		else
			ret.buf[j + 3] = '=';
	}

	return ret;
}

/* returns new allocated string base64 decoded from src */
static string_t base64_decode_string(string_t *src)
{
	/* variables */
	string_t ret;
	size_t i;
	size_t j;
	int v;

	/* sanity checks */
	assert(src);
	assert(src->len % 4 == 0);

	/* validation loop */
	for (i = 0; i < src->len; i++)
	{
		assert(base64_is_valid_char(src->buf[i]));
	}

	/* allocate return string */
	ret = string_alloc(base64_decoded_size(src->buf));

	/* decode loop */
	for (i = 0, j = 0; i < src->len; i += 4, j += 3)
	{
		v = base64_invs[src->buf[i] - 43];

		v = (v << 6) | base64_invs[src->buf[i + 1] - 43];

		v = src->buf[i + 2] == '=' ? v << 6 : (v << 6) |
			base64_invs[src->buf[i + 2] - 43];

		v = src->buf[i + 3] == '=' ? v << 6 : (v << 6) |
			base64_invs[src->buf[i + 3] - 43];

		ret.buf[j] = (v >> 16) & 0xFF;

		if (src->buf[i + 2] != '=')
			ret.buf[j + 1] = (v >> 8) & 0xFF;

		if (src->buf[i + 3] != '=')
			ret.buf[j + 2] = v & 0xFF;
	}

	return ret;
}

/*
 * utility functions
 */

/* get the length of a string after it's been base64 encoded */
static size_t base64_encoded_size(size_t in)
{
	/* variables */
	size_t ret;

	ret = in;

	if (in % 3 != 0)
		ret += 3 - (in % 3);

	ret /= 3;
	ret *= 4;

	/* return len */
	return ret;
}

/* get the length of a base64 string after it's been decoded */
static size_t base64_decoded_size(const char *in)
{
	/* variables */
	size_t len;
	size_t ret;
	size_t i;

	/* sanity check */
	assert(in);

	/* calculate len */
	len = strlen(in);
	ret = len / 4 * 3;

	/* take = into account */
	for (i = len; i > 0; i--)
	{
		if (in[i] == '=')
			ret--;
		else
			break;
	}

	/* return len */
	return ret;
}

/* generate base64 decode table */
static void base64_generate_decode_table()
{
	/* variables */
	int inv[80];
	size_t i;

	/* memset to -1 */
	memset(inv, -1, sizeof(inv));

	/* loop */
	for (i = 0; i < sizeof(base64_chars) - 1; i++)
	{
		inv[base64_chars[i] - 43] = i;
	}
}

/* test if char is a valid base64 char */
static int base64_is_valid_char(char c)
{
	if (c >= '0' && c <= '9')
		return 1;

	if (c >= 'A' && c <= 'Z')
		return 1;

	if (c >= 'a' && c <= 'z')
		return 1;

	if (c == '+' || c == '/' || c == '=')
		return 1;

	return 0;
}

#ifdef __cplusplus
}
#endif

#endif /* __LIBREX_BASE64_H__ */
