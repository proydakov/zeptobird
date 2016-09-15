//
// Book:      OpenGL(R) ES 2.0 Programming Guide
// Authors:   Aaftab Munshi, Dan Ginsburg, Dave Shreiner
// ISBN-10:   0321502795
// ISBN-13:   9780321502797
// Publisher: Addison-Wesley Professional
// URLs:      http://safari.informit.com/9780321563835
//            http://www.opengles-book.com
//

// ESUtil.c
//
//    A utility library for OpenGL ES.  This library provides a
//    basic common framework for the example applications in the
//    OpenGL ES 2.0 Programming Guide.
//

///
//  Includes
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <sys/time.h>
#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include "esUtil.h"

#include  <X11/Xlib.h>
#include  <X11/Xatom.h>
#include  <X11/Xutil.h>

// X11 related local variables
static Display *x_display = NULL;

///
// CreateEGLContext()
//
//    Creates an EGL rendering context and all associated elements
//
EGLBoolean CreateEGLContext ( EGLNativeWindowType hWnd, EGLDisplay* eglDisplay,
                              EGLContext* eglContext, EGLSurface* eglSurface,
                              EGLint attribList[])
{
    EGLint numConfigs;
    EGLint majorVersion;
    EGLint minorVersion;
    EGLDisplay display;
    EGLContext context;
    EGLSurface surface;
    EGLConfig config;
    EGLint contextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE, EGL_NONE };

    // Get Display
    display = eglGetDisplay((EGLNativeDisplayType)x_display);
    if ( display == EGL_NO_DISPLAY )
    {
        return EGL_FALSE;
    }

    // Initialize EGL
    if ( !eglInitialize(display, &majorVersion, &minorVersion) )
    {
        return EGL_FALSE;
    }

    // Get configs
    if ( !eglGetConfigs(display, NULL, 0, &numConfigs) )
    {
        return EGL_FALSE;
    }

    // Choose config
    if ( !eglChooseConfig(display, attribList, &config, 1, &numConfigs) )
    {
        return EGL_FALSE;
    }

    // Create a surface
    surface = eglCreateWindowSurface(display, config, (EGLNativeWindowType)hWnd, NULL);
    if ( surface == EGL_NO_SURFACE )
    {
        return EGL_FALSE;
    }

    // Create a GL context
    context = eglCreateContext(display, config, EGL_NO_CONTEXT, contextAttribs );
    if ( context == EGL_NO_CONTEXT )
    {
        return EGL_FALSE;
    }

    // Make the context current
    if ( !eglMakeCurrent(display, surface, surface, context) )
    {
        return EGL_FALSE;
    }

    *eglDisplay = display;
    *eglSurface = surface;
    *eglContext = context;
    return EGL_TRUE;
}


///
//  WinCreate()
//
//      This function initialized the native X11 display and window for EGL
//
EGLBoolean WinCreate(ESContext *esContext, const char *title)
{
    Window root;
    XSetWindowAttributes swa;
    XSetWindowAttributes  xattr;
    Atom wm_state;
    XWMHints hints;
    XEvent xev;
    Window win;

    /*
     * X11 native display initialization
     */
    x_display = XOpenDisplay(NULL);
    if ( x_display == NULL )
    {
        return EGL_FALSE;
    }

    root = DefaultRootWindow(x_display);

    swa.event_mask  =  ExposureMask | PointerMotionMask | KeyPressMask | ButtonPressMask | ButtonReleaseMask;
    win = XCreateWindow(
                x_display, root,
                0, 0, esContext->width, esContext->height, 0,
                CopyFromParent, InputOutput,
                CopyFromParent, CWEventMask,
                &swa );

    xattr.override_redirect = FALSE;
    XChangeWindowAttributes ( x_display, win, CWOverrideRedirect, &xattr );

    hints.input = TRUE;
    hints.flags = InputHint;
    XSetWMHints(x_display, win, &hints);

    // make the window visible on the screen
    XMapWindow (x_display, win);
    XStoreName (x_display, win, title);

    // get identifiers for the provided atom name strings
    wm_state = XInternAtom (x_display, "_NET_WM_STATE", FALSE);

    memset ( &xev, 0, sizeof(xev) );
    xev.type                 = ClientMessage;
    xev.xclient.window       = win;
    xev.xclient.message_type = wm_state;
    xev.xclient.format       = 32;
    xev.xclient.data.l[0]    = 1;
    xev.xclient.data.l[1]    = FALSE;
    XSendEvent (
                x_display,
                DefaultRootWindow ( x_display ),
                FALSE,
                SubstructureNotifyMask,
                &xev );

    esContext->hWnd = (EGLNativeWindowType) win;
    return EGL_TRUE;
}


///
//  userInterrupt()
//
//      Reads from X11 event loop and interrupt program if there is a keypress, or
//      window close action.
//
GLboolean userInterrupt(ESContext *esContext)
{
    XEvent xev;
    KeySym key;
    GLboolean userinterrupt = GL_FALSE;
    char text;

    // Pump all messages from X server. Keypresses are directed to keyfunc (if defined)
    while ( XPending ( x_display ) )
    {
        XNextEvent( x_display, &xev );

        switch( xev.type ) {
        case KeyPress:
        {
            //printf("KeyPress\n");
            if (XLookupString(&xev.xkey,&text,1,&key,0) == 1) {
                if(27 == text) {
                    userinterrupt = GL_TRUE;
                    break;
                }
                if (esContext->keyFunc != NULL) {
                    esContext->keyFunc(esContext, text, 0, 0);
                }
            }
        }
            break;

        case ButtonPress:
        {
            //printf("ButtonPress\n");
            if (esContext->mouseFunc != NULL) {
                esContext->mouseFunc(esContext, ButtonPressEvent, xev.xbutton.x, xev.xbutton.y);
            }
        }
            break;

        case ButtonRelease:
        {
            //printf("ButtonRelease\n");
            if (esContext->mouseFunc != NULL) {
                esContext->mouseFunc(esContext, ButtonReleaseEvent, xev.xbutton.x, xev.xbutton.y);
            }
        }
            break;

        case MotionNotify:
        {
            //printf("MotionNotify\n");
            if (esContext->mouseFunc != NULL) {
                esContext->mouseFunc(esContext, MotionNotifyEvent, xev.xbutton.x, xev.xbutton.y);
            }
        }
            break;

        case DestroyNotify:
        {
            //printf("DestroyNotify\n");
            userinterrupt = GL_TRUE;
        }
            break;
        }
        //fflush(stdout);
    }
    return userinterrupt;
}

//////////////////////////////////////////////////////////////////
//
//  Public Functions
//
//

///
//  esInitContext()
//
//      Initialize ES utility context.  This must be called before calling any other
//      functions.
//
void ESUTIL_API esInitContext ( ESContext *esContext )
{
    if ( esContext != NULL )
    {
        memset( esContext, 0, sizeof( ESContext) );
    }
}


///
//  esCreateWindow()
//
//      title - name for title bar of window
//      width - width of window to create
//      height - height of window to create
//      flags  - bitwise or of window creation flags
//          ES_WINDOW_ALPHA       - specifies that the framebuffer should have alpha
//          ES_WINDOW_DEPTH       - specifies that a depth buffer should be created
//          ES_WINDOW_STENCIL     - specifies that a stencil buffer should be created
//          ES_WINDOW_MULTISAMPLE - specifies that a multi-sample buffer should be created
//
int ESUTIL_API esCreateWindow ( ESContext *esContext, const char* title, int width, int height, unsigned int flags )
{
    EGLint attribList[] =
    {
        EGL_RED_SIZE,       5,
        EGL_GREEN_SIZE,     6,
        EGL_BLUE_SIZE,      5,
        EGL_ALPHA_SIZE,     (flags & ES_WINDOW_ALPHA) ? 8 : EGL_DONT_CARE,
        EGL_DEPTH_SIZE,     (flags & ES_WINDOW_DEPTH) ? 8 : EGL_DONT_CARE,
        EGL_STENCIL_SIZE,   (flags & ES_WINDOW_STENCIL) ? 8 : EGL_DONT_CARE,
        EGL_SAMPLE_BUFFERS, (flags & ES_WINDOW_MULTISAMPLE) ? 1 : 0,
        EGL_NONE
    };

    if ( esContext == NULL )
    {
        return GL_FALSE;
    }

    esContext->width = width;
    esContext->height = height;

    if ( !WinCreate ( esContext, title) )
    {
        return GL_FALSE;
    }


    if ( !CreateEGLContext ( esContext->hWnd,
                             &esContext->eglDisplay,
                             &esContext->eglContext,
                             &esContext->eglSurface,
                             attribList) )
    {
        return GL_FALSE;
    }


    return GL_TRUE;
}


///
//  esMainLoop()
//
//    Start the main loop for the OpenGL ES application
//

void ESUTIL_API esMainLoop ( ESContext *esContext )
{
    while(userInterrupt(esContext) == GL_FALSE)
    {
        if (esContext->drawFunc != NULL) {
            esContext->drawFunc(esContext);
        }
        eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
    }
}


///
//  esRegisterDrawFunc()
//
void ESUTIL_API esRegisterDrawFunc ( ESContext *esContext, void (ESCALLBACK *drawFunc) (ESContext* ) )
{
    esContext->drawFunc = drawFunc;
}


///
//  esRegisterKeyFunc()
//
void ESUTIL_API esRegisterKeyFunc ( ESContext *esContext, void (ESCALLBACK *keyFunc) (ESContext*, unsigned char, int, int ) )
{
    esContext->keyFunc = keyFunc;
}


///
//  esRegisterMouseFunc()
//
void ESUTIL_API esRegisterMouseFunc ( ESContext *esContext, void (ESCALLBACK *mouseFunc) ( ESContext*, int, int, int ) )
{
    esContext->mouseFunc = mouseFunc;
}
