#include <glh.h>

glh::GLH::GLH()
{
  SDL_Init(SDL_INIT_VIDEO);
  glewExperimental = GL_TRUE;
}

glh::GLH::~GLH()
{
  SDL_Quit();
}
