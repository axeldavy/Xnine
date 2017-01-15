/*
 * Copyright 2005, 2007-2008 Henri Verbeet
 * Copyright (C) 2007-2013 Stefan DÃ¶singer(for CodeWeavers)
 * Copyright (C) 2008 Jason Green(for TransGaming)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

/* These tests are directly adapted from wine d3d9 tests, thanks to the original authors.
 * The code was modified in 2016 */

#include <math.h>
#include <d3d9.h>
#include "Xnine.h"

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


//#define PRINT_SUCCESS


#define broken(x) 0
#ifdef PRINT_SUCCESS
#define ok(c, ...) {if (!(c)) fprintf(stderr, "FAIL: "); else fprintf(stderr, "succ: "); fprintf(stderr, __VA_ARGS__);}
#else
#define ok(c, ...) {if (!(c)) {fprintf(stderr, "FAIL: ");fprintf(stderr, __VA_ARGS__);}}
#endif
#define skip(...) {fprintf(stderr, "skip: "); fprintf(stderr, __VA_ARGS__);}
#define trace(...) {fprintf(stderr, "trace: ");fprintf(stderr, __VA_ARGS__);}

struct Xnine_private *priv;

#undef DestroyWindow
#define DestroyWindow(hwnd) Xnine_destroy_window(priv, hwnd)
#undef Direct3DCreate9
#define Direct3DCreate9(a) Xnine_get_D3D9(priv)
#undef CreateWindowA

static HWND create_window_with_size(int width, int height)
{
    HWND ret;
    (void)Xnine_create_window(priv, 640, 480, FALSE, &ret);
    return ret;
}


#define CreateWindowA(a, b, c, d, e, width, height, f, g, h, i) create_window_with_size(width, height)


struct vec2
{
    float x, y;
};

struct vec3
{
    float x, y, z;
};

struct vec4
{
    float x, y, z, w;
};

static HWND create_window(void)
{
    HWND ret;
    (void)Xnine_create_window(priv, 640, 480, FALSE, &ret);
    return ret;
}


static BOOL color_match(D3DCOLOR c1, D3DCOLOR c2, BYTE max_diff)
{
    if (abs((int)(c1 & 0xff) - (int)(c2 & 0xff)) > max_diff) return FALSE;
    c1 >>= 8; c2 >>= 8;
    if (abs((int)(c1 & 0xff) - (int)(c2 & 0xff)) > max_diff) return FALSE;
    c1 >>= 8; c2 >>= 8;
    if (abs((int)(c1 & 0xff) - (int)(c2 & 0xff)) > max_diff) return FALSE;
    c1 >>= 8; c2 >>= 8;
    if (abs((int)(c1 & 0xff) - (int)(c2 & 0xff)) > max_diff) return FALSE;
    return TRUE;
}

static BOOL adapter_is_warp(const D3DADAPTER_IDENTIFIER9 *identifier)
{
    return !strcmp(identifier->Driver, "d3d10warp.dll");
}

/* Locks a given surface and returns the color at (x,y).  It's the caller's
 * responsibility to only pass in lockable surfaces and valid x,y coordinates */
static DWORD getPixelColorFromSurface(IDirect3DSurface9 *surface, UINT x, UINT y)
{
    DWORD color;
    HRESULT hr;
    D3DSURFACE_DESC desc;
    RECT rectToLock = {x, y, x+1, y+1};
    D3DLOCKED_RECT lockedRect;

    hr = IDirect3DSurface9_GetDesc(surface, &desc);
    if(FAILED(hr))  /* This is not a test */
    {
        trace("Can't get the surface description, hr=%08x\n", hr);
        return 0xdeadbeef;
    }

    hr = IDirect3DSurface9_LockRect(surface, &lockedRect, &rectToLock, D3DLOCK_READONLY);
    if(FAILED(hr))  /* This is not a test */
    {
        trace("Can't lock the surface, hr=%08x\n", hr);
        return 0xdeadbeef;
    }
    switch(desc.Format) {
        case D3DFMT_A8R8G8B8:
        {
            color = ((DWORD *) lockedRect.pBits)[0];
            break;
        }
        case D3DFMT_A32B32G32R32F:
        {
            color = ((DWORD *) lockedRect.pBits)[0]; /* Read R */
            break;
        }
        default:
            trace("Error: unknown surface format: %d\n", desc.Format);
            color = 0xdeadbeef;
            break;
    }
    hr = IDirect3DSurface9_UnlockRect(surface);
    if(FAILED(hr))
    {
        trace("Can't unlock the surface, hr=%08x\n", hr);
    }
    return color;
}

struct surface_readback
{
    IDirect3DSurface9 *surface;
    D3DLOCKED_RECT locked_rect;
};

static void get_rt_readback(IDirect3DSurface9 *surface, struct surface_readback *rb)
{
    IDirect3DDevice9 *device;
    HRESULT hr;

    memset(rb, 0, sizeof(*rb));
    IDirect3DSurface9_GetDevice(surface, &device);
    hr = IDirect3DDevice9_CreateOffscreenPlainSurface(device, 640, 480,
            D3DFMT_A8R8G8B8, D3DPOOL_SYSTEMMEM, &rb->surface, NULL);
    if (FAILED(hr) || !rb->surface)
    {
        trace("Can't create an offscreen plain surface to read the render target data, hr %#x.\n", hr);
        goto error;
    }

    hr = IDirect3DDevice9_GetRenderTargetData(device, surface, rb->surface);
    if (FAILED(hr))
    {
        trace("Can't read the render target data, hr %#x.\n", hr);
        goto error;
    }

    hr = IDirect3DSurface9_LockRect(rb->surface, &rb->locked_rect, NULL, D3DLOCK_READONLY);
    if (FAILED(hr))
    {
        trace("Can't lock the offscreen surface, hr %#x.\n", hr);
        goto error;
    }
    IDirect3DDevice9_Release(device);

    return;

error:
    if (rb->surface)
        IDirect3DSurface9_Release(rb->surface);
    rb->surface = NULL;
    IDirect3DDevice9_Release(device);
}

static DWORD get_readback_color(struct surface_readback *rb, unsigned int x, unsigned int y)
{
    return rb->locked_rect.pBits
            ? ((DWORD *)rb->locked_rect.pBits)[y * rb->locked_rect.Pitch / sizeof(DWORD) + x] : 0xdeadbeef;
}

static void release_surface_readback(struct surface_readback *rb)
{
    HRESULT hr;

    if (!rb->surface)
        return;
    if (rb->locked_rect.pBits && FAILED(hr = IDirect3DSurface9_UnlockRect(rb->surface)))
        trace("Can't unlock the offscreen surface, hr %#x.\n", hr);
    IDirect3DSurface9_Release(rb->surface);
}

static DWORD getPixelColor(IDirect3DDevice9 *device, UINT x, UINT y)
{
    DWORD ret;
    IDirect3DSurface9 *rt;
    struct surface_readback rb;
    HRESULT hr;

    hr = IDirect3DDevice9_GetRenderTarget(device, 0, &rt);
    if(FAILED(hr))
    {
        trace("Can't get the render target, hr %#x.\n", hr);
        return 0xdeadbeed;
    }

    get_rt_readback(rt, &rb);
    /* Remove the X channel for now. DirectX and OpenGL have different ideas how to treat it apparently, and it isn't
     * really important for these tests
     */
    ret = get_readback_color(&rb, x, y) & 0x00ffffff;
    release_surface_readback(&rb);

    IDirect3DSurface9_Release(rt);
    return ret;
}

static IDirect3DDevice9 *create_device(IDirect3D9 *d3d, HWND device_window, HWND focus_window, BOOL windowed)
{
    D3DPRESENT_PARAMETERS present_parameters = {0};
    IDirect3DDevice9 *device;

    present_parameters.Windowed = windowed;
    present_parameters.hDeviceWindow = device_window;
    present_parameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
    present_parameters.BackBufferWidth = 640;
    present_parameters.BackBufferHeight = 480;
    present_parameters.BackBufferFormat = D3DFMT_A8R8G8B8;
    present_parameters.EnableAutoDepthStencil = TRUE;
    present_parameters.AutoDepthStencilFormat = D3DFMT_D24S8;

    if (SUCCEEDED(IDirect3D9_CreateDevice(d3d, D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, focus_window,
            D3DCREATE_HARDWARE_VERTEXPROCESSING, &present_parameters, &device)))
        return device;

    return NULL;
}

static void cleanup_device(IDirect3DDevice9 *device)
{
    if (device)
    {
        D3DPRESENT_PARAMETERS present_parameters;
        IDirect3DSwapChain9 *swapchain;
        ULONG ref;

        IDirect3DDevice9_GetSwapChain(device, 0, &swapchain);
        IDirect3DSwapChain9_GetPresentParameters(swapchain, &present_parameters);
        IDirect3DSwapChain9_Release(swapchain);
        ref = IDirect3DDevice9_Release(device);
        ok(ref == 0, "The device was not properly freed: refcount %u.\n", ref);
        DestroyWindow(present_parameters.hDeviceWindow);
    }
}

////////////// tests //////////////////

static void test_depthbias(void)
{
    IDirect3DDevice9 *device;
    IDirect3D9 *d3d;
    IDirect3DSurface9 *ds;
    D3DCAPS9 caps;
    D3DCOLOR color;
    ULONG refcount;
    HWND window;
    HRESULT hr;
    unsigned int i;
    static const D3DFORMAT formats[] =
    {
        D3DFMT_D16, D3DFMT_D24X8, D3DFMT_D32, D3DFMT_D24S8, MAKEFOURCC('I','N','T','Z'),
        D3DFMT_D32F_LOCKABLE, D3DFMT_D24FS8
    };

    static const struct
    {
        struct vec3 position;
    }
    quad[] =
    {
        {{-1.0f, -1.0f, 0.0f}},
        {{-1.0f,  1.0f, 0.0f}},
        {{ 1.0f, -1.0f, 1.0f}},
        {{ 1.0f,  1.0f, 1.0f}},
    };
    union
    {
        float f;
        DWORD d;
    } conv;

    window = CreateWindowA("static", "d3d9_test", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
            0, 0, 640, 480, NULL, NULL, NULL, NULL);
    d3d = Direct3DCreate9(D3D_SDK_VERSION);
    ok(!!d3d, "Failed to create a D3D object.\n");
    if (!(device = create_device(d3d, window, window, TRUE)))
    {
        skip("Failed to create a D3D device, skipping tests.\n");
        goto done;
    }

    hr = IDirect3DDevice9_GetDeviceCaps(device, &caps);
    ok(SUCCEEDED(hr), "Failed to get device caps, hr %#x.\n", hr);
    if (!(caps.RasterCaps & D3DPRASTERCAPS_DEPTHBIAS))
    {
        IDirect3DDevice9_Release(device);
        skip("D3DPRASTERCAPS_DEPTHBIAS not supported.\n");
        goto done;
    }

    hr = IDirect3DDevice9_SetRenderState(device, D3DRS_LIGHTING, FALSE);
    ok(hr == D3D_OK, "IDirect3DDevice9_SetRenderState returned %08x\n", hr);
    hr = IDirect3DDevice9_SetRenderState(device, D3DRS_ZWRITEENABLE, FALSE);
    ok(hr == D3D_OK, "IDirect3DDevice9_SetRenderState returned %08x\n", hr);
    hr = IDirect3DDevice9_SetTextureStageState(device, 0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
    ok(SUCCEEDED(hr), "Failed to set color op, hr %#x.\n", hr);
    hr = IDirect3DDevice9_SetTextureStageState(device, 0, D3DTSS_COLORARG1, D3DTA_TFACTOR);
    ok(SUCCEEDED(hr), "Failed to set color arg, hr %#x.\n", hr);
    hr = IDirect3DDevice9_SetFVF(device, D3DFVF_XYZ);
    ok(SUCCEEDED(hr), "Failed to set FVF, hr %#x.\n", hr);

    for (i = 0; i < sizeof(formats) / sizeof(*formats); ++i)
    {
        if (FAILED(IDirect3D9_CheckDeviceFormat(d3d, D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
                D3DFMT_X8R8G8B8, D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_SURFACE, formats[i])))
        {
            skip("Depth format %u not supported, skipping.\n", formats[i]);
            continue;
        }

        hr = IDirect3DDevice9_CreateDepthStencilSurface(device, 640, 480, formats[i],
                D3DMULTISAMPLE_NONE, 0, FALSE, &ds, NULL);
        ok(SUCCEEDED(hr), "Failed to create depth stencil surface, hr %#x.\n", hr);
        hr = IDirect3DDevice9_SetDepthStencilSurface(device, ds);
        ok(SUCCEEDED(hr), "Failed to set depth stencil surface, hr %#x.\n", hr);
        hr = IDirect3DDevice9_Clear(device, 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00000000, 0.5f, 0);
        ok(SUCCEEDED(hr), "Failed to clear %08x\n", hr);

        hr = IDirect3DDevice9_BeginScene(device);
        ok(SUCCEEDED(hr), "Failed to begin scene, hr %#x.\n", hr);

        hr = IDirect3DDevice9_SetRenderState(device, D3DRS_TEXTUREFACTOR, 0x00ff0000);
        ok(SUCCEEDED(hr), "Failed to set render state, hr %#x.\n", hr);
        conv.f = -0.2f;
        hr = IDirect3DDevice9_SetRenderState(device, D3DRS_DEPTHBIAS, conv.d);
        ok(SUCCEEDED(hr), "Failed to set render state, hr %#x.\n", hr);
        hr = IDirect3DDevice9_DrawPrimitiveUP(device, D3DPT_TRIANGLESTRIP, 2, quad, sizeof(*quad));
        ok(SUCCEEDED(hr), "Failed to draw, hr %#x.\n", hr);

        hr = IDirect3DDevice9_SetRenderState(device, D3DRS_TEXTUREFACTOR, 0x0000ff00);
        ok(SUCCEEDED(hr), "Failed to set render state, hr %#x.\n", hr);
        conv.f = 0.0f;
        hr = IDirect3DDevice9_SetRenderState(device, D3DRS_DEPTHBIAS, conv.d);
        ok(SUCCEEDED(hr), "Failed to set render state, hr %#x.\n", hr);
        hr = IDirect3DDevice9_DrawPrimitiveUP(device, D3DPT_TRIANGLESTRIP, 2, quad, sizeof(*quad));
        ok(SUCCEEDED(hr), "Failed to draw, hr %#x.\n", hr);

        hr = IDirect3DDevice9_SetRenderState(device, D3DRS_TEXTUREFACTOR, 0x000000ff);
        ok(SUCCEEDED(hr), "Failed to set render state, hr %#x.\n", hr);
        conv.f = 0.2f;
        hr = IDirect3DDevice9_SetRenderState(device, D3DRS_DEPTHBIAS, conv.d);
        ok(SUCCEEDED(hr), "Failed to set render state, hr %#x.\n", hr);
        hr = IDirect3DDevice9_DrawPrimitiveUP(device, D3DPT_TRIANGLESTRIP, 2, quad, sizeof(*quad));
        ok(SUCCEEDED(hr), "Failed to draw, hr %#x.\n", hr);

        hr = IDirect3DDevice9_SetRenderState(device, D3DRS_TEXTUREFACTOR, 0x00ffffff);
        ok(SUCCEEDED(hr), "Failed to set render state, hr %#x.\n", hr);
        conv.f = 0.4f;
        hr = IDirect3DDevice9_SetRenderState(device, D3DRS_DEPTHBIAS, conv.d);
        ok(SUCCEEDED(hr), "Failed to set render state, hr %#x.\n", hr);
        hr = IDirect3DDevice9_DrawPrimitiveUP(device, D3DPT_TRIANGLESTRIP, 2, quad, sizeof(*quad));
        ok(SUCCEEDED(hr), "Failed to draw, hr %#x.\n", hr);

        color = getPixelColor(device, 61, 240);
        ok(color_match(color, 0x00ffffff, 1), "Got unexpected color %08x at x=62, format %u.\n", color, formats[i]);
        color = getPixelColor(device, 65, 240);

        /* The broken results are for the WARP driver on the testbot. It seems to initialize
         * a scaling factor based on the first depth format that is used. Other formats with
         * a different depth size then render incorrectly. */
        ok(color_match(color, 0x000000ff, 1) || broken(color_match(color, 0x00ffffff, 1)),
                "Got unexpected color %08x at x=64, format %u.\n", color, formats[i]);
        color = getPixelColor(device, 190, 240);
        ok(color_match(color, 0x000000ff, 1) || broken(color_match(color, 0x00ffffff, 1)),
                "Got unexpected color %08x at x=190, format %u.\n", color, formats[i]);

        color = getPixelColor(device, 194, 240);
        ok(color_match(color, 0x0000ff00, 1) || broken(color_match(color, 0x00ffffff, 1)),
                "Got unexpected color %08x at x=194, format %u.\n", color, formats[i]);
        color = getPixelColor(device, 318, 240);
        ok(color_match(color, 0x0000ff00, 1) || broken(color_match(color, 0x00ffffff, 1)),
                "Got unexpected color %08x at x=318, format %u.\n", color, formats[i]);

        color = getPixelColor(device, 322, 240);
        ok(color_match(color, 0x00ff0000, 1) || broken(color_match(color, 0x00000000, 1)),
                "Got unexpected color %08x at x=322, format %u.\n", color, formats[i]);
        color = getPixelColor(device, 446, 240);
        ok(color_match(color, 0x00ff0000, 1) || broken(color_match(color, 0x00000000, 1)),
                "Got unexpected color %08x at x=446, format %u.\n", color, formats[i]);

        color = getPixelColor(device, 450, 240);
        ok(color_match(color, 0x00000000, 1), "Got unexpected color %08x at x=446, format %u.\n", color, formats[i]);

        hr = IDirect3DDevice9_EndScene(device);
        ok(SUCCEEDED(hr), "Failed to end scene, hr %#x.\n", hr);

        hr = IDirect3DDevice9_Present(device, NULL, NULL, NULL, NULL);
        ok(hr == D3D_OK, "IDirect3DDevice9_Present failed with %08x\n", hr);
        IDirect3DSurface9_Release(ds);
    }

    refcount = IDirect3DDevice9_Release(device);
    ok(!refcount, "Device has %u references left.\n", refcount);

done:
    IDirect3D9_Release(d3d);
    DestroyWindow(window);
}

#ifndef D3DFVF_TEXCOORDSIZE1
#define D3DFVF_TEXCOORDSIZE1(CoordIndex) (D3DFVF_TEXTUREFORMAT1 << (CoordIndex*2 + 16))
#endif

static float asfloat(D3DCOLOR color)
{
    union {
        float f;
        D3DCOLOR c;
    } convert;
    convert.c = color;
    return convert.f;
}

static void fp_special_test2(void)
{
    /* Microsoft's assembler generates nan and inf with "1.#QNAN" and "1.#INF." respectively */
    static const DWORD vs_basic[] =
    {
        0xfffe0300,                          /* vs_3_0           */
        0x0200001f, 0x80000000, 0x900f0000,  /* dcl_position v0  */
        0x0200001f, 0x80000005, 0x900f0001,  /* dcl_texcoord0 v1 */
        0x0200001f, 0x80000000, 0xe00f0000,  /* dcl_position0 o0 */
        0x0200001f, 0x80000005, 0xe00f0001,  /* dcl_texcoord0 o1 */
        0x02000001, 0xe00f0000, 0x90e40000,  /* mov o0, v0       */
        0x02000001, 0xe00f0001, 0x90e40001,  /* mov o1, v1       */
        0x0000ffff,                          /* end              */

    };

    static const DWORD ps_header[] =
    {
        0xffff0300,                                                             /* ps_3_0                       */
        0x05000051, 0xa00f0001, 0x7fc00000, 0xff800000, 0x7f800000, 0x00000000, /* def c1, nan, -inf, inf, 0    */
        0x05000051, 0xa00f0002, 0x00000000, 0x3f000000, 0x3f800000, 0x40000000, /* def c2, 0.0, 0.5, 1.0, 2.0   */
        0x0200001f, 0x80000005, 0x90030000,                                     /* dcl_texcoord0 v0.xy          */
        0x02000001, 0x800f0000, 0xa0000002,                                     /* mov r0, c2.xxxx              */
    };
    static const DWORD ps_loadc0x[] = {0x02000001, 0x80010000, 0xa0000000};     /* mov r0.x, c0.x               */
    static const DWORD ps_loadc0y[] = {0x02000001, 0x80010000, 0xa0550000};     /* mov r0.x, c0.y               */
    static const DWORD ps_loadc0z[] = {0x02000001, 0x80010000, 0xa0aa0000};     /* mov r0.x, c0.z               */
    static const DWORD ps_loadc1x[] = {0x02000001, 0x80010000, 0xa0000001};     /* mov r0.x, c1.x               */
    static const DWORD ps_loadc1y[] = {0x02000001, 0x80010000, 0xa0550001};     /* mov r0.x, c1.y               */
    static const DWORD ps_loadc1z[] = {0x02000001, 0x80010000, 0xa0aa0001};     /* mov r0.x, c1.z               */
    static const DWORD ps_log0[] =    {0x0200000f, 0x80010000, 0x90000000};     /* log r0.x, v0.x               */
    static const DWORD ps_log0cst[] = {0x0200000f, 0x80010000, 0xa0000002};     /* log r0.x, c2.x               */
    /*static const DWORD ps_loginf[] =  {0x0200000f, 0x80010000, 0xa0aa0000};*/     /* log r0.x, c0.z               */
    /*static const DWORD ps_logNaN[] =  {0x0200000f, 0x80010000, 0xa0000000};*/     /* log r0.x, c0.x               */
    static const DWORD ps_nrm0[] =    {0x02000024, 0x80070000, 0x90000000};     /* nrm r0.xyz, v0.xxxx          */
    static const DWORD ps_nrmm0[] =   {0x02000024, 0x80070000, 0x91000000};     /* nrm r0.xyz, -v0.xxxx         */
    static const DWORD ps_nrm0cst[] = {0x02000024, 0x80070000, 0xa0000002};     /* nrm r0.xyz, c2.xxxx          */
    /*static const DWORD ps_nrminf[] =  {0x02000024, 0x80070000, 0xa0aa0000};*/     /* nrm r0.xyz, c0.zzzz          */
    /*static const DWORD ps_nrmminf[] = {0x02000024, 0x80070000, 0xa0550000};*/     /* nrm r0.xyz, c0.yyyy          */
    /*static const DWORD ps_nrmNaN[] =  {0x02000024, 0x80070000, 0xa0000001};*/     /* nrm r0.xyz, c1.xxxx          */
    static const DWORD ps_mul0NaN[] = {0x03000005, 0x80010000, 0xa0000000, 0xa0ff0000};    /* mul r0.x, c0.x, c0.w             */
    static const DWORD ps_mul0inf[] = {0x03000005, 0x80010000, 0xa0ff0000, 0xa0aa0000};    /* mul r0.x, c0.w, c0.z             */
    static const DWORD ps_mul0minf[] ={0x03000005, 0x80010000, 0xa0ff0000, 0xa0550000};    /* mul r0.x, c0.w, c0.y             */
    static const DWORD ps_rcp0[] =    {0x02000006, 0x80010000, 0x90000000};     /* rcp r0.x, v0.x               */
    static const DWORD ps_rcpm0[] =   {0x02000006, 0x80010000, 0x91000000};     /* rcp r0.x, -v0.x              */
    /*static const DWORD ps_rcpinf[] =  {0x02000006, 0x80010000, 0xa0aa0000};     /* rcp r0.x, c0.z               */
    /*static const DWORD ps_rcpminf[] = {0x02000006, 0x80010000, 0xa0550000};     /* rcp r0.x, c0.y              */
    /*static const DWORD ps_rcpNaN[] =  {0x02000006, 0x80010000, 0xa0000001};     /* rcp r0.x, c1.x              */
    static const DWORD ps_rsq0[] =    {0x02000007, 0x80010000, 0x90000000};     /* rsq r0.x, v0.x               */
    static const DWORD ps_rsqm0[] =   {0x02000007, 0x80010000, 0x91000000};     /* rsq r0.x, -v0.x              */
    /*static const DWORD ps_rsqinf[] =  {0x02000007, 0x80010000, 0xa0aa0000};*/     /* rsq r0.x, c0.z               */
    /*static const DWORD ps_rsqminf[] = {0x02000007, 0x80010000, 0xa0550000};*/     /* rsq r0.x, c0.y              */
    /*static const DWORD ps_rsqNaN[] =  {0x02000007, 0x80010000, 0xa0000001};*/     /* rsq r0.x, c1.x              */
    static const DWORD ps_add05[] = {0x03000002, 0x80010000, 0x80000000, 0xa0550002};       /* add r0.x, r0.x, c2.y               */
    static const DWORD ps_footer[] = {
        0x02000001, 0x800f0800, 0x80e40000,                                     /* mov oC0, r0                  */
        0x0000ffff,                                                             /* end                          */
    };

    static const struct
    {
        const char *name;
        const DWORD *ops;
        DWORD size;
        BOOL isNaN;
        D3DCOLOR output;
        D3DCOLOR output2;
    }
    /* log, nrm, rcp and rsq with NaN and inf as inputs: gives the expected NaN(NaN as input), 0(inf as input)
     * on AMD/NVidia, and weird result on intel */
    tests[] =
    {
        {"user_cst_NaN",    ps_loadc0x,  sizeof(ps_loadc0x),  TRUE,  0x7fc00000, 0x7fc00000},
        {"user_cst_minf",   ps_loadc0y,  sizeof(ps_loadc0x),  FALSE, 0xff800000, 0xff7fffff},
        {"user_cst_inf",    ps_loadc0z,  sizeof(ps_loadc0x),  FALSE, 0x7f800000, 0x7f7fffff},
        {"shader_cst_NaN",  ps_loadc1x,  sizeof(ps_loadc0x),  TRUE,  0x7fc00000, 0x7fc00000},
        {"shader_cst_minf", ps_loadc1y,  sizeof(ps_loadc0x),  FALSE, 0xff800000, 0xff7fffff},
        {"shader_cst_inf",  ps_loadc1z,  sizeof(ps_loadc0x),  FALSE, 0x7f800000, 0x7f7fffff},
        {"shader_log0",     ps_log0,     sizeof(ps_log0),     FALSE, 0xff800000, 0xff7fffff},
        {"shader_log0cst",  ps_log0cst,  sizeof(ps_log0cst),  FALSE, 0xff800000, 0xff7fffff},
        {"shader_nrm0",     ps_nrm0,     sizeof(ps_nrm0),     FALSE, 0x00000000, 0x00000000},
        {"shader_nrmm0",    ps_nrmm0,    sizeof(ps_nrmm0),    FALSE, 0x00000000, 0x80000000},
        {"shader_nrm0cst",  ps_nrm0cst,  sizeof(ps_nrm0cst),  FALSE, 0x00000000, 0x00000000},
        {"shader_mul0NaN",  ps_mul0NaN,  sizeof(ps_mul0NaN),  FALSE, 0x00000000, 0x00000000},
        {"shader_mul0inf",  ps_mul0inf,  sizeof(ps_mul0inf),  FALSE, 0x00000000, 0x00000000},
        {"shader_mul0minf", ps_mul0minf, sizeof(ps_mul0minf), FALSE, 0x00000000, 0x00000000},
        {"shader_rcp0",     ps_rcp0,     sizeof(ps_rcp0),     FALSE, 0x7f800000, 0x7f7fffff},
        {"shader_rcpm0",    ps_rcpm0,    sizeof(ps_rcpm0),    FALSE, 0xff800000, 0xff7fffff},
        {"shader_rsq0",     ps_rsq0,     sizeof(ps_rsq0),     FALSE, 0x7f800000, 0x7f7fffff},
        {"shader_rsqm0",    ps_rsqm0,    sizeof(ps_rsqm0),    FALSE, 0x7f800000, 0x7f7fffff},
    };

    struct
    {
        float x, y, z;
        float s;
    }
    quad[] =
    {
        { -1.0f,  1.0f, 0.0f, 0.0f},
        {  1.0f,  1.0f, 1.0f, 0.0f},
        { -1.0f, -1.0f, 0.0f, 0.0f},
        {  1.0f, -1.0f, 1.0f, 0.0f},
    };

    static D3DCOLOR c0[] = {0x7fc00000, 0xff800000, 0x7f800000, 0x00000000};

    IDirect3DSurface9 *backbuffer, *surface;
    IDirect3DVertexShader9 *vs;
    IDirect3DDevice9 *device;
    UINT body_size = 0;
    IDirect3D9 *d3d;
    DWORD *ps_code;
    ULONG refcount;
    D3DCAPS9 caps;
    HWND window;
    HRESULT hr;
    UINT i;

    window = create_window();
    d3d = Direct3DCreate9(D3D_SDK_VERSION);
    ok(!!d3d, "Failed to create a D3D object.\n");
    if (!(device = create_device(d3d, window, window, TRUE)))
    {
        skip("Failed to create a D3D device, skipping tests.\n");
        goto done;
    }

    hr = IDirect3DDevice9_GetDeviceCaps(device, &caps);
    ok(SUCCEEDED(hr), "GetDeviceCaps failed, hr %#x.\n", hr);
    if (caps.PixelShaderVersion < D3DPS_VERSION(3, 0) || caps.VertexShaderVersion < D3DVS_VERSION(3, 0))
    {
        skip("No shader model 3.0 support, skipping floating point specials test.\n");
        IDirect3DDevice9_Release(device);
        goto done;
    }

    if (FAILED(IDirect3D9_CheckDeviceFormat(d3d, D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, D3DFMT_X8R8G8B8,
                D3DUSAGE_RENDERTARGET, D3DRTYPE_TEXTURE, D3DFMT_A32B32G32R32F)))
    {
        skip("Format ARGB32F not supported as render target, skipping test.\n");
        goto done;
    }

     hr = IDirect3DDevice9_CreateRenderTarget(device, 640, 480, D3DFMT_A32B32G32R32F,
            D3DMULTISAMPLE_NONE, 0, TRUE, &surface, NULL );
    ok(hr == D3D_OK, "Unable to create render target surface, hr = %08x\n", hr);

    hr = IDirect3DDevice9_GetBackBuffer(device, 0, 0, D3DBACKBUFFER_TYPE_MONO, &backbuffer);
    ok(SUCCEEDED(hr), "GetBackBuffer failed, hr %#x.\n", hr);

    hr = IDirect3DDevice9_SetFVF(device, D3DFVF_XYZ | D3DFVF_TEX1 | D3DFVF_TEXCOORDSIZE1(0));
    ok(SUCCEEDED(hr), "SetFVF failed, hr %#x.\n", hr);

    hr = IDirect3DDevice9_CreateVertexShader(device, vs_basic, &vs);
    ok(SUCCEEDED(hr), "CreateVertexShader failed, hr %#x.\n", hr);
    hr = IDirect3DDevice9_SetVertexShader(device, vs);
    ok(SUCCEEDED(hr), "SetVertexShader failed, hr %#x.\n", hr);

    hr = IDirect3DDevice9_SetPixelShaderConstantF(device, 0, (float *)c0, 1);
    ok(hr == D3D_OK, "IDirect3DDevice9_SetPixelShaderConstantF returned %08x\n", hr);

    hr = IDirect3DDevice9_SetRenderState(device, D3DRS_ZENABLE, D3DZB_FALSE);
    ok(SUCCEEDED(hr), "SetRenderState failed, hr %#x.\n", hr);

    hr = IDirect3DDevice9_SetRenderTarget(device, 0, surface);
    ok(SUCCEEDED(hr), "SetRenderTarget failed, hr %#x.\n", hr);

    for (i = 0; i < sizeof(tests) / sizeof(*tests); ++i)
    {
        if (tests[i].size > body_size) body_size = tests[i].size;
    }

    ps_code = malloc(sizeof(ps_header) + body_size + sizeof(ps_add05) + sizeof(ps_footer));
    memcpy(ps_code, ps_header, sizeof(ps_header));

    for (i = 0; i < sizeof(tests) / sizeof(*tests); ++i)
    {
        DWORD offset = sizeof(ps_header) / sizeof(*ps_header);
        IDirect3DPixelShader9 *ps;
        D3DCOLOR color;

        memcpy(ps_code + offset, tests[i].ops, tests[i].size);
        offset += tests[i].size / sizeof(*tests[i].ops);
        memcpy(ps_code + offset, ps_footer, sizeof(ps_footer));

        hr = IDirect3DDevice9_CreatePixelShader(device, ps_code, &ps);
        ok(SUCCEEDED(hr), "CreatePixelShader failed, hr %#x.\n", hr);
        hr = IDirect3DDevice9_SetPixelShader(device, ps);
        ok(SUCCEEDED(hr), "SetPixelShader failed, hr %#x.\n", hr);

        hr = IDirect3DDevice9_BeginScene(device);
        ok(SUCCEEDED(hr), "BeginScene failed, hr %#x.\n", hr);
        hr = IDirect3DDevice9_DrawPrimitiveUP(device, D3DPT_TRIANGLESTRIP, 2, quad, sizeof(*quad));
        ok(SUCCEEDED(hr), "DrawPrimitiveUP failed, hr %#x.\n", hr);
        hr = IDirect3DDevice9_EndScene(device);
        ok(SUCCEEDED(hr), "EndScene failed, hr %#x.\n", hr);

        color = getPixelColorFromSurface(surface, 320, 240);
        ok((tests[i].isNaN && isnan(asfloat(color))) || color == tests[i].output || color == tests[i].output2,
                "Expected color 0x%08x or 0x%08x for instruction \"%s\", got 0x%08x.\n",
                tests[i].output, tests[i].output2, tests[i].name, color);

        hr = IDirect3DDevice9_SetPixelShader(device, NULL);
        ok(SUCCEEDED(hr), "SetPixelShader failed, hr %#x.\n", hr);
        IDirect3DPixelShader9_Release(ps);
    }

    free(ps_code);

     hr = IDirect3DDevice9_SetRenderTarget(device, 0, backbuffer);
    ok(SUCCEEDED(hr), "SetRenderTarget failed, hr %#x.\n", hr);
    hr = IDirect3DDevice9_SetVertexShader(device, NULL);
    ok(SUCCEEDED(hr), "SetVertexShader failed, hr %#x.\n", hr);
    IDirect3DVertexShader9_Release(vs);
    IDirect3DSurface9_Release(surface);
    IDirect3DSurface9_Release(backbuffer);
    refcount = IDirect3DDevice9_Release(device);
    ok(!refcount, "Device has %u references left.\n", refcount);
done:
    IDirect3D9_Release(d3d);
    DestroyWindow(window);
}

static void launch_tests(void)
{
    test_depthbias();
    fp_special_test2();
}

int main() {
    if (!Xnine_init(-1, &priv))
        return 0;
    launch_tests();
    Xnine_close(priv);
    return 1;
}
