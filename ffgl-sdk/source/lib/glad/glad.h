#ifndef __glad_h_
#define __glad_h_

#ifdef _WIN32
#include <windows.h>
#endif

#include <GL/gl.h>

// Macros básicas para satisfacer al SDK de FFGL
#define GLAD_GL_VERSION_2_0 1

// Función dummy para que FFGL.cpp no falle al inicializar
static int gladLoadGL(void) { return 1; }

#endif
