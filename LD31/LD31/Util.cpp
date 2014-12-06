#include "Util.h"

GLuint SDL_SurfaceToTexture(SDL_Surface *surface) {
    GLuint tid;
    GLenum texture_format;
    GLint ncolors;
    SDL_Surface* s = surface;
 
    /* Convert SDL_Surface to OpenGL Texture */
    ncolors = s->format->BytesPerPixel;
    if (ncolors == 4) {
        //alpha channel
        if (s->format->Rmask == 0x000000ff)	
            texture_format = GL_RGBA;
        else
            texture_format = GL_BGRA;
    } else {
        if (ncolors == 3) {
            //no alpha channel
            if (s->format->Rmask == 0x000000ff)
                texture_format = GL_RGB;
            else
                texture_format = GL_BGR;
        } else {
            return 0;
        }
    }
 
    glGenTextures(1, &tid);
    glBindTexture(GL_TEXTURE_2D, tid);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
 
    glTexImage2D(GL_TEXTURE_2D, 0, ncolors, s->w, s->h, 0,
            texture_format, GL_UNSIGNED_BYTE, s->pixels);
 
    return tid;
}