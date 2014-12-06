#include <GL/glew.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_opengl.h>

// Delete a pointer with null checking
template <typename T>
void safe_delete(T* m)
{
	if(m != nullptr)
		delete m;
}

// Convert a SDL_Surface to a texture to be used for OpenGL
GLuint SDL_SurfaceToTexture(SDL_Surface *surface);