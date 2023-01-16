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
 * file: rexcolor.h
 *
 * authors: erysdren
 *
 * last modified: january 15 2023
 *
 * ********************************** */

/* header guard */
#pragma once
#ifndef __LIBREX_COLOR_H__
#define __LIBREX_COLOR_H__

/* cpp guard */
#ifdef __cplusplus
extern "C" {
#endif

/* *************************************
 *
 * the headers
 *
 * ********************************** */

/* rex */
#include "rextypes.h"

/* *************************************
 *
 * the types
 *
 * ********************************** */

/* color struct */
typedef struct color
{

	union val
	{
		uint8 u8;
		uint16 u16;
		uint32 u32;
	} val;

	enum tag
	{
		INDEX8,
		RGB565,
		RGBA8888,
		ARGB8888
	} tag;

} color;

/* *************************************
 *
 * the forward declarations
 *
 * ********************************** */

/* set value of color */
void color_set_index8(color *c, uint8 i);
void color_set_rgb565(color *c, uint8 r, uint8 g, uint8 b);
void color_set_rgba8888(color *c, uint8 r, uint8 g, uint8 b, uint8 a);
void color_set_argb8888(color *c, uint8 r, uint8 g, uint8 b, uint8 a);

/* retrieve color components */
uint8 color_get_index8(color *c);
uint8 color_get_red(color *c);
uint8 color_get_green(color *c);
uint8 color_get_blue(color *c);
uint8 color_get_alpha(color *c);

/* retrieve color components as float32s */
float32 color_get_redf(color *c);
float32 color_get_greenf(color *c);
float32 color_get_bluef(color *c);
float32 color_get_alphaf(color *c);

/* color packing */
uint16 pack_rgb565(uint8 r, uint8 g, uint8 b);
uint32 pack_rgba8888(uint8 r, uint8 g, uint8 b, uint8 a);
uint32 pack_argb8888(uint8 r, uint8 g, uint8 b, uint8 a);

/* color unpacking: rgb565 */
uint8 unpack_rgb565_red(uint16 c);
uint8 unpack_rgb565_green(uint16 c);
uint8 unpack_rgb565_blue(uint16 c);

/* color unpacking: rgba8888 */
uint8 unpack_rgba8888_red(uint32 c);
uint8 unpack_rgba8888_green(uint32 c);
uint8 unpack_rgba8888_blue(uint32 c);
uint8 unpack_rgba8888_alpha(uint32 c);

/* color unpacking: argb8888 */
uint8 unpack_argb8888_red(uint32 c);
uint8 unpack_argb8888_green(uint32 c);
uint8 unpack_argb8888_blue(uint32 c);
uint8 unpack_argb8888_alpha(uint32 c);

/* *************************************
 *
 * the functions
 *
 * ********************************** */

/*
 * set value of color
 */

/* set color type to index8, and set value */
void color_set_index8(color *c, uint8 i)
{
	if (!c) return;

	c->tag = INDEX8;
	c->val.u8 = i;
}

/* set color type to rgb565, and set value */
void color_set_rgb565(color *c, uint8 r, uint8 g, uint8 b)
{
	if (!c) return;

	c->tag = RGB565;
	c->val.u16 = pack_rgb565(r, g, b);
}

/* set color type to rgba8888, and set value */
void color_set_rgba8888(color *c, uint8 r, uint8 g, uint8 b, uint8 a)
{
	if (!c) return;

	c->tag = RGBA8888;
	c->val.u32 = pack_rgba8888(r, g, b, a);
}

/* set color type to argb8888, and set value */
void color_set_argb8888(color *c, uint8 r, uint8 g, uint8 b, uint8 a)
{
	if (!c) return;

	c->tag = ARGB8888;
	c->val.u32 = pack_argb8888(r, g, b, a);
}

/*
 * retrieve color components
 */

/* retrieve index of 8-bit color */
uint8 color_get_index8(color *c)
{
	if (!c) return 0;
	return (c->tag == INDEX8) ? c->val.u8 : 0;
}

/* retrieve red color component */
uint8 color_get_red(color *c)
{
	if (!c) return 0;
	switch (c->tag)
	{
		case RGB565: 
			return unpack_rgb565_red(c->val.u16);
		case RGBA8888: 
			return unpack_rgba8888_red(c->val.u32);
		case ARGB8888: 
			return unpack_argb8888_red(c->val.u32);
		default:
			return 0;
	}
}

/* retrieve green color component */
uint8 color_get_green(color *c)
{
	if (!c) return 0;
	switch (c->tag)
	{
		case RGB565: 
			return unpack_rgb565_green(c->val.u16);
		case RGBA8888: 
			return unpack_rgba8888_green(c->val.u32);
		case ARGB8888: 
			return unpack_argb8888_green(c->val.u32);
		default:
			return 0;
	}
}

/* retrieve blue color component */
uint8 color_get_blue(color *c)
{
	if (!c) return 0;
	switch (c->tag)
	{
		case RGB565: 
			return unpack_rgb565_blue(c->val.u16);
		case RGBA8888: 
			return unpack_rgba8888_blue(c->val.u32);
		case ARGB8888: 
			return unpack_argb8888_blue(c->val.u32);
		default:
			return 0;
	}
}

/* retrieve alpha color component */
uint8 color_get_alpha(color *c)
{
	if (!c) return 0;
	switch (c->tag)
	{
		case RGBA8888: 
			return unpack_rgba8888_alpha(c->val.u32);
		case ARGB8888: 
			return unpack_argb8888_alpha(c->val.u32);
		default:
			return 0;
	}
}

/* retrieve color components as floats */
float32 color_get_redf(color *c)
{
	if (!c) return 0;
	switch (c->tag)
	{
		case RGB565: 
			return (float32)unpack_rgb565_red(c->val.u16) / 255.0f;
		case RGBA8888: 
			return (float32)unpack_rgba8888_red(c->val.u32) / 255.0f;
		case ARGB8888: 
			return (float32)unpack_argb8888_red(c->val.u32) / 255.0f;
		default:
			return 0.0f;
	}
}

float32 color_get_greenf(color *c)
{
	if (!c) return 0;
	switch (c->tag)
	{
		case RGB565: 
			return (float32)unpack_rgb565_green(c->val.u16) / 255.0f;
		case RGBA8888: 
			return (float32)unpack_rgba8888_green(c->val.u32) / 255.0f;
		case ARGB8888: 
			return (float32)unpack_argb8888_green(c->val.u32) / 255.0f;
		default:
			return 0.0f;
	}
}

float32 color_get_bluef(color *c)
{
	if (!c) return 0;
	switch (c->tag)
	{
		case RGB565: 
			return (float32)unpack_rgb565_blue(c->val.u16) / 255.0f;
		case RGBA8888: 
			return (float32)unpack_rgba8888_blue(c->val.u32) / 255.0f;
		case ARGB8888: 
			return (float32)unpack_argb8888_blue(c->val.u32) / 255.0f;
		default:
			return 0.0f;
	}
}

float32 color_get_alphaf(color *c)
{
	if (!c) return 0;
	switch (c->tag)
	{
		case RGBA8888: 
			return (float32)unpack_rgba8888_alpha(c->val.u32) / 255.0f;
		case ARGB8888: 
			return (float32)unpack_argb8888_alpha(c->val.u32) / 255.0f;
		default:
			return 0.0f;
	}
}

/*
 * color packing
 */

/* pack rgb triplet to rgb565 format */
uint16 pack_rgb565(uint8 r, uint8 g, uint8 b)
{
	return (uint16)((((r >> 3) & 0x1f) << 11) |
			(((g >> 2) & 0x3f) << 5) |
			((b >> 3) & 0x1f));
}

/* pack rgba quadruplet to rgba8888 format */
uint32 pack_rgba8888(uint8 r, uint8 g, uint8 b, uint8 a)
{
	return (uint32)((r << 24) | (g << 16) | (b << 8) | a);
}

/* pack rgba quadruplet to argb8888 format */
uint32 pack_argb8888(uint8 r, uint8 g, uint8 b, uint8 a)
{
	return (uint32)((a << 24) | (r << 16) | (g << 8) | b);
}

/*
 * color unpacking: rgb565
 */

/* retrieve red from rgb565 int */
uint8 unpack_rgb565_red(uint16 c)
{
	return (uint8)(((c & 0xF800) >> 11) << 3);
}

/* retrieve green from rgb565 int */
uint8 unpack_rgb565_green(uint16 c)
{
	return (uint8)(((c & 0x7E0) >> 5) << 2);
}

/* retrieve blue from rgb565 int */
uint8 unpack_rgb565_blue(uint16 c)
{
	return (uint8)((c & 0x1F) << 3);
}

/*
 * color unpacking: rgba8888
 */

/* retrieve red from rgba8888 int */
uint8 unpack_rgba8888_red(uint32 c)
{
	return (uint8)((c >> 24) & 0xFF);
}

/* retrieve green from rgba8888 int */
uint8 unpack_rgba8888_green(uint32 c)
{
	return (uint8)((c >> 8) & 0xFF);
}

/* retrieve blue from rgba8888 int */
uint8 unpack_rgba8888_blue(uint32 c)
{
	return (uint8)((c >> 8) & 0xFF);
}

/* retrieve alpha from rgba8888 int */
uint8 unpack_rgba8888_alpha(uint32 c)
{
	return (uint8)(c & 0xFF);
}

/*
 * color unpacking: argb8888
 */

/* retrieve red from argb8888 int */
uint8 unpack_argb8888_red(uint32 c)
{
	return (uint8)((c >> 16) & 0xFF);
}

/* retrieve green from argb8888 int */
uint8 unpack_argb8888_green(uint32 c)
{
	return (uint8)((c >> 8) & 0xFF);
}

/* retrieve blue from argb8888 int */
uint8 unpack_argb8888_blue(uint32 c)
{
	return (uint8)(c & 0xFF);
}

/* retrieve alpha from argb8888 int */
uint8 unpack_argb8888_alpha(uint32 c)
{
	return (uint8)((c >> 24) & 0xFF);
}

#ifdef __cplusplus
}
#endif

#endif /* __LIBREX_COLOR_H__ */
