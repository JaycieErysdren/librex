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
 * file: rexstr.h
 *
 * authors: erysdren
 *
 * last modified: january 16 2023
 *
 * ********************************** */

/* header guard */
#pragma once
#ifndef __LIBREX_STR_H__
#define __LIBREX_STR_H__

/* cpp guard */
#ifdef __cplusplus
extern "C" {
#endif

/* *************************************
 *
 * the types
 *
 * ********************************** */

/* string type */
typedef struct string_t
{
	size_t len;
	char *buf;
} string_t;

/* *************************************
 *
 * the forward declarations
 *
 * ********************************** */

/* creation and destruction of strings */
static string_t string_create(const char *txt);
static string_t string_createf(const char *fmt, ...);
static string_t string_alloc(int len);
static int string_free(string_t *s);
static string_t string_duplicate(string_t *s);

/* string modification */
static int string_set(string_t *s, const char *txt);
static int string_setf(string_t *s, const char *fmt, ...);
static int string_setc(string_t *s, int i, int c);
static int string_copy(string_t *src, string_t *dst);
static int string_slice(string_t *src, string_t *dst, int pos, int n);
static int string_pad(string_t *s, int pos, int n, int c);
static int string_insert(string_t *src, string_t *dst, int pos);
static int string_concat(string_t *src, string_t *dst);
static int string_clear(string_t *s, int c);
static int string_resize(string_t *s, int len);
static int string_replace(string_t *s, int f, int r);

/* utility functions */
static int string_print(string_t *s);
static int string_fprint(string_t *s, FILE *stream, librex_putf putf);
static int string_getc(string_t *s, int i);
static int string_reads(string_t *s, FILE *stream, int n, int t);
static int string_readc(string_t *s, FILE *stream, int n);
static int string_compare(string_t *s1, string_t *s2);
static int string_search(string_t *s, const char *search);

/* string conversion functions */
static int string_to_int(string_t *s);
static long string_to_long(string_t *s);
static double string_to_double(string_t *s);

/* *************************************
 *
 * the functions
 *
 * ********************************** */

/*
 * creation and destruction of strings
 */

/* create new string with text input */
static string_t string_create(const char *txt)
{
	/* variables */
	string_t ret;

	/* sanity check */
	assert(txt);

	/* allocate string_t */
	ret = string_alloc(strlen(txt));

	/* set text buffer */
	string_set(&ret, txt);

	/* return pointer */
	return ret;
}

/* create new string with formatted input */
static string_t string_createf(const char *fmt, ...)
{
	/* variables */
	string_t ret;
	va_list args;
	char buf[256];

	/* sanity check */
	assert(fmt);

	/* make sure its all null */
	memset(buf, '\0', sizeof(buf));

	/* print args into buffer */
	va_start(args, fmt);
	vsprintf(buf, fmt, args);
	va_end(args);

	/* allocate string_t */
	ret = string_alloc(strlen(buf));

	/* set text buffer */
	string_set(&ret, buf);

	/* return pointer */
	return ret;
}

/* free string buffer */
static int string_free(string_t *s)
{
	/* free memory if string exists */
	if (s && s->buf)
	{
		/* free buffer */
		LIBREX_FREE(s->buf);

		/* return success */
		return 1;
	}

	/* return failure */
	return 0;
}

/* allocate a string of a specified length */
static string_t string_alloc(int len)
{
	/* variables */
	string_t ret;
	size_t alloc_size;

	/* sanity check */
	assert(len > 1);

	/* set values */
	ret.len = len;

	/* allocate memory */
	alloc_size = sizeof(char) * ret.len;
	ret.buf = (char *)LIBREX_MALLOC(alloc_size);
	assert(ret.buf);
	memset(ret.buf, '\0', alloc_size);

	/* return pointer */
	return ret;
}

/* resize string to new length while preserving contents */
static int string_resize(string_t *s, int len)
{
	/* sanity checks */
	assert(s && len > 1);

	/* realloc */
	s->buf = (char *)LIBREX_REALLOC(s->buf, len * sizeof(char));

	/* memset the last part to null to clear unused memory */
	if (len > s->len)
	{
		memset(s->buf + s->len, '\0', len - s->len);
	}

	/* set new len */
	s->len = len;

	/* return success */
	return 1;
}

/* if f is found in the string, replace with r */
static int string_replace(string_t *s, int f, int r)
{
	/* variables */
	int i;
	int replaced_something;

	/* sanity check */
	if (!s) return 0;

	/* set default */
	replaced_something = 0;

	/* find and replace loop */
	for (i = 0; i < s->len; i++)
	{
		if (s->buf[i] == f)
		{
			replaced_something = 1;
			s->buf[i] = r;
		}
	}

	/* return success */
	return replaced_something;
}

/*
 * string modification
 */

/* set the string to the given unformatted string_t */
static int string_set(string_t *s, const char *txt)
{
	/* sanity checks */
	if (!s || !s->buf || !txt) return 0;
	if (strlen(txt) > s->len) return 0;

	/* clear */
	string_clear(s, '\0');

	/* memcpy */
	memcpy(s->buf, txt, strlen(txt));

	/* return success */
	return 1;
}

/* print formatted text into existing string_t */
static int string_setf(string_t *s, const char *fmt, ...)
{
	/* variables */
	va_list args;
	char buf[256];

	/* sanity checks */
	if (!s || !s->buf|| !fmt) return 0;

	/* make sure its all null */
	memset(buf, '\0', sizeof(buf));

	/* print args into buffer */
	va_start(args, fmt);
	vsprintf(buf, fmt, args);
	va_end(args);

	/* another sanity check for the road */
	if (strlen(buf) > s->len) return 0;

	/* wipe string and copy in formatted text */
	string_clear(s, '\0');
	memcpy(s->buf, buf, strlen(buf));

	/* return success */
	return 1;
}

/* duplicate string and return pointer to copied string_t */
static string_t string_duplicate(string_t *s)
{
	/* variables */
	string_t ret;

	/* sanity checks */
	assert(s);

	/* allocate new string_t */
	ret = string_alloc(s->len);

	/* copy src to ret */
	memcpy(&ret.buf, s->buf, s->len * sizeof(char));

	/* return pointer to dst */
	return ret;
}

/* copy string from src to dst */
static int string_copy(string_t *src, string_t *dst)
{
	/* sanity checks */
	if (!src || !dst) return 0;

	/* resize */
	string_resize(dst, src->len);
	if (!dst) return 0;

	/* memcpy */
	memcpy(dst->buf, src->buf, src->len);

	/* return success */
	return 1;
}

/* slice a portion of string src and place it in dst */
static int string_slice(string_t *src, string_t *dst, int pos, int n)
{
	/* sanity checks */
	if (!src || !dst || pos < 1 || n < 1) return 0;
	if (pos + n > src->len || n > dst->len) return 0;

	/* clear dest string_t */
	string_clear(dst, '\0');

	/* memcpy the string buffer */
	memcpy(dst->buf, src->buf + pos, n);

	/* return success */
	return 1;
}

/* add len bytes of padding with pad char at pos */
static int string_pad(string_t *s, int pos, int n, int c)
{
	/* sanity checks */
	if (!s || n < 1 || pos < 1 || pos >= s->len) return 0;

	/* resize string_t */
	string_resize(s, s->len + n);
	if (!s) return 0;

	/* copy buffer */
	memcpy(s->buf + pos + n, s->buf + pos, s->len - pos);
	memset(s->buf + pos, c, n);

	/* return success */
	return 1;
}

/* insert src into dst at the specified pos */
static int string_insert(string_t *src, string_t *dst, int pos)
{
	/* sanity checks */
	if (!src || !dst || pos < 1 || pos >= dst->len) return 0;

	/* resize string_t */
	string_resize(dst, dst->len + src->len);
	if (!dst) return 0;

	/* copy buffers */
	memcpy(dst->buf + pos + src->len, dst->buf + pos, dst->len - pos);
	memcpy(dst->buf + pos, src->buf, src->len);

	/* return success */
	return 1;
}

/* create a string which is the concat of two other strings */
static int string_concat(string_t *src, string_t *dst)
{
	/* sanity checks */
	if (!src || !dst) return 0;

	/* resize dst */
	string_resize(dst, dst->len + src->len);
	if (!dst) return 0;

	/* copy data */
	memcpy(dst->buf + dst->len, src->buf, src->len);

	/* return success */
	return 1;
}

/* replace the whole string with the specificed char */
static int string_clear(string_t *s, int c)
{
	/* sanity checks */
	if (!s || !s->buf) return 0;

	/* memset */
	memset(s->buf, c, s->len * sizeof(char));

	/* return success */
	return 1;
}

/* replace the whole string with the specificed char */
static int string_setc(string_t *s, int i, int c)
{
	/* sanity checks */
	if (!s || !s->buf || i >= s->len) return 0;

	/* set value */
	s->buf[i] = c;

	/* return success */
	return 1;
}

/*
 * utility functions
 */

/* print string to stdout */
static int string_print(string_t *s)
{
	/* call the complex func with default values */
	return string_fprint(s, stdout, fputc);
}

/* print string object to specified stream, with more user control */
static int string_fprint(string_t *s, FILE *stream, librex_putf putf)
{
	/* variables */
	int i;

	/* sanity checks */
	if (!s || !s->buf || !stream)
		return 0;

	/* put the string in the stream */
	for (i = 0; i < s->len; i++)
	{
		putf(s->buf[i], stream);
	}

	return 1;
}

/* get char from specified index */
static int string_getc(string_t *s, int i)
{
	/* sanity checks */
	if (!s || i >= s->len) return -1;

	/* return char at index */
	return s->buf[i];
}

/* read n chars from stream */
static int string_readc(string_t *s, FILE *stream, int n)
{
	/* variables */
	int i;

	/* sanity checks */
	if (!s || n < 1 || n > s->len || !stream) return 0;

	/* clear string_t */
	string_clear(s, '\0');
	if (!s) return 0;

	/* get loop */
	for (i = 0; i < n; i++)
	{
		s->buf[i] = fgetc(stream);
	}

	/* return success*/
	return 1;
}

/* read t-terminated chars from stream, up to n */
static int string_reads(string_t *s, FILE *stream, int n, int t)
{
	/* variables */
	int i;

	/* sanity checks */
	if (!s || !s->buf || n < 1 || n > s->len || t < 0 || !stream)
		return 0;

	/* clear string_t */
	string_clear(s, '\0');
	if (!s) return 0;

	/* get loop */
	for (i = 0; i < n; i++)
	{
		s->buf[i] = fgetc(stream);

		if (s->buf[i] == t)
			break;
	}

	/* return success*/
	return 1;
}

/* compare two strings. returns 1 if they're the same, 0 if not */
static int string_compare(string_t *s1, string_t *s2)
{
	/* variables */
	int i;

	/* sanity checks */
	if (!s1 || !s2) return 0;
	if (s1->len != s2->len) return 0;

	/* run compare loop */
	for (i = 0; i < s1->len; i++)
	{
		/* if any chars differ, return false */
		if (s1->buf[i] != s2->buf[i])
			return 0;
	}

	/* return true */
	return 1;
}

/* search inside a string for the supplied character sequence */
/* returns negative number on failure, otherwise returns the */
/* position where the search string was found */
static int string_search(string_t *s, const char *search)
{
	/* variables */
	int ret;
	int i, n;

	/* set defaults */
	ret = -1;

	/* sanity checks */
	if (!s || strlen(search) > s->len) return ret;

	/* search loop */
	for (i = 0; i < s->len; i++)
	{
		/* if buf[i] equals search[0], loop through and compare */
		if (s->buf[i] == search[0])
		{
			/* loop through the length of the search string_t */
			for (n = 0; n < strlen(search); n++)
			{
				/* if anything is different, break */
				if (s->buf[i + n] != search[n])
				{
					ret = -1;
					break;
				}

				ret = i;
			}
		}

		/* if ret is equal to i, it means we found a match */
		if (ret == i) break;
	}

	return ret;
}

/*
 * string conversion functions
 */

/* convert string to int */
static signed int string_to_int(string_t *s)
{
	/* sanity check */
	if (!s || !s->buf) return 0;

	/* return value */
	return atoi(s->buf);
}

/* convert string to long */
static long string_to_long(string_t *s)
{
	/* sanity check */
	if (!s || !s->buf) return 0;

	/* return value */
	return atol(s->buf);
}

/* convert string to double */
static double string_to_double(string_t *s)
{
	/* sanity check */
	if (!s || !s->buf) return 0;

	/* return value */
	return atof(s->buf);
}

#ifdef __cplusplus
}
#endif

#endif /* __LIBREX_STR_H__ */
