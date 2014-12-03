XNINE=Xnine.o dri3.o
XNINE_LINK=-ldl -lX11 -lXext -lxcb -lxcb-present -lxcb-dri3 -lxcb-xfixes -lX11-xcb
EXEC=triangle_c triangle_cpp
D3DADAPTER9_LOCATION="/usr/lib/libd3dadapter9.so"

all: $(EXEC)

triangle_c: $(XNINE)
	gcc triangle.c $(XNINE) $(XNINE_LINK) -o triangle_c -I include/D3D9

triangle_cpp: $(XNINE)
	g++ triangle.cpp $(XNINE) $(XNINE_LINK) -o triangle_cpp -I include/D3D9

Xnine.o: Xnine.c
	gcc Xnine.c -o Xnine.o -I include/D3D9 -I include -c -DD3DADAPTERPATH='$(D3DADAPTER9_LOCATION)'
dri3.o: dri3.c
	gcc dri3.c -o dri3.o  -c

clean:
	rm $(XNINE)
	rm $(EXEC)
