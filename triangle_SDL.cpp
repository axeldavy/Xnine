// ConsoleApplication1.cpp : définit le point d'entrée pour l'application console.
//

#include <SDL.h>
//#include <SDL_syswm.h>

#include <d3d9.h>

#include "SDL_nine.h"

// define the screen resolution
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define ERR(...)    fprintf(stderr, __VA_ARGS__)

// global declarations
LPDIRECT3D9EX d3d;    // the pointer to our Direct3D interface
LPDIRECT3DDEVICE9EX d3ddev;    // the pointer to the device class
LPDIRECT3DVERTEXBUFFER9 v_buffer = NULL;    // the pointer to the vertex buffer

void render_frame(void);    // renders a single frame
void init_graphics(void);    // 3D declarations

struct CUSTOMVERTEX { FLOAT X, Y, Z, RHW; DWORD COLOR; };
#define CUSTOMFVF (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)


// this is the function used to render a single frame
void render_frame(void)
{
    HRESULT hr;
    static int col = 0;
    hr = d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, col++), 1.0f, 0);
    if (FAILED(hr)) ERR("Clear\n");

    hr = d3ddev->BeginScene();
    if (FAILED(hr)) ERR("BeginScene\n");

    // select which vertex format we are using
    hr = d3ddev->SetFVF(CUSTOMFVF);
    if (FAILED(hr)) ERR("SetFVF\n");

    // select the vertex buffer to display
    hr = d3ddev->SetStreamSource(0, v_buffer, 0, sizeof(CUSTOMVERTEX));
    if (FAILED(hr)) ERR("SetStreamSource\n");

    // copy the vertex buffer to the back buffer
    hr = d3ddev->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);
    if (FAILED(hr)) ERR("DrawPrimitive\n");

    hr = d3ddev->EndScene();
    if (FAILED(hr)) ERR("EndScene\n");

    hr = d3ddev->Present(NULL, NULL, NULL, NULL);
    if (FAILED(hr)) ERR("Present\n");
}

// this is the function that puts the 3D models into video RAM
void load_triangle(int w, int h, LPDIRECT3DVERTEXBUFFER9 v_buffer)
{
    float hs = (float)(w > h ? h : w) * 0.4f;
    float cx = (float)w * 0.5f;
    float cy = (float)h * 0.5f;

    // create the vertices using the CUSTOMVERTEX struct
    CUSTOMVERTEX vertices[] =
    {
        { cx,    cy-hs, 0.5f, 1.0f, D3DCOLOR_XRGB(0, 0, 255), },
        { cx+hs, cy+hs, 0.5f, 1.0f, D3DCOLOR_XRGB(0, 255, 0), },
        { cx-hs, cy+hs, 0.5f, 1.0f, D3DCOLOR_XRGB(255, 0, 0), },
    };

    void* pVoid;    // a void pointer

    // lock v_buffer and load the vertices into it
    v_buffer->Lock(0, 0, (void**)&pVoid, 0);
    memcpy(pVoid, vertices, sizeof(vertices));
    v_buffer->Unlock();
}
 
void init_graphics(void)
{
    // create a vertex buffer interface called v_buffer
    d3ddev->CreateVertexBuffer(3 * sizeof(CUSTOMVERTEX),
        0,
        CUSTOMFVF,
        D3DPOOL_MANAGED,
        &v_buffer,
        NULL);

    load_triangle(SCREEN_WIDTH, SCREEN_HEIGHT, v_buffer);
}

static void fillin_present_parameters(SDL_Window* Window, int w, int h, bool fullscreen,        D3DPRESENT_PARAMETERS& d3dpp, D3DDISPLAYMODEEX& mode)
{
    HWND FakeWnd= (HWND)Window;

    memset(&mode, 0, sizeof(mode));
    mode.Size                = sizeof(mode);
    mode.Width                = w;
    mode.Height                = h;
    mode.Format                = D3DFMT_UNKNOWN;
    mode.RefreshRate        = 60;
    mode.ScanLineOrdering    = D3DSCANLINEORDERING_UNKNOWN;

    memset(&d3dpp, 0, sizeof(d3dpp));
    d3dpp.Windowed = !fullscreen;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
    d3dpp.hDeviceWindow = FakeWnd;
    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
    d3dpp.BackBufferWidth = w;
    d3dpp.BackBufferHeight = h;
}

static bool set_window_size(SDL_Window* Window, int w, int h, bool fullscreen)
{
    D3DDISPLAYMODEEX mode;
    D3DPRESENT_PARAMETERS d3dpp;
    fillin_present_parameters(Window, w, h, fullscreen, d3dpp, mode);

    HRESULT hr = d3ddev->ResetEx(&d3dpp, &mode);
    if (FAILED(hr)) {
        ERR("Resize failed\n");
        return false;
    }

    return true;
}

int main(int argc, char **argv)
{
    bool fullscreen = false;

    if (SDL_Init(0) != 0){
        ERR("SDL_Init\n");
        return 1;
    }

    SDL_Window* Window = SDL_CreateWindow("SDL Nine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE );
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

        D3DDISPLAYMODEEX mode;
        D3DPRESENT_PARAMETERS d3dpp;
        fillin_present_parameters(Window, SCREEN_WIDTH, SCREEN_HEIGHT, fullscreen, d3dpp, mode);

        // create a device class using this information and the info from the d3dpp stuct
        HRESULT hr = d3d->CreateDeviceEx(D3DADAPTER_DEFAULT,
            D3DDEVTYPE_HAL,
            FakeWnd,
            D3DCREATE_HARDWARE_VERTEXPROCESSING,
            &d3dpp, &mode, 
            &d3ddev);

        if (FAILED(hr)) {
            ERR("X11_Direct3DCreate9\n");
            return 1;
        }
    }

    init_graphics();    // call the function to initialize the triangle

    Uint32 MainWindowID = SDL_GetWindowID(Window);
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
            else if (e.type == SDL_WINDOWEVENT && e.window.windowID == MainWindowID)
            {
                switch (e.window.event) {
                case SDL_WINDOWEVENT_SIZE_CHANGED:
                    {
                        int width = e.window.data1;
                        int height = e.window.data2;

                        bool ok = set_window_size(Window, width, height, fullscreen);
                        if (ok)
                            load_triangle(width, height, v_buffer);
                    } break;
                }
            }
            else if (e.type == SDL_KEYDOWN && e.window.windowID == MainWindowID && e.key.keysym.sym == SDLK_F11 && e.key.state == SDL_PRESSED)
            {
                fullscreen = !fullscreen;
                bool ok = set_window_size(Window, SCREEN_WIDTH, SCREEN_HEIGHT, fullscreen);
                if (ok)
                    load_triangle(SCREEN_WIDTH, SCREEN_HEIGHT, v_buffer);
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


