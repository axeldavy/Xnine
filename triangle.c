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

#include <d3d9.h>
#include "Xnine.h"

#include <unistd.h>
#include <string.h>

struct CUSTOMVERTEX {
        float x, y, z;
        DWORD color;
};

#define WIDTH 800
#define HEIGHT 600

static const struct CUSTOMVERTEX triangle_vertices[] = 
{
    {-1.f, -1.f, 0.5f, D3DCOLOR_XRGB(0, 0, 255)},
    {0.f, 1.f, 0.5f, D3DCOLOR_XRGB(0, 255, 0)},
    {1.f, -1.f, 0.5f, D3DCOLOR_XRGB(255, 0, 0)},
};

static void triangle(struct IDirect3D9 *d3d9, struct Xnine_private *priv)
{
    D3DPRESENT_PARAMETERS d3dpp;
    IDirect3DDevice9 *device = NULL;
    IDirect3DVertexBuffer9 *vertex_buf = NULL;
    int width = 800;
    int height = 600;
    HWND hwnd;
    void* pVoid;

    memset(&d3dpp, 0, sizeof(D3DPRESENT_PARAMETERS));
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
    d3dpp.BackBufferWidth = width;
    d3dpp.BackBufferHeight = height;
    (void)Xnine_create_window(priv, width, height, FALSE, &hwnd);
    d3dpp.hDeviceWindow = hwnd;
    IDirect3D9_CreateDevice(d3d9, D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd,
                            D3DCREATE_HARDWARE_VERTEXPROCESSING,
                            &d3dpp, &device);

    IDirect3DDevice9_CreateVertexBuffer(device, 3*sizeof(struct CUSTOMVERTEX),
                                        0, D3DFVF_XYZ | D3DFVF_DIFFUSE,
                                        D3DPOOL_MANAGED,
                                        &vertex_buf, NULL);

    IDirect3DVertexBuffer9_Lock(vertex_buf, 0, 0, &pVoid, 0);
    memcpy(pVoid, triangle_vertices, sizeof(triangle_vertices));
    IDirect3DVertexBuffer9_Unlock(vertex_buf);

    IDirect3DDevice9_Clear(device, 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 255), 1.0f,  0);
    IDirect3DDevice9_BeginScene(device);
    IDirect3DDevice9_SetRenderState(device, D3DRS_LIGHTING, FALSE);
    IDirect3DDevice9_SetFVF(device, D3DFVF_XYZ | D3DFVF_DIFFUSE);
    IDirect3DDevice9_SetStreamSource(device, 0, vertex_buf, 0, sizeof(struct CUSTOMVERTEX));
    IDirect3DDevice9_DrawPrimitive(device, D3DPT_TRIANGLELIST, 0, 1);
    IDirect3DDevice9_EndScene(device);
    IDirect3DDevice9_Present(device, NULL, NULL, NULL, NULL);

    sleep(10);
    IDirect3DDevice9_Release(device);
    Xnine_destroy_window(priv, hwnd);
}

int main() {
    struct Xnine_private *priv;
    struct IDirect3D9 *d3d9;

    if (!Xnine_init(-1, &priv))
        return 0;
    d3d9 = Xnine_get_D3D9(priv);
    triangle(d3d9, priv);
    IDirect3D9_Release(d3d9);
    Xnine_close(priv);
    return 1;
}
