// SPDX-License-Identifier: LGPL-2.1-or-later
/* These tests are directly adapted from wine d3d9 tests.
 * Thanks to the original authors:
 * Copyright 2005, 2007-2008 Henri Verbeet
 * Copyright (C) 2007-2013 Stefan DÃ¶singer(for CodeWeavers)
 * Copyright (C) 2008 Jason Green(for TransGaming)
 */

#include <math.h>
#include <d3d9.h>
#include "Xnine.h"

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

#include <gtest/gtest.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(*(a)))

#define UINT_PTR uintptr_t

#define broken(x) 0
#define ok(c, ...) do {{EXPECT_TRUE(c);}} while(0)
#define ok_(file, line) ok
#define skip(...) do {fprintf(stderr, "skip(%u): ", __LINE__); fprintf(stderr, __VA_ARGS__);} while(0)
#define win_skip(...) do {fprintf(stderr, "skip(%u): ", __LINE__); fprintf(stderr, __VA_ARGS__);} while(0)
#define trace(...) do {fprintf(stderr, "trace(%u): ", __LINE__);fprintf(stderr, __VA_ARGS__);} while(0)

#define ZeroMemory(p, n) memset(p, 0, n)

#define todo_nine(a)
#define todo_wine
#define todo_wine_if(c) if (c)
#define SIZE_T size_t
#define heap_alloc malloc
#define HeapAlloc(a, b, c) malloc(c)
#define HeapFree(a, b, c) free(c)
#define heap_free free
#define min(a, b) (((a) > (b)) ? (b) : (a))
#define max(a, b) (((a) > (b)) ? (a) : (b))

#define U(x)  (x).u

#define D3DFVF_TEXCOORDSIZE1(CoordIndex) (D3DFVF_TEXTUREFORMAT1 << (CoordIndex*2 + 16))
#define D3DFVF_TEXCOORDSIZE2(CoordIndex) (D3DFVF_TEXTUREFORMAT2)
#define D3DFVF_TEXCOORDSIZE3(CoordIndex) (D3DFVF_TEXTUREFORMAT3 << (CoordIndex*2 + 16))
#define D3DFVF_TEXCOORDSIZE4(CoordIndex) (D3DFVF_TEXTUREFORMAT4 << (CoordIndex*2 + 16))

#define D3DSINCOSCONST1   -1.5500992e-006f, -2.1701389e-005f,  0.0026041667f, 0.00026041668f
#define D3DSINCOSCONST2   -0.020833334f,    -0.12500000f,      1.0f,          0.50000000f

#define GetProcessHeap() 0

struct Xnine_private *priv;

#undef DestroyWindow
#define DestroyWindow(hwnd) Xnine_destroy_window(priv, hwnd)
#undef Direct3DCreate9
#define Direct3DCreate9(a) Xnine_get_D3D9(priv)
#undef CreateWindowA

static inline BOOL WINAPI SetRect(LPRECT rect, INT left, INT top, INT right, INT bottom)
{
    if (!rect) return FALSE;
    rect->left   = left;
    rect->right  = right;
    rect->top    = top;
    rect->bottom = bottom;
    return TRUE;
}

static inline BOOL WINAPI PtInRect(const RECT *rect, POINT pt)
{
    if (!rect) return FALSE;
    return ((pt.x >= rect->left) && (pt.x < rect->right) &&
            (pt.y >= rect->top) && (pt.y < rect->bottom));
}

static HWND create_window_with_size(int width, int height)
{
    HWND ret;
    (void)Xnine_create_window(priv, 640, 480, FALSE, &ret);
    return ret;
}


#define CreateWindowA(a, b, c, d, e, width, height, f, g, h, i) create_window_with_size(width, height)

static HWND create_window(void)
{
    HWND ret;
    (void)Xnine_create_window(priv, 640, 480, FALSE, &ret);
    return ret;
}

#define wait_query(a) wait_query_(__FILE__, __LINE__, a)
static inline void wait_query_(const char *file, unsigned int line, IDirect3DQuery9 *query)
{
    unsigned int i;
    HRESULT hr;

    for (i = 0; i < 500; ++i)
    {
        if ((hr = IDirect3DQuery9_GetData(query, NULL, 0, D3DGETDATA_FLUSH)) == S_OK)
            break;
        sleep(10);
    }
    ok_(file, line)(hr == S_OK, "Got unexpected hr %#x.\n", hr);
}
