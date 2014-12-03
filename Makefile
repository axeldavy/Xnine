D3DADAPTER9_LOCATION="/usr/lib/x86_64-linux-gnu/d3d/d3dadapter9.so"

XNINE=Xnine.o dri3.o
XNINE_LINK=-ldl -lX11 -lXext -lxcb -lxcb-present -lxcb-dri3 -lxcb-xfixes -lX11-xcb

SDLNINE=SDL_nine.o dri3.o
SDLNINE_LINK=$(D3DADAPTER9_LOCATION) -lSDL2 $(XNINE_LINK)

EXEC=triangle_c triangle_cpp triangle_SDL

all: $(EXEC)

triangle_c: $(XNINE) triangle.c
	gcc triangle.c $(XNINE) $(XNINE_LINK) -I include/D3D9 -o triangle_c 

triangle_cpp: $(XNINE) triangle.cpp
	g++ triangle.cpp $(XNINE) $(XNINE_LINK) -I include/D3D9 -o triangle_cpp -I include/D3D9

triangle_SDL: $(SDLNINE) triangle_SDL.cpp
	g++ triangle_SDL.cpp $(SDLNINE) $(SDLNINE_LINK) -I include/D3D9 -I /usr/include/SDL2 -o triangle_SDL

Xnine.o: Xnine.c
	gcc Xnine.c -o Xnine.o -I include/D3D9 -I include -c -DD3DADAPTERPATH='$(D3DADAPTER9_LOCATION)'
SDL_nine.o:  SDL_nine.c
	gcc SDL_nine.c -o SDL_nine.o -I /usr/include/SDL2 -I include/D3D9 -I include -c 
dri3.o: dri3.c
	gcc dri3.c -o dri3.o -I include/D3D9  -c

clean:
	rm $(XNINE) $(SDLNINE)
	rm $(EXEC)

