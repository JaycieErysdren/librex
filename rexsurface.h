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
 * file: rexsurface.h
 *
 * authors: erysdren
 *
 * last modified: february 1 2023
 *
 * description: pixel buffer operations
 *
 * ********************************** */

/* header guard */
#pragma once
#ifndef __LIBREX_SURFACE_H__
#define __LIBREX_SURFACE_H__

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

/* stdint */
#ifdef __DJGPP__
#include "rexint.h"
#else
#include <stdint.h>
#endif

/* rex */
#include "rexstd.h"
#include "rexcolor.h"
#include "rexmem.h"

#endif

/* *************************************
 *
 * the types
 *
 * ********************************** */

/* the surface type */
typedef struct surface_t
{
	int w;
	int h;
	int bpp;
	int bytes_per_row;
	void *pixels;
	surface_t **palette;
} surface_t;

/* *************************************
 *
 * the forward declarations
 *
 * ********************************** */

/* surface creation and destruction */
surface_t *surface_create(int w, int h, int bpp, void *pixels);
void surface_destroy(surface_t *s);

/* surface modification */
surface_t *surface_duplicate(surface_t *s);
void surface_copy(surface_t *src, surface_t *dst);
void surface_clear(surface_t *s, color_t *c);
void surface_pixel(surface_t *s, int x, int y, color_t *c);
void surface_filledbox(surface_t *s, int x, int y, int w, int h, color_t *c);
void surface_borderbox(surface_t *s, int x, int y, int w, int h, color_t *c);
void surface_line_horizontal(surface_t *s, int x1, int y, int x2, color_t *c);
void surface_line_vertical(surface_t *s, int x, int y1, int y2, color_t *c);

/* surface palette operations */
void surface_set_palette(surface_t *s, surface_t **palette);

/* miscellaneous */
void surface_dump_buffer(surface_t *s, const char *filename);

/* *************************************
 *
 * the functions
 *
 * ********************************** */

/*
 * surface creation and destruction
 */

/* create surface. if pixels is NULL, one will be allocated */
surface_t *surface_create(int w, int h, int bpp, void *pixels)
{
	/* variables */
	surface_t *ret;

	/* sanity checks */
	if (w < 1 || h < 1) return NULL;
	if (bpp != 8 && bpp != 16 && bpp != 32) return NULL;

	/* alloc */
	ret = LIBREX_CALLOC(1, sizeof(surface_t));
	if (!ret) return NULL;

	/* assign values */
	ret->bpp = bpp;
	ret->h = h;
	ret->w = w;
	ret->bytes_per_row = w * (bpp / 8);

	/* if pixel buffer provided */
	if (pixels)
	{
		/* assign buffer */
		ret->pixels = pixels;
	}
	else
	{
		/* allocate buffer */
		ret->pixels = LIBREX_CALLOC(w * h, bpp / 8);
		if (!ret->pixels) return NULL;
	}

	/* return ptr */
	return ret;
}

/* destroy surface and free all associated memory */
void surface_destroy(surface_t *s)
{
	if (s)
	{
		if (s->pixels)
			free(s->pixels);

		free(s);
	}
}

/*
 * surface modification
 */

/* return a pointer to a new allocated surface (a copy of s) */
surface_t *surface_duplicate(surface_t *s)
{
	/* variables */
	surface_t *ret;

	/* sanity checks */
	if (!s || !s->pixels) return NULL;

	/* create return surface */
	ret = surface_create(s->w, s->h, s->bpp, NULL);
	surface_copy(s, ret);

	/* return pointer */
	return ret;
}

/* copy the pixel contents from src to dst */
void surface_copy(surface_t *src, surface_t *dst)
{
	/* sanity checks */
	if (!src || !src->pixels || !dst || !dst->pixels) return;

	/* perform copy */
	memcpy(dst->pixels, src->pixels, src->bytes_per_row * src->h);
}

/* clear the surface with the specified color */
void surface_clear(surface_t *s, color_t *c)
{
	/* sanity checks */
	if (!s || !s->pixels || !c) return;
	if (c->tag == INDEX8 && s->bpp != 8) return;
	if (c->tag == RGB565 && s->bpp != 16) return;
	if (c->tag == RGBA8888 && s->bpp != 32) return;
	if (c->tag == ARGB8888 && s->bpp != 32) return;

	/* clear the pixel buffer */
	switch (s->bpp)
	{
		case 8:
			memset8(s->pixels, c->val.u8, s->w * s->h);
			break;

		case 16:
			memset16(s->pixels, c->val.u16, s->w * s->h);
			break;

		case 32:
			memset32(s->pixels, c->val.u32, s->w * s->h);
			break;

		default:
			break;
	}
}

/* plot a pixel on the surface */
void surface_pixel(surface_t *s, int x, int y, color_t *c)
{
	/* sanity checks */
	if (!s || !s->pixels || !c || x < 0 || y < 0) return;
	if (x >= s->w || y >= s->h) return;
	if (c->tag == INDEX8 && s->bpp != 8) return;
	if (c->tag == RGB565 && s->bpp != 16) return;
	if (c->tag == RGBA8888 && s->bpp != 32) return;
	if (c->tag == ARGB8888 && s->bpp != 32) return;

	/* plot pixel */
	switch (s->bpp)
	{
		case 8:
			((uint8_t *)s->pixels)[y * s->h + x] = c->val.u8;
			break;

		case 16:
			((uint16_t *)s->pixels)[y * s->h + x] = c->val.u16;
			break;

		case 32:
			((uint32_t *)s->pixels)[y * s->h + x] = c->val.u32;
			break;

		default:
			break;
	}
}

/* draw a filled box */
void surface_filledbox(surface_t *s, int x, int y, int w, int h, color_t *c)
{
	/* variables */
	int i;

	/* sanity checks */
	if (w < 1 || h < 1) return;

	/* make cube */
	for (i = y; i < y + h; i++)
	{
		surface_line_horizontal(s, x, i, x + w, c);
	}
}

/* draw a border box */
void surface_borderbox(surface_t *s, int x, int y, int w, int h, color_t *c)
{
	surface_line_horizontal(s, x, y, x + w, c);
	surface_line_horizontal(s, x, y + h - 1, x + w, c);
	surface_line_vertical(s, x, y, y + h, c);
	surface_line_vertical(s, x + w - 1, y, y + h, c);
}

/* draw a horizontal line */
void surface_line_horizontal(surface_t *s, int x1, int y, int x2, color_t *c)
{
	/* variables */
	int start, width;

	/* if it has a width of one, just plot a pixel */
	if (x1 == x2)
	{
		surface_pixel(s, x1, y, c);
		return;
	}

	/* sanity checks */
	if (!s || !s->pixels || !c) return;
	if (c->tag == INDEX8 && s->bpp != 8) return;
	if (c->tag == RGB565 && s->bpp != 16) return;
	if (c->tag == RGBA8888 && s->bpp != 32) return;
	if (c->tag == ARGB8888 && s->bpp != 32) return;

	/* more sanity checks */
	x1 = x1 >= s->w ? s->w - 1 : x1;
	x1 = x1 < 0 ? 0 : x1;

	x2 = x2 >= s->w ? s->w - 1 : x2;
	x2 = x2 < 0 ? 0 : x2;

	y = y >= s->h ? s->h - 1 : y;
	y = y < 0 ? 0 : y;

	/* calculate start & width */
	start = ((x2 > x1 ? x1 : x2) * (s->bpp / 8)) + (y * s->bytes_per_row);
	width = x2 > x1 ? x2 - x1 : x1 - x2;

	/* plot line */
	switch (s->bpp)
	{
		case 8:
			memset8(s->pixels + start, c->val.u8, width);
			break;

		case 16:
			memset16(s->pixels + start, c->val.u16, width);
			break;

		case 32:
			memset32(s->pixels + start, c->val.u32, width);
			break;

		default:
			break;
	}
}

/* plot a vertical line */
void surface_line_vertical(surface_t *s, int x, int y1, int y2, color_t *c)
{
	/* variables */
	int i, start, end;

	/* sanity check */
	if (y1 == y2)
	{
		surface_pixel(s, x, y1, c);
		return;
	}

	/* determine start and end */
	start = y2 > y1 ? y1 : y2;
	end = y2 > y1 ? y2 : y1;

	/* plot loop */
	for (i = start; i < end; i++)
	{
		surface_pixel(s, x, i, c);
	}
}

/*
 * surface palette operations
 */

/* set palette of surface */
void surface_set_palette(surface_t *s, surface_t **palette)
{
	/* sanity checks */
	if (!s || !palette || !*palette) return;
	if ((*palette)->bpp < 16) return;

	/* set palette */
	s->palette = palette;
}

/*
 * miscellaneous
 */

/* dump surface pixels to file */
void surface_dump_buffer(surface_t *s, const char *filename)
{
	/* variables */
	FILE *file;

	/* sanity checks */
	if (!s || !s->pixels || !filename) return;

	/* open file */
	file = fopen(filename, "wb");
	if (!file) return;

	/* write buffer */
	fwrite(s->pixels, s->bytes_per_row, s->h, file);

	/* close file ptr */
	fclose(file);
}

#ifdef __cplusplus
}
#endif

#endif /* __LIBREX_SURFACE_H__ */
