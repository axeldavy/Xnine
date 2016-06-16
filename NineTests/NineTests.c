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


//#define PRINT_SUCCESS


static int abs(int v) {
  return v > 0 ? v : -v;
}

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

static void launch_tests(void)
{
    test_depthbias();
}

int main() {
    if (!Xnine_init(-1, &priv))
        return 0;
    launch_tests();
    Xnine_close(priv);
    return 1;
}
