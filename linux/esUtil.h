//
// Book:      OpenGL(R) ES 2.0 Programming Guide
// Authors:   Aaftab Munshi, Dan Ginsburg, Dave Shreiner
// ISBN-10:   0321502795
// ISBN-13:   9780321502797
// Publisher: Addison-Wesley Professional
// URLs:      http://safari.informit.com/9780321563835
//            http://www.opengles-book.com
//

//
/// \file ESUtil.h
/// \brief A utility library for OpenGL ES.  This library provides a
///        basic common framework for the example applications in the
///        OpenGL ES 2.0 Programming Guide.
//
#ifndef ESUTIL_H
#define ESUTIL_H

///
//  Includes
//
#include <EGL/egl.h>

#ifdef __cplusplus

extern "C" {
#endif


///
//  Macros
//
#define ESUTIL_API
#define ESCALLBACK


/// esCreateWindow flag - RGB color buffer
#define ES_WINDOW_RGB           0
/// esCreateWindow flag - ALPHA color buffer
#define ES_WINDOW_ALPHA         1 
/// esCreateWindow flag - depth buffer
#define ES_WINDOW_DEPTH         2 
/// esCreateWindow flag - stencil buffer
#define ES_WINDOW_STENCIL       4
/// esCreateWindow flat - multi-sample buffer
#define ES_WINDOW_MULTISAMPLE   8


///
// Types
//

#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE 1
#endif

#define ButtonPressEvent   1
#define ButtonReleaseEvent 2
#define MotionNotifyEvent  3

typedef struct _escontext
{
    /// Put your user data here...
    void*     userData;

    /// Window width
    int       width;

    /// Window height
    int       height;

    /// Window handle
    EGLNativeWindowType  hWnd;

    /// EGL display
    EGLDisplay  eglDisplay;

    /// EGL context
    EGLContext  eglContext;

    /// EGL surface
    EGLSurface  eglSurface;

    /// Callbacks
    void (ESCALLBACK *drawFunc) ( struct _escontext * );
    void (ESCALLBACK *keyFunc) ( struct _escontext *, unsigned char, int, int );
    void (ESCALLBACK *mouseFunc) ( struct _escontext *, int, int, int );
} ESContext;


///
//  Public Functions
//

//
///
/// \brief Initialize ES framework context.  This must be called before calling any other functions.
/// \param esContext Application context
//
void ESUTIL_API esInitContext ( ESContext *esContext );

//
/// \brief Create a window with the specified parameters
/// \param esContext Application context
/// \param title Name for title bar of window
/// \param width Width in pixels of window to create
/// \param height Height in pixels of window to create
/// \param flags Bitfield for the window creation flags 
///         ES_WINDOW_RGB     - specifies that the color buffer should have R,G,B channels
///         ES_WINDOW_ALPHA   - specifies that the color buffer should have alpha
///         ES_WINDOW_DEPTH   - specifies that a depth buffer should be created
///         ES_WINDOW_STENCIL - specifies that a stencil buffer should be created
///         ES_WINDOW_MULTISAMPLE - specifies that a multi-sample buffer should be created
/// \return GL_TRUE if window creation is succesful, GL_FALSE otherwise
int ESUTIL_API esCreateWindow ( ESContext *esContext, const char *title, int width, int height, unsigned int flags );

//
/// \brief Start the main loop for the OpenGL ES application
/// \param esContext Application context
//
void ESUTIL_API esMainLoop ( ESContext *esContext );

//
/// \brief Register a draw callback function to be used to render each frame
/// \param esContext Application context
/// \param drawFunc Draw callback function that will be used to render the scene
//
void ESUTIL_API esRegisterDrawFunc ( ESContext *esContext, void (ESCALLBACK *drawFunc) ( ESContext* ) );

//
/// \brief Register an keyboard input processing callback function
/// \param esContext Application context
/// \param keyFunc Key callback function for application processing of keyboard input
//
void ESUTIL_API esRegisterKeyFunc ( ESContext *esContext, void (ESCALLBACK *keyFunc) ( ESContext*, unsigned char, int, int ) );

//
/// \brief Register an mouse input processing callback function
/// \param esContext Application context
/// \param keyFunc Key callback function for application processing of mouse input
//
void ESUTIL_API esRegisterMouseFunc ( ESContext *esContext, void (ESCALLBACK *mouseFunc) ( ESContext*, int, int, int ) );

#ifdef __cplusplus
}
#endif

#endif // ESUTIL_H
