#ifndef GLH_WINDOW
#define GLH_WINDOW

#include <string>
#include <SDL.h>
#include <GL/glew.h>

namespace glh
{

class Window
{
protected:
  SDL_Window *window;
  SDL_GLContext context;

public:
  const static Uint32 SHOWN = SDL_WINDOW_SHOWN;
  const static Uint32 OPENGL = SDL_WINDOW_OPENGL;

  Window(std::string, int, int, int, int, Uint32);
  ~Window();

  void swap();
  void clear();
  void draw(GLuint, GLuint);
};

}

#endif
