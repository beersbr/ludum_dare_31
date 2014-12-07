#pragma once

#include <GL/glew.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_opengl.h>

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	const int RMASK = 0xff000000;
	const int GMASK = 0x00ff0000;
	const int BMASK = 0x0000ff00;
	const int AMASK = 0x000000ff;
#else
	const int RMASK = 0x000000ff;
	const int GMASK = 0x0000ff00;
	const int BMASK = 0x00ff0000;
	const int AMASK = 0xff000000;
#endif

// Delete a pointer with null checking
template <typename T>
void safe_delete(T* m)
{
	if(m != nullptr)
		delete m;
}

// Convert a SDL_Surface to a texture to be used for OpenGL
GLuint SDL_SurfaceToTexture(SDL_Surface *surface);