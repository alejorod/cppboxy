#ifndef GLH_DRAWABLE
#define GLH_DRAWABLE

#include <window.h>
#include <SDL.h>
#include <GL/glew.h>

namespace glh {

struct Drawable {
  GLuint shader;
  GLuint vao;
  int count;
};

class Drawer
{
private:
  glh::Window &window;
  SDL_GLContext context;

public:
  Drawer(glh::Window &window);
  ~Drawer();

  void clear();
  void swap();
  void draw(Drawable);

  static Drawable create_drawable(GLuint shader_id, GLuint vao_id, int count)
  {
    Drawable drawable = { shader_id, vao_id, count };
    return drawable;
  }
};

}

#endif
