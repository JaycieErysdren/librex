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
 * file: rexdos.c
 *
 * authors: erysdren
 *
 * last modified: january 18 2023
 * 
 * description: rexdos.h test app
 *
 * ********************************** */

/* std */
#include <stdlib.h>
#include <stdio.h>

/* rex */
#include "rexdos.h"

int main(int argc, char **argv)
{
	/* set video mode to 3 (80x25 text mode) */
	dos_set_mode(DOS_MODE_3);

	/* mouse cursor test */
	printf("mouse cursor test\n");
	printf("current video mode: %x\n", dos_get_mode());
	dos_mouse_enable();
	dos_mouse_show();

	/* set cursor shape */
	dos_text_set_cursor_shape(DOS_CURSOR_BLOCK);

	/* print screen rows and cols */
	printf("this mode has %d rows and %d columns!\n",
		dos_text_get_screen_rows(),
		dos_text_get_screen_columns());
	while (!getchar());

	/* test clear screen */
	printf("hello! press any key to clear the screen.\n");
	while (!getchar());
	dos_clear_screen();
	printf("well, did it work?\npress any key to continue.\n");
	while (!getchar());

	/* set video mode to 13 (320x200 graphics mode) */
	dos_set_mode(DOS_MODE_13);

	/* print screen rows and cols */
	printf("this mode has %d rows and %d columns!\n",
		dos_text_get_screen_rows(),
		dos_text_get_screen_columns());
	while (!getchar());

	/* test clear screen */
	printf("hello! press any key to clear the screen.\n");
	while (!getchar());
	dos_clear_screen();
	printf("well, did it work?\npress any key to continue.\n");
	while (!getchar());

	/* set video mode to 3 (80x25 text mode) */
	dos_mouse_hide();
	dos_text_set_cursor_shape(DOS_CURSOR_LINE);
	dos_set_mode(DOS_MODE_3);

	/* exit gracefully */
	return EXIT_SUCCESS;
}
