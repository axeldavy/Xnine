
#include "include/D3D9/d3d9.h"
#include "include/D3D9/d3d9caps.h"
#include "include/D3D9/d3d9types.h"

#define ALT_WINAPI

typedef struct IDirect3D9_alt IDirect3D9_alt, *PDIRECT3D9_alt, *LPDIRECT3D9_alt;
typedef struct IDirect3D9Ex_alt IDirect3D9Ex_alt, *PDIRECT3D9EX_alt, *LPDIRECT3D9EX_alt;
typedef struct IDirect3DDevice9_alt IDirect3DDevice9_alt, *PDIRECT3DDEVICE9_alt, *LPDIRECT3DDEVICE9_alt;
typedef struct IDirect3DDevice9Ex_alt IDirect3DDevice9Ex_alt, *PDIRECT3DDEVICE9EX_alt, *LPDIRECT3DDEVICE9EX_alt;
typedef struct IDirect3DVertexBuffer9_alt IDirect3DVertexBuffer9_alt, *PDIRECT3DVERTEXBUFFER9_alt, *LPDIRECT3DVERTEXBUFFER9_alt;
typedef struct IUnknown_alt IUnknown_alt, *PUNKNOWN_alt, *LPUNKNOWN_alt;

// Add these if needed
#define IDirect3DSurface9_alt void
#define IDirect3DTexture9_alt void
#define IDirect3DVolumeTexture9_alt void
#define IDirect3DCubeTexture9_alt void
#define IDirect3DBaseTexture9_alt void
#define IDirect3DIndexBuffer9_alt void
#define IDirect3DSwapChain9_alt void
#define IDirect3DStateBlock9_alt void
#define IDirect3DVertexDeclaration9_alt void
#define IDirect3DVertexShader9_alt void
#define IDirect3DPixelShader9_alt void
#define IDirect3DQuery9_alt void

#ifdef __cplusplus

struct IUnknown_alt
{
	virtual HRESULT ALT_WINAPI QueryInterface(REFIID riid, void **ppvObject) = 0;
	virtual ULONG ALT_WINAPI AddRef() = 0;
	virtual ULONG ALT_WINAPI Release() = 0;
};


struct IDirect3D9_alt : public IUnknown_alt
{
	virtual HRESULT ALT_WINAPI RegisterSoftwareDevice(void *pInitializeFunction) = 0;
	virtual UINT ALT_WINAPI GetAdapterCount() = 0;
	virtual HRESULT ALT_WINAPI GetAdapterIdentifier(UINT Adapter, DWORD Flags, D3DADAPTER_IDENTIFIER9 *pIdentifier) = 0;
	virtual UINT ALT_WINAPI GetAdapterModeCount(UINT Adapter, D3DFORMAT Format) = 0;
	virtual HRESULT ALT_WINAPI EnumAdapterModes(UINT Adapter, D3DFORMAT Format, UINT Mode, D3DDISPLAYMODE *pMode) = 0;
	virtual HRESULT ALT_WINAPI GetAdapterDisplayMode(UINT Adapter, D3DDISPLAYMODE *pMode) = 0;
	virtual HRESULT ALT_WINAPI CheckDeviceType(UINT Adapter, D3DDEVTYPE DevType, D3DFORMAT AdapterFormat, D3DFORMAT BackBufferFormat, BOOL bWindowed) = 0;
	virtual HRESULT ALT_WINAPI CheckDeviceFormat(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT AdapterFormat, DWORD Usage, D3DRESOURCETYPE RType, D3DFORMAT CheckFormat) = 0;
	virtual HRESULT ALT_WINAPI CheckDeviceMultiSampleType(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT SurfaceFormat, BOOL Windowed, D3DMULTISAMPLE_TYPE MultiSampleType, DWORD *pQualityLevels) = 0;
	virtual HRESULT ALT_WINAPI CheckDepthStencilMatch(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT AdapterFormat, D3DFORMAT RenderTargetFormat, D3DFORMAT DepthStencilFormat) = 0;
	virtual HRESULT ALT_WINAPI CheckDeviceFormatConversion(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT SourceFormat, D3DFORMAT TargetFormat) = 0;
	virtual HRESULT ALT_WINAPI GetDeviceCaps(UINT Adapter, D3DDEVTYPE DeviceType, D3DCAPS9 *pCaps) = 0;
	virtual HMONITOR ALT_WINAPI GetAdapterMonitor(UINT Adapter) = 0;
	virtual HRESULT ALT_WINAPI CreateDevice(UINT Adapter, D3DDEVTYPE DeviceType, HWND hFocusWindow, DWORD BehaviorFlags, D3DPRESENT_PARAMETERS *pPresentationParameters, IDirect3DDevice9_alt **ppReturnedDeviceInterface) = 0;
};

struct IDirect3D9Ex_alt : public IDirect3D9_alt
{
	virtual UINT ALT_WINAPI GetAdapterModeCountEx(UINT Adapter, const D3DDISPLAYMODEFILTER *pFilter) = 0;
	virtual HRESULT ALT_WINAPI EnumAdapterModesEx(UINT Adapter, const D3DDISPLAYMODEFILTER *pFilter, UINT Mode, D3DDISPLAYMODEEX *pMode) = 0;
	virtual HRESULT ALT_WINAPI GetAdapterDisplayModeEx(UINT Adapter, D3DDISPLAYMODEEX *pMode, D3DDISPLAYROTATION *pRotation) = 0;
	virtual HRESULT ALT_WINAPI CreateDeviceEx(UINT Adapter, D3DDEVTYPE DeviceType, HWND hFocusWindow, DWORD BehaviorFlags, D3DPRESENT_PARAMETERS *pPresentationParameters, D3DDISPLAYMODEEX *pFullscreenDisplayMode, IDirect3DDevice9Ex_alt **ppReturnedDeviceInterface) = 0;
	virtual HRESULT ALT_WINAPI GetAdapterLUID(UINT Adapter, LUID *pLUID) = 0;
};

struct IDirect3DDevice9_alt : public IUnknown_alt
{
	virtual HRESULT ALT_WINAPI TestCooperativeLevel() = 0;
	virtual UINT ALT_WINAPI GetAvailableTextureMem() = 0;
	virtual HRESULT ALT_WINAPI EvictManagedResources() = 0;
	virtual HRESULT ALT_WINAPI GetDirect3D(IDirect3D9_alt **ppD3D9) = 0;
	virtual HRESULT ALT_WINAPI GetDeviceCaps(D3DCAPS9 *pCaps) = 0;
	virtual HRESULT ALT_WINAPI GetDisplayMode(UINT iSwapChain, D3DDISPLAYMODE *pMode) = 0;
	virtual HRESULT ALT_WINAPI GetCreationParameters(D3DDEVICE_CREATION_PARAMETERS *pParameters) = 0;
	virtual HRESULT ALT_WINAPI SetCursorProperties(UINT XHotSpot, UINT YHotSpot, IDirect3DSurface9_alt *pCursorBitmap) = 0;
	virtual void ALT_WINAPI SetCursorPosition(int X, int Y, DWORD Flags) = 0;
	virtual BOOL ALT_WINAPI ShowCursor(BOOL bShow) = 0;
	virtual HRESULT ALT_WINAPI CreateAdditionalSwapChain(D3DPRESENT_PARAMETERS *pPresentationParameters, IDirect3DSwapChain9_alt **pSwapChain) = 0;
	virtual HRESULT ALT_WINAPI GetSwapChain(UINT iSwapChain, IDirect3DSwapChain9_alt **pSwapChain) = 0;
	virtual UINT ALT_WINAPI GetNumberOfSwapChains() = 0;
	virtual HRESULT ALT_WINAPI Reset(D3DPRESENT_PARAMETERS *pPresentationParameters) = 0;
	virtual HRESULT ALT_WINAPI Present(const RECT *pSourceRect, const RECT *pDestRect, HWND hDestWindowOverride, const RGNDATA *pDirtyRegion) = 0;
	virtual HRESULT ALT_WINAPI GetBackBuffer(UINT iSwapChain, UINT iBackBuffer, D3DBACKBUFFER_TYPE Type, IDirect3DSurface9_alt **ppBackBuffer) = 0;
	virtual HRESULT ALT_WINAPI GetRasterStatus(UINT iSwapChain, D3DRASTER_STATUS *pRasterStatus) = 0;
	virtual HRESULT ALT_WINAPI SetDialogBoxMode(BOOL bEnableDialogs) = 0;
	virtual void ALT_WINAPI SetGammaRamp(UINT iSwapChain, DWORD Flags, const D3DGAMMARAMP *pRamp) = 0;
	virtual void ALT_WINAPI GetGammaRamp(UINT iSwapChain, D3DGAMMARAMP *pRamp) = 0;
	virtual HRESULT ALT_WINAPI CreateTexture(UINT Width, UINT Height, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DTexture9_alt **ppTexture, HANDLE *pSharedHandle) = 0;
	virtual HRESULT ALT_WINAPI CreateVolumeTexture(UINT Width, UINT Height, UINT Depth, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DVolumeTexture9_alt **ppVolumeTexture, HANDLE *pSharedHandle) = 0;
	virtual HRESULT ALT_WINAPI CreateCubeTexture(UINT EdgeLength, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DCubeTexture9_alt **ppCubeTexture, HANDLE *pSharedHandle) = 0;
	virtual HRESULT ALT_WINAPI CreateVertexBuffer(UINT Length, DWORD Usage, DWORD FVF, D3DPOOL Pool, IDirect3DVertexBuffer9_alt **ppVertexBuffer, HANDLE *pSharedHandle) = 0;
	virtual HRESULT ALT_WINAPI CreateIndexBuffer(UINT Length, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DIndexBuffer9_alt **ppIndexBuffer, HANDLE *pSharedHandle) = 0;
	virtual HRESULT ALT_WINAPI CreateRenderTarget(UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, DWORD MultisampleQuality, BOOL Lockable, IDirect3DSurface9_alt **ppSurface, HANDLE *pSharedHandle) = 0;
	virtual HRESULT ALT_WINAPI CreateDepthStencilSurface(UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, DWORD MultisampleQuality, BOOL Discard, IDirect3DSurface9_alt **ppSurface, HANDLE *pSharedHandle) = 0;
	virtual HRESULT ALT_WINAPI UpdateSurface(IDirect3DSurface9_alt *pSourceSurface, const RECT *pSourceRect, IDirect3DSurface9_alt *pDestinationSurface, const POINT *pDestPoint) = 0;
	virtual HRESULT ALT_WINAPI UpdateTexture(IDirect3DBaseTexture9_alt *pSourceTexture_alt, IDirect3DBaseTexture9_alt *pDestinationTexture_alt) = 0;
	virtual HRESULT ALT_WINAPI GetRenderTargetData(IDirect3DSurface9_alt *pRenderTarget, IDirect3DSurface9_alt *pDestSurface) = 0;
	virtual HRESULT ALT_WINAPI GetFrontBufferData(UINT iSwapChain, IDirect3DSurface9_alt *pDestSurface) = 0;
	virtual HRESULT ALT_WINAPI StretchRect(IDirect3DSurface9_alt *pSourceSurface, const RECT *pSourceRect, IDirect3DSurface9_alt *pDestSurface, const RECT *pDestRect, D3DTEXTUREFILTERTYPE Filter) = 0;
	virtual HRESULT ALT_WINAPI ColorFill(IDirect3DSurface9_alt *pSurface, const RECT *pRect, D3DCOLOR color) = 0;
	virtual HRESULT ALT_WINAPI CreateOffscreenPlainSurface(UINT Width, UINT Height, D3DFORMAT Format, D3DPOOL Pool, IDirect3DSurface9_alt **ppSurface, HANDLE *pSharedHandle) = 0;
	virtual HRESULT ALT_WINAPI SetRenderTarget(DWORD RenderTargetIndex, IDirect3DSurface9_alt *pRenderTarget) = 0;
	virtual HRESULT ALT_WINAPI GetRenderTarget(DWORD RenderTargetIndex, IDirect3DSurface9_alt **ppRenderTarget) = 0;
	virtual HRESULT ALT_WINAPI SetDepthStencilSurface(IDirect3DSurface9_alt *pNewZStencil) = 0;
	virtual HRESULT ALT_WINAPI GetDepthStencilSurface(IDirect3DSurface9_alt **ppZStencilSurface) = 0;
	virtual HRESULT ALT_WINAPI BeginScene() = 0;
	virtual HRESULT ALT_WINAPI EndScene() = 0;
	virtual HRESULT ALT_WINAPI Clear(DWORD Count, const D3DRECT *pRects, DWORD Flags, D3DCOLOR Color, float Z, DWORD Stencil) = 0;
	virtual HRESULT ALT_WINAPI SetTransform(D3DTRANSFORMSTATETYPE State, const D3DMATRIX *pMatrix) = 0;
	virtual HRESULT ALT_WINAPI GetTransform(D3DTRANSFORMSTATETYPE State, D3DMATRIX *pMatrix) = 0;
	virtual HRESULT ALT_WINAPI MultiplyTransform(D3DTRANSFORMSTATETYPE State, const D3DMATRIX *pMatrix) = 0;
	virtual HRESULT ALT_WINAPI SetViewport(const D3DVIEWPORT9 *pViewport) = 0;
	virtual HRESULT ALT_WINAPI GetViewport(D3DVIEWPORT9 *pViewport) = 0;
	virtual HRESULT ALT_WINAPI SetMaterial(const D3DMATERIAL9 *pMaterial) = 0;
	virtual HRESULT ALT_WINAPI GetMaterial(D3DMATERIAL9 *pMaterial) = 0;
	virtual HRESULT ALT_WINAPI SetLight(DWORD Index, const D3DLIGHT9 *pLight) = 0;
	virtual HRESULT ALT_WINAPI GetLight(DWORD Index, D3DLIGHT9 *pLight) = 0;
	virtual HRESULT ALT_WINAPI LightEnable(DWORD Index, BOOL Enable) = 0;
	virtual HRESULT ALT_WINAPI GetLightEnable(DWORD Index, BOOL *pEnable) = 0;
	virtual HRESULT ALT_WINAPI SetClipPlane(DWORD Index, const float *pPlane) = 0;
	virtual HRESULT ALT_WINAPI GetClipPlane(DWORD Index, float *pPlane) = 0;
	virtual HRESULT ALT_WINAPI SetRenderState(D3DRENDERSTATETYPE State, DWORD Value) = 0;
	virtual HRESULT ALT_WINAPI GetRenderState(D3DRENDERSTATETYPE State, DWORD *pValue) = 0;
	virtual HRESULT ALT_WINAPI CreateStateBlock(D3DSTATEBLOCKTYPE Type, IDirect3DStateBlock9_alt **ppSB) = 0;
	virtual HRESULT ALT_WINAPI BeginStateBlock() = 0;
	virtual HRESULT ALT_WINAPI EndStateBlock(IDirect3DStateBlock9_alt **ppSB) = 0;
	virtual HRESULT ALT_WINAPI SetClipStatus(const D3DCLIPSTATUS9 *pClipStatus) = 0;
	virtual HRESULT ALT_WINAPI GetClipStatus(D3DCLIPSTATUS9 *pClipStatus) = 0;
	virtual HRESULT ALT_WINAPI GetTexture(DWORD Stage, IDirect3DBaseTexture9_alt **ppTexture) = 0;
	virtual HRESULT ALT_WINAPI SetTexture(DWORD Stage, IDirect3DBaseTexture9_alt *pTexture) = 0;
	virtual HRESULT ALT_WINAPI GetTextureStageState(DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD *pValue) = 0;
	virtual HRESULT ALT_WINAPI SetTextureStageState(DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD Value) = 0;
	virtual HRESULT ALT_WINAPI GetSamplerState(DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD *pValue) = 0;
	virtual HRESULT ALT_WINAPI SetSamplerState(DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD Value) = 0;
	virtual HRESULT ALT_WINAPI ValidateDevice(DWORD *pNumPasses) = 0;
	virtual HRESULT ALT_WINAPI SetPaletteEntries(UINT PaletteNumber, const PALETTEENTRY *pEntries) = 0;
	virtual HRESULT ALT_WINAPI GetPaletteEntries(UINT PaletteNumber, PALETTEENTRY *pEntries) = 0;
	virtual HRESULT ALT_WINAPI SetCurrentTexturePalette(UINT PaletteNumber) = 0;
	virtual HRESULT ALT_WINAPI GetCurrentTexturePalette(UINT *PaletteNumber) = 0;
	virtual HRESULT ALT_WINAPI SetScissorRect(const RECT *pRect) = 0;
	virtual HRESULT ALT_WINAPI GetScissorRect(RECT *pRect) = 0;
	virtual HRESULT ALT_WINAPI SetSoftwareVertexProcessing(BOOL bSoftware) = 0;
	virtual BOOL ALT_WINAPI GetSoftwareVertexProcessing() = 0;
	virtual HRESULT ALT_WINAPI SetNPatchMode(float nSegments) = 0;
	virtual float ALT_WINAPI GetNPatchMode() = 0;
	virtual HRESULT ALT_WINAPI DrawPrimitive(D3DPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT PrimitiveCount) = 0;
	virtual HRESULT ALT_WINAPI DrawIndexedPrimitive(D3DPRIMITIVETYPE PrimitiveType, INT BaseVertexIndex, UINT MinVertexIndex, UINT NumVertices, UINT startIndex, UINT primCount) = 0;
	virtual HRESULT ALT_WINAPI DrawPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType, UINT PrimitiveCount, const void *pVertexStreamZeroData, UINT VertexStreamZeroStride) = 0;
	virtual HRESULT ALT_WINAPI DrawIndexedPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType, UINT MinVertexIndex, UINT NumVertices, UINT PrimitiveCount, const void *pIndexData, D3DFORMAT IndexDataFormat, const void *pVertexStreamZeroData, UINT VertexStreamZeroStride) = 0;
	virtual HRESULT ALT_WINAPI ProcessVertices(UINT SrcStartIndex, UINT DestIndex, UINT VertexCount, IDirect3DVertexBuffer9_alt *pDestBuffer, IDirect3DVertexDeclaration9_alt *pVertexDecl, DWORD Flags) = 0;
	virtual HRESULT ALT_WINAPI CreateVertexDeclaration(const D3DVERTEXELEMENT9 *pVertexElements, IDirect3DVertexDeclaration9_alt **ppDecl) = 0;
	virtual HRESULT ALT_WINAPI SetVertexDeclaration(IDirect3DVertexDeclaration9_alt *pDecl) = 0;
	virtual HRESULT ALT_WINAPI GetVertexDeclaration(IDirect3DVertexDeclaration9_alt **ppDecl) = 0;
	virtual HRESULT ALT_WINAPI SetFVF(DWORD FVF) = 0;
	virtual HRESULT ALT_WINAPI GetFVF(DWORD *pFVF) = 0;
	virtual HRESULT ALT_WINAPI CreateVertexShader(const DWORD *pFunction, IDirect3DVertexShader9_alt **ppShader) = 0;
	virtual HRESULT ALT_WINAPI SetVertexShader(IDirect3DVertexShader9_alt *pShader) = 0;
	virtual HRESULT ALT_WINAPI GetVertexShader(IDirect3DVertexShader9_alt **ppShader) = 0;
	virtual HRESULT ALT_WINAPI SetVertexShaderConstantF(UINT StartRegister, const float *pConstantData, UINT Vector4fCount) = 0;
	virtual HRESULT ALT_WINAPI GetVertexShaderConstantF(UINT StartRegister, float *pConstantData, UINT Vector4fCount) = 0;
	virtual HRESULT ALT_WINAPI SetVertexShaderConstantI(UINT StartRegister, const int *pConstantData, UINT Vector4iCount) = 0;
	virtual HRESULT ALT_WINAPI GetVertexShaderConstantI(UINT StartRegister, int *pConstantData, UINT Vector4iCount) = 0;
	virtual HRESULT ALT_WINAPI SetVertexShaderConstantB(UINT StartRegister, const BOOL *pConstantData, UINT BoolCount) = 0;
	virtual HRESULT ALT_WINAPI GetVertexShaderConstantB(UINT StartRegister, BOOL *pConstantData, UINT BoolCount) = 0;
	virtual HRESULT ALT_WINAPI SetStreamSource(UINT StreamNumber, IDirect3DVertexBuffer9_alt *pStreamData, UINT OffsetInBytes, UINT Stride) = 0;
	virtual HRESULT ALT_WINAPI GetStreamSource(UINT StreamNumber, IDirect3DVertexBuffer9_alt **ppStreamData, UINT *pOffsetInBytes, UINT *pStride) = 0;
	virtual HRESULT ALT_WINAPI SetStreamSourceFreq(UINT StreamNumber, UINT Setting) = 0;
	virtual HRESULT ALT_WINAPI GetStreamSourceFreq(UINT StreamNumber, UINT *pSetting) = 0;
	virtual HRESULT ALT_WINAPI SetIndices(IDirect3DIndexBuffer9_alt *pIndexData) = 0;
	virtual HRESULT ALT_WINAPI GetIndices(IDirect3DIndexBuffer9_alt **ppIndexData, UINT *pBaseVertexIndex) = 0;
	virtual HRESULT ALT_WINAPI CreatePixelShader(const DWORD *pFunction, IDirect3DPixelShader9_alt **ppShader) = 0;
	virtual HRESULT ALT_WINAPI SetPixelShader(IDirect3DPixelShader9_alt *pShader) = 0;
	virtual HRESULT ALT_WINAPI GetPixelShader(IDirect3DPixelShader9_alt **ppShader) = 0;
	virtual HRESULT ALT_WINAPI SetPixelShaderConstantF(UINT StartRegister, const float *pConstantData, UINT Vector4fCount) = 0;
	virtual HRESULT ALT_WINAPI GetPixelShaderConstantF(UINT StartRegister, float *pConstantData, UINT Vector4fCount) = 0;
	virtual HRESULT ALT_WINAPI SetPixelShaderConstantI(UINT StartRegister, const int *pConstantData, UINT Vector4iCount) = 0;
	virtual HRESULT ALT_WINAPI GetPixelShaderConstantI(UINT StartRegister, int *pConstantData, UINT Vector4iCount) = 0;
	virtual HRESULT ALT_WINAPI SetPixelShaderConstantB(UINT StartRegister, const BOOL *pConstantData, UINT BoolCount) = 0;
	virtual HRESULT ALT_WINAPI GetPixelShaderConstantB(UINT StartRegister, BOOL *pConstantData, UINT BoolCount) = 0;
	virtual HRESULT ALT_WINAPI DrawRectPatch(UINT Handle, const float *pNumSegs, const D3DRECTPATCH_INFO *pRectPatchInfo) = 0;
	virtual HRESULT ALT_WINAPI DrawTriPatch(UINT Handle, const float *pNumSegs, const D3DTRIPATCH_INFO *pTriPatchInfo) = 0;
	virtual HRESULT ALT_WINAPI DeletePatch(UINT Handle) = 0;
	virtual HRESULT ALT_WINAPI CreateQuery(D3DQUERYTYPE Type, IDirect3DQuery9_alt **ppQuery) = 0;
};

struct IDirect3DResource9_alt : public IUnknown_alt
{
	virtual HRESULT ALT_WINAPI GetDevice(IDirect3DDevice9_alt **ppDevice) = 0;
	virtual HRESULT ALT_WINAPI SetPrivateData(REFGUID refguid, const void *pData, DWORD SizeOfData, DWORD Flags) = 0;
	virtual HRESULT ALT_WINAPI GetPrivateData(REFGUID refguid, void *pData, DWORD *pSizeOfData) = 0;
	virtual HRESULT ALT_WINAPI FreePrivateData(REFGUID refguid) = 0;
	virtual DWORD ALT_WINAPI SetPriority(DWORD PriorityNew) = 0;
	virtual DWORD ALT_WINAPI GetPriority() = 0;
	virtual void ALT_WINAPI PreLoad() = 0;
	virtual D3DRESOURCETYPE ALT_WINAPI GetType() = 0;
};


struct IDirect3DDevice9Ex_alt : public IDirect3DDevice9_alt
{
	virtual HRESULT ALT_WINAPI SetConvolutionMonoKernel(UINT width, UINT height, float *rows, float *columns) = 0;
	virtual HRESULT ALT_WINAPI ComposeRects(IDirect3DSurface9_alt *pSrc, IDirect3DSurface9_alt *pDst, IDirect3DVertexBuffer9_alt *pSrcRectDescs, UINT NumRects, IDirect3DVertexBuffer9_alt *pDstRectDescs, D3DCOMPOSERECTSOP Operation, int Xoffset, int Yoffset) = 0;
	virtual HRESULT ALT_WINAPI PresentEx(const RECT *pSourceRect, const RECT *pDestRect, HWND hDestWindowOverride, const RGNDATA *pDirtyRegion, DWORD dwFlags) = 0;
	virtual HRESULT ALT_WINAPI GetGPUThreadPriority(INT *pPriority) = 0;
	virtual HRESULT ALT_WINAPI SetGPUThreadPriority(INT Priority) = 0;
	virtual HRESULT ALT_WINAPI WaitForVBlank(UINT iSwapChain) = 0;
	virtual HRESULT ALT_WINAPI CheckResourceResidency(IDirect3DResource9_alt **pResourceArray, UINT32 NumResources) = 0;
	virtual HRESULT ALT_WINAPI SetMaximumFrameLatency(UINT MaxLatency) = 0;
	virtual HRESULT ALT_WINAPI GetMaximumFrameLatency(UINT *pMaxLatency) = 0;
	virtual HRESULT ALT_WINAPI CheckDeviceState(HWND hDestinationWindow) = 0;
	virtual HRESULT ALT_WINAPI CreateRenderTargetEx(UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, DWORD MultisampleQuality, BOOL Lockable, IDirect3DSurface9_alt **ppSurface, HANDLE *pSharedHandle, DWORD Usage) = 0;
	virtual HRESULT ALT_WINAPI CreateOffscreenPlainSurfaceEx(UINT Width, UINT Height, D3DFORMAT Format, D3DPOOL Pool, IDirect3DSurface9_alt **ppSurface, HANDLE *pSharedHandle, DWORD Usage) = 0;
	virtual HRESULT ALT_WINAPI CreateDepthStencilSurfaceEx(UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, DWORD MultisampleQuality, BOOL Discard, IDirect3DSurface9_alt **ppSurface, HANDLE *pSharedHandle, DWORD Usage) = 0;
	virtual HRESULT ALT_WINAPI ResetEx(D3DPRESENT_PARAMETERS *pPresentationParameters, D3DDISPLAYMODEEX *pFullscreenDisplayMode) = 0;
	virtual HRESULT ALT_WINAPI GetDisplayModeEx(UINT iSwapChain, D3DDISPLAYMODEEX *pMode, D3DDISPLAYROTATION *pRotation) = 0;
};

struct IDirect3DVertexBuffer9_alt : public IDirect3DResource9_alt
{
	virtual HRESULT ALT_WINAPI Lock(UINT OffsetToLock, UINT SizeToLock, void **ppbData, DWORD Flags) = 0;
	virtual HRESULT ALT_WINAPI Unlock() = 0;
	virtual HRESULT ALT_WINAPI GetDesc(D3DVERTEXBUFFER_DESC *pDesc) = 0;
};


#else /* __cplusplus */

typedef struct IUnknownVtbl_alt
{
	/* IUnknown */
	HRESULT (ALT_WINAPI *QueryInterface)(IUnknown *This, REFIID riid, void **ppvObject);
	ULONG (ALT_WINAPI *AddRef)(IUnknown *This);
	ULONG (ALT_WINAPI *Release)(IUnknown *This);
} IUnknownVtbl_alt;

struct IUnknown_alt
{
	IUnknownVtbl_alt *lpVtbl;
};


#define IDirect3DDevice9Vtbl_alt void
#define IDirect3DDevice9ExVtbl_alt void
struct IDirect3DDevice9_alt
{
	IDirect3DDevice9Vtbl_alt *lpVtbl;
};
struct IDirect3DDevice9Ex_alt
{
	IDirect3DDevice9ExVtbl_alt *lpVtbl;
};


typedef struct IDirect3D9Vtbl_alt
{
	/* IUnknown */
	HRESULT (ALT_WINAPI *QueryInterface)(IDirect3D9_alt *This, REFIID riid, void **ppvObject);
	ULONG (ALT_WINAPI *AddRef)(IDirect3D9_alt *This);
	ULONG (ALT_WINAPI *Release)(IDirect3D9_alt *This);
	/* IDirect3D9_alt */
	HRESULT (ALT_WINAPI *RegisterSoftwareDevice)(IDirect3D9_alt *This, void *pInitializeFunction);
	UINT (ALT_WINAPI *GetAdapterCount)(IDirect3D9_alt *This);
	HRESULT (ALT_WINAPI *GetAdapterIdentifier)(IDirect3D9_alt *This, UINT Adapter, DWORD Flags, D3DADAPTER_IDENTIFIER9 *pIdentifier);
	UINT (ALT_WINAPI *GetAdapterModeCount)(IDirect3D9_alt *This, UINT Adapter, D3DFORMAT Format);
	HRESULT (ALT_WINAPI *EnumAdapterModes)(IDirect3D9_alt *This, UINT Adapter, D3DFORMAT Format, UINT Mode, D3DDISPLAYMODE *pMode);
	HRESULT (ALT_WINAPI *GetAdapterDisplayMode)(IDirect3D9_alt *This, UINT Adapter, D3DDISPLAYMODE *pMode);
	HRESULT (ALT_WINAPI *CheckDeviceType)(IDirect3D9_alt *This, UINT Adapter, D3DDEVTYPE DevType, D3DFORMAT AdapterFormat, D3DFORMAT BackBufferFormat, BOOL bWindowed);
	HRESULT (ALT_WINAPI *CheckDeviceFormat)(IDirect3D9_alt *This, UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT AdapterFormat, DWORD Usage, D3DRESOURCETYPE RType, D3DFORMAT CheckFormat);
	HRESULT (ALT_WINAPI *CheckDeviceMultiSampleType)(IDirect3D9_alt *This, UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT SurfaceFormat, BOOL Windowed, D3DMULTISAMPLE_TYPE MultiSampleType, DWORD *pQualityLevels);
	HRESULT (ALT_WINAPI *CheckDepthStencilMatch)(IDirect3D9_alt *This, UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT AdapterFormat, D3DFORMAT RenderTargetFormat, D3DFORMAT DepthStencilFormat);
	HRESULT (ALT_WINAPI *CheckDeviceFormatConversion)(IDirect3D9_alt *This, UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT SourceFormat, D3DFORMAT TargetFormat);
	HRESULT (ALT_WINAPI *GetDeviceCaps)(IDirect3D9_alt *This, UINT Adapter, D3DDEVTYPE DeviceType, D3DCAPS9 *pCaps);
	HMONITOR (ALT_WINAPI *GetAdapterMonitor)(IDirect3D9_alt *This, UINT Adapter);
	HRESULT (ALT_WINAPI *CreateDevice)(IDirect3D9_alt *This, UINT Adapter, D3DDEVTYPE DeviceType, HWND hFocusWindow, DWORD BehaviorFlags, D3DPRESENT_PARAMETERS *pPresentationParameters, IDirect3DDevice9_alt **ppReturnedDeviceInterface);
} IDirect3D9Vtbl_alt;
struct IDirect3D9_alt
{
	IDirect3D9Vtbl_alt *lpVtbl;
    IDirect3D9Vtbl *lpVtbl_mirror;
};

typedef struct IDirect3D9ExVtbl_alt
{
	/* IUnknown */
	HRESULT (ALT_WINAPI *QueryInterface)(IDirect3D9Ex_alt *This, REFIID riid, void **ppvObject);
	ULONG (ALT_WINAPI *AddRef)(IDirect3D9Ex_alt *This);
	ULONG (ALT_WINAPI *Release)(IDirect3D9Ex_alt *This);
	/* IDirect3D9 */
	HRESULT (ALT_WINAPI *RegisterSoftwareDevice)(IDirect3D9Ex_alt *This, void *pInitializeFunction);
	UINT (ALT_WINAPI *GetAdapterCount)(IDirect3D9Ex_alt *This);
	HRESULT (ALT_WINAPI *GetAdapterIdentifier)(IDirect3D9Ex_alt *This, UINT Adapter, DWORD Flags, D3DADAPTER_IDENTIFIER9 *pIdentifier);
	UINT (ALT_WINAPI *GetAdapterModeCount)(IDirect3D9Ex_alt *This, UINT Adapter, D3DFORMAT Format);
	HRESULT (ALT_WINAPI *EnumAdapterModes)(IDirect3D9Ex_alt *This, UINT Adapter, D3DFORMAT Format, UINT Mode, D3DDISPLAYMODE *pMode);
	HRESULT (ALT_WINAPI *GetAdapterDisplayMode)(IDirect3D9Ex_alt *This, UINT Adapter, D3DDISPLAYMODE *pMode);
	HRESULT (ALT_WINAPI *CheckDeviceType)(IDirect3D9Ex_alt *This, UINT Adapter, D3DDEVTYPE DevType, D3DFORMAT AdapterFormat, D3DFORMAT BackBufferFormat, BOOL bWindowed);
	HRESULT (ALT_WINAPI *CheckDeviceFormat)(IDirect3D9Ex_alt *This, UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT AdapterFormat, DWORD Usage, D3DRESOURCETYPE RType, D3DFORMAT CheckFormat);
	HRESULT (ALT_WINAPI *CheckDeviceMultiSampleType)(IDirect3D9Ex_alt *This, UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT SurfaceFormat, BOOL Windowed, D3DMULTISAMPLE_TYPE MultiSampleType, DWORD *pQualityLevels);
	HRESULT (ALT_WINAPI *CheckDepthStencilMatch)(IDirect3D9Ex_alt *This, UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT AdapterFormat, D3DFORMAT RenderTargetFormat, D3DFORMAT DepthStencilFormat);
	HRESULT (ALT_WINAPI *CheckDeviceFormatConversion)(IDirect3D9Ex_alt *This, UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT SourceFormat, D3DFORMAT TargetFormat);
	HRESULT (ALT_WINAPI *GetDeviceCaps)(IDirect3D9Ex_alt *This, UINT Adapter, D3DDEVTYPE DeviceType, D3DCAPS9 *pCaps);
	HMONITOR (ALT_WINAPI *GetAdapterMonitor)(IDirect3D9Ex_alt *This, UINT Adapter);
	HRESULT (ALT_WINAPI *CreateDevice)(IDirect3D9Ex_alt *This, UINT Adapter, D3DDEVTYPE DeviceType, HWND hFocusWindow, DWORD BehaviorFlags, D3DPRESENT_PARAMETERS *pPresentationParameters, IDirect3DDevice9_alt **ppReturnedDeviceInterface);
	/* IDirect3D9Ex */
	UINT (ALT_WINAPI *GetAdapterModeCountEx)(IDirect3D9Ex_alt *This, UINT Adapter, const D3DDISPLAYMODEFILTER *pFilter);
	HRESULT (ALT_WINAPI *EnumAdapterModesEx)(IDirect3D9Ex_alt *This, UINT Adapter, const D3DDISPLAYMODEFILTER *pFilter, UINT Mode, D3DDISPLAYMODEEX *pMode);
	HRESULT (ALT_WINAPI *GetAdapterDisplayModeEx)(IDirect3D9Ex_alt *This, UINT Adapter, D3DDISPLAYMODEEX *pMode, D3DDISPLAYROTATION *pRotation);
	HRESULT (ALT_WINAPI *CreateDeviceEx)(IDirect3D9Ex_alt *This, UINT Adapter, D3DDEVTYPE DeviceType, HWND hFocusWindow, DWORD BehaviorFlags, D3DPRESENT_PARAMETERS *pPresentationParameters, D3DDISPLAYMODEEX *pFullscreenDisplayMode, IDirect3DDevice9Ex_alt **ppReturnedDeviceInterface);
	HRESULT (ALT_WINAPI *GetAdapterLUID)(IDirect3D9Ex_alt *This, UINT Adapter, LUID *pLUID);
} IDirect3D9ExVtbl_alt;

struct IDirect3D9Ex_alt
{
	IDirect3D9ExVtbl_alt *lpVtbl;
    IDirect3D9ExVtbl *lpVtbl_mirror;
};

#if 0 // not needed, conversion not finished
typedef struct IDirect3DDevice9ExVtbl
{
	/* IUnknown */
	HRESULT (ALT_WINAPI *QueryInterface)(IDirect3DDevice9Ex *This, REFIID riid, void **ppvObject);
	ULONG (ALT_WINAPI *AddRef)(IDirect3DDevice9Ex *This);
	ULONG (ALT_WINAPI *Release)(IDirect3DDevice9Ex *This);
	/* IDirect3DDevice9 */
	HRESULT (ALT_WINAPI *TestCooperativeLevel)(IDirect3DDevice9Ex *This);
	UINT (ALT_WINAPI *GetAvailableTextureMem)(IDirect3DDevice9Ex *This);
	HRESULT (ALT_WINAPI *EvictManagedResources)(IDirect3DDevice9Ex *This);
	HRESULT (ALT_WINAPI *GetDirect3D)(IDirect3DDevice9Ex *This, IDirect3D9 **ppD3D9);
	HRESULT (ALT_WINAPI *GetDeviceCaps)(IDirect3DDevice9Ex *This, D3DCAPS9 *pCaps);
	HRESULT (ALT_WINAPI *GetDisplayMode)(IDirect3DDevice9Ex *This, UINT iSwapChain, D3DDISPLAYMODE *pMode);
	HRESULT (ALT_WINAPI *GetCreationParameters)(IDirect3DDevice9Ex *This, D3DDEVICE_CREATION_PARAMETERS *pParameters);
	HRESULT (ALT_WINAPI *SetCursorProperties)(IDirect3DDevice9Ex *This, UINT XHotSpot, UINT YHotSpot, IDirect3DSurface9 *pCursorBitmap);
	void (ALT_WINAPI *SetCursorPosition)(IDirect3DDevice9Ex *This, int X, int Y, DWORD Flags);
	BOOL (ALT_WINAPI *ShowCursor)(IDirect3DDevice9Ex *This, BOOL bShow);
	HRESULT (ALT_WINAPI *CreateAdditionalSwapChain)(IDirect3DDevice9Ex *This, D3DPRESENT_PARAMETERS *pPresentationParameters, IDirect3DSwapChain9 **pSwapChain);
	HRESULT (ALT_WINAPI *GetSwapChain)(IDirect3DDevice9Ex *This, UINT iSwapChain, IDirect3DSwapChain9 **pSwapChain);
	UINT (ALT_WINAPI *GetNumberOfSwapChains)(IDirect3DDevice9Ex *This);
	HRESULT (ALT_WINAPI *Reset)(IDirect3DDevice9Ex *This, D3DPRESENT_PARAMETERS *pPresentationParameters);
	HRESULT (ALT_WINAPI *Present)(IDirect3DDevice9Ex *This, const RECT *pSourceRect, const RECT *pDestRect, HWND hDestWindowOverride, const RGNDATA *pDirtyRegion);
	HRESULT (ALT_WINAPI *GetBackBuffer)(IDirect3DDevice9Ex *This, UINT iSwapChain, UINT iBackBuffer, D3DBACKBUFFER_TYPE Type, IDirect3DSurface9 **ppBackBuffer);
	HRESULT (ALT_WINAPI *GetRasterStatus)(IDirect3DDevice9Ex *This, UINT iSwapChain, D3DRASTER_STATUS *pRasterStatus);
	HRESULT (ALT_WINAPI *SetDialogBoxMode)(IDirect3DDevice9Ex *This, BOOL bEnableDialogs);
	void (ALT_WINAPI *SetGammaRamp)(IDirect3DDevice9Ex *This, UINT iSwapChain, DWORD Flags, const D3DGAMMARAMP *pRamp);
	void (ALT_WINAPI *GetGammaRamp)(IDirect3DDevice9Ex *This, UINT iSwapChain, D3DGAMMARAMP *pRamp);
	HRESULT (ALT_WINAPI *CreateTexture)(IDirect3DDevice9Ex *This, UINT Width, UINT Height, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DTexture9 **ppTexture, HANDLE *pSharedHandle);
	HRESULT (ALT_WINAPI *CreateVolumeTexture)(IDirect3DDevice9Ex *This, UINT Width, UINT Height, UINT Depth, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DVolumeTexture9 **ppVolumeTexture, HANDLE *pSharedHandle);
	HRESULT (ALT_WINAPI *CreateCubeTexture)(IDirect3DDevice9Ex *This, UINT EdgeLength, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DCubeTexture9 **ppCubeTexture, HANDLE *pSharedHandle);
	HRESULT (ALT_WINAPI *CreateVertexBuffer)(IDirect3DDevice9Ex *This, UINT Length, DWORD Usage, DWORD FVF, D3DPOOL Pool, IDirect3DVertexBuffer9 **ppVertexBuffer, HANDLE *pSharedHandle);
	HRESULT (ALT_WINAPI *CreateIndexBuffer)(IDirect3DDevice9Ex *This, UINT Length, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DIndexBuffer9 **ppIndexBuffer, HANDLE *pSharedHandle);
	HRESULT (ALT_WINAPI *CreateRenderTarget)(IDirect3DDevice9Ex *This, UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, DWORD MultisampleQuality, BOOL Lockable, IDirect3DSurface9 **ppSurface, HANDLE *pSharedHandle);
	HRESULT (ALT_WINAPI *CreateDepthStencilSurface)(IDirect3DDevice9Ex *This, UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, DWORD MultisampleQuality, BOOL Discard, IDirect3DSurface9 **ppSurface, HANDLE *pSharedHandle);
	HRESULT (ALT_WINAPI *UpdateSurface)(IDirect3DDevice9Ex *This, IDirect3DSurface9 *pSourceSurface, const RECT *pSourceRect, IDirect3DSurface9 *pDestinationSurface, const POINT *pDestPoint);
	HRESULT (ALT_WINAPI *UpdateTexture)(IDirect3DDevice9Ex *This, IDirect3DBaseTexture9 *pSourceTexture, IDirect3DBaseTexture9 *pDestinationTexture);
	HRESULT (ALT_WINAPI *GetRenderTargetData)(IDirect3DDevice9Ex *This, IDirect3DSurface9 *pRenderTarget, IDirect3DSurface9 *pDestSurface);
	HRESULT (ALT_WINAPI *GetFrontBufferData)(IDirect3DDevice9Ex *This, UINT iSwapChain, IDirect3DSurface9 *pDestSurface);
	HRESULT (ALT_WINAPI *StretchRect)(IDirect3DDevice9Ex *This, IDirect3DSurface9 *pSourceSurface, const RECT *pSourceRect, IDirect3DSurface9 *pDestSurface, const RECT *pDestRect, D3DTEXTUREFILTERTYPE Filter);
	HRESULT (ALT_WINAPI *ColorFill)(IDirect3DDevice9Ex *This, IDirect3DSurface9 *pSurface, const RECT *pRect, D3DCOLOR color);
	HRESULT (ALT_WINAPI *CreateOffscreenPlainSurface)(IDirect3DDevice9Ex *This, UINT Width, UINT Height, D3DFORMAT Format, D3DPOOL Pool, IDirect3DSurface9 **ppSurface, HANDLE *pSharedHandle);
	HRESULT (ALT_WINAPI *SetRenderTarget)(IDirect3DDevice9Ex *This, DWORD RenderTargetIndex, IDirect3DSurface9 *pRenderTarget);
	HRESULT (ALT_WINAPI *GetRenderTarget)(IDirect3DDevice9Ex *This, DWORD RenderTargetIndex, IDirect3DSurface9 **ppRenderTarget);
	HRESULT (ALT_WINAPI *SetDepthStencilSurface)(IDirect3DDevice9Ex *This, IDirect3DSurface9 *pNewZStencil);
	HRESULT (ALT_WINAPI *GetDepthStencilSurface)(IDirect3DDevice9Ex *This, IDirect3DSurface9 **ppZStencilSurface);
	HRESULT (ALT_WINAPI *BeginScene)(IDirect3DDevice9Ex *This);
	HRESULT (ALT_WINAPI *EndScene)(IDirect3DDevice9Ex *This);
	HRESULT (ALT_WINAPI *Clear)(IDirect3DDevice9Ex *This, DWORD Count, const D3DRECT *pRects, DWORD Flags, D3DCOLOR Color, float Z, DWORD Stencil);
	HRESULT (ALT_WINAPI *SetTransform)(IDirect3DDevice9Ex *This, D3DTRANSFORMSTATETYPE State, const D3DMATRIX *pMatrix);
	HRESULT (ALT_WINAPI *GetTransform)(IDirect3DDevice9Ex *This, D3DTRANSFORMSTATETYPE State, D3DMATRIX *pMatrix);
	HRESULT (ALT_WINAPI *MultiplyTransform)(IDirect3DDevice9Ex *This, D3DTRANSFORMSTATETYPE State, const D3DMATRIX *pMatrix);
	HRESULT (ALT_WINAPI *SetViewport)(IDirect3DDevice9Ex *This, const D3DVIEWPORT9 *pViewport);
	HRESULT (ALT_WINAPI *GetViewport)(IDirect3DDevice9Ex *This, D3DVIEWPORT9 *pViewport);
	HRESULT (ALT_WINAPI *SetMaterial)(IDirect3DDevice9Ex *This, const D3DMATERIAL9 *pMaterial);
	HRESULT (ALT_WINAPI *GetMaterial)(IDirect3DDevice9Ex *This, D3DMATERIAL9 *pMaterial);
	HRESULT (ALT_WINAPI *SetLight)(IDirect3DDevice9Ex *This, DWORD Index, const D3DLIGHT9 *pLight);
	HRESULT (ALT_WINAPI *GetLight)(IDirect3DDevice9Ex *This, DWORD Index, D3DLIGHT9 *pLight);
	HRESULT (ALT_WINAPI *LightEnable)(IDirect3DDevice9Ex *This, DWORD Index, BOOL Enable);
	HRESULT (ALT_WINAPI *GetLightEnable)(IDirect3DDevice9Ex *This, DWORD Index, BOOL *pEnable);
	HRESULT (ALT_WINAPI *SetClipPlane)(IDirect3DDevice9Ex *This, DWORD Index, const float *pPlane);
	HRESULT (ALT_WINAPI *GetClipPlane)(IDirect3DDevice9Ex *This, DWORD Index, float *pPlane);
	HRESULT (ALT_WINAPI *SetRenderState)(IDirect3DDevice9Ex *This, D3DRENDERSTATETYPE State, DWORD Value);
	HRESULT (ALT_WINAPI *GetRenderState)(IDirect3DDevice9Ex *This, D3DRENDERSTATETYPE State, DWORD *pValue);
	HRESULT (ALT_WINAPI *CreateStateBlock)(IDirect3DDevice9Ex *This, D3DSTATEBLOCKTYPE Type, IDirect3DStateBlock9 **ppSB);
	HRESULT (ALT_WINAPI *BeginStateBlock)(IDirect3DDevice9Ex *This);
	HRESULT (ALT_WINAPI *EndStateBlock)(IDirect3DDevice9Ex *This, IDirect3DStateBlock9 **ppSB);
	HRESULT (ALT_WINAPI *SetClipStatus)(IDirect3DDevice9Ex *This, const D3DCLIPSTATUS9 *pClipStatus);
	HRESULT (ALT_WINAPI *GetClipStatus)(IDirect3DDevice9Ex *This, D3DCLIPSTATUS9 *pClipStatus);
	HRESULT (ALT_WINAPI *GetTexture)(IDirect3DDevice9Ex *This, DWORD Stage, IDirect3DBaseTexture9 **ppTexture);
	HRESULT (ALT_WINAPI *SetTexture)(IDirect3DDevice9Ex *This, DWORD Stage, IDirect3DBaseTexture9 *pTexture);
	HRESULT (ALT_WINAPI *GetTextureStageState)(IDirect3DDevice9Ex *This, DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD *pValue);
	HRESULT (ALT_WINAPI *SetTextureStageState)(IDirect3DDevice9Ex *This, DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD Value);
	HRESULT (ALT_WINAPI *GetSamplerState)(IDirect3DDevice9Ex *This, DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD *pValue);
	HRESULT (ALT_WINAPI *SetSamplerState)(IDirect3DDevice9Ex *This, DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD Value);
	HRESULT (ALT_WINAPI *ValidateDevice)(IDirect3DDevice9Ex *This, DWORD *pNumPasses);
	HRESULT (ALT_WINAPI *SetPaletteEntries)(IDirect3DDevice9Ex *This, UINT PaletteNumber, const PALETTEENTRY *pEntries);
	HRESULT (ALT_WINAPI *GetPaletteEntries)(IDirect3DDevice9Ex *This, UINT PaletteNumber, PALETTEENTRY *pEntries);
	HRESULT (ALT_WINAPI *SetCurrentTexturePalette)(IDirect3DDevice9Ex *This, UINT PaletteNumber);
	HRESULT (ALT_WINAPI *GetCurrentTexturePalette)(IDirect3DDevice9Ex *This, UINT *PaletteNumber);
	HRESULT (ALT_WINAPI *SetScissorRect)(IDirect3DDevice9Ex *This, const RECT *pRect);
	HRESULT (ALT_WINAPI *GetScissorRect)(IDirect3DDevice9Ex *This, RECT *pRect);
	HRESULT (ALT_WINAPI *SetSoftwareVertexProcessing)(IDirect3DDevice9Ex *This, BOOL bSoftware);
	BOOL (ALT_WINAPI *GetSoftwareVertexProcessing)(IDirect3DDevice9Ex *This);
	HRESULT (ALT_WINAPI *SetNPatchMode)(IDirect3DDevice9Ex *This, float nSegments);
	float (ALT_WINAPI *GetNPatchMode)(IDirect3DDevice9Ex *This);
	HRESULT (ALT_WINAPI *DrawPrimitive)(IDirect3DDevice9Ex *This, D3DPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT PrimitiveCount);
	HRESULT (ALT_WINAPI *DrawIndexedPrimitive)(IDirect3DDevice9Ex *This, D3DPRIMITIVETYPE PrimitiveType, INT BaseVertexIndex, UINT MinVertexIndex, UINT NumVertices, UINT startIndex, UINT primCount);
	HRESULT (ALT_WINAPI *DrawPrimitiveUP)(IDirect3DDevice9Ex *This, D3DPRIMITIVETYPE PrimitiveType, UINT PrimitiveCount, const void *pVertexStreamZeroData, UINT VertexStreamZeroStride);
	HRESULT (ALT_WINAPI *DrawIndexedPrimitiveUP)(IDirect3DDevice9Ex *This, D3DPRIMITIVETYPE PrimitiveType, UINT MinVertexIndex, UINT NumVertices, UINT PrimitiveCount, const void *pIndexData, D3DFORMAT IndexDataFormat, const void *pVertexStreamZeroData, UINT VertexStreamZeroStride);
	HRESULT (ALT_WINAPI *ProcessVertices)(IDirect3DDevice9Ex *This, UINT SrcStartIndex, UINT DestIndex, UINT VertexCount, IDirect3DVertexBuffer9 *pDestBuffer, IDirect3DVertexDeclaration9 *pVertexDecl, DWORD Flags);
	HRESULT (ALT_WINAPI *CreateVertexDeclaration)(IDirect3DDevice9Ex *This, const D3DVERTEXELEMENT9 *pVertexElements, IDirect3DVertexDeclaration9 **ppDecl);
	HRESULT (ALT_WINAPI *SetVertexDeclaration)(IDirect3DDevice9Ex *This, IDirect3DVertexDeclaration9 *pDecl);
	HRESULT (ALT_WINAPI *GetVertexDeclaration)(IDirect3DDevice9Ex *This, IDirect3DVertexDeclaration9 **ppDecl);
	HRESULT (ALT_WINAPI *SetFVF)(IDirect3DDevice9Ex *This, DWORD FVF);
	HRESULT (ALT_WINAPI *GetFVF)(IDirect3DDevice9Ex *This, DWORD *pFVF);
	HRESULT (ALT_WINAPI *CreateVertexShader)(IDirect3DDevice9Ex *This, const DWORD *pFunction, IDirect3DVertexShader9 **ppShader);
	HRESULT (ALT_WINAPI *SetVertexShader)(IDirect3DDevice9Ex *This, IDirect3DVertexShader9 *pShader);
	HRESULT (ALT_WINAPI *GetVertexShader)(IDirect3DDevice9Ex *This, IDirect3DVertexShader9 **ppShader);
	HRESULT (ALT_WINAPI *SetVertexShaderConstantF)(IDirect3DDevice9Ex *This, UINT StartRegister, const float *pConstantData, UINT Vector4fCount);
	HRESULT (ALT_WINAPI *GetVertexShaderConstantF)(IDirect3DDevice9Ex *This, UINT StartRegister, float *pConstantData, UINT Vector4fCount);
	HRESULT (ALT_WINAPI *SetVertexShaderConstantI)(IDirect3DDevice9Ex *This, UINT StartRegister, const int *pConstantData, UINT Vector4iCount);
	HRESULT (ALT_WINAPI *GetVertexShaderConstantI)(IDirect3DDevice9Ex *This, UINT StartRegister, int *pConstantData, UINT Vector4iCount);
	HRESULT (ALT_WINAPI *SetVertexShaderConstantB)(IDirect3DDevice9Ex *This, UINT StartRegister, const BOOL *pConstantData, UINT BoolCount);
	HRESULT (ALT_WINAPI *GetVertexShaderConstantB)(IDirect3DDevice9Ex *This, UINT StartRegister, BOOL *pConstantData, UINT BoolCount);
	HRESULT (ALT_WINAPI *SetStreamSource)(IDirect3DDevice9Ex *This, UINT StreamNumber, IDirect3DVertexBuffer9 *pStreamData, UINT OffsetInBytes, UINT Stride);
	HRESULT (ALT_WINAPI *GetStreamSource)(IDirect3DDevice9Ex *This, UINT StreamNumber, IDirect3DVertexBuffer9 **ppStreamData, UINT *pOffsetInBytes, UINT *pStride);
	HRESULT (ALT_WINAPI *SetStreamSourceFreq)(IDirect3DDevice9Ex *This, UINT StreamNumber, UINT Setting);
	HRESULT (ALT_WINAPI *GetStreamSourceFreq)(IDirect3DDevice9Ex *This, UINT StreamNumber, UINT *pSetting);
	HRESULT (ALT_WINAPI *SetIndices)(IDirect3DDevice9Ex *This, IDirect3DIndexBuffer9 *pIndexData);
	HRESULT (ALT_WINAPI *GetIndices)(IDirect3DDevice9Ex *This, IDirect3DIndexBuffer9 **ppIndexData, UINT *pBaseVertexIndex);
	HRESULT (ALT_WINAPI *CreatePixelShader)(IDirect3DDevice9Ex *This, const DWORD *pFunction, IDirect3DPixelShader9 **ppShader);
	HRESULT (ALT_WINAPI *SetPixelShader)(IDirect3DDevice9Ex *This, IDirect3DPixelShader9 *pShader);
	HRESULT (ALT_WINAPI *GetPixelShader)(IDirect3DDevice9Ex *This, IDirect3DPixelShader9 **ppShader);
	HRESULT (ALT_WINAPI *SetPixelShaderConstantF)(IDirect3DDevice9Ex *This, UINT StartRegister, const float *pConstantData, UINT Vector4fCount);
	HRESULT (ALT_WINAPI *GetPixelShaderConstantF)(IDirect3DDevice9Ex *This, UINT StartRegister, float *pConstantData, UINT Vector4fCount);
	HRESULT (ALT_WINAPI *SetPixelShaderConstantI)(IDirect3DDevice9Ex *This, UINT StartRegister, const int *pConstantData, UINT Vector4iCount);
	HRESULT (ALT_WINAPI *GetPixelShaderConstantI)(IDirect3DDevice9Ex *This, UINT StartRegister, int *pConstantData, UINT Vector4iCount);
	HRESULT (ALT_WINAPI *SetPixelShaderConstantB)(IDirect3DDevice9Ex *This, UINT StartRegister, const BOOL *pConstantData, UINT BoolCount);
	HRESULT (ALT_WINAPI *GetPixelShaderConstantB)(IDirect3DDevice9Ex *This, UINT StartRegister, BOOL *pConstantData, UINT BoolCount);
	HRESULT (ALT_WINAPI *DrawRectPatch)(IDirect3DDevice9Ex *This, UINT Handle, const float *pNumSegs, const D3DRECTPATCH_INFO *pRectPatchInfo);
	HRESULT (ALT_WINAPI *DrawTriPatch)(IDirect3DDevice9Ex *This, UINT Handle, const float *pNumSegs, const D3DTRIPATCH_INFO *pTriPatchInfo);
	HRESULT (ALT_WINAPI *DeletePatch)(IDirect3DDevice9Ex *This, UINT Handle);
	HRESULT (ALT_WINAPI *CreateQuery)(IDirect3DDevice9Ex *This, D3DQUERYTYPE Type, IDirect3DQuery9 **ppQuery);
	/* IDirect3DDevice9Ex */
	HRESULT (ALT_WINAPI *SetConvolutionMonoKernel)(IDirect3DDevice9Ex *This, UINT width, UINT height, float *rows, float *columns);
	HRESULT (ALT_WINAPI *ComposeRects)(IDirect3DDevice9Ex *This, IDirect3DSurface9 *pSrc, IDirect3DSurface9 *pDst, IDirect3DVertexBuffer9 *pSrcRectDescs, UINT NumRects, IDirect3DVertexBuffer9 *pDstRectDescs, D3DCOMPOSERECTSOP Operation, int Xoffset, int Yoffset);
	HRESULT (ALT_WINAPI *PresentEx)(IDirect3DDevice9Ex *This, const RECT *pSourceRect, const RECT *pDestRect, HWND hDestWindowOverride, const RGNDATA *pDirtyRegion, DWORD dwFlags);
	HRESULT (ALT_WINAPI *GetGPUThreadPriority)(IDirect3DDevice9Ex *This, INT *pPriority);
	HRESULT (ALT_WINAPI *SetGPUThreadPriority)(IDirect3DDevice9Ex *This, INT Priority);
	HRESULT (ALT_WINAPI *WaitForVBlank)(IDirect3DDevice9Ex *This, UINT iSwapChain);
	HRESULT (ALT_WINAPI *CheckResourceResidency)(IDirect3DDevice9Ex *This, IDirect3DResource9 **pResourceArray, UINT32 NumResources);
	HRESULT (ALT_WINAPI *SetMaximumFrameLatency)(IDirect3DDevice9Ex *This, UINT MaxLatency);
	HRESULT (ALT_WINAPI *GetMaximumFrameLatency)(IDirect3DDevice9Ex *This, UINT *pMaxLatency);
	HRESULT (ALT_WINAPI *CheckDeviceState)(IDirect3DDevice9Ex *This, HWND hDestinationWindow);
	HRESULT (ALT_WINAPI *CreateRenderTargetEx)(IDirect3DDevice9Ex *This, UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, DWORD MultisampleQuality, BOOL Lockable, IDirect3DSurface9 **ppSurface, HANDLE *pSharedHandle, DWORD Usage);
	HRESULT (ALT_WINAPI *CreateOffscreenPlainSurfaceEx)(IDirect3DDevice9Ex *This, UINT Width, UINT Height, D3DFORMAT Format, D3DPOOL Pool, IDirect3DSurface9 **ppSurface, HANDLE *pSharedHandle, DWORD Usage);
	HRESULT (ALT_WINAPI *CreateDepthStencilSurfaceEx)(IDirect3DDevice9Ex *This, UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, DWORD MultisampleQuality, BOOL Discard, IDirect3DSurface9 **ppSurface, HANDLE *pSharedHandle, DWORD Usage);
	HRESULT (ALT_WINAPI *ResetEx)(IDirect3DDevice9Ex *This, D3DPRESENT_PARAMETERS *pPresentationParameters, D3DDISPLAYMODEEX *pFullscreenDisplayMode);
	HRESULT (ALT_WINAPI *GetDisplayModeEx)(IDirect3DDevice9Ex *This, UINT iSwapChain, D3DDISPLAYMODEEX *pMode, D3DDISPLAYROTATION *pRotation);
} IDirect3DDevice9ExVtbl;
struct IDirect3DDevice9Ex
{
	IDirect3DDevice9ExVtbl *lpVtbl;
};


typedef struct IDirect3DVertexBuffer9Vtbl_alt
{
	/* IUnknown */
	HRESULT (ALT_WINAPI *QueryInterface)(IDirect3DVertexBuffer9_alt *This, REFIID riid, void **ppvObject);
	ULONG (ALT_WINAPI *AddRef)(IDirect3DVertexBuffer9_alt *This);
	ULONG (ALT_WINAPI *Release)(IDirect3DVertexBuffer9_alt *This);
	/* IDirect3DResource9 */
	HRESULT (ALT_WINAPI *GetDevice)(IDirect3DVertexBuffer9_alt *This, IDirect3DDevice9 **ppDevice);
	HRESULT (ALT_WINAPI *SetPrivateData)(IDirect3DVertexBuffer9_alt *This, REFGUID refguid, const void *pData, DWORD SizeOfData, DWORD Flags);
	HRESULT (ALT_WINAPI *GetPrivateData)(IDirect3DVertexBuffer9_alt *This, REFGUID refguid, void *pData, DWORD *pSizeOfData);
	HRESULT (ALT_WINAPI *FreePrivateData)(IDirect3DVertexBuffer9_alt *This, REFGUID refguid);
	DWORD (ALT_WINAPI *SetPriority)(IDirect3DVertexBuffer9_alt *This, DWORD PriorityNew);
	DWORD (ALT_WINAPI *GetPriority)(IDirect3DVertexBuffer9_alt *This);
	void (ALT_WINAPI *PreLoad)(IDirect3DVertexBuffer9_alt *This);
	D3DRESOURCETYPE (ALT_WINAPI *GetType)(IDirect3DVertexBuffer9_alt *This);
	/* IDirect3DVertexBuffer9_alt */
	HRESULT (ALT_WINAPI *Lock)(IDirect3DVertexBuffer9_alt *This, UINT OffsetToLock, UINT SizeToLock, void **ppbData, DWORD Flags);
	HRESULT (ALT_WINAPI *Unlock)(IDirect3DVertexBuffer9_alt *This);
	HRESULT (ALT_WINAPI *GetDesc)(IDirect3DVertexBuffer9_alt *This, D3DVERTEXBUFFER_DESC *pDesc);
} IDirect3DVertexBuffer9Vtbl_alt;
struct IDirect3DVertexBuffer9_alt
{
	IDirect3DVertexBuffer9Vtbl_alt *lpVtbl;
};
#endif

#endif /* __cplusplus */



 
