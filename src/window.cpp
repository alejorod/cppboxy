#include <window.h>
#include <shader_manager.h>

glh::Window::Window(std::string title, int x, int y, int w, int h, Uint32 flags)
{
  window = SDL_CreateWindow(title.c_str(), x, y, w, h, flags);
}

glh::Window::~Window()
{
  SDL_DestroyWindow(window);
}

SDL_GLContext glh::Window::create_context()
{
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  return SDL_GL_CreateContext(window);
}

void glh::Window::swap()
{
  SDL_GL_SwapWindow(window);
}

void glh::Window::clear()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
