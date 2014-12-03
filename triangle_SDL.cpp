// ConsoleApplication1.cpp : définit le point d'entrée pour l'application console.
//

#include <SDL.h>
//#include <SDL_syswm.h>

#include <d3d9.h>

#include "SDL_nine.h"

// define the screen resolution
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 576

#define ERR(...)    fprintf(stderr, __VA_ARGS__)

// global declarations
LPDIRECT3D9 d3d;    // the pointer to our Direct3D interface
LPDIRECT3DDEVICE9 d3ddev;    // the pointer to the device class
LPDIRECT3DVERTEXBUFFER9 v_buffer = NULL;    // the pointer to the vertex buffer

void render_frame(void);    // renders a single frame
void init_graphics(void);    // 3D declarations

struct CUSTOMVERTEX { FLOAT X, Y, Z, RHW; DWORD COLOR; };
#define CUSTOMFVF (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)


// this is the function used to render a single frame
void render_frame(void)
{
    static int col = 0;
    d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, col++), 1.0f, 0);

    d3ddev->BeginScene();

    // select which vertex format we are using
    d3ddev->SetFVF(CUSTOMFVF);

    // select the vertex buffer to display
    d3ddev->SetStreamSource(0, v_buffer, 0, sizeof(CUSTOMVERTEX));

    // copy the vertex buffer to the back buffer
    d3ddev->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);

    d3ddev->EndScene();

    d3ddev->Present(NULL, NULL, NULL, NULL);
}

// this is the function that puts the 3D models into video RAM
void init_graphics(void)
{
    // create the vertices using the CUSTOMVERTEX struct
    CUSTOMVERTEX vertices[] =
    {
        { 400.0f, 62.5f, 0.5f, 1.0f, D3DCOLOR_XRGB(0, 0, 255), },
        { 650.0f, 500.0f, 0.5f, 1.0f, D3DCOLOR_XRGB(0, 255, 0), },
        { 150.0f, 500.0f, 0.5f, 1.0f, D3DCOLOR_XRGB(255, 0, 0), },
    };

    // create a vertex buffer interface called v_buffer
    d3ddev->CreateVertexBuffer(3 * sizeof(CUSTOMVERTEX),
        0,
        CUSTOMFVF,
        D3DPOOL_MANAGED,
        &v_buffer,
        NULL);

    void* pVoid;    // a void pointer

    // lock v_buffer and load the vertices into it
    v_buffer->Lock(0, 0, (void**)&pVoid, 0);
    memcpy(pVoid, vertices, sizeof(vertices));
    v_buffer->Unlock();
}

int main(int argc, char **argv)
{
    if (SDL_Init(0) != 0){
        ERR("SDL_Init\n");
        return 1;
    }

    SDL_Window* Window = SDL_CreateWindow("SDL Nine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN /*| SDL_WINDOW_RESIZABLE*/ );
    if (!Window) {
        ERR("SDL_CreateWindow\n");
        return 1;
    }

    d3d = SDL_Direct3DCreate9Ex(Window);
    if (!d3d) {
        ERR("X11_Direct3DCreate9\n");
        return 1;
    }

    {
        HWND FakeWnd= (HWND)Window;

        D3DPRESENT_PARAMETERS d3dpp;
        memset(&d3dpp, 0, sizeof(d3dpp));
        d3dpp.Windowed = TRUE;
        d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
        d3dpp.hDeviceWindow = FakeWnd;
        d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;          // works
        d3dpp.BackBufferWidth = SCREEN_WIDTH;
        d3dpp.BackBufferHeight = SCREEN_HEIGHT;

        // create a device class using this information and the info from the d3dpp stuct
        HRESULT hr = d3d->CreateDevice(D3DADAPTER_DEFAULT,
            D3DDEVTYPE_HAL,
            FakeWnd,
            D3DCREATE_HARDWARE_VERTEXPROCESSING,
            &d3dpp,
            &d3ddev);

        if (FAILED(hr)) {
            ERR("X11_Direct3DCreate9\n");
            return 1;
        }
    }

    init_graphics();    // call the function to initialize the triangle

    bool quit = false;
    SDL_Event e;

    //While application is running
    while (!quit)
    {
        //Handle events on queue
        while (SDL_PollEvent(&e) != 0)
        {
            //User requests quit
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
        }

        //Render quad
        render_frame();
    }

    // clean up DirectX
    {
        v_buffer->Release();    // close and release the vertex buffer
        d3ddev->Release();    // close and release the 3D device
        d3d->Release();    // close and release Direct3D
    }

    SDL_Quit();

    return 0;
}


