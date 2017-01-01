#ifndef GLH_DRAWER
#define GLH_DRAWER

#include <window.h>
#include <camera.h>
#include <drawable.h>
#include <SDL.h>
#include <GL/glew.h>

namespace glh {

class Drawer
{
private:
  glh::Window &window;
  SDL_GLContext context;

public:
  Drawer(glh::Window&);
  ~Drawer();

  void clear();
  void swap();
  void draw(Camera&, Drawable);

  static Drawable create_drawable(GLuint shader_id, GLuint vao_id, int count)
  {
    Drawable drawable = { shader_id, vao_id, count };
    return drawable;
  }
};

}

#endif
