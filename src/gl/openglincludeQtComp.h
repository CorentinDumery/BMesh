#ifndef OPENGLINCLUDEQTCOMP_
#define OPENGLINCLUDEQTCOMP_



#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <iostream>
#include <cstdlib>
#include <cstdio>

#if 1
        #define GetOpenGLError() t__GetOpenGLError( (char*)__FILE__, (int)__LINE__ )
#else
        #define GetOpenGLError()
#endif

inline int t__GetOpenGLError ( char* szFile, int iLine )
{
        int    retCode = 0;
        GLenum glErr = glGetError();
        while ( glErr != GL_NO_ERROR ) {
            std::cout << "GLError in file << " << szFile << " @ line " << iLine << ":" << gluErrorString( glErr ) << std::endl;
                retCode = 1;
                glErr = glGetError();
        }
        return retCode;
}




#define printOpenGLError() printOglError(__FILE__, __LINE__)

/// Returns 1 if an OpenGL error occurred, 0 otherwise.
static int printOglError (const char * file, int line) {
    GLenum glErr;
    int    retCode = 0;
    glErr = glGetError ();
    while (glErr != GL_NO_ERROR) {
        printf ("glError in file %s @ line %d: %s\n", file, line, gluErrorString(glErr));
        retCode = 1;
        glErr = glGetError ();
    }
    return retCode;
}





#endif // OPENGLINCLUDEQTCOMP_
