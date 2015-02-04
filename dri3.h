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

#ifndef __XNINE_DRI3_H
#define __XNINE_DRI3_H

#include <X11/extensions/Xfixes.h>
#include <X11/Xlib.h>
#include <X11/Xlib-xcb.h>
#include <xcb/xcb.h>
#include <xcb/dri3.h>
#include <xcb/present.h>

BOOL
DRI3CheckExtension(Display *dpy, int major, int minor);

#if D3DADAPTER9_WITHDRI2
struct DRI2priv;

BOOL
DRI2FallbackInit(Display *dpy, struct DRI2priv **priv);

void
DRI2FallbackDestroy(struct DRI2priv *priv);

BOOL
DRI2FallbackCheckSupport(Display *dpy);
#endif

BOOL
PRESENTCheckExtension(Display *dpy, int major, int minor);

BOOL
DRI3Open(Display *dpy, int screen, int *device_fd);

#if D3DADAPTER9_WITHDRI2
BOOL
DRI2FallbackOpen(Display *dpy, int screen, int *device_fd);
#endif

BOOL
DRI3PixmapFromDmaBuf(Display *dpy, int screen, int fd, int width, int height, int stride, int depth, int bpp, Pixmap *pixmap);

BOOL
DRI3DmaBufFromPixmap(Display *dpy, Pixmap pixmap, int *fd, int *width, int *height, int *stride, int *depth, int *bpp);

typedef struct PRESENTPriv PRESENTpriv;
typedef struct PRESENTPixmapPriv PRESENTPixmapPriv;

BOOL
PRESENTInit(Display *dpy, PRESENTpriv **present_priv);

/* will clean properly and free all PRESENTPixmapPriv associated to PRESENTpriv.
 * PRESENTPixmapPriv should not be freed by something else.
 * If never a PRESENTPixmapPriv has to be destroyed,
 * please destroy the current PRESENTpriv and create a new one.
 * This will take care than all pixmaps are released */
void
PRESENTDestroy(Display *dpy, PRESENTpriv *present_priv);

BOOL
PRESENTPixmapInit(PRESENTpriv *present_priv, Pixmap pixmap, PRESENTPixmapPriv **present_pixmap_priv);

#if D3DADAPTER9_WITHDRI2
BOOL
DRI2FallbackPRESENTPixmap(PRESENTpriv *present_priv, struct DRI2priv *priv,
                          int fd, int width, int height, int stride, int depth,
                          int bpp, PRESENTPixmapPriv **present_pixmap_priv);
#endif

BOOL
PRESENTTryFreePixmap(Display *dpy, PRESENTPixmapPriv *present_pixmap_priv);

BOOL
PRESENTHelperCopyFront(Display *dpy, PRESENTPixmapPriv *present_pixmap_priv);

BOOL
PRESENTPixmap(Display *dpy, XID window,
              PRESENTPixmapPriv *present_pixmap_priv, D3DPRESENT_PARAMETERS *pPresentationParameters,
              const RECT *pSourceRect, const RECT *pDestRect, const RGNDATA *pDirtyRegion);

BOOL
PRESENTWaitPixmapReleased(PRESENTPixmapPriv *present_pixmap_priv);

#endif /* __XNINE_DRI3_H */
