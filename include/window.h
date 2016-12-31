#ifndef GLH_WINDOW
#define GLH_WINDOW

#include <string>
#include <SDL.h>
#include <GL/glew.h>
#include <buffer_manager.h>

namespace glh
{

class Window
{
protected:
  SDL_Window *window;

public:
  const static Uint32 SHOWN = SDL_WINDOW_SHOWN;
  const static Uint32 OPENGL = SDL_WINDOW_OPENGL;

  Window(std::string, int, int, int, int, Uint32);
  ~Window();

  void swap();
  void clear();
  SDL_GLContext create_context();
};

}

#endif
