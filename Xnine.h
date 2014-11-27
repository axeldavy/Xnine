/*
 * Copyright © 2014 Axel Davy
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */ 


#include "d3d9.h"

#ifdef __cplusplus
extern "C" {
#endif

struct Xnine_private;

BOOL Xnine_init(int screen_num, struct Xnine_private **priv);

struct IDirect3D9 *Xnine_get_D3D9(struct Xnine_private *priv);
struct IDirect3D9Ex *Xnine_get_D3D9Ex(struct Xnine_private *priv);

BOOL Xnine_create_window(struct Xnine_private *priv, int width, int height, BOOL fullscreen, HWND *hwnd);

BOOL Xnine_resize_window(struct Xnine_private *priv, HWND win, int width, int height, BOOL fullscreen);

void Xnine_destroy_window(struct Xnine_private *priv, HWND win);

void Xnine_close(struct Xnine_private *priv);

#ifdef __cplusplus
}
#endif