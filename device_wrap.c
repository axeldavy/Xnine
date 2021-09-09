/* SPDX-License-Identifier: LGPL-2.1-or-later */
/*
 * Copyright 2016 Axel Davy
 */
#include <stdio.h>
#include <stdlib.h>
#include <d3d9.h>

#include <d3dadapter/d3dadapter9.h>

#define ALT_WINAPI
#define ALT_DECLSPEC_HOTPATCH 
typedef struct common_vtable {
	/* IUnknown */
	HRESULT (ALT_WINAPI *QueryInterface)(void *This, REFIID riid, void **ppvObject);
	ULONG (ALT_WINAPI *AddRef)(void *This);
	ULONG (ALT_WINAPI *Release)(void *This);
	/* IDirect3DResource9 */
	HRESULT (ALT_WINAPI *GetDevice)(void *This, IDirect3DDevice9 **ppDevice);
	HRESULT (ALT_WINAPI *SetPrivateData)(IDirect3DIndexBuffer9 *This, REFGUID refguid, const void *pData, DWORD SizeOfData, DWORD Flags);
	HRESULT (ALT_WINAPI *GetPrivateData)(IDirect3DIndexBuffer9 *This, REFGUID refguid, void *pData, DWORD *pSizeOfData);
	HRESULT (ALT_WINAPI *FreePrivateData)(IDirect3DIndexBuffer9 *This, REFGUID refguid);
	DWORD (ALT_WINAPI *SetPriority)(IDirect3DIndexBuffer9 *This, DWORD PriorityNew);
	DWORD (ALT_WINAPI *GetPriority)(IDirect3DIndexBuffer9 *This);
	void (ALT_WINAPI *PreLoad)(IDirect3DIndexBuffer9 *This);
	D3DRESOURCETYPE (ALT_WINAPI *GetType)(IDirect3DIndexBuffer9 *This);
} common_vtable;

typedef struct common_wrap {
   common_vtable *lpVtbl;
   common_vtable *lpVtbl_internal;
} common_wrap;

#define COMMON_WRAP0(ret, func)  \
    ret ALT_WINAPI Nine_ ## func(void *This) \
    { \
        return ((common_wrap *)This)->lpVtbl_internal->func(This); \
    }

#define COMMON_WRAP1(ret, func, type1)  \
    ret ALT_WINAPI Nine_ ## func(void *This, type1 arg1) \
    { \
        return ((common_wrap *)This)->lpVtbl_internal->func(This, arg1); \
    }

#define COMMON_WRAP2(ret, func, type1, type2)  \
    ret ALT_WINAPI Nine_ ## func(void *This, type1 arg1, type2 arg2) \
    { \
        return ((common_wrap *)This)->lpVtbl_internal->func(This, arg1, arg2); \
    }

#define COMMON_WRAP3(ret, func, type1, type2, type3)  \
    ret ALT_WINAPI Nine_ ## func(void *This, type1 arg1, type2 arg2, type3 arg3) \
    { \
        return ((common_wrap *)This)->lpVtbl_internal->func(This, arg1, arg2, arg3); \
    }

#define COMMON_WRAP4(ret, func, type1, type2, type3, type4)  \
    ret ALT_WINAPI Nine_ ## func(void *This, type1 arg1, type2 arg2, type3 arg3, type4 arg4) \
    { \
        return ((common_wrap *)This)->lpVtbl_internal->func(This, arg1, arg2, arg3, arg4); \
    }

COMMON_WRAP2(HRESULT, QueryInterface, REFIID, void **)
COMMON_WRAP0(ULONG, AddRef)
COMMON_WRAP0(ULONG, Release)
COMMON_WRAP1(HRESULT, GetDevice, IDirect3DDevice9 **)
COMMON_WRAP4(HRESULT, SetPrivateData, REFGUID, const void *, DWORD, DWORD)
COMMON_WRAP3(HRESULT, GetPrivateData, REFGUID, void *, DWORD*)
COMMON_WRAP1(HRESULT, FreePrivateData, REFGUID)
COMMON_WRAP1(DWORD, SetPriority, DWORD)
COMMON_WRAP0(DWORD, GetPriority)
COMMON_WRAP0(void, PreLoad)
COMMON_WRAP0(D3DRESOURCETYPE, GetType)

struct IDirect3DSurface9_Minor1
{
        IDirect3DSurface9Vtbl *lpVtbl;
        IDirect3DSurface9Vtbl *lpVtbl_internal;
};
typedef struct IDirect3DSurface9_Minor1 IDirect3DSurface9_Minor1;

#define SURFACE_WRAP0(ret, func)  \
    ret ALT_WINAPI NineSurface9_ ## func(void *This) \
    { \
        return ((IDirect3DSurface9_Minor1 *)This)->lpVtbl_internal->func(This); \
    }

#define SURFACE_WRAP1(ret, func, type1)  \
    ret ALT_WINAPI NineSurface9_ ## func(void *This, type1 arg1) \
    { \
        return ((IDirect3DSurface9_Minor1 *)This)->lpVtbl_internal->func(This, arg1); \
    }

#define SURFACE_WRAP2(ret, func, type1, type2)  \
    ret ALT_WINAPI NineSurface9_ ## func(void *This, type1 arg1, type2 arg2) \
    { \
        return ((IDirect3DSurface9_Minor1 *)This)->lpVtbl_internal->func(This, arg1, arg2); \
    }

#define SURFACE_WRAP3(ret, func, type1, type2, type3)  \
    ret ALT_WINAPI NineSurface9_ ## func(void *This, type1 arg1, type2 arg2, type3 arg3) \
    { \
        return ((IDirect3DSurface9_Minor1 *)This)->lpVtbl_internal->func(This, arg1, arg2, arg3); \
    }

SURFACE_WRAP2(HRESULT, GetContainer, REFIID, void**)
SURFACE_WRAP1(HRESULT, GetDesc, D3DSURFACE_DESC*)
SURFACE_WRAP3(HRESULT, LockRect, D3DLOCKED_RECT *, const RECT *, DWORD)
SURFACE_WRAP0(HRESULT, UnlockRect)
SURFACE_WRAP1(HRESULT, GetDC, HDC*)
SURFACE_WRAP1(HRESULT, ReleaseDC, HDC)

static IDirect3DSurface9Vtbl NineSurface9_vtable = {
    (void *)Nine_QueryInterface,
    (void *)Nine_AddRef,
    (void *)Nine_Release,
    (void *)Nine_GetDevice, /* actually part of  iface */
    (void *)Nine_SetPrivateData,
    (void *)Nine_GetPrivateData,
    (void *)Nine_FreePrivateData,
    (void *)Nine_SetPriority,
    (void *)Nine_GetPriority,
    (void *)Nine_PreLoad, /* nop */
    (void *)Nine_GetType, /* immutable */
    (void *)NineSurface9_GetContainer,
    (void *)NineSurface9_GetDesc, /* immutable */
    (void *)NineSurface9_LockRect,
    (void *)NineSurface9_UnlockRect,
    (void *)NineSurface9_GetDC,
    (void *)NineSurface9_ReleaseDC
};


struct IDirect3DDevice9Ex_Minor1
{
        IDirect3DDevice9ExVtbl *lpVtbl;
        IDirect3DDevice9ExVtbl *lpVtbl_internal;
};

struct IDirect3DSwapChain9Ex_Minor1
{
        IDirect3DSwapChain9ExVtbl *lpVtbl;
        IDirect3DSwapChain9ExVtbl *lpVtbl_internal;
};


typedef struct IDirect3DDevice9Ex_Minor1 IDirect3DDevice9Ex_Minor1;
typedef struct IDirect3DSwapChain9Ex_Minor1 IDirect3DSwapChain9Ex_Minor1;
typedef struct IDirect3DVertexDeclaration9_Minor1 {
   IDirect3DVertexDeclaration9Vtbl *lpVtbl;
   IDirect3DVertexDeclaration9Vtbl *lpVtbl_internal;
} IDirect3DVertexDeclaration9_Minor1;

#define SWAPCHAIN_WRAP0(ret, func)  \
    ret ALT_WINAPI NineSwapChain9_ ## func(IDirect3DSwapChain9Ex *This) \
    { \
     printf("%s\n", __func__); \
        return ((IDirect3DSwapChain9Ex_Minor1 *)This)->lpVtbl_internal->func(This); \
    }

#define SWAPCHAIN_WRAP1(ret, func, type1)  \
    ret ALT_WINAPI NineSwapChain9_ ## func(IDirect3DSwapChain9Ex *This, type1 arg1) \
    { \
     printf("%s\n", __func__); \
        return ((IDirect3DSwapChain9Ex_Minor1 *)This)->lpVtbl_internal->func(This, arg1); \
    }

#define SWAPCHAIN_WRAP2(ret, func, type1, type2)  \
    ret ALT_WINAPI NineSwapChain9_ ## func(IDirect3DSwapChain9Ex *This, type1 arg1, type2 arg2) \
    { \
     printf("%s\n", __func__); \
        return ((IDirect3DSwapChain9Ex_Minor1 *)This)->lpVtbl_internal->func(This, arg1, arg2); \
    }

#define SWAPCHAIN_WRAP3(ret, func, type1, type2, type3)  \
    ret ALT_WINAPI NineSwapChain9_ ## func(IDirect3DSwapChain9Ex *This, type1 arg1, type2 arg2, type3 arg3) \
    { \
     printf("%s\n", __func__); \
        return ((IDirect3DSwapChain9Ex_Minor1 *)This)->lpVtbl_internal->func(This, arg1, arg2, arg3); \
    }

#define SWAPCHAIN_H_WRAP5(ret, func, type1, type2, type3, type4, type5)  \
    ret ALT_WINAPI ALT_DECLSPEC_HOTPATCH NineSwapChain9_ ## func(IDirect3DSwapChain9Ex *This, type1 arg1, type2 arg2, type3 arg3, type4 arg4, type5 arg5) \
    { \
     printf("%s\n", __func__); \
        return ((IDirect3DSwapChain9Ex_Minor1 *)This)->lpVtbl_internal->func(This, arg1, arg2, arg3, arg4, arg5); \
    }

#define DEVICE_WRAP0(ret, func)  \
    ret ALT_WINAPI NineDevice9_ ## func(IDirect3DDevice9Ex *This) \
    { \
     printf("%s\n", __func__); \
        return ((IDirect3DDevice9Ex_Minor1 *)This)->lpVtbl_internal->func(This); \
    }

#define DEVICE_WRAP1(ret, func, type1)  \
    ret ALT_WINAPI NineDevice9_ ## func(IDirect3DDevice9Ex *This, type1 arg1) \
    { printf("%s\n", __func__); \
        return ((IDirect3DDevice9Ex_Minor1 *)This)->lpVtbl_internal->func(This, arg1); \
    }

#define DEVICE_WRAP2(ret, func, type1, type2)  \
    ret ALT_WINAPI NineDevice9_ ## func(IDirect3DDevice9Ex *This, type1 arg1, type2 arg2) \
    { printf("%s\n", __func__); \
        return ((IDirect3DDevice9Ex_Minor1 *)This)->lpVtbl_internal->func(This, arg1, arg2); \
    }

#define DEVICE_WRAP3(ret, func, type1, type2, type3)  \
    ret ALT_WINAPI NineDevice9_ ## func(IDirect3DDevice9Ex *This, type1 arg1, type2 arg2, type3 arg3) \
    { printf("%s\n", __func__); \
        return ((IDirect3DDevice9Ex_Minor1 *)This)->lpVtbl_internal->func(This, arg1, arg2, arg3); \
    }

#define DEVICE_WRAP4(ret, func, type1, type2, type3, type4)  \
    ret ALT_WINAPI NineDevice9_ ## func(IDirect3DDevice9Ex *This, type1 arg1, type2 arg2, type3 arg3, type4 arg4) \
    { printf("%s\n", __func__); \
        return ((IDirect3DDevice9Ex_Minor1 *)This)->lpVtbl_internal->func(This, arg1, arg2, arg3, arg4); \
    }

#define DEVICE_WRAP5(ret, func, type1, type2, type3, type4, type5)  \
    ret ALT_WINAPI NineDevice9_ ## func(IDirect3DDevice9Ex *This, type1 arg1, type2 arg2, type3 arg3, type4 arg4, type5 arg5) \
    { printf("%s\n", __func__); \
        return ((IDirect3DDevice9Ex_Minor1 *)This)->lpVtbl_internal->func(This, arg1, arg2, arg3, arg4, arg5); \
    }

#define DEVICE_WRAP6(ret, func, type1, type2, type3, type4, type5, type6)  \
    ret ALT_WINAPI NineDevice9_ ## func(IDirect3DDevice9Ex *This, type1 arg1, type2 arg2, type3 arg3, type4 arg4, type5 arg5, type6 arg6) \
    { printf("%s\n", __func__); \
        return ((IDirect3DDevice9Ex_Minor1 *)This)->lpVtbl_internal->func(This, arg1, arg2, arg3, arg4, arg5, arg6); \
    }

#define DEVICE_WRAP7(ret, func, type1, type2, type3, type4, type5, type6, type7)  \
    ret ALT_WINAPI NineDevice9_ ## func(IDirect3DDevice9Ex *This, type1 arg1, type2 arg2, type3 arg3, type4 arg4, type5 arg5, type6 arg6, type7 arg7) \
    { printf("%s\n", __func__); \
        return ((IDirect3DDevice9Ex_Minor1 *)This)->lpVtbl_internal->func(This, arg1, arg2, arg3, arg4, arg5, arg6, arg7); \
    }

#define DEVICE_WRAP8(ret, func, type1, type2, type3, type4, type5, type6, type7, type8)  \
    ret ALT_WINAPI NineDevice9_ ## func(IDirect3DDevice9Ex *This, type1 arg1, type2 arg2, type3 arg3, type4 arg4, type5 arg5, type6 arg6, type7 arg7, type8 arg8) \
    { printf("%s\n", __func__); \
        return ((IDirect3DDevice9Ex_Minor1 *)This)->lpVtbl_internal->func(This, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8); \
    }

#define DEVICE_WRAP9(ret, func, type1, type2, type3, type4, type5, type6, type7, type8, type9)  \
    ret ALT_WINAPI NineDevice9_ ## func(IDirect3DDevice9Ex *This, type1 arg1, type2 arg2, type3 arg3, type4 arg4, type5 arg5, type6 arg6, type7 arg7, type8 arg8, type9 arg9) \
    { printf("%s\n", __func__); \
        return ((IDirect3DDevice9Ex_Minor1 *)This)->lpVtbl_internal->func(This, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9); \
    }

#define DEVICE_H_WRAP0(ret, func)  \
    ret ALT_WINAPI ALT_DECLSPEC_HOTPATCH NineDevice9_ ## func(IDirect3DDevice9Ex *This) \
    { printf("%s\n", __func__); \
        return ((IDirect3DDevice9Ex_Minor1 *)This)->lpVtbl_internal->func(This); \
    }

#define DEVICE_H_WRAP1(ret, func, type1)  \
    ret ALT_WINAPI ALT_DECLSPEC_HOTPATCH NineDevice9_ ## func(IDirect3DDevice9Ex *This, type1 arg1) \
    { printf("%s\n", __func__); \
        return ((IDirect3DDevice9Ex_Minor1 *)This)->lpVtbl_internal->func(This, arg1); \
    }

#define DEVICE_H_WRAP2(ret, func, type1, type2)  \
    ret ALT_WINAPI ALT_DECLSPEC_HOTPATCH NineDevice9_ ## func(IDirect3DDevice9Ex *This, type1 arg1, type2 arg2) \
    { printf("%s\n", __func__); \
        return ((IDirect3DDevice9Ex_Minor1 *)This)->lpVtbl_internal->func(This, arg1, arg2); \
    }

#define DEVICE_H_WRAP3(ret, func, type1, type2, type3)  \
    ret ALT_WINAPI ALT_DECLSPEC_HOTPATCH NineDevice9_ ## func(IDirect3DDevice9Ex *This, type1 arg1, type2 arg2, type3 arg3) \
    { printf("%s\n", __func__); \
        return ((IDirect3DDevice9Ex_Minor1 *)This)->lpVtbl_internal->func(This, arg1, arg2, arg3); \
    }

#define DEVICE_H_WRAP4(ret, func, type1, type2, type3, type4)  \
    ret ALT_WINAPI ALT_DECLSPEC_HOTPATCH NineDevice9_ ## func(IDirect3DDevice9Ex *This, type1 arg1, type2 arg2, type3 arg3, type4 arg4) \
    { printf("%s\n", __func__); \
        return ((IDirect3DDevice9Ex_Minor1 *)This)->lpVtbl_internal->func(This, arg1, arg2, arg3, arg4); \
    }

#define DEVICE_H_WRAP5(ret, func, type1, type2, type3, type4, type5)  \
    ret ALT_WINAPI ALT_DECLSPEC_HOTPATCH NineDevice9_ ## func(IDirect3DDevice9Ex *This, type1 arg1, type2 arg2, type3 arg3, type4 arg4, type5 arg5) \
    { printf("%s\n", __func__); \
        return ((IDirect3DDevice9Ex_Minor1 *)This)->lpVtbl_internal->func(This, arg1, arg2, arg3, arg4, arg5); \
    }


static HRESULT ALT_WINAPI
NineSwapChain9_GetBackBuffer(IDirect3DSwapChain9Ex *This, UINT Level, D3DBACKBUFFER_TYPE type, IDirect3DSurface9 **ppSurface)
{    HRESULT hr;

    hr = ((IDirect3DSwapChain9Ex_Minor1 *)This)->lpVtbl_internal->GetBackBuffer(This, Level, type, ppSurface);
    if (FAILED(hr))
        return hr;

    (*ppSurface)->lpVtbl = (IDirect3DSurface9Vtbl *)&NineSurface9_vtable;

    return hr;
}



SWAPCHAIN_WRAP2(HRESULT, QueryInterface, REFIID, void **)
SWAPCHAIN_WRAP0(ULONG, AddRef)
SWAPCHAIN_WRAP0(ULONG, Release)
SWAPCHAIN_H_WRAP5(HRESULT, Present, const RECT *, const RECT *, HWND, const RGNDATA *, DWORD)
SWAPCHAIN_WRAP1(HRESULT, GetFrontBufferData, IDirect3DSurface9 *)
SWAPCHAIN_WRAP1(HRESULT, GetRasterStatus, D3DRASTER_STATUS *)
SWAPCHAIN_WRAP1(HRESULT, GetDisplayMode, D3DDISPLAYMODE *)
SWAPCHAIN_WRAP1(HRESULT, GetDevice, IDirect3DDevice9 **)
SWAPCHAIN_WRAP1(HRESULT, GetPresentParameters, D3DPRESENT_PARAMETERS *)
SWAPCHAIN_WRAP1(HRESULT, GetLastPresentCount, UINT *)
SWAPCHAIN_WRAP1(HRESULT, GetPresentStats, D3DPRESENTSTATS *)
SWAPCHAIN_WRAP2(HRESULT, GetDisplayModeEx, D3DDISPLAYMODEEX *, D3DDISPLAYROTATION *)

static HRESULT ALT_WINAPI
NineDevice9_GetBackBuffer(IDirect3DDevice9Ex *This, UINT Level, UINT arg, D3DBACKBUFFER_TYPE type, IDirect3DSurface9 **ppSurface)
{    HRESULT hr;

    hr = ((IDirect3DDevice9Ex_Minor1 *)This)->lpVtbl_internal->GetBackBuffer(This, Level, arg, type, ppSurface);
    if (FAILED(hr))
        return hr;

    (*ppSurface)->lpVtbl = (IDirect3DSurface9Vtbl *)&NineSurface9_vtable;

    return hr;
}

static HRESULT ALT_WINAPI
NineDevice9_CreateRenderTarget(IDirect3DDevice9Ex *This, UINT arg1, UINT arg2, D3DFORMAT arg3, D3DMULTISAMPLE_TYPE arg4, DWORD arg5, BOOL arg6, IDirect3DSurface9 **ppSurface, HANDLE *arg7)
{    HRESULT hr;

    hr = ((IDirect3DDevice9Ex_Minor1 *)This)->lpVtbl_internal->CreateRenderTarget(This, arg1, arg2, arg3, arg4, arg5, arg6, ppSurface, arg7);
    if (FAILED(hr))
        return hr;

    (*ppSurface)->lpVtbl = (IDirect3DSurface9Vtbl *)&NineSurface9_vtable;

    return hr;
}

static HRESULT ALT_WINAPI
NineDevice9_CreateRenderTargetEx(IDirect3DDevice9Ex *This, UINT arg1, UINT arg2, D3DFORMAT arg3, D3DMULTISAMPLE_TYPE arg4, DWORD arg5, BOOL arg6, IDirect3DSurface9 **ppSurface, HANDLE *arg7, DWORD arg8)
{    HRESULT hr;

    hr = ((IDirect3DDevice9Ex_Minor1 *)This)->lpVtbl_internal->CreateRenderTargetEx(This, arg1, arg2, arg3, arg4, arg5, arg6, ppSurface, arg7, arg8);
    if (FAILED(hr))
        return hr;

    (*ppSurface)->lpVtbl = (IDirect3DSurface9Vtbl *)&NineSurface9_vtable;

    return hr;
}

static HRESULT ALT_WINAPI
NineDevice9_CreateDepthStencilSurface(IDirect3DDevice9Ex *This, UINT arg1, UINT arg2, D3DFORMAT arg3, D3DMULTISAMPLE_TYPE arg4, DWORD arg5, BOOL arg6, IDirect3DSurface9 **ppSurface, HANDLE *arg7)
{    HRESULT hr;

    hr = ((IDirect3DDevice9Ex_Minor1 *)This)->lpVtbl_internal->CreateDepthStencilSurface(This, arg1, arg2, arg3, arg4, arg5, arg6, ppSurface, arg7);
    if (FAILED(hr))
        return hr;

    (*ppSurface)->lpVtbl = (IDirect3DSurface9Vtbl *)&NineSurface9_vtable;

    return hr;
}

static HRESULT ALT_WINAPI
NineDevice9_CreateDepthStencilSurfaceEx(IDirect3DDevice9Ex *This, UINT arg1, UINT arg2, D3DFORMAT arg3, D3DMULTISAMPLE_TYPE arg4, DWORD arg5, BOOL arg6, IDirect3DSurface9 **ppSurface, HANDLE *arg7, DWORD arg8)
{    HRESULT hr;

    hr = ((IDirect3DDevice9Ex_Minor1 *)This)->lpVtbl_internal->CreateDepthStencilSurfaceEx(This, arg1, arg2, arg3, arg4, arg5, arg6, ppSurface, arg7, arg8);
    if (FAILED(hr))
        return hr;

    (*ppSurface)->lpVtbl = (IDirect3DSurface9Vtbl *)&NineSurface9_vtable;

    return hr;
}

static HRESULT ALT_WINAPI
NineDevice9_CreateOffscreenPlainSurface(IDirect3DDevice9Ex *This, UINT arg1, UINT arg2, D3DFORMAT arg3, D3DPOOL arg4, IDirect3DSurface9 **ppSurface, HANDLE *arg5)
{    HRESULT hr;

    hr = ((IDirect3DDevice9Ex_Minor1 *)This)->lpVtbl_internal->CreateOffscreenPlainSurface(This, arg1, arg2, arg3, arg4, ppSurface, arg5);
    if (FAILED(hr))
        return hr;

    (*ppSurface)->lpVtbl = (IDirect3DSurface9Vtbl *)&NineSurface9_vtable;

    return hr;
}

static HRESULT ALT_WINAPI
NineDevice9_CreateOffscreenPlainSurfaceEx(IDirect3DDevice9Ex *This, UINT arg1, UINT arg2, D3DFORMAT arg3, D3DPOOL arg4, IDirect3DSurface9 **ppSurface, HANDLE *arg5, DWORD arg6)
{    HRESULT hr;

    hr = ((IDirect3DDevice9Ex_Minor1 *)This)->lpVtbl_internal->CreateOffscreenPlainSurfaceEx(This, arg1, arg2, arg3, arg4, ppSurface, arg5, arg6);
    if (FAILED(hr))
        return hr;

    (*ppSurface)->lpVtbl = (IDirect3DSurface9Vtbl *)&NineSurface9_vtable;

    return hr;
}

static HRESULT ALT_WINAPI
NineDevice9_GetDirect3D(struct NineDevice9 *This,
                         IDirect3D9 **ppD3D9)
{
    void **vtable_mirror;
    printf("NineDevice9_GetDirect3D\n");
    HRESULT hr = ((IDirect3DDevice9Ex_Minor1 *)This)->lpVtbl_internal->GetDirect3D(This, &vtable_mirror);
    /* ppD3D9 is the IDirect3D9 version. Let's get the _alt */
    ppD3D9 = (void*)(vtable_mirror-1);
    
    
}

DEVICE_WRAP2(HRESULT, QueryInterface, REFIID, void **)
DEVICE_WRAP0(ULONG, AddRef)
DEVICE_H_WRAP0(ULONG, Release)
DEVICE_WRAP0(HRESULT, TestCooperativeLevel)
DEVICE_WRAP0(UINT, GetAvailableTextureMem)
DEVICE_WRAP0(HRESULT, EvictManagedResources)
DEVICE_WRAP1(HRESULT, GetDeviceCaps, D3DCAPS9 *)
DEVICE_WRAP2(HRESULT, GetDisplayMode, UINT, D3DDISPLAYMODE*)
DEVICE_WRAP1(HRESULT, GetCreationParameters, D3DDEVICE_CREATION_PARAMETERS *)
DEVICE_WRAP3(HRESULT, SetCursorProperties, UINT, UINT, IDirect3DSurface9 *)
DEVICE_WRAP3(void, SetCursorPosition, int, int, DWORD)
DEVICE_WRAP1(BOOL, ShowCursor, BOOL)
/*DEVICE_H_WRAP2(HRESULT, CreateAdditionalSwapChain, D3DPRESENT_PARAMETERS *, IDirect3DSwapChain9 **)*/
/*DEVICE_H_WRAP2(HRESULT, GetSwapChain, UINT, IDirect3DSwapChain9 **)*/
DEVICE_WRAP0(UINT, GetNumberOfSwapChains)
DEVICE_H_WRAP1(HRESULT, Reset, D3DPRESENT_PARAMETERS *)
DEVICE_H_WRAP4(HRESULT, Present, const RECT *, const RECT *, HWND, const RGNDATA *)
DEVICE_WRAP2(HRESULT, GetRasterStatus, UINT, D3DRASTER_STATUS *)
DEVICE_WRAP1(HRESULT, SetDialogBoxMode, BOOL)
DEVICE_H_WRAP3(void, SetGammaRamp, UINT, DWORD, const D3DGAMMARAMP *)
DEVICE_WRAP2(void, GetGammaRamp, UINT, D3DGAMMARAMP *)
DEVICE_WRAP4(HRESULT, UpdateSurface, IDirect3DSurface9 *, const RECT *, IDirect3DSurface9 *, const POINT *)
DEVICE_WRAP2(HRESULT, UpdateTexture, IDirect3DBaseTexture9 *, IDirect3DBaseTexture9 *)
DEVICE_WRAP2(HRESULT, GetRenderTargetData, IDirect3DSurface9 *, IDirect3DSurface9 *)
DEVICE_WRAP2(HRESULT, GetFrontBufferData, UINT, IDirect3DSurface9 *)
DEVICE_WRAP5(HRESULT, StretchRect, IDirect3DSurface9 *, const RECT *, IDirect3DSurface9 *, const RECT *, D3DTEXTUREFILTERTYPE)
DEVICE_WRAP3(HRESULT, ColorFill, IDirect3DSurface9 *, const RECT *, D3DCOLOR)
DEVICE_WRAP2(HRESULT, SetRenderTarget, DWORD, IDirect3DSurface9 *)
DEVICE_WRAP2(HRESULT, GetRenderTarget, DWORD, IDirect3DSurface9 **)
DEVICE_WRAP1(HRESULT, GetDepthStencilSurface, IDirect3DSurface9 **)
DEVICE_WRAP1(HRESULT, SetDepthStencilSurface, IDirect3DSurface9 *)
DEVICE_WRAP0(HRESULT, BeginScene)
DEVICE_H_WRAP0(HRESULT, EndScene)
DEVICE_WRAP6(HRESULT, Clear, DWORD, const D3DRECT *, DWORD, D3DCOLOR, float, DWORD)
DEVICE_WRAP2(HRESULT, SetTransform, D3DTRANSFORMSTATETYPE, const D3DMATRIX *)
DEVICE_WRAP2(HRESULT, GetTransform, D3DTRANSFORMSTATETYPE, D3DMATRIX *)
DEVICE_WRAP2(HRESULT, MultiplyTransform, D3DTRANSFORMSTATETYPE, const D3DMATRIX *)
DEVICE_WRAP1(HRESULT, SetViewport, const D3DVIEWPORT9 *)
DEVICE_WRAP1(HRESULT, GetViewport, D3DVIEWPORT9 *)
DEVICE_WRAP1(HRESULT, SetMaterial, const D3DMATERIAL9 *)
DEVICE_WRAP1(HRESULT, GetMaterial, D3DMATERIAL9 *)
DEVICE_WRAP2(HRESULT, SetLight, DWORD, const D3DLIGHT9 *)
DEVICE_WRAP2(HRESULT, GetLight, DWORD, D3DLIGHT9 *)
DEVICE_WRAP2(HRESULT, LightEnable, DWORD, BOOL)
DEVICE_WRAP2(HRESULT, GetLightEnable, DWORD, BOOL *)
DEVICE_WRAP2(HRESULT, SetClipPlane, DWORD, const float *)
DEVICE_WRAP2(HRESULT, GetClipPlane, DWORD, float *)
DEVICE_H_WRAP2(HRESULT, SetRenderState, D3DRENDERSTATETYPE, DWORD)
DEVICE_WRAP2(HRESULT, GetRenderState, D3DRENDERSTATETYPE, DWORD *)
DEVICE_WRAP2(HRESULT, CreateStateBlock, D3DSTATEBLOCKTYPE, IDirect3DStateBlock9 **)
DEVICE_WRAP0(HRESULT, BeginStateBlock)
DEVICE_WRAP1(HRESULT, EndStateBlock, IDirect3DStateBlock9 **)
DEVICE_WRAP1(HRESULT, SetClipStatus, const D3DCLIPSTATUS9 *)
DEVICE_WRAP1(HRESULT, GetClipStatus, D3DCLIPSTATUS9 *)
DEVICE_WRAP2(HRESULT, GetTexture, DWORD, IDirect3DBaseTexture9 **)
DEVICE_WRAP2(HRESULT, SetTexture, DWORD, IDirect3DBaseTexture9 *)
DEVICE_WRAP3(HRESULT, GetTextureStageState, DWORD, D3DTEXTURESTAGESTATETYPE, DWORD *)
DEVICE_WRAP3(HRESULT, SetTextureStageState, DWORD, D3DTEXTURESTAGESTATETYPE, DWORD)
DEVICE_WRAP3(HRESULT, GetSamplerState, DWORD, D3DSAMPLERSTATETYPE, DWORD *)
DEVICE_H_WRAP3(HRESULT, SetSamplerState, DWORD, D3DSAMPLERSTATETYPE, DWORD)
DEVICE_WRAP1(HRESULT, ValidateDevice, DWORD *)
DEVICE_WRAP2(HRESULT, SetPaletteEntries, UINT, const PALETTEENTRY *)
DEVICE_WRAP2(HRESULT, GetPaletteEntries, UINT, PALETTEENTRY *)
DEVICE_WRAP1(HRESULT, SetCurrentTexturePalette, UINT)
DEVICE_WRAP1(HRESULT, GetCurrentTexturePalette, UINT *)
DEVICE_WRAP1(HRESULT, SetScissorRect, const RECT *)
DEVICE_WRAP1(HRESULT, GetScissorRect, RECT *)
DEVICE_WRAP1(HRESULT, SetSoftwareVertexProcessing, BOOL)
DEVICE_WRAP0(BOOL, GetSoftwareVertexProcessing)
DEVICE_WRAP1(HRESULT, SetNPatchMode, float)
DEVICE_WRAP0(float, GetNPatchMode)
DEVICE_WRAP3(HRESULT, DrawPrimitive, D3DPRIMITIVETYPE, UINT, UINT)
DEVICE_WRAP6(HRESULT, DrawIndexedPrimitive, D3DPRIMITIVETYPE, INT, UINT, UINT, UINT, UINT)
DEVICE_WRAP4(HRESULT, DrawPrimitiveUP, D3DPRIMITIVETYPE, UINT, const void *, UINT)
DEVICE_WRAP8(HRESULT, DrawIndexedPrimitiveUP, D3DPRIMITIVETYPE, UINT, UINT, UINT, const void *, D3DFORMAT, const void *, UINT)
DEVICE_WRAP6(HRESULT, ProcessVertices, UINT, UINT, UINT, IDirect3DVertexBuffer9 *, IDirect3DVertexDeclaration9 *, DWORD)
DEVICE_WRAP1(HRESULT, SetVertexDeclaration, IDirect3DVertexDeclaration9 *)
DEVICE_WRAP1(HRESULT, GetVertexDeclaration, IDirect3DVertexDeclaration9 **)
DEVICE_WRAP1(HRESULT, SetFVF, DWORD)
DEVICE_WRAP1(HRESULT, GetFVF, DWORD *)
DEVICE_WRAP1(HRESULT, SetVertexShader, IDirect3DVertexShader9 *)
DEVICE_WRAP1(HRESULT, GetVertexShader, IDirect3DVertexShader9 **)
DEVICE_WRAP3(HRESULT, SetVertexShaderConstantF, UINT, const float *, UINT)
DEVICE_WRAP3(HRESULT, GetVertexShaderConstantF, UINT, float *, UINT)
DEVICE_WRAP3(HRESULT, SetVertexShaderConstantI, UINT, const int *, UINT)
DEVICE_WRAP3(HRESULT, GetVertexShaderConstantI, UINT, int *, UINT)
DEVICE_WRAP3(HRESULT, SetVertexShaderConstantB, UINT, const BOOL *, UINT)
DEVICE_WRAP3(HRESULT, GetVertexShaderConstantB, UINT, BOOL *, UINT)
DEVICE_WRAP4(HRESULT, SetStreamSource, UINT, IDirect3DVertexBuffer9 *, UINT, UINT)
DEVICE_WRAP4(HRESULT, GetStreamSource, UINT, IDirect3DVertexBuffer9 **, UINT *, UINT *)
DEVICE_WRAP2(HRESULT, SetStreamSourceFreq, UINT, UINT)
DEVICE_WRAP2(HRESULT, GetStreamSourceFreq, UINT, UINT *)
DEVICE_WRAP1(HRESULT, SetIndices, IDirect3DIndexBuffer9 *)
DEVICE_WRAP2(HRESULT, GetIndices, IDirect3DIndexBuffer9 **, UINT*) //this should only have 1 param?
DEVICE_WRAP1(HRESULT, SetPixelShader, IDirect3DPixelShader9 *)
DEVICE_WRAP1(HRESULT, GetPixelShader, IDirect3DPixelShader9 **)
DEVICE_WRAP3(HRESULT, SetPixelShaderConstantF, UINT, const float *, UINT)
DEVICE_WRAP3(HRESULT, GetPixelShaderConstantF, UINT, float *, UINT)
DEVICE_WRAP3(HRESULT, SetPixelShaderConstantI, UINT, const int *, UINT)
DEVICE_WRAP3(HRESULT, GetPixelShaderConstantI, UINT, int *, UINT)
DEVICE_WRAP3(HRESULT, SetPixelShaderConstantB, UINT, const BOOL *, UINT)
DEVICE_WRAP3(HRESULT, GetPixelShaderConstantB, UINT, BOOL *, UINT)
DEVICE_WRAP3(HRESULT, DrawRectPatch, UINT, const float *, const D3DRECTPATCH_INFO *)
DEVICE_WRAP3(HRESULT, DrawTriPatch, UINT, const float *, const D3DTRIPATCH_INFO *)
DEVICE_WRAP1(HRESULT, DeletePatch, UINT)
DEVICE_WRAP4(HRESULT, SetConvolutionMonoKernel, UINT, UINT, float *, float *)
DEVICE_WRAP8(HRESULT, ComposeRects, IDirect3DSurface9 *, IDirect3DSurface9 *, IDirect3DVertexBuffer9 *, UINT, IDirect3DVertexBuffer9 *, D3DCOMPOSERECTSOP, int, int)
DEVICE_H_WRAP5(HRESULT, PresentEx, const RECT *, const RECT *, HWND, const RGNDATA *, DWORD)
DEVICE_WRAP1(HRESULT, GetGPUThreadPriority, INT *)
DEVICE_WRAP1(HRESULT, SetGPUThreadPriority, INT)
DEVICE_WRAP1(HRESULT, WaitForVBlank, UINT)
DEVICE_WRAP2(HRESULT, CheckResourceResidency, IDirect3DResource9 **, UINT32)
DEVICE_WRAP1(HRESULT, SetMaximumFrameLatency, UINT)
DEVICE_WRAP1(HRESULT, GetMaximumFrameLatency, UINT *)
DEVICE_WRAP1(HRESULT, CheckDeviceState, HWND)
DEVICE_H_WRAP2(HRESULT, ResetEx, D3DPRESENT_PARAMETERS *, D3DDISPLAYMODEEX *)
DEVICE_WRAP3(HRESULT, GetDisplayModeEx, UINT, D3DDISPLAYMODEEX *, D3DDISPLAYROTATION *)

IDirect3DSwapChain9ExVtbl NineSwapChain9Ex_vtable = {
    NineSwapChain9_QueryInterface,
    NineSwapChain9_AddRef,
    NineSwapChain9_Release,
    NineSwapChain9_Present,
    NineSwapChain9_GetFrontBufferData,
    NineSwapChain9_GetBackBuffer,
    NineSwapChain9_GetRasterStatus,
    NineSwapChain9_GetDisplayMode,
    NineSwapChain9_GetDevice,
    NineSwapChain9_GetPresentParameters,
    NineSwapChain9_GetLastPresentCount,
    NineSwapChain9_GetPresentStats,
    NineSwapChain9_GetDisplayModeEx
};

HRESULT ALT_WINAPI ALT_DECLSPEC_HOTPATCH NineDevice9_CreateAdditionalSwapChain(IDirect3DDevice9Ex *This, D3DPRESENT_PARAMETERS *pPresentationParameters, IDirect3DSwapChain9 **pSwapChain)
{
    HRESULT hr;

    hr = ((IDirect3DDevice9Ex_Minor1 *)This)->lpVtbl_internal->CreateAdditionalSwapChain(This, pPresentationParameters, pSwapChain);
    if (FAILED(hr))
        return hr;

    (*pSwapChain)->lpVtbl = (IDirect3DSwapChain9Vtbl *)&NineSwapChain9Ex_vtable;

    return hr;
}

HRESULT ALT_WINAPI ALT_DECLSPEC_HOTPATCH NineDevice9_GetSwapChain(IDirect3DDevice9Ex *This, UINT iSwapChain, IDirect3DSwapChain9 **pSwapChain)
{
    HRESULT hr;

    hr = ((IDirect3DDevice9Ex_Minor1 *)This)->lpVtbl_internal->GetSwapChain(This, iSwapChain, pSwapChain);
    if (FAILED(hr))
        return hr;

    (*pSwapChain)->lpVtbl = (IDirect3DSwapChain9Vtbl *)&NineSwapChain9Ex_vtable;

    return hr;
}



#define VDECL_WRAP2(ret, func, type1, type2)  \
    ret ALT_WINAPI NineVertexDeclaration9_ ## func(IDirect3DVertexDeclaration9 *This, type1 arg1, type2 arg2) \
    { \
        return ((IDirect3DVertexDeclaration9_Minor1 *)This)->lpVtbl_internal->func(This, arg1, arg2); \
    }


VDECL_WRAP2(HRESULT, GetDeclaration, D3DVERTEXELEMENT9 *, UINT *)

static IDirect3DVertexDeclaration9Vtbl NineVertexDeclaration9_vtable = {
    (void *)Nine_QueryInterface,
    (void *)Nine_AddRef,
    (void *)Nine_Release,
    (void *)Nine_GetDevice,
    (void *)NineVertexDeclaration9_GetDeclaration
};

static HRESULT ALT_WINAPI ALT_DECLSPEC_HOTPATCH NineDevice9_CreateVertexDeclaration(IDirect3DDevice9Ex *This, const D3DVERTEXELEMENT9 *pVertexElements, IDirect3DVertexDeclaration9 **ppDecl)
{
    HRESULT hr;
printf("WRAPPED NineDevice9_CreateVertexDeclaration");
    hr = ((IDirect3DDevice9Ex_Minor1 *)This)->lpVtbl_internal->CreateVertexDeclaration(This, pVertexElements, ppDecl);
    if (FAILED(hr))
        return hr;

    (*ppDecl)->lpVtbl = (IDirect3DVertexDeclaration9Vtbl *)&NineVertexDeclaration9_vtable;

    return hr;
}


struct IDirect3DTexture9_Minor1
{
        IDirect3DTexture9Vtbl *lpVtbl;
        IDirect3DTexture9Vtbl *lpVtbl_internal;
};
typedef struct IDirect3DTexture9_Minor1 IDirect3DTexture9_Minor1;
#define TEX_WRAP0(ret, func)  \
    ret ALT_WINAPI NineTexture9_ ## func(void *This) \
    { \
        return ((IDirect3DTexture9_Minor1 *)This)->lpVtbl_internal->func(This); \
    }

#define TEX_WRAP1(ret, func, type1)  \
    ret ALT_WINAPI NineTexture9_ ## func(void *This, type1 arg1) \
    { \
        return ((IDirect3DTexture9_Minor1 *)This)->lpVtbl_internal->func(This, arg1); \
    }

#define TEX_WRAP2(ret, func, type1, type2)  \
    ret ALT_WINAPI NineTexture9_ ## func(void *This, type1 arg1, type2 arg2) \
    { \
        return ((IDirect3DTexture9_Minor1 *)This)->lpVtbl_internal->func(This, arg1, arg2); \
    }

#define TEX_WRAP4(ret, func, type1, type2, type3, type4)  \
    ret ALT_WINAPI NineTexture9_ ## func(void *This, type1 arg1, type2 arg2, type3 arg3, type4 arg4) \
    { \
        return ((IDirect3DTexture9_Minor1 *)This)->lpVtbl_internal->func(This, arg1, arg2, arg3, arg4); \
    }

TEX_WRAP1(DWORD, SetLOD, DWORD)
TEX_WRAP0(DWORD, GetLOD)
TEX_WRAP0(DWORD, GetLevelCount)
TEX_WRAP1(HRESULT, SetAutoGenFilterType, D3DTEXTUREFILTERTYPE)
TEX_WRAP0(D3DTEXTUREFILTERTYPE, GetAutoGenFilterType)
TEX_WRAP0(void, GenerateMipSubLevels)
TEX_WRAP2(HRESULT, GetLevelDesc, UINT, D3DSURFACE_DESC*)
TEX_WRAP4(HRESULT, LockRect, UINT, D3DLOCKED_RECT *, const RECT *, DWORD)
TEX_WRAP1(HRESULT, UnlockRect, UINT)
TEX_WRAP1(HRESULT, AddDirtyRect, const RECT *)

static HRESULT ALT_WINAPI ALT_DECLSPEC_HOTPATCH 
NineTexture9_GetSurfaceLevel(IDirect3DTexture9 *This, UINT Level, IDirect3DSurface9 **ppSurfaceLevel)
{    HRESULT hr;

    hr = ((IDirect3DTexture9_Minor1 *)This)->lpVtbl_internal->GetSurfaceLevel(This, Level, ppSurfaceLevel);
    if (FAILED(hr))
        return hr;

    (*ppSurfaceLevel)->lpVtbl = (IDirect3DSurface9Vtbl *)&NineSurface9_vtable;

    return hr;
}

static IDirect3DTexture9Vtbl NineTexture9_vtable = {
    (void *)Nine_QueryInterface,
    (void *)Nine_AddRef,
    (void *)Nine_Release,
    (void *)Nine_GetDevice,
    (void *)Nine_SetPrivateData,
    (void *)Nine_GetPrivateData,
    (void *)Nine_FreePrivateData,
    (void *)Nine_SetPriority,
    (void *)Nine_GetPriority,
    (void *)Nine_PreLoad,
    (void *)Nine_GetType,
    (void *)NineTexture9_SetLOD,
    (void *)NineTexture9_GetLOD,
    (void *)NineTexture9_GetLevelCount,
    (void *)NineTexture9_SetAutoGenFilterType,
    (void *)NineTexture9_GetAutoGenFilterType,
    (void *)NineTexture9_GenerateMipSubLevels,
    (void *)NineTexture9_GetLevelDesc, /* immutable */
    (void *)NineTexture9_GetSurfaceLevel, /* AddRef */
    (void *)NineTexture9_LockRect,
    (void *)NineTexture9_UnlockRect,
    (void *)NineTexture9_AddDirtyRect
};

static HRESULT ALT_WINAPI ALT_DECLSPEC_HOTPATCH 
NineDevice9_CreateTexture( IDirect3DDevice9Ex *This,
                           UINT Width,
                           UINT Height,
                           UINT Levels,
                           DWORD Usage,
                           D3DFORMAT Format,
                           D3DPOOL Pool,
                           IDirect3DTexture9 **ppTexture,
                           HANDLE *pSharedHandle )
{
    HRESULT hr;

    hr = ((IDirect3DDevice9Ex_Minor1 *)This)->lpVtbl_internal->CreateTexture(This, Width, Height, Levels, Usage, Format, Pool, ppTexture, pSharedHandle);
    if (FAILED(hr))
        return hr;

    (*ppTexture)->lpVtbl = (IDirect3DTexture9Vtbl *)&NineTexture9_vtable;

    return hr;
}


struct IDirect3DQuery9_Minor1
{
        IDirect3DQuery9Vtbl *lpVtbl;
        IDirect3DQuery9Vtbl *lpVtbl_internal;
};
typedef struct IDirect3DQuery9_Minor1 IDirect3DQuery9_Minor1;
#define QUERY_WRAP0(ret, func)  \
    ret ALT_WINAPI NineQuery9_ ## func(void *This) \
    { \
        return ((IDirect3DQuery9_Minor1 *)This)->lpVtbl_internal->func(This); \
    }

#define QUERY_WRAP1(ret, func, type1)  \
    ret ALT_WINAPI NineQuery9_ ## func(void *This, type1 arg1) \
    { \
        return ((IDirect3DQuery9_Minor1 *)This)->lpVtbl_internal->func(This, arg1); \
    }

#define QUERY_WRAP3(ret, func, type1, type2, type3)  \
    ret ALT_WINAPI NineQuery9_ ## func(void *This, type1 arg1, type2 arg2, type3 arg3) \
    { \
        return ((IDirect3DQuery9_Minor1 *)This)->lpVtbl_internal->func(This, arg1, arg2, arg3); \
    }

QUERY_WRAP0(D3DRESOURCETYPE, GetType)
QUERY_WRAP0(DWORD, GetDataSize)
QUERY_WRAP1(HRESULT, Issue, DWORD)
QUERY_WRAP3(HRESULT, GetData, void *, DWORD, DWORD)
static IDirect3DQuery9Vtbl NineQuery9_vtable = {
    (void *)Nine_QueryInterface,
    (void *)Nine_AddRef,
    (void *)Nine_Release,
    (void *)Nine_GetDevice, /* actually part of Query9 iface */
    (void *)NineQuery9_GetType, /* immutable */
    (void *)NineQuery9_GetDataSize, /* immutable */
    (void *)NineQuery9_Issue,
    (void *)NineQuery9_GetData
};
static HRESULT ALT_WINAPI
NineDevice9_CreateQuery(IDirect3DDevice9Ex *This, D3DQUERYTYPE Type, IDirect3DQuery9 **ppQuery)
{
    HRESULT hr;

    hr = ((IDirect3DDevice9Ex_Minor1 *)This)->lpVtbl_internal->CreateQuery(This, Type, ppQuery);
    if (FAILED(hr))
        return hr;

    (*ppQuery)->lpVtbl = (IDirect3DQuery9Vtbl *)&NineQuery9_vtable;

    return hr;
}

struct IDirect3DPixelShader9_Minor1
{
        IDirect3DPixelShader9Vtbl *lpVtbl;
        IDirect3DPixelShader9Vtbl *lpVtbl_internal;
};
typedef struct IDirect3DPixelShader9_Minor1 IDirect3DPixelShader9_Minor1;
#define PS_WRAP2(ret, func, type1, type2)  \
    ret ALT_WINAPI NinePixelShader9_ ## func(void *This, type1 arg1, type2 arg2) \
    { \
        return ((IDirect3DPixelShader9_Minor1 *)This)->lpVtbl_internal->func(This, arg1, arg2); \
    }

PS_WRAP2(HRESULT, GetFunction, void *, UINT*)
static IDirect3DPixelShader9Vtbl NinePixelShader9_vtable = {
    (void *)Nine_QueryInterface,
    (void *)Nine_AddRef,
    (void *)Nine_Release,
    (void *)Nine_GetDevice, /* actually part of PixelShader9 iface */
    (void *)NinePixelShader9_GetFunction
};
static HRESULT ALT_WINAPI
NineDevice9_CreatePixelShader(IDirect3DDevice9Ex *This, const DWORD *pFunction, IDirect3DPixelShader9 **ppShader)
{
    HRESULT hr;

    hr = ((IDirect3DDevice9Ex_Minor1 *)This)->lpVtbl_internal->CreatePixelShader(This, pFunction, ppShader);
    if (FAILED(hr))
        return hr;

    (*ppShader)->lpVtbl = (IDirect3DPixelShader9Vtbl *)&NinePixelShader9_vtable;

    return hr;
}

struct IDirect3DVertexShader9_Minor1
{
        IDirect3DVertexShader9Vtbl *lpVtbl;
        IDirect3DVertexShader9Vtbl *lpVtbl_internal;
};
typedef struct IDirect3DVertexShader9_Minor1 IDirect3DVertexShader9_Minor1;
#define VS_WRAP2(ret, func, type1, type2)  \
    ret ALT_WINAPI NineVertexShader9_ ## func(void *This, type1 arg1, type2 arg2) \
    { \
        return ((IDirect3DVertexShader9_Minor1 *)This)->lpVtbl_internal->func(This, arg1, arg2); \
    }

VS_WRAP2(HRESULT, GetFunction, void *, UINT*)
static IDirect3DVertexShader9Vtbl NineVertexShader9_vtable = {
    (void *)Nine_QueryInterface,
    (void *)Nine_AddRef,
    (void *)Nine_Release,
    (void *)Nine_GetDevice, /* actually part of VertexShader9 iface */
    (void *)NineVertexShader9_GetFunction
};
static HRESULT ALT_WINAPI
NineDevice9_CreateVertexShader(IDirect3DDevice9Ex *This, const DWORD *pFunction, IDirect3DVertexShader9 **ppShader)
{
    HRESULT hr;

    hr = ((IDirect3DDevice9Ex_Minor1 *)This)->lpVtbl_internal->CreateVertexShader(This, pFunction, ppShader);
    if (FAILED(hr))
        return hr;

    (*ppShader)->lpVtbl = (IDirect3DVertexShader9Vtbl *)&NineVertexShader9_vtable;

    return hr;
}

struct IDirect3DVolumeTexture9_Minor1
{
        IDirect3DVolumeTexture9Vtbl *lpVtbl;
        IDirect3DVolumeTexture9Vtbl *lpVtbl_internal;
};
typedef struct IDirect3DVolumeTexture9_Minor1 IDirect3DVolumeTexture9_Minor1;
#define TEX3D_WRAP2(ret, func, type1, type2)  \
    ret ALT_WINAPI NineVolumeTexture9_ ## func(void *This, type1 arg1, type2 arg2) \
    { \
        return ((IDirect3DVolumeTexture9_Minor1 *)This)->lpVtbl_internal->func(This, arg1, arg2); \
    }

#define TEX3D_WRAP1(ret, func, type1)  \
    ret ALT_WINAPI NineVolumeTexture9_ ## func(void *This, type1 arg1) \
    { \
        return ((IDirect3DVolumeTexture9_Minor1 *)This)->lpVtbl_internal->func(This, arg1); \
    }

#define TEX3D_WRAP4(ret, func, type1, type2, type3, type4)  \
    ret ALT_WINAPI NineVolumeTexture9_ ## func(void *This, type1 arg1, type2 arg2, type3 arg3, type4 arg4) \
    { \
        return ((IDirect3DVolumeTexture9_Minor1 *)This)->lpVtbl_internal->func(This, arg1, arg2, arg3, arg4); \
    }

TEX3D_WRAP2(HRESULT, GetVolumeLevel, UINT, IDirect3DVolume9 **)
TEX3D_WRAP4(HRESULT, LockBox, UINT, D3DLOCKED_BOX *, const D3DBOX *, DWORD)
TEX3D_WRAP1(HRESULT, UnlockBox, UINT)
TEX3D_WRAP1(HRESULT, AddDirtyBox, const D3DBOX *)

IDirect3DVolumeTexture9Vtbl NineVolumeTexture9_vtable = {
    (void *)Nine_QueryInterface,
    (void *)Nine_AddRef,
    (void *)Nine_Release,
    (void *)Nine_GetDevice,
    (void *)Nine_SetPrivateData,
    (void *)Nine_GetPrivateData,
    (void *)Nine_FreePrivateData,
    (void *)Nine_SetPriority,
    (void *)Nine_GetPriority,
    (void *)Nine_PreLoad,
    (void *)Nine_GetType,
    (void *)NineTexture9_SetLOD,
    (void *)NineTexture9_GetLOD,
    (void *)NineTexture9_GetLevelCount,
    (void *)NineTexture9_SetAutoGenFilterType,
    (void *)NineTexture9_GetAutoGenFilterType,
    (void *)NineTexture9_GenerateMipSubLevels,
    (void *)NineTexture9_GetLevelDesc, /* immutable */
    (void *)NineVolumeTexture9_GetVolumeLevel, /* AddRef */
    (void *)NineVolumeTexture9_LockBox,
    (void *)NineVolumeTexture9_UnlockBox,
    (void *)NineVolumeTexture9_AddDirtyBox
};
static HRESULT ALT_WINAPI
NineDevice9_CreateVolumeTexture(IDirect3DDevice9Ex *This, UINT Width, UINT Height, UINT Depth, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DVolumeTexture9 **ppVolumeTexture, HANDLE *pSharedHandle)
{
    HRESULT hr;

    hr = ((IDirect3DDevice9Ex_Minor1 *)This)->lpVtbl_internal->CreateVolumeTexture(This, Width, Height, Depth, Levels, Usage, Format, Pool, ppVolumeTexture, pSharedHandle);
    if (FAILED(hr))
        return hr;

    (*ppVolumeTexture)->lpVtbl = (IDirect3DVolumeTexture9Vtbl *)&NineVolumeTexture9_vtable;

    return hr;
}

struct IDirect3DCubeTexture9_Minor1
{
        IDirect3DCubeTexture9Vtbl *lpVtbl;
        IDirect3DCubeTexture9Vtbl *lpVtbl_internal;
};
typedef struct IDirect3DCubeTexture9_Minor1 IDirect3DCubeTexture9_Minor1;
#define CUBE_WRAP2(ret, func, type1, type2)  \
    ret ALT_WINAPI NineCubeTexture9_ ## func(void *This, type1 arg1, type2 arg2) \
    { \
        return ((IDirect3DCubeTexture9_Minor1 *)This)->lpVtbl_internal->func(This, arg1, arg2); \
    }
#define CUBE_WRAP3(ret, func, type1, type2, type3)  \
    ret ALT_WINAPI NineCubeTexture9_ ## func(void *This, type1 arg1, type2 arg2, type3 arg3) \
    { \
        return ((IDirect3DCubeTexture9_Minor1 *)This)->lpVtbl_internal->func(This, arg1, arg2, arg3); \
    }
typedef struct IDirect3DCubeTexture9_Minor1 IDirect3DCubeTexture9_Minor1;
#define CUBE_WRAP5(ret, func, type1, type2, type3, type4, type5)  \
    ret ALT_WINAPI NineCubeTexture9_ ## func(void *This, type1 arg1, type2 arg2, type3 arg3, type4 arg4, type5 arg5) \
    { \
        return ((IDirect3DCubeTexture9_Minor1 *)This)->lpVtbl_internal->func(This, arg1, arg2, arg3, arg4, arg5); \
    }
CUBE_WRAP2(HRESULT, GetLevelDesc, UINT, D3DSURFACE_DESC*)
CUBE_WRAP3(HRESULT, GetCubeMapSurface, D3DCUBEMAP_FACES, UINT, IDirect3DSurface9 **)
CUBE_WRAP5(HRESULT, LockRect, D3DCUBEMAP_FACES, UINT, D3DLOCKED_RECT *, const RECT *, DWORD)
CUBE_WRAP2(HRESULT, UnlockRect, D3DCUBEMAP_FACES, UINT)
CUBE_WRAP2(HRESULT, AddDirtyRect, D3DCUBEMAP_FACES, const RECT *)

static IDirect3DCubeTexture9Vtbl NineCubeTexture9_vtable = {
    (void *)Nine_QueryInterface,
    (void *)Nine_AddRef,
    (void *)Nine_Release,
    (void *)Nine_GetDevice,
    (void *)Nine_SetPrivateData,
    (void *)Nine_GetPrivateData,
    (void *)Nine_FreePrivateData,
    (void *)Nine_SetPriority,
    (void *)Nine_GetPriority,
    (void *)Nine_PreLoad,
    (void *)Nine_GetType,
    (void *)NineTexture9_SetLOD,
    (void *)NineTexture9_GetLOD,
    (void *)NineTexture9_GetLevelCount,
    (void *)NineTexture9_SetAutoGenFilterType,
    (void *)NineTexture9_GetAutoGenFilterType,
    (void *)NineTexture9_GenerateMipSubLevels,
    (void *)NineCubeTexture9_GetLevelDesc, /* immutable */
    (void *)NineCubeTexture9_GetCubeMapSurface, /* AddRef */
    (void *)NineCubeTexture9_LockRect,
    (void *)NineCubeTexture9_UnlockRect,
    (void *)NineCubeTexture9_AddDirtyRect
};

static HRESULT ALT_WINAPI ALT_DECLSPEC_HOTPATCH 
NineDevice9_CreateCubeTexture(IDirect3DDevice9Ex *This, UINT EdgeLength, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DCubeTexture9 **ppCubeTexture, HANDLE *pSharedHandle)
{
    HRESULT hr;

    hr = ((IDirect3DDevice9Ex_Minor1 *)This)->lpVtbl_internal->CreateCubeTexture(This, EdgeLength, Levels, Usage, Format, Pool, ppCubeTexture, pSharedHandle);
    if (FAILED(hr))
        return hr;

    (*ppCubeTexture)->lpVtbl = (IDirect3DCubeTexture9Vtbl *)&NineCubeTexture9_vtable;

    return hr;
}

struct IDirect3DIndexBuffer9_Minor1
{
        IDirect3DIndexBuffer9Vtbl *lpVtbl;
        IDirect3DIndexBuffer9Vtbl *lpVtbl_internal;
};
typedef struct IDirect3DIndexBuffer9_Minor1 IDirect3DIndexBuffer9_Minor1;
#define IB_WRAP0(ret, func)  \
    ret ALT_WINAPI NineIndexBuffer9_ ## func(void *This) \
    { \
        return ((IDirect3DIndexBuffer9_Minor1 *)This)->lpVtbl_internal->func(This); \
    }

#define IB_WRAP1(ret, func, type1)  \
    ret ALT_WINAPI NineIndexBuffer9_ ## func(void *This, type1 arg1) \
    { \
        return ((IDirect3DIndexBuffer9_Minor1 *)This)->lpVtbl_internal->func(This, arg1); \
    }

#define IB_WRAP4(ret, func, type1, type2, type3, type4)  \
    ret ALT_WINAPI NineIndexBuffer9_ ## func(void *This, type1 arg1, type2 arg2, type3 arg3, type4 arg4) \
    { \
        return ((IDirect3DIndexBuffer9_Minor1 *)This)->lpVtbl_internal->func(This, arg1, arg2, arg3, arg4); \
    }
IB_WRAP4(HRESULT, Lock, UINT, UINT, void **, DWORD)
IB_WRAP0(HRESULT, Unlock)
IB_WRAP1(HRESULT, GetDesc, D3DINDEXBUFFER_DESC *)

IDirect3DIndexBuffer9Vtbl NineIndexBuffer9_vtable = {
    (void *)Nine_QueryInterface,
    (void *)Nine_AddRef,
    (void *)Nine_Release,
    (void *)Nine_GetDevice, /* actually part of  iface */
    (void *)Nine_SetPrivateData,
    (void *)Nine_GetPrivateData,
    (void *)Nine_FreePrivateData,
    (void *)Nine_SetPriority,
    (void *)Nine_GetPriority,
    (void *)Nine_PreLoad, /* nop */
    (void *)Nine_GetType, /* immutable */
    (void *)NineIndexBuffer9_Lock,
    (void *)NineIndexBuffer9_Unlock,
    (void *)NineIndexBuffer9_GetDesc /* immutable */
};

static HRESULT ALT_WINAPI
NineDevice9_CreateIndexBuffer(IDirect3DDevice9Ex *This, UINT Length, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DIndexBuffer9 **ppIndexBuffer, HANDLE *pSharedHandle)
{
    HRESULT hr;

    hr = ((IDirect3DDevice9Ex_Minor1 *)This)->lpVtbl_internal->CreateIndexBuffer(This, Length, Usage, Format, Pool, ppIndexBuffer, pSharedHandle);
    if (FAILED(hr))
        return hr;

    (*ppIndexBuffer)->lpVtbl = (IDirect3DIndexBuffer9Vtbl *)&NineIndexBuffer9_vtable;

    return hr;
}

static HRESULT ALT_WINAPI
NineDevice9_CreateVertexBuffer(IDirect3DDevice9Ex *This, UINT Length, DWORD Usage, DWORD FVF, D3DPOOL Pool, IDirect3DVertexBuffer9 **ppVertexBuffer, HANDLE *pSharedHandle)
{
    HRESULT hr;

    hr = ((IDirect3DDevice9Ex_Minor1 *)This)->lpVtbl_internal->CreateVertexBuffer(This, Length, Usage, FVF, Pool, ppVertexBuffer, pSharedHandle);
    if (FAILED(hr))
        return hr;

    (*ppVertexBuffer)->lpVtbl = (IDirect3DVertexBuffer9Vtbl *)&NineIndexBuffer9_vtable;

    return hr;
}

static IDirect3DDevice9ExVtbl NineDevice9_vtable = {
    NineDevice9_QueryInterface,
    NineDevice9_AddRef,
    NineDevice9_Release,
    NineDevice9_TestCooperativeLevel,
    NineDevice9_GetAvailableTextureMem,
    NineDevice9_EvictManagedResources,
    NineDevice9_GetDirect3D,
    NineDevice9_GetDeviceCaps,
    NineDevice9_GetDisplayMode,
    NineDevice9_GetCreationParameters,
    NineDevice9_SetCursorProperties,
    NineDevice9_SetCursorPosition,
    NineDevice9_ShowCursor,
    NineDevice9_CreateAdditionalSwapChain,
    NineDevice9_GetSwapChain,
    NineDevice9_GetNumberOfSwapChains,
    NineDevice9_Reset,
    NineDevice9_Present,
    NineDevice9_GetBackBuffer,
    NineDevice9_GetRasterStatus,
    NineDevice9_SetDialogBoxMode,
    NineDevice9_SetGammaRamp,
    NineDevice9_GetGammaRamp,
    NineDevice9_CreateTexture,
    NineDevice9_CreateVolumeTexture,
    NineDevice9_CreateCubeTexture,
    NineDevice9_CreateVertexBuffer,
    NineDevice9_CreateIndexBuffer,
    NineDevice9_CreateRenderTarget,
    NineDevice9_CreateDepthStencilSurface,
    NineDevice9_UpdateSurface,
    NineDevice9_UpdateTexture,
    NineDevice9_GetRenderTargetData,
    NineDevice9_GetFrontBufferData,
    NineDevice9_StretchRect,
    NineDevice9_ColorFill,
    NineDevice9_CreateOffscreenPlainSurface,
    NineDevice9_SetRenderTarget,
    NineDevice9_GetRenderTarget,
    NineDevice9_SetDepthStencilSurface,
    NineDevice9_GetDepthStencilSurface,
    NineDevice9_BeginScene,
    NineDevice9_EndScene,
    NineDevice9_Clear,
    NineDevice9_SetTransform,
    NineDevice9_GetTransform,
    NineDevice9_MultiplyTransform,
    NineDevice9_SetViewport,
    NineDevice9_GetViewport,
    NineDevice9_SetMaterial,
    NineDevice9_GetMaterial,
    NineDevice9_SetLight,
    NineDevice9_GetLight,
    NineDevice9_LightEnable,
    NineDevice9_GetLightEnable,
    NineDevice9_SetClipPlane,
    NineDevice9_GetClipPlane,
    NineDevice9_SetRenderState,
    NineDevice9_GetRenderState,
    NineDevice9_CreateStateBlock,
    NineDevice9_BeginStateBlock,
    NineDevice9_EndStateBlock,
    NineDevice9_SetClipStatus,
    NineDevice9_GetClipStatus,
    NineDevice9_GetTexture,
    NineDevice9_SetTexture,
    NineDevice9_GetTextureStageState,
    NineDevice9_SetTextureStageState,
    NineDevice9_GetSamplerState,
    NineDevice9_SetSamplerState,
    NineDevice9_ValidateDevice,
    NineDevice9_SetPaletteEntries,
    NineDevice9_GetPaletteEntries,
    NineDevice9_SetCurrentTexturePalette,
    NineDevice9_GetCurrentTexturePalette,
    NineDevice9_SetScissorRect,
    NineDevice9_GetScissorRect,
    NineDevice9_SetSoftwareVertexProcessing,
    NineDevice9_GetSoftwareVertexProcessing,
    NineDevice9_SetNPatchMode,
    NineDevice9_GetNPatchMode,
    NineDevice9_DrawPrimitive,
    NineDevice9_DrawIndexedPrimitive,
    NineDevice9_DrawPrimitiveUP,
    NineDevice9_DrawIndexedPrimitiveUP,
    NineDevice9_ProcessVertices,
    NineDevice9_CreateVertexDeclaration,
    NineDevice9_SetVertexDeclaration,
    NineDevice9_GetVertexDeclaration,
    NineDevice9_SetFVF,
    NineDevice9_GetFVF,
    NineDevice9_CreateVertexShader,
    NineDevice9_SetVertexShader,
    NineDevice9_GetVertexShader,
    NineDevice9_SetVertexShaderConstantF,
    NineDevice9_GetVertexShaderConstantF,
    NineDevice9_SetVertexShaderConstantI,
    NineDevice9_GetVertexShaderConstantI,
    NineDevice9_SetVertexShaderConstantB,
    NineDevice9_GetVertexShaderConstantB,
    NineDevice9_SetStreamSource,
    NineDevice9_GetStreamSource,
    NineDevice9_SetStreamSourceFreq,
    NineDevice9_GetStreamSourceFreq,
    NineDevice9_SetIndices,
    NineDevice9_GetIndices,
    NineDevice9_CreatePixelShader,
    NineDevice9_SetPixelShader,
    NineDevice9_GetPixelShader,
    NineDevice9_SetPixelShaderConstantF,
    NineDevice9_GetPixelShaderConstantF,
    NineDevice9_SetPixelShaderConstantI,
    NineDevice9_GetPixelShaderConstantI,
    NineDevice9_SetPixelShaderConstantB,
    NineDevice9_GetPixelShaderConstantB,
    NineDevice9_DrawRectPatch,
    NineDevice9_DrawTriPatch,
    NineDevice9_DeletePatch,
    NineDevice9_CreateQuery,
    NineDevice9_SetConvolutionMonoKernel,
    NineDevice9_ComposeRects,
    NineDevice9_PresentEx,
    NineDevice9_GetGPUThreadPriority,
    NineDevice9_SetGPUThreadPriority,
    NineDevice9_WaitForVBlank,
    NineDevice9_CheckResourceResidency,
    NineDevice9_SetMaximumFrameLatency,
    NineDevice9_GetMaximumFrameLatency,
    NineDevice9_CheckDeviceState,
    NineDevice9_CreateRenderTargetEx,
    NineDevice9_CreateOffscreenPlainSurfaceEx,
    NineDevice9_CreateDepthStencilSurfaceEx,
    NineDevice9_ResetEx,
    NineDevice9_GetDisplayModeEx
};

void *get_device_vtable()
{
    printf("WRAPPED DEVICE TABLE\n");
    return &NineDevice9_vtable;
}
